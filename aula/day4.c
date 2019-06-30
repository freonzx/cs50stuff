#include <stdio.h>
#include <stdlib.h>


void getVect(float vect[]);
void display(float vect[]);
void decreBubbleSort(float vet[], int tam);
int busca_bin(float vet[], int tam, float x);

int main () {
    float vect[10] = {0};
    
    //A
    getVect(vect);
    //B
    decreBubbleSort(vect,10);
    //C
    float buscar = 0;
    printf("Entre com float para busca >> \n");
    scanf("%f", &buscar);
    
    int res = busca_bin(vect,10,buscar);
    if (res != -1) printf("Encontrado numero na posição %d \n", res);
    else printf("Nada encontrado");

    
    //D
    display(vect);
    
    return 0;
}


void getVect(float vect[]) {
    for(int i=0; i< 10; i++) {
        printf("Entre com float para vet pos %d >> \n", i);
        scanf("%f", &vect[i]);
    }
}

void display(float vect[]){
    for(int i=0; i< 10; i++) {
        printf("pos %d : %f \n", i, vect[i]);
    }
}

void decreBubbleSort(float vet[], int tam) {
    int i, j;
    int aux;
    
    for (i = 1; i < tam; i++) {
        for (j = 0; j < tam - i; j++) {
            if (vet[j] < vet[j + 1]) {
                aux = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = aux;
            }
        }
    }
}

int busca_bin(float vet[], int tam, float x) {
    int ini, fim, meio, pos;

    ini = 0;
    fim = tam - 1;
    pos = -1;

    while (ini <= fim) {
        meio = (int)((ini + fim) / 2);
        if (vet[meio] == x) {
            pos = meio;
            ini = fim + 1;
        } else if (vet[meio] > x)
            ini = meio + 1;
        else fim = meio - 1;
    }

    return (pos);

}