typedef struct bloco No;

typedef struct blocoLista {
    No *filme;
    struct blocoLista *prox;
} NoLista;

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
    enum {Aluno, Filme} tipo;

    int FB, altura;
    struct bloco *esq, *dir;
};

typedef struct{
    No *raiz;
} AVL;

// Metodos

AVL *CriarAVL(int tipo);
void *FinalizarAVL(No **p, int tipo);
int EstaVazia(AVL *A);
No **buscar(No *p, elem *x);
int inserir(No **p, elem *x);
int remover(No **p, elem *x); // Proxima aula (26/Nov)
void imprimirAVL(AVL *A, int tipo);