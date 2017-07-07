#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct produto
{
    char nome[30];
    int cod;
    char marca [30];
    char categoria[30];
    int n_estoque;
    float preco;

}Produto;

typedef struct cliente
{
    char nome[50], cpf [12];
    char sexo;
    char email[50];

}Cliente;

typedef struct funcionario
{
    char nome [50], sexo, cpf[12];
    int cod;
    int senha;

}Funcionario;

typedef struct fornecedor
{
    char nome_fornecedor[30];
    char codigo_fornecedor[7];
    char cnpj[15];

}Fornecedor;


typedef struct lista{
    struct lista *prox;
    Produto x;
}Lista_produto;

//FUNCOES

void cadastro_cliente ()
{
    FILE* arquivo;
    Cliente b;
    char escolha;
    arquivo=fopen("listacliente.bin", "ab");

    if (arquivo==NULL){
        printf ("ERRO");
        exit (1);
    }
    do{
        printf ("---------CADASTRO DE CLIENTE----------\n\n");

        printf ("Digite o nome do cliente: \n");
        fflush(stdin);
        fgets(b.nome,50,stdin);

        printf ("Digite o sexo(m/f): \n");
        fflush(stdin);
        scanf ("%c", &b.sexo);

        printf ("Digite o cpf do cliente: \n ");
        fflush(stdin);
        fgets((b.cpf),12,stdin);

        printf ("Digite o email: \n");
        fflush(stdin);
        fgets (b.email,50,stdin);

        printf ("Deseja fazer mais cadastros? S/N\n");
        fflush(stdin);
        scanf ("%c", &escolha);

        fwrite(&b,sizeof(Cliente),1,arquivo);
       } while ((escolha == 's')||(escolha=='S'));

    fclose(arquivo);
    //volta para o menu principal

}

int  consulta_cliente(){
    FILE* arquivo;
    arquivo = fopen("listacliente.bin", "rb");

    if(arquivo==NULL){
        printf("Erro na abertura do arquivo");
        exit(1);

    }
    else{
        Cliente b;
        char cpf_2[12];
        char escolha;
        printf("Digite o cpf do cliente que deseja consultar: \n ");
        scanf(" %s",cpf_2);

        while(fread(&b,sizeof(Cliente),1,arquivo)==1){
            if((strcmp(b.cpf,cpf_2)==0)){
                printf("Cliente cadastrado!\n");
                printf ("Nome: %s", b.nome);
                return 1;

            }
            continue;
        }


        printf("Cliente nao cadastrado! \n");
        fflush(stdin);
        printf ("Deseja fazer o cadastro agora? S/N \n");
        scanf ("%c", &escolha);
            if(escolha=='S' || escolha == 's'){
                cadastro_cliente();
            }
            else {
                //VOLTAR PARA O MENU PRINCIPAL

            }

        return 0;



       fclose(arquivo);

    }
}

void cadastro_fornecedor (){
    FILE *arquivo;
    Fornecedor b;
    char escolha;

    arquivo=fopen ("listafornecedor.bin", "ab");
    if (arquivo==NULL){
        printf ("Erro na abertura do arquivo");
        exit (1);
    }

    do{
        printf ("--------CADASTRO DE FORNECEDOR--------\n");

        printf ("Digite o nome da empresa fornecedora: \n");
        fflush(stdin);
        fgets (b.nome_fornecedor,30,stdin);

        printf ("Digite o codigo do fornecedor: \n");
        fflush(stdin);
        fgets (b.codigo_fornecedor,7, stdin);

        printf ("Digite o cnpj da empresa fornecedora: \n");
        fflush(stdin);
        fgets (b.cnpj, 15, stdin);

        printf ("Deseja fazer mais cadastros? S/N\n");
        fflush(stdin);
        scanf ("%c", &escolha);


        fwrite(&b, sizeof (Fornecedor), 1, arquivo);

       }while ((escolha == 's')||(escolha=='S'));

    fclose(arquivo);
    //voltar para o menu principal

}

int consulta_fornecedor (){
    FILE *arquivo;
    arquivo=fopen("listafornecedor.bin", "rb");

    if (arquivo==NULL){
        printf ("Erro na abertura do arquivo");
        exit (1);
    }

    else {
        Fornecedor b;
        char cnpj_2[15];
        char escolha;

        printf("\nDigite o cnpj da empresa que deseja consultar: \n ");
        scanf(" %s",cnpj_2);

        while (fread(&b,sizeof(Fornecedor),1,arquivo)==1){
                if (strcmp(b.cnpj,cnpj_2)==0){
                    printf ("Fornecedor cadastrado!\n");
                    printf ("Nome: %s", b.nome_fornecedor);
                    return 1;

                }
                continue;

        }

        printf ("Fornecedor não cadastrado. Deseja cadastrar agora? S/N");
        fflush(stdin);
        scanf ("%c", &escolha);

            if(escolha=='S' || escolha == 's'){
                cadastro_fornecedor();
            }
            else {
                //VOLTAR PARA O MENU PRINCIPAL

            }

            fclose (arquivo);

            return 0;
    }




}



int main ()
{
    cadastro_cliente();
    consulta_cliente();
    cadastro_fornecedor();
    consulta_fornecedor();
}
