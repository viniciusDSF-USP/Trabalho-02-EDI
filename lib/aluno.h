#include "filme.h"

Lista *CriarListaNroUSP();
int inserirListaNroUSP(No *raiz_filme, NoLista **p, elem *x);
int removerListaNroUSP(No *raiz_filme, NoLista **p, elem *x);

// p: Raiz da AVL Aluno

int inserir_aluno(No **p, elem *x, NoLista *s);
int remover_aluno(No **p, elem *x);

/* Indicar ao aluno 'x' um(1) colega de turma
que tenha varios filmes em comum
em sua lista de favoritos */
No *sugerir_similar(No *p, elem *x);

/* Indicar ao aluno 'x' um(1) colega de turma
que tenha poucos ou nenhum filme em comum
em sua lista de favoritos */
No *sugerir_inedito(No *p, elem *x);

/* O usuario pode produzir um arquivo texto com
todas as informacoes armazenadas no sistema */
int salvar_sistema(No *p);

int numero_alunos(No *p);

/* A altura eh um dos dados armazenados na struct AVL. Eh possivel acessa-la diretamente.
Nao eh necessario calcula-la (ela eh consequencia da adicao e remocao de nos na AVL).
Logo, a funcao abaixo eh OBSOLETA. Pode ser deletada */
//int altura_arvore(No *p);

int maior_FB(No *p);

/* Funcao para fazer a leitura dos 
usuarios a serem cadastrados e suas preferencias
a partir de um arquivo */
int inserir_de_arquivo(No **p, char *nome_arquivo); //Opcional

/*
Criar Lista: Cria uma Lista ordenada alfabeticamente pelo nome dos No de Filmes, com sentinela
 usando um No de Filme com nome = "\0", que sempre vai ser menor que qualquer elemento;

Inserir Lista: Busca na AVL de Filmes se tem o elemento, se ja tiver aumenta um na frequencia,
 se nao, insere na AVL de Filmes com inserir_filme();

Remover Lista: Busca na AVL de Filmes se tem o elemento, se ja tiver diminui um na frequencia.
 Se a frequencia virar zero, remove na AVL de Filmes com remover_filme();

Inserir Aluno: Insere na AVL de Aluno usando o inserir() do avl.h, concatenando o inicio da Lista
 no *filmes_fav;

Remover Aluno: Busca o aluno 'x' na arvore AVL de Alunos, se encontrar remove todos os filmes
 da Lista de filmes favoritos (usando o remover_filme() para cada NoLista), depois remove o No
 'x' encontrado da arvore AVL de Alunos, que vai usar remover() do avl.h;

Sugerir Similar: Busca o aluno 'x' na arvore AVL de Alunos, percorre a arvore ate encontrar
 alguem que tenha pelo menos um filme em comum com o aluno 'x'. Se tiver retorna esse aluno 'y';

Sugerir Inedito: Busca o aluno 'x' na arvore AVL de Alunos, percorre a arvore ate encontrar
 alguem que tenha zero filmes em comum com o aluno 'x'. Se tiver retorna essa aluno 'y';

Salvar Sistema: Percorre em ordem a arvore AVL de Alunos, depois a de Filmes e salva em um .txt;

Inserir de Arquivo: Lemos um arquivo que tenha "NOME|NRO_USP|FILME1;FILME2;FILME3;...;FILMEN",
 separamos NOME, NRO_USP, LISTA com o separador '|' e separamos os NoLista da Lista por ';'.
 Depois, fazemos o mesmo procedimento de Inserir Aluno acima;
*/