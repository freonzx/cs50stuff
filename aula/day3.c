#include <stdio.h>

#include <stdlib.h>


int tam_max = 10, tam = 0;
void exibe(int vet[]) {
    int i;
    printf(" \n");

    if (tam >= 1) {
        for (i = 0; i < tam; i++)
            printf("\nvet[%d]=%d", i, vet[i]);
    } else printf("\n pilha vazia");
    getch();
}

void push(int vet[], int elem) {
    int num;

    if (tam == tam_max) {
        printf("\n pilha cheia");
        getch();
    }
    else {
        vet[tam] = elem;
        tam++;
    }
}

void pop(int vet[]) {
    if (tam >= 1)
        tam--;
    else {
        printf("\n pilha vazia");
        getch();
    }
}
//***************************************************************************
int main() {
    int vet[10], op, elem;
    do {
        system("cls");
        printf("\n 1 - Insere pilha ");
        printf("\n 2 - Remove pilha");
        printf("\n 3 - Exibe pilha");
        printf("\n 0 - Sair\n");

        scanf("%d", &op);
        switch (op) {
        case 1:
            {
                printf("\n Digite o elemento da pilha");
                scanf("%d", &elem);
                push(vet, elem);
                break;
            }
        case 2:
            {
                pop(vet);
                break;
            }
        case 3:
            {
                system("cls");
                exibe(vet);
                break;
            }
        }
    }
    while (op != 0);
}