#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

AVL *CriarAVL(int tipo) {
    AVL *A = (AVL *) malloc(sizeof(AVL));

    if (A != NULL){
        A->raiz = NULL;
    }

    return A;
}

int EstaVazia(AVL *A) {
    return A->raiz == NULL;
}

No **buscar(No *p, elem *x) {
    if (p == NULL) return NULL;

    switch (p->tipo){
        case Aluno:
            if ((*x).aluno.nroUSP == p->info.aluno.nroUSP){
                return &p;
            } else if ((*x).aluno.nroUSP < p->info.aluno.nroUSP) {
                return buscar(p->esq, x);
            } else {
                return buscar(p->dir, x);
            }
            break;
        
        case Filme:
            if (strcmp((*x).filme.nome, p->info.filme.nome) == 0){
                return &p;
            } else if (strcmp((*x).filme.nome, p->info.filme.nome) <= -1) {
                return buscar(p->esq, x);
            } else {
                return buscar(p->dir, x);
            }
            break;
    }
}

int inserir(No **p, elem *x) {


    return 0;
}

int remover(No **p, elem *x) { // Proxima aula


    return 0;
}

void imprimir_recursiva(No *p, int tipo){ // Em ordem
    if (p == NULL) return;

    imprimir_recursiva(p->esq, tipo);

    switch (tipo){
        case Aluno:
            printf("(%s, %d)", p->info.aluno.nome, p->info.aluno.nroUSP);
            break;
        case Filme:
            printf("(%s, %d)", p->info.filme.nome, p->info.filme.frequencia);
            break;
    }

    if (p->esq != NULL || p->dir != NULL) // Nao eh uma folha
        printf(", ");

    imprimir_recursiva(p->dir, tipo);
}

void imprimirAVL(AVL *A, int tipo) {
    switch (tipo){
        case Aluno:
            imprimir_recursiva(A->raiz, tipo);
            break;
        case Filme:
            imprimir_recursiva(A->raiz, tipo);
            break;
    }

    printf("\n");
}