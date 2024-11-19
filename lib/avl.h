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
} elem;

struct bloco {
    elem info;
    type tipo;

    int FB, altura;
    struct bloco *esq, *dir;
};

typedef struct{
    No *raiz;
} AVL;

// Metodos

AVL *CriarAVL();
void FinalizarAVL(No **p);
No **buscar(No **p, elem *x);
int inserir(No **p, elem *x, int tipo);
int remover(No **p, elem *x);
void imprimirAVL(AVL *A);
void imprimirGrafo(AVL *A);

void finalizarLista(NoLista **p);