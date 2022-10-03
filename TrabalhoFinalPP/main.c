#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cliente{
        char nome_cliente[100];
        char cidade[100];
        float valor_frete;
} Cliente;

typedef struct Produto{
        char nome_produto[100];
        int codigo_produto;
        float valor;
} Produto;

typedef struct Data{
    int dia, mes, ano;
} Data;

typedef struct Venda{
    Data data_venda;
    Cliente cliente_venda;
    int qtd_produtos;
    Produto produto_venda[100];
    float valor_total_com_frete;
    char forma_pagamento[100];
    float valorFinalVenda;
} Venda;

void menu(){
    int aux = 1;
    int opcao;

            while (aux != 0)
            {
                system("cls");
                printf("Escolha uma opcao do menu :\n");
                printf(" [1] - Cadastrar cliente\n");
                printf(" [2] - Cadastrar produto\n");
                printf(" [3] - Verificar cadastros clientes\n");
                printf(" [4] - Verificar cadastros produtos\n");
                printf(" [5] - Registrar venda\n");
                printf(" [6] - Exibir vendas de 2022\n");
                printf(" [7] - Sair\n");

                scanf("%d", &opcao);

                switch (opcao)
                {
                    case 1:
                        system("cls");
                        printf("\n\tCadastrando novo cliente:");
                        printf("\n__________________________________________________________\n");
                        cadastroCliente();

                        getch();
                        break;

                    case 2:
                        system("cls");
                        printf("\n\tCadastrando novo produto:");
                        printf("\n__________________________________________________________\n");
                        cadastroProduto();

                        getch();
                        break;

                    case 3:
                        system("cls");
                        printf("\n\tVerificando cadastros de clientes:");
                        printf("\n__________________________________________________________\n");
                        verificaCadastro();

                        getch();
                        break;

                    case 4:
                        system("cls");
                        printf("\n\tVerificando cadastros de produtos:");
                        printf("\n__________________________________________________________\n");
                        verificaProduto();

                        getch();
                        break;

                    case 5:
                        system("cls");
                        printf("\n\tRegistrando nova venda:");
                        printf("\n__________________________________________________________\n\n");
                        registrarVenda();

                        getch();
                        break;

                    case 6:
                        system("cls");
                        printf("\n\tVendas Realizadas no ano de 2022");
                        printf("\n\n__________________________________________________________\n");
                        pergunta();

                        getch();
                        break;

                    case 7:
                        exit(0);
                        break;

                    default:
                        printf("Favor selecionar uma das opcoes mostradas no menu\n");
                        break;
                }
            }

}


void cadastroCliente (){
    Cliente cliente;
    FILE *arq ;
    arq = fopen("cadastroClientes.dat", "ab");

    if(arq == NULL){
        printf("ERRO - Falha ao abrir arquivo.");
        exit(1);
    }
    else{
        printf ("\nDigite o nome do cliente: ");
        fflush(stdin);
        fgets(cliente.nome_cliente, 100, stdin);
        fflush(stdin);
        printf("Digite a cidade do cliente: ");
        fgets(cliente.cidade, 100, stdin);
        fflush(stdin);
        printf ("Digite o valor do frete(use ponto no lugar de virgula): ");
        scanf ("%f", &cliente.valor_frete);
        fflush(stdin);
        fflush(stdin);

        fwrite (&cliente, sizeof(cliente), 1, arq);
        fclose(arq);

        printf("\nCadastro realizado com sucesso. Pressione Enter para voltar ao menu.");
    }
 }

void cadastroProduto(){
    Produto produto;
    FILE *arq ;
    arq = fopen("cadastroProdutos.dat", "ab");

    if (arq == NULL){
        printf("ERRO - Falha ao abrir arquivo.");
        exit(1);
    }
    else{
        printf ("\nDigite o nome do produto: ");
        fflush(stdin);
        fgets(produto.nome_produto, 100, stdin);
        printf("Digite o codigo do produto: ");
        fflush(stdin);
        scanf("%d", &produto.codigo_produto);
        printf("Digite o valor do produto (use ponto no lugar de virgula): ");
        fflush(stdin);
        scanf("%f", &produto.valor);

        fwrite (&produto, sizeof (produto), 1, arq);
        fclose(arq);

        printf("\nCadastro realizado com sucesso. Pressione Enter para voltar ao menu.");
    }
 }

void verificaProduto(){
    Produto produto;
    FILE *arq;
    arq = fopen("cadastroProdutos.dat", "rb");

    if (arq == NULL){
        printf("ERRO - Falha ao abrir arquivo.");
        exit(1);
    }else{
        while(1){
            fread (&produto, sizeof(produto), 1, arq);

            if(feof(arq)){
                break;
            }

            printf("\n\t- %s\t  CODIGO: %d\t  VALOR:%.2f\n", produto.nome_produto, produto.codigo_produto, produto.valor);
        }
    }
    fclose(arq);

    printf("\nPressione Enter para voltar ao menu principal.");
 }

void verificaCadastro(){
    Cliente cliente;
    FILE *arq;
    arq = fopen("cadastroClientes.dat", "rb");

    if (arq == NULL){
        printf("ERRO - Falha ao abrir arquivo.");
        exit(1);
    }else{
        while (1){
            fread(&cliente, sizeof (cliente), 1, arq);

            if(feof(arq)){
                break;
            }

            printf ("\n\tNOME: %s\tCIDADE: %s\tVALOR DO FRETE: %.2f\n", cliente.nome_cliente, cliente.cidade, cliente.valor_frete);
        }
    }

    printf("\n\nPressione Enter para voltar ao menu.");
    fclose(arq);
 }

void registrarVenda(){
    Venda venda;
    int i;
    float soma_prod;
    FILE *arq;
    arq = fopen("registrosVendas.dat", "ab");

    if (arq == NULL){
        printf("ERRO - Falha ao abrir arquivo.");
        exit(1);
    }

    else{
        printf ("Digite a data da venda (dd mm aaaa): ");
        scanf ("%d %d %d", &venda.data_venda.dia, &venda.data_venda.mes, &venda.data_venda.ano);

        printf ("Digite o nome do cliente e o valor do frete: ");
        fflush(stdin);
        printf("\nNome do cliente: ");
        fflush(stdin);
        fgets(venda.cliente_venda.nome_cliente, 100, stdin);
        fflush(stdin);
        printf("\nValor do frete: ");
        scanf ("%f", &venda.cliente_venda.valor_frete);

        printf ("Quantos produtos foram pedidos? ");
        fflush(stdin);
        scanf("%d", &venda.qtd_produtos);

        for (i = 0; i < venda.qtd_produtos; i++){
            printf ("Digite o nome do produto %d: ", i+1);
            fflush(stdin);
            fgets(venda.produto_venda[i].nome_produto, 100, stdin);
            fflush(stdin);
            printf("Digite o valor do produto %d: ", i+1);
            scanf ("%f", &venda.produto_venda[i].valor);
            soma_prod += venda.produto_venda[i].valor;
        }

        venda.valorFinalVenda = soma_prod + venda.cliente_venda.valor_frete;

        printf("\n\nSoma: %.2f \n", soma_prod);
        printf("O valor total da venda com frete eh: %.2f \n", venda.valorFinalVenda);

        fwrite(&venda, sizeof (venda), 1, arq);

        printf("\nPressione Enter para voltar ao menu principal.");

        fclose(arq);
    }
 }

 void pergunta(){
    Venda venda;
    FILE *arq;
    arq = fopen("registrosVendas.dat", "rb");

    while(1)
    {
        fread(&venda, sizeof(venda), 1, arq);

        if(feof(arq))
        {
            break;
        }

        if(venda.data_venda.ano == 2022)
        {

            printf("\n\tDATA: %d/%d/%d\n", venda.data_venda.dia, venda.data_venda.mes, venda.data_venda.ano);
            printf("\n\tNome do comprador: %s", venda.cliente_venda.nome_cliente);
            printf("\tValor total da venda: %.2f\n", venda.valorFinalVenda);
        }
    }

    printf("\n\nPressione Enter para voltar ao menu principal.");

    fclose(arq);
 }



int main(){

    while(1){//Loop pra sempre voltar ao menu
        menu();
    }

    return 0;
}
