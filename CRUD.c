#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<windows.h> // É para criar o CRUD

//struct
typedef struct Produto{
	char nome[15],descricao[30],uniMedida[10];
	int id, qtds;
}Produto;

//variaveis globais

Produto p; //Instância do Struct do Produto

 
//prototipos das funcoes do CRUD
void inclusao();
void alteracao();
void consulta();
void exclusao();

//Funcao para Buscar Produto já existente
int idProduto(int idBuscar){

	//Declaracao e inicializacao do arquivo
	FILE* arquivoProduto = fopen("./ex.dat","rb");
	int encontrou = FALSE;
	int test;
	//Executa a operação de pesquisa
	while(fread(&p,sizeof(Produto),1,arquivoProduto)){
		//Verifica se o produto já existe
		if(idBuscar==p.id){
				return 1;
			}
		}
		fclose(arquivoProduto);
		return 0;
}

//Funcao de inclusao dos dados no arquivo
void inclusao(){
	//char nome[15],descricao[30],uniMedida;
	//int id, qtds;
	char op;
	Produto p;
	int id, test=0;
	do{
		system("cls");
		printf("O codigo do produto:");
		scanf("%d",&id);
		setbuf(stdin, NULL);
		test=idProduto(id);
		if(test==1){
			printf("\n\tJa existe produto\n\n");
			system("pause");
		}
	}while(test==1);
	p.id=id;
	
	printf("Quantidade do Produto: ");
	scanf("%d",&p.qtds);
	setbuf(stdin, NULL);
	
	printf("Nome do Produto:");
	fgets(p.nome,15,stdin);
	setbuf(stdin, NULL);
	
	printf("Descricao do Produto:");
	fgets(p.descricao,30,stdin);
	setbuf(stdin, NULL);
	
	printf("A unidade de medida do Produto: ");
	fgets(p.uniMedida,10,stdin);
	setbuf(stdin, NULL);
	
	//Declaração do arquivo
	FILE* arquivoProduto;
	
	//Função que abre o arquivo
	//"ab" //Arquivo em Binario
	arquivoProduto = fopen("./ex.dat","ab");
	
	//Verifica se o arquivo existe ou está aberto
	if(arquivoProduto == NULL){
		printf("erro\n");
		exit(1);
	}
	
	//Função que escreve no arquivo o conteudo armazenado na variavel p-Produto
	fwrite(&p, sizeof(Produto), 1, arquivoProduto);
	
	//Função para fechar o arquivo
	fclose(arquivoProduto);
	printf("pressione enter");
	getchar();
	system("cls");
}

void consultaTodos(){
	
	system("cls");
	
	FILE* arquivoProduto = fopen("./ex.dat","rb"); 
	
	if(arquivoProduto==NULL){
		printf("\nNao ha nenhum produto cadastrado!\n");
	}
	
	while(fread(&p,sizeof(Produto),1,arquivoProduto)){
		printf("\n");
				printf("\nO codigo do produto:%d",p.id);
				printf("\nQuatidade do produto:%d",p.qtds);
				printf("\nNome do produto:%s",p.nome);
				printf("Descricao do produto:%s",p.descricao);
				printf("Unidade de medida:%s",p.uniMedida);
				printf("\n");
				printf("\n");
	}
	system("pause");
	//Fechar o arquivo
	fclose(arquivoProduto);
	printf("\n\n\nPressione qualquer tecla para voltar\n");
	getchar();
	system("cls");
}




//funcao de alteracao de dados do arquivo
void alteracao(){
	
	//Declaracao e inicializacao do arquivo
	FILE* arquivoProduto = fopen("./ex.dat","rb");
	int encontrou = FALSE;
	int idBuscar;
	
	printf("Codigo do produto que deseja alterar: \n");
	scanf("%d",&idBuscar);
	setbuf(stdin, NULL);
	//Executa a operação de pesquisa
	while(fread(&p,sizeof(Produto),1,arquivoProduto)){
		//Verifica se a matricula existe
		if(idBuscar==p.id){
			encontrou = TRUE;
			break;
		}
	}
	
	setbuf(stdin, NULL);
	
	//NAO ENCONTROU
	
	if(!encontrou){
		printf("nao encontrou\n");
		getchar();
		system("cls");
		return;
	}
	
	
	printf("Novos dados\n");
	
	printf("INFORME O CODIGO DO PRODUTO: ");
	scanf("%d",&p.id);
	setbuf(stdin, NULL);

	printf("INFORME A QUANTIDADE DO PRODUTO: ");
	scanf("%d",&p.qtds);
	setbuf(stdin, NULL);
	
	printf("INFORME O NOME DO PRODUTO");
	fgets(p.nome,15,stdin);
	setbuf(stdin, NULL);
	
	printf("INFORME A DESCRICAO DO PRODUTO: ");
	fgets(p.descricao,30,stdin);
	setbuf(stdin, NULL);
	
	printf("INFORME A UNIDADE DE MEDIDA: ");
	fgets(p.uniMedida,10,stdin);
	setbuf(stdin, NULL);
	
	
	FILE* arqAux = fopen("./exAux.dat","ab");
	rewind(arquivoProduto);
	
	if(arquivoProduto == NULL || arqAux == NULL){
		printf("erro\n");
	}
	else{
		//Executa a operação de pesquisa
		fwrite(&p,sizeof(Produto),1,arqAux);
		while(fread(&p,sizeof(Produto),1,arquivoProduto)){
			if(idBuscar!=p.id){
				fwrite(&p,sizeof(Produto),1,arqAux);
			}
		}
	}
	
	//Fecha o arquivo
	fclose(arquivoProduto);
	fclose(arqAux);
	
	//Remove o arquivo
	remove("./ex.dat");
	rename("./exAux.dat","./ex.dat");
	
	printf("pressione enter");
	getchar();
	system("cls");
}

void excluir(){
	
	system("cls");
	
	//Declaracao e inicializacao do arquivo
	Produto leituram;
	FILE* arquivoProduto = fopen("./ex.dat","rb");
	int encontrou = FALSE;
	int idBuscar;
	
	printf("Codigo do produto que deseja excluir: \n");
	scanf("%d",&idBuscar);
	setbuf(stdin, NULL);
	//Executa a operação de pesquisa
	while(fread(&p,sizeof(Produto),1,arquivoProduto)){
		//Verifica se a matricula existe
		if(idBuscar==p.id){
			fclose(arquivoProduto);
				excluirProduto(leituram);
			}
		}
		fclose(arquivoProduto);
	
	printf("Codigo do produto incorreto!\n");
	system("pause");
	system("cls");

}

void excluirProduto(Produto antigo){
	system("cls");
	FILE *arquivoProduto, *aux; Produto passar;
	
	arquivoProduto = fopen("./ex.dat","rb");
	aux = fopen("./exAux.dat","wb");
	
	while(fread(&passar,sizeof(Produto),1,arquivoProduto)){
		if(antigo.id!=passar.id){
			fwrite(&passar,sizeof(Produto),1,aux);
		}
	}fclose(arquivoProduto);
	fclose(aux);
	
	arquivoProduto = fopen("./ex.dat","wb");
	aux = fopen("./exAux.dat","rb");
	
	while(fread(&passar,sizeof(Produto),1,arquivoProduto)){
		fwrite(&passar,sizeof(Produto),1,arquivoProduto);
	}
	
	fclose(arquivoProduto);
	fclose(aux);
	
	printf("Dados apagados com sucesso!");
	getch();
	system("cls");
	main();
}
//funcao principal
int main(){
	system("cls");
	SetConsoleTitle("Controle de Estoque");
	
	int opcao;
		
	do{
		// menu 
		printf( " \t\t\t\t\t\t CRUD PARA ESTOQUE \t\t\n");
		printf("1- Cadastrar produto:\n");
		printf("2- Buscar todos os produtos\n");
		printf("3- Alterar dados do produto por codigo:\n");
		printf("4- Excluir dados do produto por codigo:\n");
		printf("6-SAIR:\n");
		scanf("%d",&opcao);
		setbuf(stdin, NULL);
		
		system("cls");
		
		switch(opcao){
			
		case 1:
			system("cls");
			inclusao();
			break;
		case 2:
			system("cls");
			consultaTodos();
			break;
		case 3:
			system("cls");
			alteracao();
			break;	
		case 4:
			system("cls");
			excluir();
			break;
		}
	}while(opcao != 0);
}
