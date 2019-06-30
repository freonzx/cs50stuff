#include <stdio.h>

#include <stdlib.h>

struct no_arv {
    int info;
    struct no_arv * esq;
    struct no_arv * dir;
};

typedef struct no_arv * tipo_arv;
tipo_arv raiz = NULL;
//*****************************************************************************
int arvoreVazia() {
    if (raiz == NULL)
        return (1);
    return (0);
}
//*****************************************************************************
tipo_arv criaRaiz(int x) {
    tipo_arv novoNo = (tipo_arv) malloc(sizeof(no_arv));
    novoNo - > info = x;
    novoNo - > esq = NULL;
    novoNo - > dir = NULL;
    raiz = novoNo;
    return (novoNo);
}
//*****************************************************************************
tipo_arv insereDir(tipo_arv * pai, int x) {
    tipo_arv no_pai = * pai;
    if (!arvoreVazia()) {
        if (no_pai - > dir != NULL) {
            printf("\n No direito ja ocupado");
            return NULL;
        } else {
            tipo_arv novoNo = (tipo_arv) malloc(sizeof(no_arv));
            novoNo - > info = x;
            novoNo - > esq = NULL;
            novoNo - > dir = NULL;
            no_pai - > dir = novoNo;
            return (novoNo);
        }
    }
    return NULL;
}
tipo_arv insereEsq(tipo_arv * pai, int x) {
    tipo_arv no_pai = * pai;
    if (!arvoreVazia()) {
        if (no_pai - > esq != NULL) {
            printf("\n No esquerdo ja ocupado");
            return NULL;
        } else {
            tipo_arv novoNo = (tipo_arv) malloc(sizeof(no_arv));
            novoNo - > info = x;
            novoNo - > esq = NULL;
            novoNo - > dir = NULL;
            no_pai - > esq = novoNo;
            return (novoNo);
        }
    }
    return NULL;
}
//*****************************************************************************
// principal
//*****************************************************************************
int main() {
    tipo_arv No;
    raiz = criaRaiz(8);
    No = raiz;
    insereDir( & No, 10);
    No = insereEsq( & No, 14);
    No = insereEsq( & No.dir, 7);
    No = insereDir( & No.dir, 9);
    //getch();
}