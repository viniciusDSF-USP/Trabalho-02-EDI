#include "filme.h"

int inserir_filme_fav(NoLista **p, No **filme);
int remover_filme_fav(NoLista **p, No **filme);
int limpar_filmes_fav(NoLista **p, No **raiz_filmes);

// p: Raiz da AVL Aluno

/* Indicar ao aluno 'x' um(1) colega de turma
que tenha varios filmes em comum
em sua lista de favoritos */
No *sugerir_similar(AVL *arvore, int nroUSP);

/* Indicar ao aluno 'x' um(1) colega de turma
que tenha poucos ou nenhum filme em comum
em sua lista de favoritos */
No *sugerir_diferente(No *p, elem *x);

int numero_alunos(No *p);

/* A altura eh um dos dados armazenados na struct AVL. Eh possivel acessa-la diretamente.
Nao eh necessario calcula-la (ela eh consequencia da adicao e remocao de nos na AVL).
Logo, a funcao abaixo eh OBSOLETA. Pode ser deletada */
//int altura_arvore(No *p);

int maior_FB(No *p);

/*
Criar Lista: Cria uma Lista ordenada alfabeticamente pelo nome dos No de Filmes, com sentinela
 usando um No de Filme com nome = "\0", que sempre vai ser menor que qualquer elemento;

Inserir Lista: Busca na AVL de Filmes se tem o elemento, se ja tiver aumenta um na frequencia,
 se nao, insere na AVL de Filmes com inserir_filme();

Remover Lista: Busca na AVL de Filmes se tem o elemento, se ja tiver diminui um na frequencia.
 Se a frequencia virar zero, remove na AVL de Filmes com remover_filme();

Sugerir Similar: Busca o aluno 'x' na arvore AVL de Alunos, percorre a arvore ate encontrar
 alguem que tenha pelo menos um filme em comum com o aluno 'x'. Se tiver retorna esse aluno 'y';

Sugerir Diferente: Busca o aluno 'x' na arvore AVL de Alunos, percorre a arvore ate encontrar
 alguem que tenha zero filmes em comum com o aluno 'x'. Se tiver retorna essa aluno 'y';
*/