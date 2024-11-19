#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "filme.h"

int inserir_aluno(No **p, elem *x){
    return;
} 

int remover_aluno(No **p, elem *x){
    return;
}

int inserir_filme_fav(No **raiz_aluno, elem *info_aluno, No **raiz_filme, elem *info_filme){
    return;
}

No *sugerir_similar(No *p, elem *x){
    return;
}

No *sugerir_inedito(No *p, elem *x){
    return;
}

int salvar_sistema(No *p){
    return;
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
    return;
}