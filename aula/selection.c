#include <stdio.h>
#include <stdlib.h>

void selection(int vet[], int tam);

int main()
{
    int vet[9] = {4, 66, 44, 33, 88, 99, 22, 65, 78 };
    int tam = 9;
    
    selection(vet, tam);
    
    for(int i = 0 ; i < 9 ; i ++) {
        printf("%d ", vet[i]);
    }
    
    return 0;
}

void selection(int vet[], int tam)
{
    int i, j, posmenor, menor, aux;
    for (i = 0; i < tam; ++i)
    {
        menor = vet[i];
        posmenor = i;

        for (j = i + 1; j < tam; ++j)
        {
            if (vet[j] < menor)
            {
                menor = vet[j];
                posmenor = j;
            }
        }
        aux = vet[i];
        vet[i] = vet[posmenor];
        vet[posmenor] = aux;
    }
}