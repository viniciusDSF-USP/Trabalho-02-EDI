#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filme.h"

Lista *CriarListaFreq(){
    Lista *L = (Lista *) malloc(sizeof(Lista));

    if (L != NULL){        
        NoLista *head = (NoLista *) malloc(sizeof(NoLista));

        if (head != NULL){
            head->filme = NULL;
            head->prox = NULL;

            L->ini = head;
        } else {
            free(L);
            return 0;
        }
    }

    return L;
}

int LimparListaFreq(NoLista **p){
    if (*p == NULL)
        return 0;
    
    if ((*p)->prox == NULL){
        free(*p);
        *p = NULL;
        return 1;
    }

    return LimparListaFreq(&(*p)->prox);
}

int inserir_recursivo(NoLista *p, No **x){
    if (p == NULL)
        return -1;

    int aux = 0;

    if (p->filme == NULL){
        aux = inserir_recursivo(p->prox, x);

        if (aux == -1){
            NoLista *new = (NoLista *) malloc(sizeof(NoLista));

            if (new != NULL){
                new->filme = *x;
                new->prox = p->prox;

                p->prox = new;
            } else
                return 0;
            
            return 1;
        }

        return aux;
    }

    if (p->filme->info.filme.frequencia < (*x)->info.filme.frequencia-1)
        return -1;
    else if (p->filme->info.filme.frequencia > (*x)->info.filme.frequencia-1) {
        aux = inserir_recursivo(p->prox, x);

        if (aux == -1){
            NoLista *new = (NoLista *) malloc(sizeof(NoLista));

            if (new != NULL){
                new->filme = *x;
                new->prox = p->prox;

                p->prox = new;
            } else
                return 0;
            
            return 1;
        }

        return aux;
    } else
        return inserir_recursivo(p->prox, x);
}

int inserirListaFreq(No **F, NoLista *p){
    if (*F == NULL)
        return 1;

    inserirListaFreq(&(*F)->esq, p);

    if (inserir_recursivo(p, F) != 1)
        return 0;

    inserirListaFreq(&(*F)->dir, p);

    return 1;
}

void mais_queridos(No **F){
    Lista *L = CriarListaFreq();

    if (L != NULL){
        if (inserirListaFreq(F, L->ini)){
            NoLista *p = L->ini->prox;

            if (p == NULL)
                printf("Nao ha filmes cadastrados.");
            else{
                while (p != NULL){
                    printf("\tCitado %d vezes: %s", p->filme->info.filme.frequencia, p->filme->info.filme.nome);

                    if (p->prox != NULL)
                        printf("\n");
                    
                    p = p->prox;
                }
            }

            LimparListaFreq(&L->ini);
        } else
            printf("Erro ao ordenar a lista!");
    } else
        printf("Erro ao criar a lista!");
}