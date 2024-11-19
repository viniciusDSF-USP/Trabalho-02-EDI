#include <avl.h>
#include <filme.h>

// p: Raiz da AVL Aluno

int inserir_aluno(No **p, elem *x); // Usa o 'inserir' do avl.h 
int remover_aluno(No **p, elem *x); // Usa o 'remover' do avl.h
int inserir_filme_fav(No **raiz_aluno, elem *info_aluno, No **raiz_filme, elem *info_filme); // Usa o 'buscar' do avl.h e 'inserir_filme' do filme.h

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