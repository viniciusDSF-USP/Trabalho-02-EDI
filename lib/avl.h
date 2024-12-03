#define STRLIM 100
#define TAB 12

typedef enum {Aluno, Filme} type;

typedef struct bloco No;

typedef struct blocoLista {
    No *filme;
    struct blocoLista *prox;
} NoLista;

typedef struct {
    No *ini;
} Lista;

typedef union {
    struct {
        char *nome;
        int nroUSP;
        NoLista *filmes_fav;
    } aluno;
    struct {
        char *nome;
        int frequencia;
    } filme;
} elem_union;

typedef struct {
	elem_union info;
	type tipo;
} elem;

struct bloco {
    elem_union info;
    type tipo;

    int FB, altura;
    struct bloco *esq, *dir;
};

typedef struct{
    No *raiz;
} AVL;

// Metodos

void finalizarLista(NoLista **p);

AVL *CriarAVL();
void FinalizarAVL(No **p);
No **buscar(No **p, elem *x);
int inserir(No **p, elem *x);
int remover(No **p, elem *x);
void imprimirAVL(AVL *A);
void imprimirGrafo(AVL *A);

/* Funcao para fazer a leitura dos 
usuarios a serem cadastrados e suas preferencias
a partir de um arquivo */
int inserir_de_arquivo(No **p, char *nome_arquivo); //Opcional

/* O usuario pode produzir um arquivo texto com
todas as informacoes armazenadas no sistema */
int salvar_sistema(AVL *p);

// Auxiliares dos dados tecnicos das arvores
//int altura(No *p);
//int numero_nos(No *p);
//int maior_fb(No *p);
int dados_tecnicos_arvores(AVL *A);

/*
Salvar Sistema: Percorre em ordem a arvore AVL de Alunos, depois a de Filmes e salva em um .txt;

Inserir de Arquivo: Lemos um arquivo que tenha "NOME;NRO_USP;FILME1;FILME2;FILME3;...;FILMEN",
 separados por ;. Depois, fazemos o mesmo procedimento de Inserir Aluno acima;
 */