#include <stdio.h>
#include <stdlib.h>
#include "lib/aluno.h"

int main(){
    AVL *Filmes = CriarAVL();
    elem x;

    x.filme.nome = "B";
    inserir_filme(&Filmes->raiz, &x);

    x.filme.nome = "D";
    inserir_filme(&Filmes->raiz, &x);

    x.filme.nome = "C";
    inserir_filme(&Filmes->raiz, &x);

    x.filme.nome = "E";
    inserir_filme(&Filmes->raiz, &x);

    x.filme.nome = "A";
    inserir_filme(&Filmes->raiz, &x);

    x.filme.nome = "F";
    inserir_filme(&Filmes->raiz, &x);

    imprimirAVL(Filmes);
    imprimirGrafo(Filmes);

    x.filme.nome = "C";
    remover_filme(&Filmes->raiz, &x);

    imprimirAVL(Filmes);
    imprimirGrafo(Filmes);

    x.filme.nome = "E";
    inserir_filme(&Filmes->raiz, &x);

    x.filme.nome = "E";
    inserir_filme(&Filmes->raiz, &x);

    x.filme.nome = "F";
    inserir_filme(&Filmes->raiz, &x);

    x.filme.nome = "C";
    inserir_filme(&Filmes->raiz, &x);

    imprimirAVL(Filmes);
    imprimirGrafo(Filmes);

    return 0;
}