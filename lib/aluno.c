#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

int inserir_filme_fav(NoLista **p, No **filme){
	if (*p == NULL){
		NoLista *new = (NoLista *) malloc(sizeof(NoLista));
			
		if (new != NULL){
			new->filme = *filme;
			new->prox = NULL;

			(*filme)->info.filme.frequencia++;

			*p = new;
			
			return 1;
		} else {
			return 0;
		}
	}

	if ((*p)->filme == NULL){
		int aux = inserir_filme_fav(&(*p)->prox, filme);

		if (aux == -1){
			NoLista *new = (NoLista *) malloc(sizeof(NoLista));
			
			if (new != NULL){
				new->filme = *filme;
				new->prox = (*p)->prox;
				(*p)->prox = new;

				(*filme)->info.filme.frequencia++;
				
				return 1;
			} else {
				return 0;
			}
		}

		return aux;
	}
	
	if (strcmp((*filme)->info.filme.nome, (*p)->filme->info.filme.nome) < 0){ // filme < p
		return -1;
	} else if (strcmp((*filme)->info.filme.nome, (*p)->filme->info.filme.nome) > 0){ // filme > p
		int aux = inserir_filme_fav(&(*p)->prox, filme);
		
		if (aux == -1){
			NoLista *new = (NoLista *) malloc(sizeof(NoLista));
			
			if (new != NULL){
				new->filme = *filme;
				new->prox = (*p)->prox;
				(*p)->prox = new;

				(*filme)->info.filme.frequencia++;
				
				return 1;
			} else {
				return 0;
			}
		} else
			return aux;
	} else { // filme == p
		return 0;
	}
}

int remover_filme_fav(NoLista **p, No **filme){
	if (*p == NULL)
		return 0;

	if ((*p)->filme == NULL){
		int aux = remover_filme_fav(&(*p)->prox, filme);
		if (aux == -1){
			(*p)->prox = (*p)->prox->prox;
			free((*p)->prox);
			
			(*filme)->info.filme.frequencia--;
			
			return 1;
		}
		return aux;
	}
	
	if (strcmp((*filme)->info.filme.nome, (*p)->filme->info.filme.nome) == 0) // filme == p
		return -1;
	
	return remover_filme_fav(&(*p)->prox, filme);
}

int limpar_filmes_fav(NoLista **p, No **raiz_filmes){
	if (*p == NULL)
		return 1;
	
	if ((*p)->filme == NULL){
		int aux = limpar_filmes_fav(&(*p)->prox, raiz_filmes);

		if (aux){
			free(*p);
			*p = NULL;
			return 1;
		}

		return aux;
	}
	
	if (limpar_filmes_fav(&(*p)->prox, raiz_filmes)){
		(*p)->filme->info.filme.frequencia--;

		if ((*p)->filme->info.filme.frequencia == 0){
			elem aux;

			aux.info.filme.nome = (*p)->filme->info.filme.nome;
			aux.tipo = Filme;

			if (!remover(raiz_filmes, &aux))
				return 0;
		}

		free(*p);
		*p = NULL;

		return 1;
	}

	return 0;
}

typedef struct Resultado {
    No *aluno;
    int filmes_similares;
} Resultado;

void comparar_filmes(NoLista *lista1, NoLista *lista2, Resultado *resultado, No *aluno_atual) {
    int similares = 0;
    NoLista *aux1 = lista1;
    NoLista *aux2 = lista2;

    while (aux1 != NULL && aux2 != NULL) {
        if (aux1->filme != NULL && aux2->filme != NULL) {
            int cmp = strcmp(aux1->filme->info.filme.nome, aux2->filme->info.filme.nome);

            if (cmp == 0) {
                similares++;
                aux1 = aux1->prox;
                aux2 = aux2->prox;
            } else if (cmp < 0) {
                aux1 = aux1->prox;
            } else {
                aux2 = aux2->prox;
            }
        } else {
            break;
        }
    }


    if (similares > resultado->filmes_similares) {
        resultado->filmes_similares = similares;
        resultado->aluno = aluno_atual;
    }
}

void buscar_aluno_similar(No *raiz, No *aluno_chave, Resultado *resultado) {
    if (raiz == NULL) return;

    if (raiz->tipo == Aluno && raiz != aluno_chave) {
        comparar_filmes(aluno_chave->info.aluno.filmes_fav, raiz->info.aluno.filmes_fav, resultado, raiz);
    }

    buscar_aluno_similar(raiz->esq, aluno_chave, resultado);
    buscar_aluno_similar(raiz->dir, aluno_chave, resultado);
}

No *sugerir_similar(AVL *arvore, int nroUSP) {
    elem chave;
    chave.tipo = Aluno;
    chave.info.aluno.nroUSP = nroUSP;

    No **aluno_chave = buscar(&arvore->raiz, &chave);
    if (aluno_chave == NULL || *aluno_chave == NULL) {
        printf("Aluno não encontrado.\n");
        return NULL;
    }

    Resultado resultado = {NULL, 0};

    buscar_aluno_similar(arvore->raiz, *aluno_chave, &resultado);

    return resultado.aluno;
}

No *sugerir_diferente(No *p, elem *x){
    return NULL;
}