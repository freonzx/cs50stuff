#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


int tam_max = 15, tam = 0;

void exibe(int vet[]) {
    int i;
    printf(" \n");

    if (tam >= 1) {
        for (i = 0; i < tam; i++)
            printf("\nvet[%d]=%d", i, vet[i]);
    } else printf("Pilha vazia \n");
    getch();
}

void pushPar(int vet[], int elem) {
    int num;

    if (tam == tam_max) {
        printf("Pilha cheia \n");
        getch();
    }
    else if (elem % 2 == 0){
        vet[tam] = elem;
        tam++;
    }
	else {
		printf("Elemento nao e par \n");
	}
}

void pushImpar(int vet[], int elem) {
    int num;

    if (tam == tam_max) {
        printf("Pilha cheia \n");
        getch();
    }
    else if (elem % 2 == 1){
        vet[tam] = elem;
        tam++;
    }
	else {
		printf("Elemento nao e impar \n");
	}
}


void pop(int vet[]) {
    if (tam >= 1)
        tam--;
    else {
        printf("\nPilha vazia");
        getch();
    }
}


int main() {
    int vetA[15], vetB[15], op, elem;
    
    do {
        //system("cls");
        printf("\n 1 - Inserir par na pilha A ");
        printf("\n 2 - Inserir impar na pilha B ");
        printf("\n 3 - Exibe pilha");
        printf("\n 0 - Sair\n");

        scanf("%d", &op);
        switch (op) {
        case 1:
            {
                printf("\nDigite o elemento da pilha >> ");
                scanf("%d", &elem);
                pushPar(vetA, elem);
                break;
            }
        case 2:
            {
                pushImpar(vetB, elem);;
                break;
            }
        case 3:
            {
                system("cls");
                printf("Vetor Par: \n");
                exibe(vetA);
                printf("Vetor Impar: \n");
                exibe(vetB);
                break;
            }
        }
    }
    while (op != 0);
}