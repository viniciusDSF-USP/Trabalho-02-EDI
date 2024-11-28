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

No *sugerir_similar(No *p, elem *x){
    return NULL;
}

No *sugerir_inedito(No *p, elem *x){
    return NULL;
}

int salvar_sistema(No *p){
    return 0;
}

int numero_alunos(No *p){
    if (p != NULL) return 0;

    return 1 + numero_alunos(p->esq) + numero_alunos(p->dir);
}

int maior_FB(No *p){
    if (p == NULL) return 0;

    if (p->FB == -1 || p->FB == 1) return 1;
    int E = maior_FB(p->esq);
    int D = maior_FB(p->dir);

    return E || D;
}

int inserir_de_arquivo(No **p, char *nome_arquivo){
    return 0;
}