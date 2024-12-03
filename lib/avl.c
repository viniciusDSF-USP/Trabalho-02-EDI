#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

int altura(No *p){
    if (p == NULL) return 0;
    return p->altura;
}

int numero_nos(No *p){
    if (p != NULL) return 0;

    return 1 + numero_nos(p->esq) + numero_nos(p->dir);
}

int maior_FB(No *p){
    if (p == NULL) return 0;

    if (p->FB == -1 || p->FB == 1) return 1;
    int E = maior_FB(p->esq);
    int D = maior_FB(p->dir);

    return E || D;
}

int dados_tecnicos_arvores(AVL *A){
    if (A->raiz == NULL) return 0;
    
    switch (A->raiz->tipo){
        case Aluno:
            printf("AVL de Alunos:\n");
            break;
        
        case Filme:
            printf("AVL de Filmes:\n");
            break;
    }

    printf("\tNumero de nos: %d\n", numero_nos(A->raiz));
    printf("\tAltura total: %d\n", altura(A->raiz));
    printf("\tMaior fator de balanceamento (em modulo): %d\n", maior_FB(A->raiz));

    return 1;
}

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
        printf("\n");

    switch (p->tipo){
        case Aluno:
            //printf("(%s, %d)", p->info.aluno.nome, p->info.aluno.nroUSP);
            printf("\t%s - %d", p->info.aluno.nome, p->info.aluno.nroUSP);
            break;
        case Filme:
            //printf("(%s, %d)", p->info.filme.nome, p->info.filme.frequencia);
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

void salvar_recursivo(No *p, FILE* file) {
    fprintf(file, "%s;%d", p->info.aluno.nome, p->info.aluno.nroUSP);

    NoLista* no = p->info.aluno.filmes_fav;
    do {
        fprintf(file, ";%s", no->filme->info.filme.nome);
    } while((no = no->prox) != NULL);
    fprintf(file, "\n");
}

int salvar_sistema(AVL *A){
    FILE *file;
    file = fopen("save.txt", "w");
    
    salvar_recursivo(A->raiz, file);
    return 0;
}

void ler_recursivo(AVL *alunos, AVL *filmes, FILE* file) {
    char* line;
    fgets(line, 100000, file);
    
    char* endptr;
    long nroUsp = strtol(strtok(line, ";"), &endptr, 10);

    char* nome = strtok(NULL, ";");
    
    printf("\tNome do Aluno: ");
    
    elem* e;
    e->tipo = Aluno;
    e->info.aluno.nroUSP = (int) nroUsp;
    e->info.aluno.nome = nome;
    e->info.aluno.filmes_fav = (NoLista*) malloc(sizeof(NoLista));

    NoLista* p = e->info.aluno.filmes_fav;
    
    char* token;
    while ((token = strtok(NULL, ";")) != NULL) {
        inserir();
    }

    inserir(alunos->raiz, e);    
}

/*
case 1: // Cadastrar aluno
    printf("Cadastrar aluno\n\n");
    printf("\tNome do Aluno: ");
    
    getchar();
    fgets(string, STRLIM, stdin);
    string[strcspn(string, "\n")] = 0;
    
    x.info.aluno.nome = string;
    
    printf("\tNumero USP: ");
    if (scanf("%d", &x.info.aluno.nroUSP) != 1){
        while (getchar() != '\n'); // Limpa o buffer
        printf("Erro ao cadastrar o aluno!");
        break;
    }
    
    x.tipo = Aluno;
    
    if (inserir(&Alunos->raiz, &x)){
        printf("Aluno cadastrado com sucesso!");
    } else {
        printf("Erro ao cadastrar o aluno!");
    }
    
    break;
*/

ler_de_arquivo(AVL *alunos, AVL* filmes, char *nome_arquivo){
    FILE *file;
    file = fopen(nome_arquivo, "r");
    if (file == NULL) return -1;
    
    ler_recursivo(alunos, file);
}