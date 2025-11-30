#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10
#define MAX_COMPONENTES 20

typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
} Item;

typedef struct {
    char nome[50];
    char tipo[50];
    int prioridade;
} Componente;

typedef struct No {
    Item item;
    struct No* proximo;
} No;

void nivelNovato() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;
    
    printf("\n=== NIVEL NOVATO - INVENTARIO ===\n");
    
    do {
        printf("\n1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();
        
        if (opcao == 1) {
            if (total < MAX_ITENS) {
                printf("Nome: ");
                fgets(mochila[total].nome, 50, stdin);
                mochila[total].nome[strcspn(mochila[total].nome, "\n")] = 0;
                
                printf("Tipo: ");
                fgets(mochila[total].tipo, 50, stdin);
                mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = 0;
                
                printf("Quantidade: ");
                scanf("%d", &mochila[total].quantidade);
                
                total++;
                printf("Item adicionado!\n");
            } else {
                printf("Mochila cheia!\n");
            }
        }
        
        else if (opcao == 2) {
            char nome[50];
            printf("Nome do item: ");
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = 0;
            
            int encontrado = -1;
            for (int i = 0; i < total; i++) {
                if (strcmp(mochila[i].nome, nome) == 0) {
                    encontrado = i;
                    break;
                }
            }
            
            if (encontrado != -1) {
                for (int i = encontrado; i < total - 1; i++) {
                    mochila[i] = mochila[i + 1];
                }
                total--;
                printf("Item removido!\n");
            } else {
                printf("Item nao encontrado!\n");
            }
        }
        
        else if (opcao == 3) {
            printf("\n--- Mochila ---\n");
            for (int i = 0; i < total; i++) {
                printf("%s (%s) - Qtd: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            }
        }
        
        else if (opcao == 4) {
            char nome[50];
            printf("Nome do item: ");
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = 0;
            
            int comparacoes = 0;
            int encontrado = -1;
            
            for (int i = 0; i < total; i++) {
                comparacoes++;
                if (strcmp(mochila[i].nome, nome) == 0) {
                    encontrado = i;
                    break;
                }
            }
            
            if (encontrado != -1) {
                printf("Encontrado: %s (%s) - Qtd: %d\n", 
                       mochila[encontrado].nome, mochila[encontrado].tipo, mochila[encontrado].quantidade);
            } else {
                printf("Nao encontrado!\n");
            }
            printf("Comparacoes: %d\n", comparacoes);
        }
        
    } while (opcao != 0);
}

void nivelAventureiro() {
    int escolha;
    printf("\n=== NIVEL AVENTUREIRO ===\n");
    printf("1. Usar Vetor\n");
    printf("2. Usar Lista Encadeada\n");
    printf("Escolha: ");
    scanf("%d", &escolha);
    getchar();
    
    if (escolha == 1) {
        Item mochila[MAX_ITENS];
        int total = 0;
        int opcao;
        int ordenado = 0;
        
        do {
            printf("\n1. Inserir\n2. Remover\n3. Listar\n4. Busca Sequencial\n");
            printf("5. Ordenar\n6. Busca Binaria\n0. Voltar\n");
            printf("Escolha: ");
            scanf("%d", &opcao);
            getchar();
            
            if (opcao == 1) {
                if (total < MAX_ITENS) {
                    printf("Nome: ");
                    fgets(mochila[total].nome, 50, stdin);
                    mochila[total].nome[strcspn(mochila[total].nome, "\n")] = 0;
                    printf("Tipo: ");
                    fgets(mochila[total].tipo, 50, stdin);
                    mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = 0;
                    printf("Quantidade: ");
                    scanf("%d", &mochila[total].quantidade);
                    total++;
                    ordenado = 0;
                }
            }
            
            else if (opcao == 3) {
                for (int i = 0; i < total; i++) {
                    printf("%s (%s) - %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
                }
            }
            
            else if (opcao == 4) {
                char nome[50];
                printf("Nome: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                int comp = 0;
                for (int i = 0; i < total; i++) {
                    comp++;
                    if (strcmp(mochila[i].nome, nome) == 0) {
                        printf("Encontrado: %s\n", mochila[i].nome);
                        break;
                    }
                }
                printf("Comparacoes: %d\n", comp);
            }
            
            else if (opcao == 5) {
                for (int i = 0; i < total - 1; i++) {
                    for (int j = 0; j < total - i - 1; j++) {
                        if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                            Item temp = mochila[j];
                            mochila[j] = mochila[j + 1];
                            mochila[j + 1] = temp;
                        }
                    }
                }
                ordenado = 1;
                printf("Ordenado!\n");
            }
            
            else if (opcao == 6) {
                if (!ordenado) {
                    printf("Ordenando primeiro...\n");
                    for (int i = 0; i < total - 1; i++) {
                        for (int j = 0; j < total - i - 1; j++) {
                            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                                Item temp = mochila[j];
                                mochila[j] = mochila[j + 1];
                                mochila[j + 1] = temp;
                            }
                        }
                    }
                    ordenado = 1;
                }
                
                char nome[50];
                printf("Nome: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                int esq = 0, dir = total - 1, comp = 0;
                int encontrado = -1;
                
                while (esq <= dir) {
                    comp++;
                    int meio = (esq + dir) / 2;
                    int res = strcmp(mochila[meio].nome, nome);
                    
                    if (res == 0) {
                        encontrado = meio;
                        break;
                    } else if (res < 0) {
                        esq = meio + 1;
                    } else {
                        dir = meio - 1;
                    }
                }
                
                if (encontrado != -1) {
                    printf("Encontrado: %s\n", mochila[encontrado].nome);
                } else {
                    printf("Nao encontrado!\n");
                }
                printf("Comparacoes: %d\n", comp);
            }
            
        } while (opcao != 0);
    }
    
    else if (escolha == 2) {
        No* cabeca = NULL;
        int opcao;
        
        do {
            printf("\n1. Inserir\n2. Listar\n3. Buscar\n0. Voltar\n");
            printf("Escolha: ");
            scanf("%d", &opcao);
            getchar();
            
            if (opcao == 1) {
                No* novo = (No*)malloc(sizeof(No));
                printf("Nome: ");
                fgets(novo->item.nome, 50, stdin);
                novo->item.nome[strcspn(novo->item.nome, "\n")] = 0;
                printf("Tipo: ");
                fgets(novo->item.tipo, 50, stdin);
                novo->item.tipo[strcspn(novo->item.tipo, "\n")] = 0;
                printf("Quantidade: ");
                scanf("%d", &novo->item.quantidade);
                novo->proximo = NULL;
                
                if (cabeca == NULL) {
                    cabeca = novo;
                } else {
                    No* atual = cabeca;
                    while (atual->proximo != NULL) {
                        atual = atual->proximo;
                    }
                    atual->proximo = novo;
                }
            }
            
            else if (opcao == 2) {
                No* atual = cabeca;
                while (atual != NULL) {
                    printf("%s (%s) - %d\n", atual->item.nome, atual->item.tipo, atual->item.quantidade);
                    atual = atual->proximo;
                }
            }
            
            else if (opcao == 3) {
                char nome[50];
                printf("Nome: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                No* atual = cabeca;
                int comp = 0;
                while (atual != NULL) {
                    comp++;
                    if (strcmp(atual->item.nome, nome) == 0) {
                        printf("Encontrado: %s\n", atual->item.nome);
                        break;
                    }
                    atual = atual->proximo;
                }
                printf("Comparacoes: %d\n", comp);
            }
            
        } while (opcao != 0);
        
        while (cabeca != NULL) {
            No* temp = cabeca;
            cabeca = cabeca->proximo;
            free(temp);
        }
    }
}

void nivelMestre() {
    Componente torre[MAX_COMPONENTES];
    int total = 0;
    int opcao;
    
    printf("\n=== NIVEL MESTRE - TORRE DE FUGA ===\n");
    
    do {
        printf("\n1. Inserir componente\n2. Listar\n");
        printf("3. Ordenar por nome (Bubble)\n4. Ordenar por tipo (Insertion)\n");
        printf("5. Ordenar por prioridade (Selection)\n6. Buscar\n0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();
        
        if (opcao == 1 && total < MAX_COMPONENTES) {
            printf("Nome: ");
            fgets(torre[total].nome, 50, stdin);
            torre[total].nome[strcspn(torre[total].nome, "\n")] = 0;
            printf("Tipo: ");
            fgets(torre[total].tipo, 50, stdin);
            torre[total].tipo[strcspn(torre[total].tipo, "\n")] = 0;
            printf("Prioridade: ");
            scanf("%d", &torre[total].prioridade);
            total++;
        }
        
        else if (opcao == 2) {
            for (int i = 0; i < total; i++) {
                printf("%s (%s) - Prioridade: %d\n", torre[i].nome, torre[i].tipo, torre[i].prioridade);
            }
        }
        
        else if (opcao == 3) {
            clock_t inicio = clock();
            int comp = 0;
            
            for (int i = 0; i < total - 1; i++) {
                for (int j = 0; j < total - i - 1; j++) {
                    comp++;
                    if (strcmp(torre[j].nome, torre[j + 1].nome) > 0) {
                        Componente temp = torre[j];
                        torre[j] = torre[j + 1];
                        torre[j + 1] = temp;
                    }
                }
            }
            
            clock_t fim = clock();
            printf("Bubble Sort - Comparacoes: %d | Tempo: %f s\n", 
                   comp, (double)(fim - inicio) / CLOCKS_PER_SEC);
        }
        
        else if (opcao == 4) {
            clock_t inicio = clock();
            int comp = 0;
            
            for (int i = 1; i < total; i++) {
                Componente chave = torre[i];
                int j = i - 1;
                
                while (j >= 0 && strcmp(torre[j].tipo, chave.tipo) > 0) {
                    comp++;
                    torre[j + 1] = torre[j];
                    j--;
                }
                if (j >= 0) comp++;
                torre[j + 1] = chave;
            }
            
            clock_t fim = clock();
            printf("Insertion Sort - Comparacoes: %d | Tempo: %f s\n", 
                   comp, (double)(fim - inicio) / CLOCKS_PER_SEC);
        }
        
        else if (opcao == 5) {
            clock_t inicio = clock();
            int comp = 0;
            
            for (int i = 0; i < total - 1; i++) {
                int menor = i;
                for (int j = i + 1; j < total; j++) {
                    comp++;
                    if (torre[j].prioridade < torre[menor].prioridade) {
                        menor = j;
                    }
                }
                if (menor != i) {
                    Componente temp = torre[i];
                    torre[i] = torre[menor];
                    torre[menor] = temp;
                }
            }
            
            clock_t fim = clock();
            printf("Selection Sort - Comparacoes: %d | Tempo: %f s\n", 
                   comp, (double)(fim - inicio) / CLOCKS_PER_SEC);
        }
        
        else if (opcao == 6) {
            char nome[50];
            printf("Nome: ");
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = 0;
            
            int comp = 0;
            for (int i = 0; i < total; i++) {
                comp++;
                if (strcmp(torre[i].nome, nome) == 0) {
                    printf("Encontrado: %s (%s) - Prioridade: %d\n", 
                           torre[i].nome, torre[i].tipo, torre[i].prioridade);
                    break;
                }
            }
            printf("Comparacoes: %d\n", comp);
        }
        
    } while (opcao != 0);
}

int main() {
    int opcao;
    
    printf("=== FREE FIRE - DESAFIO ===\n");
    
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
