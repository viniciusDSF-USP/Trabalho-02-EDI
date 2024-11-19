#include <avl.h>

// p: Raiz da AVL Filme

int inserir_filme(No *p, NoLista *q); // Usa o 'inserir' do avl.h e faz enquanto a Lista nao acabar
int remover_filme(No *p, elem *x); // Usa o 'remover' do avl.h
void mais_queridos(No *p); // Ordena a AVL em uma Lista por frequencia