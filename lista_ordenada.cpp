#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct {
    char nome[20];
    int codigo;
    int quantidade;
    double preco;
} t_produto;


typedef struct {
    int max;
    int n;
    t_produto *itens;
} t_lista;




t_lista* criarLista(int tam) {
    t_lista *lista = (t_lista *) malloc(sizeof(t_lista));
    lista->max = tam;
    lista->n = 0;
    lista->itens = (t_produto *) malloc(sizeof(t_produto) * tam);
    return lista;
}

int tamanho(t_lista *lista) {
    return lista->n;
}

int cheia(t_lista *lista) {
    if (lista->n == lista->max) {
        return 1;
    }
    return 0;
}

int vazia(t_lista *lista) {
    if (lista->n == 0) {
        return 1;
    }
    return 0;
}

int inserirFim(t_lista *lista, t_produto elem) {
    if (!cheia(lista)) {
        lista->itens[lista->n] = elem;
        lista->n++;
        return 1;
    }
    return 0;
}

int inserirIndice(t_lista *lista, int indice, t_produto elem) {
    if (!cheia(lista) && (indice < lista->n)) {
        for (int i = lista->n - 1; i >= indice; i--) {
            lista->itens[i + 1] = lista->itens[i];
        }
        lista->itens[indice] = elem;
        lista->n++;
        (*lista).n;
        return 1;
    }
    return 0;
}

////


int buscarProduto(t_lista *lista, int codigo) {
    for (int i = 0; i < lista->n; i++) {
        if (lista->itens[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}


int adicionarProduto(t_lista *lista, char nome[], int codigo, int quantidade, double preco){
	int indice = buscarProduto(lista, codigo);
	t_produto novoProduto;
	
	if(indice == -1){
		strcpy(novoProduto.nome, nome);
		novoProduto.codigo = codigo;
		novoProduto.quantidade = quantidade;
		novoProduto.preco = preco;
		inserirFim(lista, novoProduto);
		return 1;
	}
	return 0;
}


int excluirProduto(t_lista *lista, int codigo) {
    int indice = buscarProduto(lista, codigo);

    if (indice != -1) {
        // Move os elementos seguintes uma posição para a esquerda
        for (int i = indice; i < (lista->n - 1); i++) {
            lista->itens[i] = lista->itens[i + 1];
        }
        // Reduz o número de produtos no vetor
        (lista->n)--;
        return 1;
    } else {
        return 0;
    }
}

int alterarProduto(t_lista *lista, int codigo, char newNome[20], int newQuantidade, double newPreco){
	int indice = buscarProduto(lista, codigo);
	char LIXO[2];
	
	if(indice != -1){
		strcpy(lista->itens[indice].nome, newNome);
		lista->itens[indice].quantidade = newQuantidade;
		lista->itens[indice].preco = newPreco;
		return 1;
	}else{
		return 0;
	}
	
}

t_produto* consultarUmProduto(t_lista *lista, int codigo){
	int indice = buscarProduto(lista, codigo);
	
	if(indice != -1){
		
		return &lista->itens[indice];
	}else{
		return NULL;
	}
}

int ordenarPorNome(t_lista *lista) {
    t_produto ordenar;

	if(!vazia(lista)){
	    for (int i = 0; i < lista->n - 1; i++) {
	        for (int j = i + 1; j < lista->n; j++) {
	            if (strcmp(lista->itens[i].nome, lista->itens[j].nome) > 0) {
	                // Trocar os produtos
	                ordenar = lista->itens[i];
	                lista->itens[i] = lista->itens[j];
	                lista->itens[j] = ordenar;
	            }
	        }
	    }
	    return 1;
	}
	return 0;
}

int ordenarPorCodigo(t_lista *lista){
	t_produto ordenar;
	
	if(!vazia(lista)){
		for (int i = 0; i < lista->n - 1; i++) {
	        for (int j = i + 1; j < lista->n; j++) {
	            if(lista->itens[i].codigo > lista->itens[j].codigo) {
	                // Trocar os produtos
	                ordenar = lista->itens[i];
	                lista->itens[i] = lista->itens[j];
	                lista->itens[j] = ordenar;
	            }
	        }
	    }
	    return 1;
	}
	return 0;
}


int ordenarPorQuantidade(t_lista *lista){
	t_produto ordenar;
	
	if(!vazia(lista)){
		for (int i = 0; i < lista->n - 1; i++) {
	        for (int j = i + 1; j < lista->n; j++) {
	            if(lista->itens[i].quantidade > lista->itens[j].quantidade) {
	                // Trocar os produtos
	                ordenar = lista->itens[i];
	                lista->itens[i] = lista->itens[j];
	                lista->itens[j] = ordenar;
	            }
	        }
	    }
	    return 1;
	}
	return 0;
}

int ordenarPorPreco(t_lista *lista){
	t_produto ordenar;
	
	if(!vazia(lista)){
		for (int i = 0; i < lista->n - 1; i++) {
        	for (int j = i + 1; j < lista->n; j++) {
            	if(lista->itens[i].preco > lista->itens[j].preco) {
                // Trocar os produtos
                	ordenar = lista->itens[i];
                	lista->itens[i] = lista->itens[j];
                	lista->itens[j] = ordenar;
            	}
        	}
    	}
    	return 1;
	}
	return 0;
}


int verificarEstoqueBaixo(t_lista *lista) {
	int flag = 1;
	
	if(!vazia(lista)){
		for (int i = 0; i < lista->n; i++) {
	        if (lista->itens[i].quantidade < 5) {
	            printf("\nAVISO: Produto '%s' (Codigo %d) esta com estoque baixo (Quantidade: %d).\n",
	                   lista->itens[i].nome, lista->itens[i].codigo, lista->itens[i].quantidade);
	                   flag = 2;
	        	}
    	}
    	if(flag){
    		return 1;
		}else{
			return 2;
		}
	}
    return 0;
}

void salvarDados(t_lista *lista) {
    FILE *arquivo = fopen("dados.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < lista->n; i++) {
        fprintf(arquivo, "%s %d %d %lf\n", lista->itens[i].nome, lista->itens[i].codigo, lista->itens[i].quantidade, lista->itens[i].preco);
    }

    fclose(arquivo);
}

void carregarDados(t_lista *lista) {
    FILE *arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo nao encontado.\n");
        return;
    }

    while (!feof(arquivo)) {
        t_produto novoProduto;
        if (fscanf(arquivo, "%s %d %d %lf", novoProduto.nome, &novoProduto.codigo, &novoProduto.quantidade, &novoProduto.preco) == 4) {
            inserirFim(lista, novoProduto);
        }
    }

    fclose(arquivo);
}



int main() {
    t_lista *lista;
    lista = criarLista(3);
    carregarDados(lista);
    
    int opcao, opcao_sub_menu;
    char nome[20];
    int codigo, quantidade;
    double preco;
    
    int adicionar, alterar, excluir;
    t_produto *consultar;
    
    int estoque, ordenarNome, ordenarCodigo, ordenarQuant, ordenarPreco;
    
    char LIXO[2];
    

    do {
        printf("\n\n----------MENU PRINCIPAL----------");
        printf("\nSubmenu de Produtos..............1");
        printf("\nSubmenu de Relatorios............2");
        printf("\nSair do Programa.................3");
        printf("\nEscolha uma opcao: ");
        scanf("%d%*c", &opcao);
        printf("\n");

        switch (opcao) {
            case 1:
                do {
                    printf("\n\n--------SUBMENU PRODUTOS-------");
                    printf("\nAdicionar Produto..............1");
                    printf("\nAlterar Produto................2");
                    printf("\nExcluir Produto................3");
                    printf("\nConsultar Produto..............4");
                    printf("\nVoltar ao Menu Principal.......5\n");
                    printf("\nEscolha uma opcao: ");
                    scanf("%d%*c", &opcao_sub_menu);
                    printf("\n");

                    switch (opcao_sub_menu) {
                        case 1:
                            printf("\nDigite o nome do produto: ");
                            gets(nome);
                            printf("\nDigite o codigo do produto: ");
                            scanf("%d", &codigo);
                            printf("\nDigite a quantidade do produto: ");
                            scanf("%d", &quantidade);
                            printf("\nDigite o preco do produto: ");
                            scanf("%lf", &preco);
                            
                            adicionar = adicionarProduto(lista, nome, codigo, quantidade, preco);
                            
                            if(adicionar == 0){
                                printf("\n Ja existe um produto com esse codigo!");
                            } else {
                                printf("\nProduto adicionado na lista com sucesso.");
                            }
                            salvarDados(lista);
                            break;
                        case 2:
                            printf("\nDigite o codigo do produto: ");
                            scanf("%d", &codigo);
                            gets(LIXO);
                            printf("\nDigite o novo nome do produto: ");
                            gets(nome);
                            printf("\nDigite a nova quantidade do produto: ");
                            scanf("%d", &quantidade);
                            printf("\nDigite o novo preco do produto: ");
                            scanf("%lf", &preco);
                            
                            alterar = alterarProduto(lista, codigo, nome, quantidade, preco);
                            
                            if(alterar == 0){
                                printf("\n Nao existe um produto com esse codigo!");
                            } else {
                                printf("\nProduto alterado com sucesso.");
                            }
                            salvarDados(lista);
                            
                            break;
                        case 3:
                            printf("\nDigite o codigo do produto: ");
                            scanf("%d", &codigo);
                            
                            excluir = excluirProduto(lista, codigo);
                            
                            if(excluir == 0){
                                printf("\n Nao existe um produto com esse codigo!");
                            } else {
                                printf("\nProduto removido com sucesso.");
                            }
                            salvarDados(lista);
                            break;
                        case 4:
                            printf("\nDigite o codigo do produto: ");
                            scanf("%d", &codigo);
                            
                            consultar = consultarUmProduto(lista, codigo);
                            
                            if(consultar == NULL){
                                printf("\n Nao existe um produto com esse codigo!");
                            } else {
                                printf("\n Nome do produto: %s", consultar->nome);
                                printf("\n Codigo do produto: %d", consultar->codigo);
                                printf("\n Quantidade: %d", consultar->quantidade);
                                printf("\n Preco: %lf", consultar->preco);
                            }
                            break;
                        case 5:
                            printf("Voltar ao menu principal...\n");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                    }
                } while (opcao_sub_menu != 5);
                break;
            case 2:
                do {
                    printf("\n\n--------SUBMENU RELATORIOS--------");
                    printf("\nListar Produtos com Estoque baixo.......1");
                    printf("\nListar Produto por Nome.................2");
                    printf("\nListar Produto por Codigo...............3");
                    printf("\nListar Produto por Quantidade...........4");
                    printf("\nListar Produto por Preco................5");
                    printf("\nVoltar ao Menu Principal........6\n");
                    printf("\nEscolha uma opcao: ");
                    scanf("%d%*c", &opcao_sub_menu);
                    printf("\n");

                    switch (opcao_sub_menu) {
                        case 1:                         
                            estoque = verificarEstoqueBaixo(lista);
                            
                            if(estoque == 0){
                                printf("\nNao tem produtos no estoque.");
                            }if(estoque == 2){
                                printf("\nNenhum produto esta abaixo do estoque minimo.");
                            }
                            break;
                        case 2:
                             ordenarNome = ordenarPorNome(lista);
                            
                            if(ordenarNome == 0){
                                printf("\nNao tem produtos na lista.");
                            } else {
                                for(int i = 0; i < lista->n ; i++){
                                    printf("\nNome do produto: %s", lista->itens[i].nome);
                                    printf("\nCodigo: %d", lista->itens[i].codigo);
                                    printf("\nQuantidade: %d", lista->itens[i].quantidade);
                                    printf("\nPreco: %lf\n", lista->itens[i].preco);
                                }
                            }
                            break;
                        case 3:
                              ordenarCodigo = ordenarPorCodigo(lista);
                            
                            if(ordenarCodigo == 0){
                                printf("\nNao tem produtos na lista.");
                            } else {
                                for(int i = 0; i < lista->n; i++){
                                    printf("\nCodigo: %d", lista->itens[i].codigo);
                                    printf("\nNome do produto: %s", lista->itens[i].nome);
                                    printf("\nQuantidade: %d", lista->itens[i].quantidade);
                                    printf("\nPreco: %lf\n", lista->itens[i].preco);
                                }
                            }
                            break;
                        case 4:
                             ordenarQuant = ordenarPorQuantidade(lista);
                            
                            if(ordenarQuant == 0){
                                printf("\nNao tem produtos na lista.");
                            } else {
                                for(int i = 0; i < lista->n; i++){
                                    printf("\nQuantidade: %d", lista->itens[i].quantidade);
                                    printf("\nCodigo: %d", lista->itens[i].codigo);
                                    printf("\nNome do produto: %s", lista->itens[i].nome);
                                    printf("\nPreco: %lf\n", lista->itens[i].preco);
                                }
                            }
                            break;
                        case 5:
                             ordenarPreco = ordenarPorPreco(lista);
                            
                            if(ordenarPreco == 0){
                                printf("\nNao tem produtos na lista.");
                            } else {
                                for(int i = 0; i < lista->n; i++){
                                    printf("\nPreco: %lf", lista->itens[i].preco);
                                    printf("\nQuantidade: %d", lista->itens[i].quantidade);
                                    printf("\nCodigo: %d", lista->itens[i].codigo);
                                    printf("\nNome do produto: %s\n", lista->itens[i].nome);
                                }
                            }
                            break;
                        case 6:
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                    }
                } while (opcao_sub_menu != 6);
                break;
        }
    } while (opcao != 3);
    	free(lista->itens);
    	free(lista);
    return 0;
}


