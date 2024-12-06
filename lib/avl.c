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

	if ((*p)->filme != NULL){
		(*p)->filme->info.filme.frequencia--;
	} else {
		free((*p)->filme);
	}
	
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
            if (x->info.aluno.nroUSP == (*p)->info.aluno.nroUSP){
                return p;
            } else if (x->info.aluno.nroUSP < (*p)->info.aluno.nroUSP) {
                return buscar(&(*p)->esq, x);
            } else {
                return buscar(&(*p)->dir, x);
            }
            break;
        
        case Filme:
            if (strcmp(x->info.filme.nome, (*p)->info.filme.nome) == 0){
                return p;
            } else if (strcmp(x->info.filme.nome, (*p)->info.filme.nome) <= -1) {
                return buscar(&(*p)->esq, x);
            } else {
                return buscar(&(*p)->dir, x);
            }
            break;
    }

    return NULL;
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

int inserir(No **p, elem *x) {
    if (*p == NULL){
		No *new = (No *) malloc(sizeof(No));
		
		if (new != NULL){
			switch (x->tipo){
                case Aluno:
                    new->info.aluno.nome = (char *) malloc(STRLIM * sizeof(char));

                    if (new->info.aluno.nome == NULL){
                        free(new);
                        return 0;
                    }

                    strcpy(new->info.aluno.nome, x->info.aluno.nome);
                    new->info.aluno.nroUSP = x->info.aluno.nroUSP;
                    
                    NoLista *head = (NoLista *) malloc(sizeof(NoLista));
			
					if (head != NULL){
						head->filme = NULL;
						head->prox = NULL;
						
						new->info.aluno.filmes_fav = head;
					} else {
						free(new->info.aluno.nome);
						free(new);
						return 0;
					}
					
                    break;
                
                case Filme:
                    new->info.aluno.nome = (char *) malloc(STRLIM * sizeof(char));
                    
                    if (new->info.filme.nome == NULL){
                        free(new);
                        return 0;
                    }

                    strcpy(new->info.filme.nome, x->info.filme.nome);
                    new->info.filme.frequencia = 0;
                    break;
            }

            new->tipo = x->tipo;
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

    switch (x->tipo){
        case Aluno:
            if (x->info.aluno.nroUSP < (*p)->info.aluno.nroUSP)
                E = inserir(&(*p)->esq, x);
            else if (x->info.aluno.nroUSP > (*p)->info.aluno.nroUSP)
                D = inserir(&(*p)->dir, x);
            else
                return 0;
            break;
        
        case Filme:
            if (strcmp(x->info.filme.nome, (*p)->info.filme.nome) <= -1)
                E = inserir(&(*p)->esq, x);
            else if (strcmp(x->info.filme.nome, (*p)->info.filme.nome) >= 1)
                D = inserir(&(*p)->dir, x);
            else {
                (*p)->info.filme.frequencia++;
                return 0;
            }
            break;
    }
	
	if (E || D){
		(*p)->altura = max( altura((*p)->esq), altura((*p)->dir) )+1;
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
            if (x->info.aluno.nroUSP < (*p)->info.aluno.nroUSP)
                E = remover(&(*p)->esq, x);
            else if (x->info.aluno.nroUSP > (*p)->info.aluno.nroUSP)
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

                    //strcpy(aux->info.aluno.nome, x->info.aluno.nome); // Nao precisa pq quando encontrar o aux ele vai ser removido
                    aux->info.aluno.nroUSP = x->info.aluno.nroUSP;

                    E = remover(&(*p)->esq, x);
                }
            }
            break;
        
        case Filme:
            if (strcmp(x->info.filme.nome, (*p)->info.filme.nome) <= -1)
                E = remover(&(*p)->esq, x);
            else if (strcmp(x->info.filme.nome, (*p)->info.filme.nome) >= 1)
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

                    strcpy(aux->info.filme.nome, x->info.filme.nome);
                    //aux->info.filme.frequencia = x->info.filme.frequencia; // Nao precisa pq quando encontrar o aux ele vai ser removido

                    E = remover(&(*p)->esq, x);
                }
            }
            break;
    }
	
	if (E || D){
		(*p)->altura = max( altura((*p)->esq), altura((*p)->dir) )+1;
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
        printf("\n");

    switch (p->tipo){
        case Aluno:
            if (p->esq != NULL)
                printf("\n");

            printf("\t            Nome: %s\n", p->info.aluno.nome);
            printf("\t      Numero USP: %d\n", p->info.aluno.nroUSP);
            printf("\tFilmes favoritos: {");

            NoLista *aux = p->info.aluno.filmes_fav->prox;
            while (aux != NULL){
                printf("%s", aux->filme->info.filme.nome);

                if (aux->prox != NULL)
                    printf(", ");
                aux = aux->prox;
            }

            printf("}");

            if (p->dir != NULL)
                printf("\n");

            break;
        case Filme:
            printf("\t%s", p->info.filme.nome);
            break;
    }

    if (p->dir != NULL)
        printf("\n");

    imprimir_recursivo(p->dir);
}

void imprimirAVL(AVL *A) {	
    imprimir_recursivo(A->raiz);
}

void imprimir_recursivo_2(No *p, int spaces){
    if (p == NULL) return;

    spaces += TAB;

    imprimir_recursivo_2(p->dir, spaces);

    printf("\n");
    for (int i=TAB; i<=spaces; i++) printf(" ");

    switch (p->tipo){
        case Aluno:
            printf("(%s, %d) [%d,%d]", p->info.aluno.nome, p->info.aluno.nroUSP, p->FB, p->altura);
            break;
        case Filme:
            printf("(%s, %d) [%d,%d]", p->info.filme.nome, p->info.filme.frequencia, p->FB, p->altura);
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

int numero_nos(No *p){
    if (p == NULL) return 0;

    return 1 + numero_nos(p->esq) + numero_nos(p->dir);
}

int altura(No *p){
	if (p == NULL) return 0;
	return p->altura;
}

int maior_FB(No *p){
    if (p == NULL) return 0;

    if (p->FB == -1 || p->FB == 1) return 1;
    int E = maior_FB(p->esq);
    int D = maior_FB(p->dir);

    return E || D;
}

int imprimir_dadosAVL(AVL *A){
    if (A->raiz == NULL) return 0;

    switch(A->raiz->tipo){
        case Aluno:
            printf("Dados da AVL de Alunos:\n");
            break;
        
        case Filme:
            printf("Dados da AVL de Filmes:\n");
            break;
    }

    printf("\t            Numero de Nos: %d\n", numero_nos(A->raiz));
    printf("\t             Altura Total: %d\n", altura(A->raiz));
    printf("\tMaior Diferenca de Altura: %d", maior_FB(A->raiz));

    return 1;
}

void salvar_recursivo(No *p, FILE *f){
    if (p == NULL) return;

    salvar_recursivo(p->esq, f);

    char line[800];
    char int_str[12];

    strcpy(line, p->info.aluno.nome);
    strcat(line, ";");

    sprintf(int_str, "%d", p->info.aluno.nroUSP);
    strcat(line, int_str);

    NoLista *mov = p->info.aluno.filmes_fav->prox;
    while (mov != NULL){
        strcat(line, ";");
        strcat(line, mov->filme->info.filme.nome);

        mov = mov->prox;
    }

    strcat(line, "\n");

    fprintf(f, "%s", line);

    salvar_recursivo(p->dir, f);
}

int salvar_sistema(AVL *A){
    FILE *f;

    f = fopen("./src/saida_sistema.txt", "w");

    if (f == NULL)
        return 0;

    salvar_recursivo(A->raiz, f);

    fclose(f);

    return 1;
}