#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

Lista *CriarListaNroUSP(){
    return NULL;
}

int inserirListaNroUSP(No *raiz_filme, NoLista **p, elem *x){
    return 0;
}

int removerListaNroUSP(No *raiz_filme, NoLista **p, elem *x){
    return 0;
}

int inserir_aluno(No **p, elem *x, NoLista *s){
    return 0;
}

int remover_aluno(No **p, elem *x){
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