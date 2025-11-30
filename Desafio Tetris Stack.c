#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

typedef struct {
    char nome;
    int id;
} Peca;

typedef struct {
    Peca pecas[MAX_FILA];
    int inicio;
    int fim;
    int tamanho;
} Fila;

typedef struct {
    Peca pecas[MAX_PILHA];
    int topo;
} Pilha;

int proximoId = 1;

Peca gerarPeca() {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = proximoId++;
    return nova;
}

void inicializarFila(Fila* f) {
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    
    for (int i = 0; i < MAX_FILA; i++) {
        f->pecas[f->fim] = gerarPeca();
        f->fim = (f->fim + 1) % MAX_FILA;
        f->tamanho++;
    }
}

int filaVazia(Fila* f) {
    return f->tamanho == 0;
}

int filaCheia(Fila* f) {
    return f->tamanho == MAX_FILA;
}

void enqueue(Fila* f) {
    if (filaCheia(f)) {
        printf("Fila cheia!\n");
        return;
    }
    
    f->pecas[f->fim] = gerarPeca();
    f->fim = (f->fim + 1) % MAX_FILA;
    f->tamanho++;
    printf("Peca adicionada!\n");
}

Peca dequeue(Fila* f) {
    Peca removida = f->pecas[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->tamanho--;
    return removida;
}

void exibirFila(Fila* f) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }
    
    printf("\n--- FILA DE PECAS ---\n");
    int idx = f->inicio;
    for (int i = 0; i < f->tamanho; i++) {
        printf("[%d] Peca %c (ID: %d)\n", i + 1, f->pecas[idx].nome, f->pecas[idx].id);
        idx = (idx + 1) % MAX_FILA;
    }
}

void inicializarPilha(Pilha* p) {
    p->topo = -1;
}

int pilhaVazia(Pilha* p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha* p) {
    return p->topo == MAX_PILHA - 1;
}

void push(Pilha* p, Peca peca) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia!\n");
        return;
    }
    
    p->topo++;
    p->pecas[p->topo] = peca;
}

Peca pop(Pilha* p) {
    Peca removida = p->pecas[p->topo];
    p->topo--;
    return removida;
}

void exibirPilha(Pilha* p) {
    if (pilhaVazia(p)) {
        printf("\n--- PILHA DE RESERVA ---\n");
        printf("Vazia!\n");
        return;
    }
    
    printf("\n--- PILHA DE RESERVA ---\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%d] Peca %c (ID: %d)\n", p->topo - i + 1, p->pecas[i].nome, p->pecas[i].id);
    }
}

void nivelNovato() {
    Fila fila;
    int opcao;
    
    inicializarFila(&fila);
    
    printf("\n=== NIVEL NOVATO - FILA DE PECAS ===\n");
    
    do {
        printf("\n1. Jogar peca\n2. Inserir nova peca\n3. Exibir fila\n0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        
        if (opcao == 1) {
            if (filaVazia(&fila)) {
                printf("Fila vazia!\n");
            } else {
                Peca jogada = dequeue(&fila);
                printf("Jogou peca %c (ID: %d)\n", jogada.nome, jogada.id);
            }
        }
        
        else if (opcao == 2) {
            enqueue(&fila);
        }
        
        else if (opcao == 3) {
            exibirFila(&fila);
        }
        
    } while (opcao != 0);
}

void nivelAventureiro() {
    Fila fila;
    Pilha pilha;
    int opcao;
    
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    
    printf("\n=== NIVEL AVENTUREIRO - FILA E PILHA ===\n");
    
    do {
        printf("\n1. Jogar peca\n2. Reservar peca\n3. Usar peca reservada\n");
        printf("4. Exibir fila e pilha\n0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        
        if (opcao == 1) {
            if (filaVazia(&fila)) {
                printf("Fila vazia!\n");
            } else {
                Peca jogada = dequeue(&fila);
                printf("Jogou peca %c (ID: %d)\n", jogada.nome, jogada.id);
                
                if (!filaCheia(&fila)) {
                    Peca nova = gerarPeca();
                    fila.pecas[fila.fim] = nova;
                    fila.fim = (fila.fim + 1) % MAX_FILA;
                    fila.tamanho++;
                    printf("Nova peca %c (ID: %d) adicionada na fila!\n", nova.nome, nova.id);
                }
            }
        }
        
        else if (opcao == 2) {
            if (filaVazia(&fila)) {
                printf("Fila vazia!\n");
            } else if (pilhaCheia(&pilha)) {
                printf("Pilha cheia!\n");
            } else {
                Peca reservada = dequeue(&fila);
                push(&pilha, reservada);
                printf("Peca %c (ID: %d) reservada!\n", reservada.nome, reservada.id);
                
                if (!filaCheia(&fila)) {
                    Peca nova = gerarPeca();
                    fila.pecas[fila.fim] = nova;
                    fila.fim = (fila.fim + 1) % MAX_FILA;
                    fila.tamanho++;
                    printf("Nova peca %c (ID: %d) adicionada na fila!\n", nova.nome, nova.id);
                }
            }
        }
        
        else if (opcao == 3) {
            if (pilhaVazia(&pilha)) {
                printf("Pilha vazia!\n");
            } else {
                Peca usada = pop(&pilha);
                printf("Usou peca reservada %c (ID: %d)\n", usada.nome, usada.id);
            }
        }
        
        else if (opcao == 4) {
            exibirFila(&fila);
            exibirPilha(&pilha);
        }
        
    } while (opcao != 0);
}

void nivelMestre() {
    Fila fila;
    Pilha pilha;
    int opcao;
    
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    
    printf("\n=== NIVEL MESTRE - TROCAS ESTRATEGICAS ===\n");
    
    do {
        printf("\n1. Jogar peca\n2. Reservar peca\n3. Usar peca reservada\n");
        printf("4. Trocar peca atual\n5. Troca multipla (3x3)\n");
        printf("6. Exibir fila e pilha\n0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        
        if (opcao == 1) {
            if (filaVazia(&fila)) {
                printf("Fila vazia!\n");
            } else {
                Peca jogada = dequeue(&fila);
                printf("Jogou peca %c (ID: %d)\n", jogada.nome, jogada.id);
                
                if (!filaCheia(&fila)) {
                    Peca nova = gerarPeca();
                    fila.pecas[fila.fim] = nova;
                    fila.fim = (fila.fim + 1) % MAX_FILA;
                    fila.tamanho++;
                    printf("Nova peca adicionada!\n");
                }
            }
        }
        
        else if (opcao == 2) {
            if (filaVazia(&fila)) {
                printf("Fila vazia!\n");
            } else if (pilhaCheia(&pilha)) {
                printf("Pilha cheia!\n");
            } else {
                Peca reservada = dequeue(&fila);
                push(&pilha, reservada);
                printf("Peca %c (ID: %d) reservada!\n", reservada.nome, reservada.id);
                
                if (!filaCheia(&fila)) {
                    Peca nova = gerarPeca();
                    fila.pecas[fila.fim] = nova;
                    fila.fim = (fila.fim + 1) % MAX_FILA;
                    fila.tamanho++;
                    printf("Nova peca adicionada!\n");
                }
            }
        }
        
        else if (opcao == 3) {
            if (pilhaVazia(&pilha)) {
                printf("Pilha vazia!\n");
            } else {
                Peca usada = pop(&pilha);
                printf("Usou peca %c (ID: %d)\n", usada.nome, usada.id);
            }
        }
        
        else if (opcao == 4) {
            if (filaVazia(&fila) || pilhaVazia(&pilha)) {
                printf("Fila ou pilha vazia!\n");
            } else {
                Peca daFila = fila.pecas[fila.inicio];
                Peca daPilha = pilha.pecas[pilha.topo];
                
                fila.pecas[fila.inicio] = daPilha;
                pilha.pecas[pilha.topo] = daFila;
                
                printf("Trocada peca %c com peca %c!\n", daFila.nome, daPilha.nome);
            }
        }
        
        else if (opcao == 5) {
            if (fila.tamanho < 3 || pilha.topo + 1 < 3) {
                printf("Necessario pelo menos 3 pecas em cada estrutura!\n");
            } else {
                Peca tempFila[3];
                Peca tempPilha[3];
                
                for (int i = 0; i < 3; i++) {
                    int idx = (fila.inicio + i) % MAX_FILA;
                    tempFila[i] = fila.pecas[idx];
                }
                
                for (int i = 0; i < 3; i++) {
                    tempPilha[i] = pilha.pecas[pilha.topo - i];
                }
                
                for (int i = 0; i < 3; i++) {
                    int idx = (fila.inicio + i) % MAX_FILA;
                    fila.pecas[idx] = tempPilha[i];
                }
                
                for (int i = 0; i < 3; i++) {
                    pilha.pecas[pilha.topo - i] = tempFila[i];
                }
                
                printf("Troca multipla realizada (3x3)!\n");
            }
        }
        
        else if (opcao == 6) {
            exibirFila(&fila);
            exibirPilha(&pilha);
        }
        
    } while (opcao != 0);
}

int main() {
    srand(time(NULL));
    int opcao;
    
    printf("=== TETRIS STACK - DESAFIO ===\n");
    
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
