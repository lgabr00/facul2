#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_STRING 50

typedef struct {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
} Territorio;

typedef struct {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    char* missao;
} Jogador;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarTerritorio(Territorio* territorios, int indice) {
    printf("\n--- Cadastro do Territorio %d ---\n", indice + 1);
    
    printf("Nome do territorio: ");
    fgets(territorios[indice].nome, TAM_STRING, stdin);
    territorios[indice].nome[strcspn(territorios[indice].nome, "\n")] = '\0';
    
    printf("Cor do territorio: ");
    fgets(territorios[indice].cor, TAM_STRING, stdin);
    territorios[indice].cor[strcspn(territorios[indice].cor, "\n")] = '\0';
    
    printf("Numero de tropas: ");
    scanf("%d", &territorios[indice].tropas);
    limparBuffer();
}

void exibirTerritorios(Territorio* territorios, int total) {
    printf("\n========================================\n");
    printf("         TERRITORIOS CADASTRADOS\n");
    printf("========================================\n");
    
    for (int i = 0; i < total; i++) {
        printf("\n[%d] %s\n", i, territorios[i].nome);
        printf("    Cor: %s\n", territorios[i].cor);
        printf("    Tropas: %d\n", territorios[i].tropas);
    }
    
    printf("\n========================================\n");
}

void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n--- BATALHA ---\n");
    printf("Atacante: %s (%s) - %d tropas\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) - %d tropas\n", defensor->nome, defensor->cor, defensor->tropas);
    
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("\nDado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);
    
    if (dadoAtacante > dadoDefensor) {
        printf("\nAtacante venceu!\n");
        int tropasTranferidas = atacante->tropas / 2;
        
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = tropasTranferidas;
        atacante->tropas -= tropasTranferidas;
        
        printf("%s agora pertence a %s com %d tropas.\n", defensor->nome, defensor->cor, defensor->tropas);
    } else {
        printf("\nDefensor resistiu!\n");
        atacante->tropas--;
        printf("%s perdeu 1 tropa. Tropas restantes: %d\n", atacante->nome, atacante->tropas);
    }
}

void atribuirMissao(Jogador* jogador) {
    char* missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Dominar 5 territorios de qualquer cor",
        "Conquistar todos os territorios da cor azul",
        "Acumular 20 tropas em territorios da sua cor"
    };
    
    int numMissoes = 5;
    int indiceMissao = rand() % numMissoes;
    
    jogador->missao = (char*)malloc(strlen(missoes[indiceMissao]) + 1);
    strcpy(jogador->missao, missoes[indiceMissao]);
    
    printf("\n========================================\n");
    printf("         SUA MISSAO ESTRATEGICA\n");
    printf("========================================\n");
    printf("%s\n", jogador->missao);
    printf("========================================\n\n");
}

int verificarMissao(Jogador* jogador, Territorio* territorios, int total) {
    int conquistados = 0;
    int tropasTotal = 0;
    int temVermelho = 0;
    int temAzul = 0;
    
    for (int i = 0; i < total; i++) {
        if (strcmp(territorios[i].cor, jogador->cor) == 0) {
            conquistados++;
            tropasTotal += territorios[i].tropas;
        }
        if (strcmp(territorios[i].cor, "vermelho") == 0 || strcmp(territorios[i].cor, "Vermelho") == 0) {
            temVermelho = 1;
        }
        if (strcmp(territorios[i].cor, "azul") == 0 || strcmp(territorios[i].cor, "Azul") == 0) {
            temAzul = 1;
        }
    }
    
    if (strstr(jogador->missao, "3 territorios") && conquistados >= 3) {
        return 1;
    }
    if (strstr(jogador->missao, "vermelha") && !temVermelho) {
        return 1;
    }
    if (strstr(jogador->missao, "5 territorios") && conquistados >= 5) {
        return 1;
    }
    if (strstr(jogador->missao, "azul") && !temAzul) {
        return 1;
    }
    if (strstr(jogador->missao, "20 tropas") && tropasTotal >= 20) {
        return 1;
    }
    
    return 0;
}

void liberarMemoria(Territorio* territorios, Jogador* jogador) {
    free(territorios);
    free(jogador->missao);
}

int main() {
    srand(time(NULL));
    
    int numTerritorios;
    Territorio* territorios;
    Jogador jogador;
    
    printf("========================================\n");
    printf("       WAR - DESAFIO ESTRUTURADO\n");
    printf("========================================\n\n");
    
    printf("Nome do jogador: ");
    fgets(jogador.nome, TAM_STRING, stdin);
    jogador.nome[strcspn(jogador.nome, "\n")] = '\0';
    
    printf("Cor do seu exercito: ");
    fgets(jogador.cor, TAM_STRING, stdin);
    jogador.cor[strcspn(jogador.cor, "\n")] = '\0';
    
    printf("\nQuantos territorios deseja cadastrar? ");
    scanf("%d", &numTerritorios);
    limparBuffer();
    
    territorios = (Territorio*)calloc(numTerritorios, sizeof(Territorio));
    
    if (territorios == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }
    
    for (int i = 0; i < numTerritorios; i++) {
        cadastrarTerritorio(territorios, i);
    }
    
    atribuirMissao(&jogador);
    
    int turno = 1;
    int jogoAtivo = 1;
    
    while (jogoAtivo) {
        printf("\n========================================\n");
        printf("              TURNO %d\n", turno);
        printf("========================================\n");
        
        exibirTerritorios(territorios, numTerritorios);
        
        int indiceAtacante, indiceDefensor;
        
        printf("\nEscolha o territorio atacante (0-%d): ", numTerritorios - 1);
        scanf("%d", &indiceAtacante);
        
        if (indiceAtacante < 0 || indiceAtacante >= numTerritorios) {
            printf("Indice invalido!\n");
            limparBuffer();
            continue;
        }
        
        printf("Escolha o territorio defensor (0-%d): ", numTerritorios - 1);
        scanf("%d", &indiceDefensor);
        limparBuffer();
        
        if (indiceDefensor < 0 || indiceDefensor >= numTerritorios) {
            printf("Indice invalido!\n");
            continue;
        }
        
        if (indiceAtacante == indiceDefensor) {
            printf("Nao pode atacar o proprio territorio!\n");
            continue;
        }
        
        if (strcmp(territorios[indiceAtacante].cor, territorios[indiceDefensor].cor) == 0) {
            printf("Nao pode atacar territorio da mesma cor!\n");
            continue;
        }
        
        if (territorios[indiceAtacante].tropas <= 0) {
            printf("Territorio atacante nao tem tropas suficientes!\n");
            continue;
        }
        
        atacar(&territorios[indiceAtacante], &territorios[indiceDefensor]);
        
        if (verificarMissao(&jogador, territorios, numTerritorios)) {
            printf("\n========================================\n");
            printf("          MISSAO CUMPRIDA!\n");
            printf("========================================\n");
            printf("Parabens %s, voce venceu o jogo!\n", jogador.nome);
            printf("Missao: %s\n", jogador.missao);
            printf("========================================\n");
            jogoAtivo = 0;
        }
        
        turno++;
    }
    
    liberarMemoria(territorios, &jogador);
    
    return 0;
}
