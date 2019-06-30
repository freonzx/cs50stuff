#include <stdio.h>
#include <stdlib.h>

void InsertionSort(int vet[], int tam);
int busca_bin(int vet[], int tam, int x);
void bubble_sort (int vetor[], int n);
void mostraVetor (int vet[], int tam);

#define SIZE 5

int main(int argc, char const * argv[]) {
	// int vetor[SIZE] = {4, 66, 44, 33, 88, 99, 22, 65, 78, 63};
    //int vetor[SIZE] = {0};

    int vet[8] = {30, 18, 45, 6, 25, 2, 15, 20 };

	//Modulo A - Leitura vetor
// 	for (int i = 0; i < SIZE; ++i)
// 	{
// 		printf("Entre com int pro vetor >> \n");
// 		scanf("%d", &vetor[i]);
// 	}

	//Chamada de funções Sort
	// InsertionSort(vetor, SIZE);
	bubble_sort(vet, 8);
    int vecc[6] = {55, 15, 3, 10, 5, 20};
    //InsertionSort(vecc, 6);

	//Mostrando vetor - Modulo C
	//mostraVetor(vetor, SIZE);
    int ghh[8] = {5, 10, 12, 25, 30, 45, 50, 68};
    //busca_bin(ghh, 8, 2);
	//Modulo D
	//int intbusca = 0;

// 	printf("\nBuscar no vetor >> \n");
// 	scanf("%d", &intbusca);

	//Chama função busca binaria e guarda resultado, compara e mostra
// 	int res_busca = busca_bin(vetor, SIZE, intbusca);

// 	if (res_busca != -1)
// 	{
// 		printf(">>> Numero encontrado na pos do vetor: %d\n", res_busca);
// 	}
// 	else
// 	{
// 		printf(">>> Numero não encontrado no vetor\n");
// 	}

    return 0;
}

void mostraVetor (int vetor[], int tam) {
    for (int i = 0; i < tam; ++i)
	{
		printf("pos[%d] = %d \n", i, vetor[i]);
	}
}

void InsertionSort(int vet[], int tam) {
    int i, j, elem, troca;

    for (i = 1; i < tam; i++) {
        elem = vet[i];
        j = i - 1;

        while (j >= 0 && vet[j] > elem) {
            vet[j + 1] = vet[j];
            troca++;

            j--;
        }
        vet[j + 1] = elem;
    }
    printf("%d  ", troca);
}

int busca_bin(int vet[], int tam, int x) {
    int ini, fim, meio, pos;

    ini = 0;
    fim = tam - 1;
    pos = -1;

    while (ini <= fim) {
        meio = (int)((ini + fim) / 2);
        if (vet[meio] == x) {
            pos = meio;
            ini = fim + 1;
        } else if (vet[meio] < x)
            ini = meio + 1;
        else fim = meio - 1;
    }

    printf("ini: %d meio : %d  pos: %d   fim: %d   ", ini, meio, pos, fim);
    return (pos);

}

void bubble_sort (int vetor[], int n) {
    int k, j, aux, troca;

    for (k = 1; k < n; k++) {
        for (j = 0; j < n - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                troca++;
                aux          = vetor[j];
                vetor[j]     = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
    printf("%d  ", troca);
}