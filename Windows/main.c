#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/aluno.h"

#define MAX_INT 0x7FFFFFFF

void menu00(){
	printf("\t    Amigos de Graduacao Indo ao Cinema\n");
	printf("\t==========================================\n");
	printf("\tCody Stefano Barham Setti ........  4856322\n");
	printf("\tLuis Henrique de Queiroz Veras ... 14592414\n");
	printf("\tRaphael Mendes Batista ........... 15497660\n");
	printf("\tVinicius de Sa Ferreira .......... 15491650\n\n");

	printf("+===+===================+\n");
	printf("| 0 | Sair              |\n");
	printf("| 1 | Entrar no sistema |\n");
	printf("+===+===================+\n");
	printf("Escolha: ");
}

void menu01(int modo){
	printf("+====+===============================+\n");
	printf("|  0 | Sair                          |\n");
	printf("|  1 | Cadastrar aluno               |\n");
	printf("|  2 | Remover cadastro de aluno     |\n");
	printf("|  3 | Adicionar filme predileto     |\n");
	printf("|  4 | Remover filme predileto       |\n");
	printf("|  5 | Listar alunos cadastrados     |\n");
	printf("|  6 | Buscar aluno                  |\n");
	printf("|  7 | Listar filmes cadastrados     |\n");
	printf("|  8 | Buscar filme                  |\n");
	printf("|  9 | Indicar colega similar        |\n");
	printf("| 10 | Indicar colega diferente      |\n");
	printf("| 11 | Salvar arquivo                |\n");
	printf("| 12 | Mostrar dados das arvores     |\n");
	printf("| 13 | Listar filmes mais citados    |\n");
	printf("| 14 | Cadastrar a partir de arquivo |\n");
	printf("| 15 | Finalizar todos os dados      |\n");
	printf("| 16 | Limpar a tela                 |\n");
	printf("| 17 | Modo de visualizacao (%s) |\n", modo == 0 ? "Listas" : "Arvore");
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
	NoLista *r;
	int modo = 0, comum, diferente;
	FILE *f;
    
    choice = -1;
    while(choice){
		choice = -1;

    	menu01(modo);
    	if (scanf("%d", &choice) != 1){
			while (getchar() != '\n'); // Limpa o buffer
		}
    	printf("\n");
    	
    	if (choice > 0 && choice <= 17) system("cls");
    	
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

						if (inserir_filme_fav(&(*p)->info.aluno.filmes_fav, q) == 1)
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
	    			if (modo == 0) imprimirAVL(Alunos);
					else imprimirGrafo(Alunos);
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
    			if (p != NULL){
    				printf("\nAluno encontrado:\n\n");
					printf("\t            Nome: %s\n", (*p)->info.aluno.nome);
					printf("\t      Numero USP: %d\n", (*p)->info.aluno.nroUSP);
					printf("\tFilmes favoritos: {");

					r = (*p)->info.aluno.filmes_fav->prox;
					while (r != NULL){
						printf("%s", r->filme->info.filme.nome);

						if (r->prox != NULL)
							printf(", ");
						r = r->prox;
					}

					printf("}");
				} else
    				printf("Aluno nao encontrado!");
    			
    			break;
    		
    		case 7: // Listar filmes cadastrados
    			if (Filmes->raiz != NULL){
	    			printf("Filmes cadastrados:\n");
	    			if (modo == 0) imprimirAVL(Filmes);
					else imprimirGrafo(Filmes);
	    		} else
					printf("Nao ha filmes cadastrados.");
	    		
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
    		
    		case 9: // Indicar colega similar
				printf("Indicar colega similar\n\n");
    			printf("\tNumero USP: ");
    			if (scanf("%d", &x.info.aluno.nroUSP) != 1){
					while (getchar() != '\n'); // Limpa o buffer
					printf("Aluno nao encontrado!");
					break;
				}
    			
    			x.tipo = Aluno;
    			
    			p = buscar(&Alunos->raiz, &x);
    			if (p != NULL){
					q = NULL;
					comum = 0;

    				sugerir_similar(&Alunos->raiz, p, &q, &comum);

					if (q != NULL){
						if (comum != 0 && filmes_fav_comum(q, q) != 0){
							printf("\nSugestao:\n");
							printf("\t            Nome: %s\n", (*q)->info.aluno.nome);
							printf("\t      Numero USP: %d\n", (*q)->info.aluno.nroUSP);
							printf("\tFilmes favoritos: {");

							NoLista *aux = (*q)->info.aluno.filmes_fav->prox;
							while (aux != NULL){
								printf("%s", aux->filme->info.filme.nome);

								if (aux->prox != NULL)
									printf(", ");
								aux = aux->prox;
							}

							printf("} (%d em comum!)", comum);
						} else
							printf("Nao ha nenhum aluno com algum filme similar!");
					} else
						printf("Nao ha nenhum outro aluno cadastrado!");
				} else
    				printf("Aluno nao encontrado!");

    			break;
    		
    		case 10: // Indicar colega diferente
				printf("Indicar colega diferente\n\n");
    			printf("\tNumero USP: ");
    			if (scanf("%d", &x.info.aluno.nroUSP) != 1){
					while (getchar() != '\n'); // Limpa o buffer
					printf("Aluno nao encontrado!");
					break;
				}
    			
    			x.tipo = Aluno;
    			
    			p = buscar(&Alunos->raiz, &x);
    			if (p != NULL){
					q = NULL;
					diferente = 0;

    				sugerir_diferente(&Alunos->raiz, p, &q, &diferente);

					if (q != NULL){
						if (diferente != 0){
							printf("\nSugestao de colega com filmes diferentes:\n");
							printf("\t            Nome: %s\n", (*q)->info.aluno.nome);
							printf("\t      Numero USP: %d\n", (*q)->info.aluno.nroUSP);
							printf("\tFilmes favoritos: {");

							NoLista *aux = (*q)->info.aluno.filmes_fav->prox;
							while (aux != NULL){
								printf("%s", aux->filme->info.filme.nome);

								if (aux->prox != NULL)
									printf(", ");
								aux = aux->prox;
							}

							if (diferente != 0)
								printf("} (%d diferentes!)", diferente);
							else
								printf("} (nenhum em comum!)");
						} else
							printf("Nao ha nenhum aluno com algum filme diferente!");
					} else
						printf("Nao ha nenhum outro aluno cadastrado!");
				} else
    				printf("Aluno nao encontrado!");

    			break;
    		
    		case 11: // Salvar arquivo
				if (salvar_sistema(Alunos))
					printf("Salvo com sucesso!");
				else
					printf("Erro ao salvar!");

    			break;
    		
    		case 12: // Mostrar dados das arvores
				if (!imprimir_dadosAVL(Alunos))
					printf("Nao ha alunos cadastrados.");
				
				printf("\n\n");

				if (!imprimir_dadosAVL(Filmes))
					printf("Nao ha filmes cadastrados.");

    			break;
    		
    		case 13: // Listar filmes mais citados
				printf("Filmes mais citados:\n\n");
				mais_queridos(&Filmes->raiz);

    			break;
    		
    		case 14: // Cadastrar a partir de arquivo
				f = fopen("./src/entrada_sistema.txt", "a");
				fclose(f);

				printf("Insira os dados em 'src/entrada_sistema.txt' da seguinte forma:\n");
				printf("\tNOME_ALUNO_1;NROUSP_1;FILME_FAV_1;FILME_FAV_2;FILME_FAV_3;...;FILME_FAV_N\n");
				printf("\tNOME_ALUNO_2;NROUSP_3;FILME_FAV_1;FILME_FAV_2;FILME_FAV_3;...;FILME_FAV_N\n");
				printf("\t...\n\n");
				printf("\tPressione qualquer tecla para continuar... ");

				getchar();
				fgets(string, STRLIM, stdin);

				printf("\n");

				if (carregar_arquivo(&Alunos, &Filmes))
					printf("Dados carregados com sucesso!");
				else
					printf("Houve um erro ao carregar os dados!");

    			break;
    		
    		case 15: // Finalizar todos os dados
    			FinalizarAVL(&Alunos->raiz);
    			FinalizarAVL(&Filmes->raiz);
    			
    			printf("Dados apagados com sucesso!");
    			
    			break;
    		
    		case 16:
				system("cls");

    			break;

			case 17: //  Modo de visualizacao
				modo = !modo;

				printf("Modo alterado com sucesso!");

				break;
    		
    		default:
    			printf("Opcao Invalida!");
    			
    			break;
    		
    	}
    	
    	if (choice != 16) printf("\n\n");
    }
    
    return 0;
}