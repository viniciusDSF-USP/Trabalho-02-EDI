#include "avl.h"

Lista *CriarListaFreq();
int inserirListaFreq(No *raiz_filme, NoLista **p, elem *x);

// p: Raiz da AVL Filme

int inserir_filme(No **p, elem *x); // Usa o 'inserir' do avl.h
int remover_filme(No **p, elem *x); // Usa o 'remover' do avl.h
void mais_queridos(); // Ordena a AVL em uma Lista por frequencia

/*
Criar Lista por Frequencia: Cria uma Lista ordenada pela maior frequencia ate a menor,
 com sentinela No de Filme com frequencia = MAX_INT, que sempre vai ser maior que
 qualquer elemento;

Inserir Lista por Frequencia: Insere ordenado do com maior frequencia para o de menor;

Inserir Filme: Insere na AVL de Filme usando o inserir() do avl.h;

Remover Filme: Insere na AVL de Filme usando o inserir() do avl.h;

Mais Queridos: Percorre a arvore AVL de Filme, inserindo na Lista, depois mostra a Lista,
 que vai estar ordenada do com maior frequencia para o com menor, depois limparLista();
*/