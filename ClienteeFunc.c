#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct cliente
{
    char nome[50], cpf [12];
    char sexo;
    char email[50];

}Cliente;


typedef struct fornecedor
{
    char nome_fornecedor[30];
    char codigo_fornecedor[7];
    char cnpj[15];

}Fornecedor;

//******************funcoes*******************
void cadastro_cliente ()
{
    FILE* arquivo;
    Cliente b;
    char escolha;
    arquivo=fopen("listacliente.dat", "ab");

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
    arquivo = fopen("listacliente.dat", "rb");

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
                fclose (arquivo);
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
        fclose(arquivo);
        return 0;

    }
}

void cadastro_fornecedor (){
    FILE *arquivo;
    Fornecedor b;
    char escolha;

    arquivo=fopen ("listafornecedor.dat", "ab");
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
    arquivo=fopen("listafornecedor.dat", "rb");

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
                    fclose (arquivo);
                    return 1;

                }
                continue;

        }

        printf ("Fornecedor nao cadastrado! Deseja cadastrar agora? S/N \n");
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


int exclui_cliente (){
    FILE *arquivo;
    char cpf_2 [12];
    char escolha;

    arquivo=fopen ("listacliente.dat", "r+b" );
    if (arquivo==NULL){
        printf ("Erro na abertura do arquivo");
        exit (1);
    }
    else {
        Cliente b;
        int encontrado =0;

        printf ("Digite o cpf do cliente que deseja remover: ");
        scanf ("%s", cpf_2);

        while(fread(&b,sizeof(Cliente),1,arquivo)==1){
            if((strcmp(b.cpf,cpf_2)==0)){
                printf("Cliente cadastrado!\n");
                printf ("Nome: %s\n", b.nome);
                encontrado =1;
                break;
            }
            continue;
        }

         if (encontrado==0){
            printf ("Cliente nao cadastrado!");
            fclose (arquivo);
            return 0;
            //FUNCAO PARA O MENU
         }

       else {
        printf ("Tem certeza que deseja remover este cliente? S/N \n");
        fflush(stdin);
        scanf ("%c", &escolha);

        if (escolha=='S' || escolha == 's'){

                b.nome[0]='\0';
                b.cpf[0]='\0';
                b.sexo='0';
                b.email[0]='\0';
                printf ("Exclusao feita com sucesso!\n");
                fseek(arquivo,-sizeof(struct cliente),SEEK_CUR);
                fwrite(&b,sizeof(Cliente),1,arquivo);
                fclose (arquivo);
                return 1; //voltar para menu


                }
                else{
                    printf ("Exclusao cancelada");
                    fclose (arquivo);
                    return 0;
                    //funcao para voltar para o menu
                }
       }

    }

}

int altera_cliente (){
    FILE *arquivo;
    char cpf_2[12];

    arquivo=fopen ("listacliente.dat", "r+b");
    if (arquivo==NULL){
        printf ("Erro na abertura do arquivo");
        exit (1);
    }
    else{
        Cliente b;
        int escolha;
        int verificador = 0;
        char escolha_1;

        printf ("Digite o cpf do cliente para fazer a alteracao de dados: \n");
        scanf ("%s", cpf_2);


        while(fread(&b,sizeof(Cliente),1,arquivo)==1){
            if((strcmp(b.cpf,cpf_2)==0)){
                printf("Cliente cadastrado!\n");
                printf ("Nome: %s\n", b.nome);
                verificador =1;
                break;
            }
            continue;
        }

        if (verificador==0){
            printf("Cliente nao encontrado\n");
            fclose(arquivo);
            return 0; //voltar para menu
        }


        do{
        printf ("[1] Alterar o nome\n[2] Alterar o cpf\n[3] Alterar o sexo\n[4] Alterar o email\n[5] Alterar todos os campos\n ");
        scanf ("%d", &escolha);

        switch (escolha)
        {
            case 1: printf ("Digite o novo nome do cliente: ");
                    fflush(stdin);
                    scanf ("%[^\n]s", b.nome);
                    break;

            case 2: printf ("Digite o novo cpf: ");
                    fflush(stdin);
                    scanf ("%s", b.cpf);
                    break;

            case 3: printf ("Digite o sexo do cliente: ");
                    fflush(stdin);
                    scanf (" %c", &b.sexo);
                    break;

            case 4: printf ("Digite o novo email do cliente: ");
                    fflush(stdin);
                    scanf ("%s", b.email);
                    break;

            case 5: printf("Digite o novo nome do cliente: ");
                    fflush(stdin);
                    scanf ("%[^\n]s", b.nome);

                    printf ("Digite o novo cpf: ");
                    fflush (stdin);
                    scanf ("%s", b.cpf);

                    printf ("Digite o sexo do cliente: ");
                    scanf (" %c", &b.sexo);

                    printf ("Digite o novo email do cliente: ");
                    fflush (stdin);
                    scanf ("%s", b.email);
                    break;

            default: printf ("Erro!");

        }

        printf ("Deseja fazer mais alguma alteracao no cadastro desse cliente? [S/N] \n");
        scanf (" %c", &escolha_1);

        }while (escolha_1=='S' || escolha_1 == 's');


        fseek(arquivo,-sizeof(struct cliente),SEEK_CUR);
        fwrite(&b,sizeof(Cliente),1,arquivo);

        printf ("%s \n", b.nome);
        printf ("%s \n", b.cpf);
        printf (" %c \n", b.sexo);
        printf ("%s \n", b.email);
        fclose (arquivo); //volta para menu
        return 1;

    }
}

int exclui_fornecedor (){
    FILE *arquivo;
    char cnpj_2[15];
    char escolha;

    arquivo=fopen ("listafornecedor.dat", "r+b" );
    if (arquivo==NULL){
        printf ("Erro na abertura do arquivo");
        exit (1);
    }
    else {
        Fornecedor b;
        int encontrado =0;

        printf ("Digite o cnpj do fornecedor que deseja remover: ");
        scanf ("%s", cnpj_2);

        while(fread(&b,sizeof(Fornecedor),1,arquivo)==1){
            if((strcmp(b.cnpj,cnpj_2)==0)){
                printf("Fornecedor cadastrado!\n");
                printf ("Nome: %s\n", b.nome_fornecedor);
                encontrado=1;
                break;
            }
            continue;
        }

         if (encontrado==0){
            printf ("Fornecedor nao cadastrado!");
            fclose(arquivo);
            return 0; //voltar para menu
         }

                printf ("Tem certeza que deseja remover este fornecedor? S/N \n");
                scanf (" %c", &escolha);

                if (escolha=='S' || escolha == 's'){

                    b.nome_fornecedor[0]='\0';
                    b.codigo_fornecedor[0]='\0';
                    b.cnpj[0]='\0';
                    printf ("Exclusao feita com sucesso!");

                    fseek(arquivo,-sizeof(struct fornecedor),SEEK_CUR);
                    fwrite(&b,sizeof(Fornecedor),1,arquivo);
                    fclose (arquivo);
                    return 1; //voltar para menu

                }
                else{
                    printf ("Exclusao cancelada");
                    fclose (arquivo);
                    return 0; //voltar para menu

                }

        }


    }

int altera_fornecedor (){
    FILE *arquivo;
    char cnpj_2[15];

    arquivo=fopen ("listafornecedor.dat", "r+b");
    if (arquivo==NULL){
        printf ("Erro na abertura do arquivo");
        exit (1);
    }
    else{
        Fornecedor b;
        int escolha;
        int verificador = 0;
        char escolha_1;

        printf ("Digite o cnpj do fornecedor para fazer a alteracao de dados: \n");
        scanf ("%s", cnpj_2);


        while(fread(&b,sizeof(Fornecedor),1,arquivo)==1){
            if((strcmp(b.cnpj,cnpj_2)==0)){
                printf("Fornecedor cadastrado!\n");
                printf ("Nome: %s\n", b.nome_fornecedor);
                verificador =1;
                break;
            }
            continue;
        }

        if (verificador==0){
            printf("Fornecedor nao encontrado\n");
            fclose(arquivo);
            return 0; //VOLTAR PARA MENU
        }


        do{
        printf ("[1] Alterar o nome\n[2] Alterar o cnpj\n[3] Alterar o codigo\n[4] Alterar todos os campos\n ");
        scanf ("%d", &escolha);

        switch (escolha)
        {
            case 1: printf ("Digite o novo nome do fornecedor: ");
                    fflush(stdin);
                    scanf ("%[^\n]s", b.nome_fornecedor);
                    break;

            case 2: printf ("Digite o novo cnpj: ");
                    fflush(stdin);
                    scanf ("%s", b.cnpj);
                    break;

            case 3: printf ("Digite o novo codigo do cliente: ");
                    fflush(stdin);
                    scanf ("%s", b.codigo_fornecedor);
                    break;

            case 4: printf("Digite o novo nome do fornecedor: ");
                    fflush(stdin);
                    scanf ("%[^\n]s", b.nome_fornecedor);

                    printf ("Digite o novo cnpj: ");
                    fflush (stdin);
                    scanf ("%s", b.cnpj);

                    printf ("Digite o novo codigo do fornecedor: ");
                    fflush (stdin);
                    scanf ("%s", b.codigo_fornecedor);
                    break;

            default: printf ("Erro!");

        }

        printf ("Deseja fazer mais alguma alteracao no cadastro desse fornecedor? [S/N] \n");
        scanf (" %c", &escolha_1);

        }while (escolha_1=='S' || escolha_1 == 's');


        fseek(arquivo,-sizeof(struct fornecedor),SEEK_CUR);
        fwrite(&b,sizeof(Fornecedor),1,arquivo);

        printf ("%s \n", b.nome_fornecedor);
        printf ("%s \n", b.cnpj);
        printf ("%s \n", b.codigo_fornecedor);

        fclose (arquivo);
        return 1; //VOLTAR PARA MENU

    }
}



int main ()
{
  
    cadastro_cliente();
    altera_cliente();
    exclui_cliente();
    consulta_cliente();

   cadastro_fornecedor();
   altera_fornecedor();
   exclui_fornecedor();
   consulta_fornecedor();
}
