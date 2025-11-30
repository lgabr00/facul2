#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

typedef struct NoMapa {
    char nome[50];
    char pista[50];
    struct NoMapa* esquerda;
    struct NoMapa* direita;
} NoMapa;

typedef struct NoBST {
    char pista[50];
    struct NoBST* esquerda;
    struct NoBST* direita;
} NoBST;

typedef struct NoHash {
    char pista[50];
    char suspeito[50];
    struct NoHash* proximo;
} NoHash;

typedef struct {
    NoHash* tabela[TAM_HASH];
} TabelaHash;

NoMapa* criarSala(char* nome, char* pista) {
    NoMapa* nova = (NoMapa*)malloc(sizeof(NoMapa));
    strcpy(nova->nome, nome);
    if (pista != NULL) {
        strcpy(nova->pista, pista);
    } else {
        strcpy(nova->pista, "");
    }
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

NoMapa* construirMapa() {
    NoMapa* hall = criarSala("Hall de Entrada", NULL);
    
    hall->esquerda = criarSala("Biblioteca", "Livro Antigo");
    hall->direita = criarSala("Cozinha", "Faca Suja");
    
    hall->esquerda->esquerda = criarSala("Escritorio", "Carta Rasgada");
    hall->esquerda->direita = criarSala("Sala de Estar", "Cinzas");
    
    hall->direita->esquerda = criarSala("Despensa", "Veneno");
    hall->direita->direita = criarSala("Jardim", NULL);
    
    return hall;
}

void explorarMapaNovato(NoMapa* sala) {
    if (sala == NULL) return;
    
    printf("\nVoce esta em: %s\n", sala->nome);
    
    if (sala->esquerda == NULL && sala->direita == NULL) {
        printf("Comodo final alcancado!\n");
        return;
    }
    
    char escolha;
    printf("Escolha o caminho: (e) esquerda, (d) direita: ");
    scanf(" %c", &escolha);
    
    if (escolha == 'e' && sala->esquerda != NULL) {
        explorarMapaNovato(sala->esquerda);
    } else if (escolha == 'd' && sala->direita != NULL) {
        explorarMapaNovato(sala->direita);
    } else {
        printf("Caminho invalido!\n");
    }
}

void nivelNovato() {
    printf("\n=== NIVEL NOVATO - MAPA DA MANSAO ===\n");
    
    NoMapa* mapa = construirMapa();
    explorarMapaNovato(mapa);
    
    printf("\nExploracao concluida!\n");
}

NoBST* inserirBST(NoBST* raiz, char* pista) {
    if (raiz == NULL) {
        NoBST* novo = (NoBST*)malloc(sizeof(NoBST));
        strcpy(novo->pista, pista);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }
    
    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirBST(raiz->esquerda, pista);
    } else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirBST(raiz->direita, pista);
    }
    
    return raiz;
}

void exibirBSTOrdenado(NoBST* raiz) {
    if (raiz != NULL) {
        exibirBSTOrdenado(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirBSTOrdenado(raiz->direita);
    }
}

void explorarMapaAventureiro(NoMapa* sala, NoBST** pistasColetadas) {
    if (sala == NULL) return;
    
    printf("\nVoce esta em: %s\n", sala->nome);
    
    if (strlen(sala->pista) > 0) {
        printf("Pista encontrada: %s\n", sala->pista);
        *pistasColetadas = inserirBST(*pistasColetadas, sala->pista);
    }
    
    if (sala->esquerda == NULL && sala->direita == NULL) {
        printf("Comodo final alcancado!\n");
        return;
    }
    
    char escolha;
    printf("Escolha: (e) esquerda, (d) direita, (s) sair: ");
    scanf(" %c", &escolha);
    
    if (escolha == 's') {
        return;
    } else if (escolha == 'e' && sala->esquerda != NULL) {
        explorarMapaAventureiro(sala->esquerda, pistasColetadas);
    } else if (escolha == 'd' && sala->direita != NULL) {
        explorarMapaAventureiro(sala->direita, pistasColetadas);
    } else {
        printf("Escolha invalida!\n");
    }
}

void nivelAventureiro() {
    printf("\n=== NIVEL AVENTUREIRO - COLETA DE PISTAS ===\n");
    
    NoMapa* mapa = construirMapa();
    NoBST* pistasColetadas = NULL;
    
    explorarMapaAventureiro(mapa, &pistasColetadas);
    
    printf("\n--- PISTAS COLETADAS (ordem alfabetica) ---\n");
    exibirBSTOrdenado(pistasColetadas);
}

int funcaoHash(char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TAM_HASH;
}

void inicializarHash(TabelaHash* hash) {
    for (int i = 0; i < TAM_HASH; i++) {
        hash->tabela[i] = NULL;
    }
}

void inserirHash(TabelaHash* hash, char* pista, char* suspeito) {
    int indice = funcaoHash(pista);
    
    NoHash* novo = (NoHash*)malloc(sizeof(NoHash));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->proximo = hash->tabela[indice];
    hash->tabela[indice] = novo;
}

char* buscarSuspeitoHash(TabelaHash* hash, char* pista) {
    int indice = funcaoHash(pista);
    NoHash* atual = hash->tabela[indice];
    
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->proximo;
    }
    
    return NULL;
}

void contarPistasPorSuspeito(NoBST* raiz, TabelaHash* hash, char* suspeitoAcusado, int* contador) {
    if (raiz != NULL) {
        contarPistasPorSuspeito(raiz->esquerda, hash, suspeitoAcusado, contador);
        
        char* suspeito = buscarSuspeitoHash(hash, raiz->pista);
        if (suspeito != NULL && strcmp(suspeito, suspeitoAcusado) == 0) {
            (*contador)++;
        }
        
        contarPistasPorSuspeito(raiz->direita, hash, suspeitoAcusado, contador);
    }
}

void nivelMestre() {
    printf("\n=== NIVEL MESTRE - ACUSACAO FINAL ===\n");
    
    NoMapa* mapa = construirMapa();
    NoBST* pistasColetadas = NULL;
    TabelaHash hash;
    
    inicializarHash(&hash);
    
    inserirHash(&hash, "Livro Antigo", "Professor");
    inserirHash(&hash, "Faca Suja", "Chef");
    inserirHash(&hash, "Carta Rasgada", "Professor");
    inserirHash(&hash, "Cinzas", "Mordomo");
    inserirHash(&hash, "Veneno", "Chef");
    
    explorarMapaAventureiro(mapa, &pistasColetadas);
    
    printf("\n--- PISTAS COLETADAS ---\n");
    exibirBSTOrdenado(pistasColetadas);
    
    printf("\n--- FASE DE ACUSACAO ---\n");
    printf("Suspeitos: Professor, Chef, Mordomo\n");
    
    char acusacao[50];
    printf("Quem voce acusa? ");
    scanf(" %[^\n]", acusacao);
    
    int contador = 0;
    contarPistasPorSuspeito(pistasColetadas, &hash, acusacao, &contador);
    
    printf("\nPistas que apontam para %s: %d\n", acusacao, contador);
    
    if (contador >= 2) {
        printf("\n*** CASO RESOLVIDO! ***\n");
        printf("Voce acusou corretamente %s com evidencias suficientes!\n", acusacao);
    } else {
        printf("\n*** CASO NAO RESOLVIDO ***\n");
        printf("Evidencias insuficientes. Sao necessarias pelo menos 2 pistas.\n");
    }
}

int main() {
    int opcao;
    
    printf("=== DETECTIVE QUEST - DESAFIO ===\n");
    
    do {
        printf("\n1. Nivel Novato\n2. Nivel Aventureiro\n3. Nivel Mestre\n0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        
        if (opcao == 1) nivelNovato();
        else if (opcao == 2) nivelAventureiro();
        else if (opcao == 3) nivelMestre();
        
    } while (opcao != 0);
    
    return 0;
}
