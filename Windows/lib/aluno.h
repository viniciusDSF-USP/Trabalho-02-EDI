#include "filme.h"

int inserir_filme_fav(NoLista **p, No **filme);
int remover_filme_fav(NoLista **p, No **filme);
int limpar_filmes_fav(NoLista **p, No **raiz_filmes);

int filmes_fav_comum(No **p, No **q);
void sugerir_similar(No **p, No **aluno, No ***max_no, int *max_comum);
int filmes_fav_diferente(No **p, No **q);
void sugerir_diferente(No **p, No **aluno, No ***min_no, int *min_comum);

int carregar_arquivo(AVL **A, AVL **F);