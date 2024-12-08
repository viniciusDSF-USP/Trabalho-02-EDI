#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

int inserir_filme_fav(NoLista **p, No **filme){
	if (*p == NULL)
		return -1;

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
		
		if (aux != 1){
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

	int aux;
	NoLista *rem;

	if ((*p)->filme == NULL){
		aux = remover_filme_fav(&(*p)->prox, filme);
		if (aux == -1){
			rem = (*p)->prox;
			(*p)->prox = rem->prox;
			free(rem);
			
			(*filme)->info.filme.frequencia--;
			
			return 1;
		}
		return aux;
	}
	
	if (strcmp((*filme)->info.filme.nome, (*p)->filme->info.filme.nome) == 0) // filme == p
		return -1;
	
	aux = remover_filme_fav(&(*p)->prox, filme);

	if (aux == -1){
		rem = (*p)->prox;
		(*p)->prox = rem->prox;
		free(rem);
		
		(*filme)->info.filme.frequencia--;
		
		return 1;
	}

	return aux;
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

int filmes_fav_comum(No **p, No **q){
	NoLista *i, *j;

	i = (*p)->info.aluno.filmes_fav->prox;
	j = (*q)->info.aluno.filmes_fav->prox;

	int comum = 0;

	while (i != NULL && j != NULL){
		if (strcmp(j->filme->info.filme.nome, i->filme->info.filme.nome) < 0) // j < i --> j++
			j = j->prox;
		else if (strcmp(j->filme->info.filme.nome, i->filme->info.filme.nome) > 0) // j > i --> i++
			i = i->prox;
		else { // j = i --> comum++ e i++ e j++
			comum++;
			i = i->prox;
			j = j->prox;
		}
	}

	return comum;
}

void sugerir_similar(No **p, No **aluno, No ***max_no, int *max_comum){
	if (*p == NULL) return;

	sugerir_similar(&(*p)->esq, aluno, max_no, max_comum);

	if (p != aluno){
		int aux = filmes_fav_comum(p, aluno);

		if (aux >= *max_comum) {
			*max_no = p;
			*max_comum = aux;
		}
	}

	sugerir_similar(&(*p)->dir, aluno, max_no, max_comum);
}

int filmes_fav_diferente(No **p, No **q){
	int qtdP = filmes_fav_comum(p,p);
	int qtdQ = filmes_fav_comum(q,q);

	if (!qtdP) return 0;

	return qtdP - filmes_fav_comum(p,q);
}

void sugerir_diferente(No **p, No **aluno, No ***min_no, int *max_diferente){
    if (*p == NULL) return;

	sugerir_diferente(&(*p)->esq, aluno, min_no, max_diferente);

	if (p != aluno){
		int aux = filmes_fav_diferente(p, aluno);

		if (aux >= *max_diferente) {
			*min_no = p;
			*max_diferente = aux;
		}
	}

	sugerir_diferente(&(*p)->dir, aluno, min_no, max_diferente);
}

int carregar_arquivo(AVL **A, AVL **F){
    FILE *f = fopen("./src/entrada_sistema.txt", "r");

    char line[800];
    char *tok;
    No **p, **q;
    elem x;
    int aux = 1, test;

    while (fgets(line, 800, f) != NULL){
        line[strcspn(line, "\n")] = 0;

        tok = strtok(line, ";"); // tok = NOME_ALUNO
        x.info.aluno.nome = tok;

        if (tok != NULL){
            tok = strtok(NULL, ";"); // tok = NROUSP
            if (tok == NULL) // Tem nome mas nao tem NROUSP
                aux = 0;
            else {
                x.info.aluno.nroUSP = atoi(tok);

                x.tipo = Aluno;

                if (!inserir(&(*A)->raiz, &x))
                    aux = 0;
                else {
                    p = buscar(&(*A)->raiz, &x);
                    if (p == NULL)
                        aux = 0;
                    else {
                        while ((tok = strtok(NULL, ";")) != NULL){ // tok = FILME_FAV_i
                            x.info.filme.nome = tok;

                            x.tipo = Filme;

                            test = inserir(&(*F)->raiz, &x);
                            q = buscar(&(*F)->raiz, &x);

                            if (q != NULL){
                                if (!test) (*q)->info.filme.frequencia--;

                                if (inserir_filme_fav(&(*p)->info.aluno.filmes_fav, q) != 1)
                                    aux = 0;
                            }
                        }
                    }
                }
            }
        }
    }

    return aux;
}