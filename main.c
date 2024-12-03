#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/aluno.h"

void menu00(){
	printf("\t    Amigos de Graduacao Indo ao Cinema\n");
	printf("\t==========================================\n");
	printf("\tCody Stefano Barham Setti ........  4856322\n");
	printf("\tLuis Henrique de Queiroz Veras ... 14592414\n");
	printf("\tRaphael Mendes Batista ........... 15497660\n");
	printf("\tVinicius de Sa Ferreira .......... 15491650\n\n");

	printf("+===+===================+\n");
	printf("| 0 |       Sair        | (V)\n");
	printf("| 1 | Entrar no sistema | (V)\n");
	printf("+===+===================+\n");
	printf("Escolha: ");
}

void menu01(){
	printf("+====+===============================+\n");
	printf("|  0 |             Sair              | (V)\n");
	printf("|  1 |        Cadastrar aluno        | (V)\n");
	printf("|  2 |   Remover cadastro de aluno   | (V)\n");
	printf("|  3 |   Adicionar filme predileto   | (V)\n");
	printf("|  4 |    Remover filme predileto    | (V)\n");
	printf("|  5 |   Listar alunos cadastrados   | (V)\n");
	printf("|  6 |         Buscar aluno          | (V)\n");
	printf("|  7 |   Listar filmes cadastrados   | (V)\n");
	printf("|  8 |         Buscar filme          | (V)\n");
	printf("|  9 |    Indicar colega similar     | (X)\n");
	printf("| 10 |   Indicar colega diferente    | (X)\n");
	printf("| 11 |        Gerar arquivo          | (X)\n");
	printf("| 12 |   Mostrar dados das arvores   | (X)\n");
	printf("| 13 |   Listar filmes mais citados  | (X)\n");
	printf("| 14 | Cadastrar a partir de arquivo | (X)\n");
	printf("| 15 |    Finalizar todos os dados   | (V)\n");
	printf("| 16 |         Limpar a tela         | (V)\n");
	printf("+====+===============================+\n");
	printf("Escolha: ");
}

int main(){
    int choice = 0;
    menu00();
    if (scanf("%d", &choice) != 1){
		while (getchar() != '\n'); // Limpa o buffer
	}
    printf("\n");
    
    switch(choice){
    	case 1:
    		system("cls");
    		
    		break;
    		
    	default:
    		printf("Saindo...\n");
    		return 0;
    		
    		break;
    }
    
    AVL *Alunos = CriarAVL();
    AVL *Filmes = CriarAVL();
    char *string = (char *) malloc(STRLIM * sizeof(char));
    elem x;
    No **p, **q;
    
    choice = -1;
    while(choice){
		choice = -1;

    	menu01();
    	if (scanf("%d", &choice) != 1){
			while (getchar() != '\n'); // Limpa o buffer
		}
    	printf("\n");
    	
    	if (choice > 0 && choice <= 16) system("cls");
    	
    	switch(choice){
    		case 0: // Sair
    			printf("Saindo...\n");
    			return 0;
    			
    			break;
    		
    		case 1: // Cadastrar aluno
    			printf("Cadastrar aluno\n\n");
    			printf("\tNome do Aluno: ");
    			
    			getchar();
    			fgets(string, STRLIM, stdin);
    			string[strcspn(string, "\n")] = 0;
    			
    			x.info.aluno.nome = string;
    			
    			printf("\tNumero USP: ");
    			if (scanf("%d", &x.info.aluno.nroUSP) != 1){
					while (getchar() != '\n'); // Limpa o buffer
					printf("Erro ao cadastrar o aluno!");
					break;
				}
    			
    			x.tipo = Aluno;
    			
    			if (inserir(&Alunos->raiz, &x)){
    				printf("Aluno cadastrado com sucesso!");
    			} else {
    				printf("Erro ao cadastrar o aluno!");
    			}
    			
    			break;
    		
    		case 2: // Remover cadastro de aluno
    			printf("Remover cadastro de aluno\n\n");
    			printf("\tNumero USP: ");
    			if (scanf("%d", &x.info.aluno.nroUSP) != 1){
					while (getchar() != '\n'); // Limpa o buffer
					printf("Aluno nao cadastrado!");
					break;
				}
    			
    			x.tipo = Aluno;

				p = buscar(&Alunos->raiz, &x);
				
				if (p != NULL){
					limpar_filmes_fav(&(*p)->info.aluno.filmes_fav, &Filmes->raiz);
					
					if (remover(&Alunos->raiz, &x)){
						printf("Aluno removido com sucesso!");
					} else {
						printf("Erro ao remover o aluno!");
					}
				} else
					printf("Aluno nao cadastrado!");
    			
    			break;
    		
    		case 3: // Adicionar filme predileto
    			printf("Adicionar filme predileto\n\n");
    			printf("\tNumero USP: ");
    			
    			if (scanf("%d", &x.info.aluno.nroUSP) != 1){
					while (getchar() != '\n'); // Limpa o buffer
					printf("Aluno nao encontrado!");
					break;
				}
    			
    			x.tipo = Aluno;
    			
    			p = buscar(&Alunos->raiz, &x);
    			if (p != NULL){
    				printf("\tNome do filme: ");
    			
					getchar();
					fgets(string, STRLIM, stdin);
					string[strcspn(string, "\n")] = 0;
					
					x.info.filme.nome = string;
					
					x.tipo = Filme;

					int aux = inserir(&Filmes->raiz, &x);
					q = buscar(&Filmes->raiz, &x);
					
					if (q != NULL){
						if (!aux) (*q)->info.filme.frequencia--;

						if (inserir_filme_fav(&(*p)->info.aluno.filmes_fav, q))
    						printf("Filme adicionado com sucesso!");
    					else {
    						if (aux)
								remover(&Filmes->raiz, &x);
							
    						printf("Filme ja adicionado!");
    					}
					} else {
						printf("Erro ao adicionar o filme!");
					}
    			
    				
    			} else
    				printf("Aluno nao encontrado!");
    			
    			break;
    		
    		case 4: // Remover filme predileto
    			printf("Remover filme predileto\n\n");
    			printf("\tNumero USP: ");
    			
    			if (scanf("%d", &x.info.aluno.nroUSP) != 1){
					while (getchar() != '\n'); // Limpa o buffer
					printf("Aluno nao encontrado!");
					break;
				}
    			
    			x.tipo = Aluno;
    			
    			p = buscar(&Alunos->raiz, &x);
    			if (p != NULL){
    				printf("\tNome do filme: ");
    			
					getchar();
					fgets(string, STRLIM, stdin);
					string[strcspn(string, "\n")] = 0;
					
					x.info.filme.nome = string;
					
					x.tipo = Filme;
    			
					q = buscar(&Filmes->raiz, &x);
					
					if (q != NULL){
						if (remover_filme_fav(&(*p)->info.aluno.filmes_fav, q)){
							if ((*q)->info.filme.frequencia == 0){
								if (remover(&Filmes->raiz, &x))
									printf("Filme removido com sucesso!");
								else
									printf("Erro ao remover o filme!");
							} else {
								printf("Filme removido com sucesso!");
							}
						} else
							printf("Erro ao remover o filme!");
					} else
						printf("Filme nao encontrado!");
    			} else
    				printf("Aluno nao encontrado!");
    		
    			break;
    		
    		case 5: // Listar alunos cadastrados
    			if (Alunos->raiz != NULL){
    				printf("Alunos cadastrados:\n");
	    			imprimirAVL(Alunos);
    			} else
    				printf("Nao ha alunos cadastrados.");
	    		
    			break;
    		
    		case 6: // Buscar aluno
    			printf("Buscar aluno\n\n");
    			printf("\tNumero USP: ");
    			if (scanf("%d", &x.info.aluno.nroUSP) != 1){
					while (getchar() != '\n'); // Limpa o buffer
					printf("Aluno nao encontrado!");
					break;
				}
    			
    			x.tipo = Aluno;
    			
    			p = buscar(&Alunos->raiz, &x);
    			if (p != NULL)
    				printf("\nAluno encontrado:\n\t%s - %d", (*p)->info.aluno.nome, (*p)->info.aluno.nroUSP);
    			else
    				printf("Aluno nao encontrado!");
    			
    			break;
    		
    		case 7: // Listar filmes cadastrados
    			if (Filmes->raiz == NULL)
    				printf("Nao ha filmes cadastrados.");
    			else {
	    			printf("Filmes cadastrados:\n");
	    			imprimirAVL(Filmes);
	    		}
	    		
    			break;
    		
    		case 8: // Buscar filme
    			printf("Buscar filme\n\n");
    			printf("\tNome do filme: ");
    			
    			getchar();
    			fgets(string, STRLIM, stdin);
    			string[strcspn(string, "\n")] = 0;
    			
    			x.info.filme.nome = string;
    			
    			x.tipo = Filme;
    			
    			p = buscar(&Filmes->raiz, &x);
    			if (p != NULL)
    				printf("Filme encontrado! Citado %d vezes.", (*p)->info.filme.frequencia);
    			else
    				printf("Filme nao encontrado!");
    		
    			break;
    		
    		case 9:
    			break;
    		
    		case 10:
    			break;
    		
    		case 11:
    			break;
    		
    		case 12: // Mostrar dados das arvores
				if (!dados_tecnicos_arvores(Alunos))
					printf("Nao ha alunos cadastrados!");

				printf("\n");

				if (!dados_tecnicos_arvores(Filmes))
					printf("Nao ha filmes cadastrados!");
    			break;
    		
    		case 13:
    			break;
    		
    		case 14:
    			break;
    		
    		case 15: // Finalizar todos os dados
    			FinalizarAVL(&Alunos->raiz);
    			FinalizarAVL(&Filmes->raiz);
    			
    			printf("Dados apagados com sucesso!");
    			
    			break;
    		
    		case 16:
    			break;
    		
    		default:
    			printf("Opcao Invalida!");
    			
    			break;
    		
    	}
    	
    	if (choice != 16) printf("\n\n");
    }
    
    return 0;
}