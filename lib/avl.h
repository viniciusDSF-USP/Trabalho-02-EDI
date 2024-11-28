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