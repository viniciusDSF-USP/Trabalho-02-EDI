#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

AVL *CriarAVL() {
    AVL *A = (AVL *) malloc(sizeof(AVL));

    if (A != NULL){
        A->raiz = NULL;
    }

    return A;
}

void finalizarLista(NoLista **p){
    if (*p == NULL) return;

    finalizarLista(&(*p)->prox);

    free(*p);
    *p = NULL;
}

void FinalizarAVL(No **p){
    if (*p == NULL) return;

    FinalizarAVL(&(*p)->esq);
    FinalizarAVL(&(*p)->dir);

    switch ((*p)->tipo){
        case Aluno:
            finalizarLista(&(*p)->info.aluno.filmes_fav);
            free(*p);
            *p = NULL;

            break;

        case Filme:
            free(*p);
            *p = NULL;

            break;
    }
}

No **buscar(No **p, elem *x) {
    if (*p == NULL) return NULL;

    switch ((*p)->tipo){
        case Aluno:
            if ((*x).aluno.nroUSP == (*p)->info.aluno.nroUSP){
                return p;
            } else if ((*x).aluno.nroUSP < (*p)->info.aluno.nroUSP) {
                return buscar(&(*p)->esq, x);
            } else {
                return buscar(&(*p)->dir, x);
            }
            break;
        
        case Filme:
            if (strcmp((*x).filme.nome, (*p)->info.filme.nome) == 0){
                return p;
            } else if (strcmp((*x).filme.nome, (*p)->info.filme.nome) <= -1) {
                return buscar(&(*p)->esq, x);
            } else {
                return buscar(&(*p)->dir, x);
            }
            break;
    }
}

int altura(No *p){
	if (p == NULL) return 0;
	return p->altura;
}

int max(int a, int b){
	return a > b ? a : b;
}

void rot_esq(No **a){
	No *b = (*a)->dir;
	
	(*a)->dir = b->esq;
	b->esq = *a;
	
	(*a)->altura = max( altura((*a)->esq), altura((*a)->dir) )+1;
	b->altura = max( altura(b->esq), altura(b->dir) )+1;
	
	(*a)->FB = altura((*a)->dir) - altura((*a)->esq);
	b->FB = altura(b->dir) - altura(b->esq);
	
	*a = b;
}

void rot_dir(No **a){
	No *b = (*a)->esq;
	
	(*a)->esq = b->dir;
	b->dir = *a;
	
	(*a)->altura = max( altura((*a)->esq), altura((*a)->dir) )+1;
	b->altura = max( altura(b->esq), altura(b->dir) )+1;
	
	(*a)->FB = altura((*a)->dir) - altura((*a)->esq);
	b->FB = altura(b->dir) - altura(b->esq);
	
	*a = b;
}

int inserir(No **p, elem *x, int tipo) {
    if (*p == NULL){
		No *new = (No *) malloc(sizeof(No));
		
		if (new != NULL){
			switch (tipo){
                case Aluno:
                    new->info.aluno.nome = (char *) malloc(STRLIM * sizeof(char));

                    if (new->info.aluno.nome == NULL){
                        free(new);
                        return 0;
                    }

                    strcpy(new->info.aluno.nome, x->aluno.nome);
                    new->info.aluno.nroUSP = x->aluno.nroUSP;
                    break;
                
                case Filme:
                    new->info.aluno.nome = (char *) malloc(STRLIM * sizeof(char));
                    
                    if (new->info.filme.nome == NULL){
                        free(new);
                        return 0;
                    }

                    strcpy(new->info.filme.nome, x->filme.nome);
                    new->info.filme.frequencia = 0;
                    break;
            }

            new->tipo = tipo;
			new->FB = 0;
			new->altura = 1;
			new->esq = new->dir = NULL;
			
			*p = new;
		} else {
            return 0;
        }
		
		return 1;
	}
	
	int E = 0, D = 0;

    switch (tipo){
        case Aluno:
            if (x->aluno.nroUSP < (*p)->info.aluno.nroUSP)
                E = inserir(&(*p)->esq, x, tipo);
            else if (x->aluno.nroUSP > (*p)->info.aluno.nroUSP)
                D = inserir(&(*p)->dir, x, tipo);
            else
                return 0;
            break;
        
        case Filme:
            if (strcmp(x->filme.nome, (*p)->info.filme.nome) <= -1)
                E = inserir(&(*p)->esq, x, tipo);
            else if (strcmp(x->filme.nome, (*p)->info.filme.nome) >= 1)
                D = inserir(&(*p)->dir, x, tipo);
            else {
                (*p)->info.filme.frequencia++;
                return 0;
            }
            break;
    }
	
	if (E || D){
		(*p)->altura++;
		(*p)->FB = altura((*p)->dir) - altura((*p)->esq);
	}
	
	if ((*p)->FB <= -2){
		if ((*p)->esq->FB > 0)
			rot_esq(&(*p)->esq);
		rot_dir(p);
	} else if ((*p)->FB >= 2){
		if ((*p)->dir->FB < 0)
			rot_dir(&(*p)->dir);
		rot_esq(p);
	}
	
	return (E || D);
}

No *max_esq(No *p){
	if (p == NULL) return NULL;
	if (p->dir == NULL) return p;
	return max_esq(p->dir);
}

int remover(No **p, elem *x) {
    if (*p == NULL) return 0;
	
	int E = 0, D = 0;

    switch ((*p)->tipo){
        case Aluno:
            if (x->aluno.nroUSP < (*p)->info.aluno.nroUSP)
                E = remover(&(*p)->esq, x);
            else if (x->aluno.nroUSP > (*p)->info.aluno.nroUSP)
                D = remover(&(*p)->dir, x);
            else {
                if ((*p)->esq == NULL && (*p)->dir == NULL){
                    free(*p);
                    *p = NULL;
                    
                    return 1;
                } else if ((*p)->esq != NULL && (*p)->dir == NULL){
                    No *aux = (*p)->esq;
                    free(*p);
                    *p = aux;
                    
                    return 1;
                } else if ((*p)->esq == NULL && (*p)->dir != NULL){
                    No *aux = (*p)->dir;
                    free(*p);
                    *p = aux;
                    
                    return 1;
                } else {
                    No *aux = max_esq((*p)->esq);

                    strcpy((*p)->info.aluno.nome, aux->info.aluno.nome);
                    (*p)->info.aluno.nroUSP = aux->info.aluno.nroUSP;

                    strcpy(aux->info.aluno.nome, x->aluno.nome);
                    aux->info.aluno.nroUSP = x->aluno.nroUSP;

                    E = remover(&(*p)->esq, x);
                }
            }
            break;
        
        case Filme:
            if (strcmp(x->filme.nome, (*p)->info.filme.nome) <= -1)
                E = remover(&(*p)->esq, x);
            else if (strcmp(x->filme.nome, (*p)->info.filme.nome) >= 1)
                D = remover(&(*p)->dir, x);
            else {
                if ((*p)->esq == NULL && (*p)->dir == NULL){
                    free(*p);
                    *p = NULL;
                    
                    return 1;
                } else if ((*p)->esq != NULL && (*p)->dir == NULL){
                    No *aux = (*p)->esq;
                    free(*p);
                    *p = aux;
                    
                    return 1;
                } else if ((*p)->esq == NULL && (*p)->dir != NULL){
                    No *aux = (*p)->dir;
                    free(*p);
                    *p = aux;
                    
                    return 1;
                } else {
                    No *aux = max_esq((*p)->esq);

                    strcpy((*p)->info.filme.nome, aux->info.filme.nome);
                    (*p)->info.filme.frequencia = aux->info.filme.frequencia;

                    strcpy(aux->info.filme.nome, x->filme.nome);

                    E = remover(&(*p)->esq, x);
                }
            }
            break;
    }
	
	if (E || D){
		(*p)->altura--;
		(*p)->FB = altura((*p)->dir) - altura((*p)->esq);
	}
	
	if ((*p)->FB <= -2){
		if ((*p)->esq->FB > 0)
			rot_esq(&(*p)->esq);
		rot_dir(p);
	} else if ((*p)->FB >= 2){
		if ((*p)->dir->FB < 0)
			rot_dir(&(*p)->dir);
		rot_esq(p);
	}
	
	return (E || D);
}

void imprimir_recursivo(No *p){ // Em ordem
    if (p == NULL) return;

    imprimir_recursivo(p->esq);

    if (p->esq != NULL)
        printf(", ");

    switch (p->tipo){
        case Aluno:
            printf("(%s, %d)", p->info.aluno.nome, p->info.aluno.nroUSP);
            break;
        case Filme:
            printf("(%s, %d)", p->info.filme.nome, p->info.filme.frequencia);
            break;
    }

    if (p->dir != NULL)
        printf(", ");

    imprimir_recursivo(p->dir);
}

void imprimirAVL(AVL *A) {
    imprimir_recursivo(A->raiz);
    printf("\n");
}

void imprimir_recursivo_2(No *p, int spaces){
    if (p == NULL) return;

    spaces += TAB;

    imprimir_recursivo_2(p->dir, spaces);

    printf("\n");
    for (int i=TAB; i<=spaces; i++) printf(" ");

    switch (p->tipo){
        case Aluno:
            printf("(%s, %d) [%d]", p->info.aluno.nome, p->info.aluno.nroUSP, p->FB);
            break;
        case Filme:
            printf("(%s, %d) [%d]", p->info.filme.nome, p->info.filme.frequencia, p->FB);
            break;
    }

    printf("\n");
    imprimir_recursivo_2(p->esq, spaces);
}

void imprimirGrafo(AVL *A){
    printf("\n--------------\n");
    imprimir_recursivo_2(A->raiz, 0);
    printf("----------------\n\n");
}