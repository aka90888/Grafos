#include <stdio.h>
#include <stdlib.h>

#define M 50

typedef struct No {
    int info;
    struct No *prox;
}TNo;

void listar(FILE *arq) {
    int num;

    //comecar no 1 num
    fseek(arq, 6, 0);
    while(!feof(arq)) {
        fscanf(arq, "%d", &num);

        if(num == -1)
            printf("\n");
        else if(num == -2)
            return;
        else
            printf("%d ", num);

    }
}

TNo *criarNo(int posi) {
    TNo *novo = (TNo*)malloc(sizeof(TNo));
    novo->info = posi;
    novo->prox = NULL;

    return novo;
}

void inicializar(TNo **lista, int vertices) {
    int i;
    for(i = 0; i < vertices; i++) {
        lista[i] = criarNo(i + 1);
    }
}

void inserirFim(TNo **lista, int num) {
    TNo *aux = lista;
    TNo *novo = (TNo*)malloc(sizeof(TNo));
    novo->info = num;
    novo->prox = NULL;

    while(aux->prox != NULL) {
        aux = aux->prox;
    }

    aux->prox = novo;
}

void convListaAdj(FILE *arq, TNo **lista, int vertices) {
    int i, num;

    //comecar no 1 num
    fseek(arq, 6, 0);
    for(i = 0; i < vertices; i++) {
        while(!feof(arq)) {
            fscanf(arq, "%d", &num);

            if(num == -1)
                break;
            else if(num == -2)
                return;
            else
                inserirFim(lista[i], num);

        }
    }
}

void listarListaAdj(TNo **lista, int vertices) {
    int i;
    TNo *aux;

    for(i = 0; i < vertices; i++) {
        aux = lista[i];
        while(aux != NULL) {
            printf("%d ", aux->info);
            aux = aux->prox;
        }
        printf("\n");
    }
}

void convListaMatriz(TNo **lista, int vertices, int matriz[M][M]) {
    int i, j;
    TNo *aux;

    for(i = 0; i < vertices; i++) {
        for(j = 0; j < vertices; j++) {
            matriz[i][j] = 0;
        }
    }

    for(i = 0; i < vertices; i++) {
        aux = lista[i]->prox;
        while(aux != NULL) {
            matriz[i][aux->info - 1] = 1;
            aux = aux->prox;
        }
    }
}

void listarMatrizAdj(int matriz[M][M], int vertices) {
    int i, j;
    for(i = 0; i < vertices; i++) {
        for(j = 0; j < vertices; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void matrizGrau(int matriz[M][M], int vertices, int *grau) {
    int i, j, cont = 0;
    for(i = 0; i < vertices; i++) {
        for(j = 0; j < vertices; j++) {
            if(matriz[i][j] == 1) {
                cont++;
            }
        }
        grau[i] = cont;
        cont = 0;
    }
}

void listarGrau(int *grau, int vertices) {
    int i;
    for(i = 0; i < vertices; i++) {
        printf("%d ", grau[i]);
    }
}

void grauS(TNo **lista, int vertices, int *grauSaida) {
    int i, cont = 0;
    TNo *aux;

    for(i = 0; i< vertices; i++) {
        aux = lista[i]->prox;
        while(aux != NULL) {
            cont++;
            aux = aux->prox;
        }
        grauSaida[i] = cont;
        cont = 0;
    }
}

void grauE(TNo **lista, int vertices, int *grauEntrada) {
    int i, j = 0, cont = 0;
    TNo *aux;

    for(i = 0; i < vertices; i++) {
        for(j = 0; j < vertices; j++) {
            aux = lista[j]->prox;
            while(aux != NULL) {
                if(aux->info == i + 1) {
                    cont++;
                }
                aux = aux->prox;
            }
        }
        grauEntrada[i] = cont;
        j = 0;
        cont = 0;
    }
}

void listarGrauES(int *grauEntrada, int *grauSaida, int vertices) {

    int i;

    for(i = 0; i < vertices; i++) {
        printf("%d ", grauEntrada[i]);
    }
    printf("\n");

    for(i = 0; i < vertices; i++) {
        printf("%d ", grauSaida[i]);
    }
}

void questaoUm(TNo **lista, int vertices, int valor) {
    int i;
    TNo *aux, *aux2;

    for(i = 0; i < vertices; i++) {
        aux = lista[i]->prox;
        if(lista[i]->info == valor) {
            while(aux != NULL) {
                aux2 = aux->prox;
                free(aux);
                aux = aux2;
            }
            lista[i]->prox = NULL;
        }
        else {
            aux2 = lista[i];
            while(aux != NULL) {
                if(aux->info == valor) {
                    aux2->prox = aux->prox;
                    free(aux);
                    break;
                }

                aux2 = aux;
                aux = aux->prox;
            }
        }
    }
}

void questaoDois(TNo **lista, int vertices) {
    int i, cont = 0;
    TNo *aux;

    for(i = 0; i < vertices; i++) {
        aux = lista[i]->prox;
        while(aux != NULL) {
            cont++;
            aux = aux->prox;
        }
    }

    printf("%f \n", cont/(float)vertices);
}

int main(){
    int op, vertices, v;
    int matriz[M][M];
    int grau[M];
    int grauSaida[M];
    int grauEntrada[M];
    TNo lista[M];
    FILE *arq = fopen("grafo.txt", "r");
    //FILE *arq = fopen("grafo2.txt", "r");
    fscanf(arq, "%d", &vertices);
    fseek(arq, 0, 0);

    inicializar(&lista, vertices);

    do {
        printf("\n");
        printf("1 - Listar grafo.txt \n\n");

        printf("2 - Converter grafo.txt em Lista de Adjecencia \n");
        printf("3 - Listar Lista Adjacente \n\n");

        printf("4 - Converter Lista de Adjacencia em Matriz de Adjacencia \n");
        printf("5 - Listar Matriz de Adjacencia \n\n");

        printf("6 - Converter Mariz de Adjacencia em Grau \n");
        printf("7 - Listar Grau \n\n");

        printf("8 - Grau de Entrada e Saida \n");
        printf("9 - Listar Grau de Entrada e Saida \n\n");

        printf("10 - Questao 1 \n");
        printf("11 - Questao 2 \n\n");

        printf("0 - Sair \n");
        scanf("%d", &op);
        printf("\n");
        switch(op) {
        case 0:
            fclose(arq);
            return 0;
        case 1:
            listar(arq);
            break;
        case 2:
            convListaAdj(arq, &lista, vertices);
            break;
        case 3:
            listarListaAdj(lista, vertices);
            break;
        case 4:
            convListaMatriz(lista, vertices, matriz);
            break;
        case 5:
            listarMatrizAdj(matriz, vertices);
            break;
        case 6:
            matrizGrau(matriz, vertices, grau);
            break;
        case 7:
            listarGrau(grau, vertices);
            break;
        case 8:
            grauE(lista, vertices, grauEntrada);
            grauS(lista, vertices, grauSaida);
            break;
        case 9:
            listarGrauES(grauEntrada, grauSaida, vertices);
            break;
        case 10:
            printf("Digite um vertice valido a ser removido: \n");
            scanf("%d", &v);
            questaoUm(lista, vertices, v);
            break;
        case 11:
            questaoDois(lista, vertices);
            break;
        default:
            printf("Opcao Invalida \n");
            break;
        }
    } while(op != 0);

    return 0;
}
