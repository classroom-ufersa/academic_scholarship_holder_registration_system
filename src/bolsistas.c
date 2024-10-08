#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/bolsistas.h"

struct bolsista
{
    char nome_completo[MAX];
    long int matricula;
    char curso[50];
    char CPF[15];
    char bolsa_associada[MAX];
    struct bolsista *proximo_bolsista;
};

void adiciona_bolsista(Bolsista **bolsistas, char *nome_bolsa)
{

    Bolsista *novo_bolsista = (Bolsista *)malloc(sizeof(Bolsista));
    if (novo_bolsista == NULL)
    {
        printf("Memoria Insuficiente!\n");
        exit(1);
    }
    char nome_bolsista[MAX], curso[50], CPF[TAMANHO_CPF + 1];
    char matricula_bolsista[9];
    long matricula_convertida;
    int verificador = FALHA, verificador2 = FALHA;

    do
    {

        printf("Informe o Nome:\n");
        scanf(" %[^\n]", nome_bolsista);
        fflush(stdin);
        if (strlen(nome_bolsista) >= MAX - 1)
        {
            printf("Nome muito grande!Digite Novamente\n");
            verificador = FALHA;
        }
        else
        {

            verificador = verifica_caracter(nome_bolsista);
            transforma_caracter_padrao(nome_bolsista); // conserta o nome para um padrao
            verificador2 = verifica_bolsista_existente(*bolsistas, nome_bolsista);
        }

    } while (verificador == FALHA || verificador2 == FALHA);

    do
    {
        printf("Informe o Curso:\n");
        scanf(" %[^\n]", curso);
        fflush(stdin);
        if (strlen(curso) == 50)
        {
            printf("Nome muito grande!Digite Novamente\n");
            verificador = FALHA;
        }
        else
        {
            verificador = verifica_caracter(curso);
            transforma_caracter_padrao(curso); // conserta o nome para um padrao
        }

    } while (verificador == FALHA);

    do
    {
        printf("Informe a Matricula (8 digitos):\n");
        scanf(" %[^\n]", matricula_bolsista);
        verificador = verifica_matricula_valida(matricula_bolsista);
        matricula_convertida = strtol(matricula_bolsista, NULL, 10);
        verificador2 = verifica_matricula_existente(matricula_convertida, *bolsistas);

        // não deixar que matricula menores ou maiores de 8 digitos passem
    } while (verificador == FALHA || verificador2 == FALHA);

    do
    {
        printf("Informe o CPF: (FORMATO: 000.000.000-00)\n");
        scanf(" %[^\n]", CPF);
        fflush(stdin);
    } while (verifica_cpf_existente(CPF, *bolsistas) == FALHA || verifica_cpf_valido(CPF) == FALHA);

    // adicionando as informações ao novo bolsista
    strcpy(novo_bolsista->nome_completo, nome_bolsista);
    strcpy(novo_bolsista->curso, curso);
    strcpy(novo_bolsista->bolsa_associada, nome_bolsa);
    strcpy(novo_bolsista->CPF, CPF);
    novo_bolsista->matricula = matricula_convertida;

    // vinculando a lista de bolsistas da bolsa
    insere_bolsista_ordenado(bolsistas, novo_bolsista); // inserir um bolsista ordenado
}

// função para adicionar um bolsista em ordem correta
void insere_bolsista_ordenado(Bolsista **bolsistas, Bolsista *novo_bolsista)
{
    Bolsista *count = *bolsistas;
    Bolsista *ant = NULL;

    // Se a lista estiver vazia ou se o novo bolsista deve ser inserida no início
    if (count == NULL || strcmp(novo_bolsista->nome_completo, count->nome_completo) < 0)
    {
        novo_bolsista->proximo_bolsista = count;
        *bolsistas = novo_bolsista;
        return;
    }
    else
    {
        // Percorre a lista até encontrar a posição correta para inserir
        while (count != NULL && strcmp(novo_bolsista->nome_completo, count->nome_completo) > 0)
        {
            ant = count;
            count = count->proximo_bolsista;
        }

        // Insere a nova bolsa na posição correta
        novo_bolsista->proximo_bolsista = count;
        ant->proximo_bolsista = novo_bolsista;
    }
}
// função para buscar um bolsista em uma bolsa
Bolsista *auxiliar_buscar_bolsista_por_nome(Bolsista *bolsistas, char *nome_bolsista)
{

    // caso não exista nenhum bolsista cadastrado na bolsa
    if (bolsistas == NULL)
    {
        return NULL;
    }

    // percorre a lista de bolsistas de uma determianda bolsa
    Bolsista *count = bolsistas;
    while (count != NULL)
    {
        if (strcmp(count->nome_completo, nome_bolsista) == 0)
        {

            printf("\nBolsista: %s\n", count->nome_completo);
            printf("Matricula: %ld\n", count->matricula);
            printf("Curso: %s\n", count->curso);
            printf("CPF: %s\n", count->CPF);
            printf("Bolsa Associada: %s\n\n", count->bolsa_associada);
            return count;
        }
        count = count->proximo_bolsista;
    }

    // caso o bolsista não esteja cadastrado na bolsa
    printf("Bolsista %s nao cadastrado em nenhuma bolsa!\n", nome_bolsista);
    return bolsistas;
}

Bolsista *auxiliar_buscar_bolsista_por_matricula(Bolsista *bolsistas, long int matricula)
{
    if (bolsistas == NULL)
    {
        return FALHA;
    }
    Bolsista *count = bolsistas;
    while (count != NULL)
    {
        if (count->matricula == matricula)
        {
            printf("\nBolsista: %s\n", count->nome_completo);
            printf("Matricula: %ld\n", count->matricula);
            printf("Curso: %s\n", count->curso);
            printf("CPF: %s\n", count->CPF);
            printf("Bolsa Associada: %s\n\n", count->bolsa_associada);
            return count;
        }
        count = count->proximo_bolsista;
    }
    printf("Bolsista com matricula %ld nao esta cadastrado em nenhuma bolsa!", count->matricula);
    return bolsistas;
}

void auxiliar_editar_bolsista(Bolsista *bolsista_encontrado, Bolsista *bolsistas)
{
    int opcao = 0;
    char c_numero[2];
    int verificador = FALHA, verificador2 = FALHA;
    char curso[50], nome_bolsista[MAX], novo_cpf[15];
    long int matricula;
    char matricula_bolsista[10];
    long matricula_convertida;
    do
    {
        printf("MENU DE EDICAO:\n");
        printf("1 - Editar Nome. \n");
        printf("2 - Editar Curso.\n");
        printf("3 - Editar Matricula.\n");
        printf("4 - Editar CPF.\n");
        printf("5 - Sair.\n");
        scanf("%s", c_numero);
        opcao = verifica_inteiro(c_numero);

        switch (opcao)
        {
        case 1:
            do
            {
                printf("Digite o novo nome:\n");
                scanf(" %[^\n]", nome_bolsista);
                fflush(stdin);
                verificador = verifica_caracter(nome_bolsista);
                transforma_caracter_padrao(nome_bolsista); // conserta o nome para um padrao
                verificador2 = verifica_bolsista_existente(bolsistas, nome_bolsista);

                if (strlen(nome_bolsista) >= MAX)
                {
                    printf("Nome muito grande!Digite Novamente\n");
                    verificador = FALHA;
                }

            } while (verificador == FALHA || verificador2 == FALHA);

            strcpy(bolsista_encontrado->nome_completo, nome_bolsista);
            printf("Nome alterado para %s\n", nome_bolsista);

            break;

        case 2:
            do
            {
                printf("Informe o novo nome do curso:\n");
                scanf(" %[^\n]", curso);
                fflush(stdin);
                verificador = verifica_caracter(curso);
                transforma_caracter_padrao(curso); // conserta o nome para um padrao

                if (strlen(curso) >= 50)
                {
                    printf("Nome muito grande!Digite Novamente\n");
                    verificador = FALHA;
                }

            } while (verificador == FALHA);

            strcpy(bolsista_encontrado->curso, curso);
            break;
        case 3:
            do
            {
                printf("Informe a nova matricula:\n");
                scanf(" %8[^\n]", matricula_bolsista);
                verificador = verifica_matricula_valida(matricula_bolsista);
                matricula_convertida = strtol(matricula_bolsista, NULL, 10);
                verificador2 = verifica_matricula_existente(matricula_convertida, bolsistas);

            } while (verificador == FALHA || verificador2 == FALHA);
            bolsista_encontrado->matricula = matricula_convertida;
            break;

        case 4:
            do
            {
                printf("Informe o CPF: (FORMATO: 000.000.000-00)\n");
                scanf(" %[^\n]", novo_cpf);
                fflush(stdin);
            } while (verifica_cpf_existente(novo_cpf, bolsistas) == FALHA || verifica_cpf_valido(novo_cpf) == FALHA);

            strcpy(bolsista_encontrado->CPF, novo_cpf);
            break;
        case 5:
            printf("Voltando ao menu!\n");
            break;

        default:
            printf("Opcao Invalida! Por favor, escolha entre 1 e 5\n");
            break;
        }
    } while (opcao != 5);
}

int auxiliar_excluir_bolsista_por_nome(Bolsista **bolsistas, char *nome_bolsista)
{

    Bolsista *contador_de_bolsistas = *bolsistas;
    Bolsista *ant = NULL;
    while (contador_de_bolsistas != NULL)
    {

        // encontrou o bolsista para remover
        if (strcmp(contador_de_bolsistas->nome_completo, nome_bolsista) == 0)
        {

            // caso seja o primeiro bolsista
            if (ant == NULL)
            {
                *bolsistas = contador_de_bolsistas->proximo_bolsista;
            }
            // caso seja algum bolsista apos o primeiro
            else
            {
                ant->proximo_bolsista = contador_de_bolsistas->proximo_bolsista;
            }
            printf("Bolsista '%s' removido com sucesso!\n", nome_bolsista);
            free(contador_de_bolsistas);
            return SUCESSO; // flag indicando se o bolsista foi excluido
        }

        // avança para o proximo bolsista
        ant = contador_de_bolsistas;
        contador_de_bolsistas = contador_de_bolsistas->proximo_bolsista;
    }
    return FALHA;
}

// função auxiliar para excluir todas as bolsas
void auxiliar_excluir_bolsas(Bolsista **bolsistas)
{
    Bolsista *count = *bolsistas;
    Bolsista *proxima = NULL;

    while (count != NULL)
    {
        proxima = count->proximo_bolsista;
        free(count);
        count = proxima;
    }

    *bolsistas = NULL;
}

// função para exibir todos os bolsistas de uma determinada bolsa
void listar_bolsistas(Bolsista *bolsistas)
{
    if (bolsistas == NULL)
    {
        printf("Nenhum bolsista cadastrado!\n\n");
        return;
    }
    Bolsista *count = bolsistas;
    while (count != NULL)
    {
        printf("Bolsista: %s\n", count->nome_completo);
        printf("Matricula: %ld\n", count->matricula);
        printf("Curso: %s\n", count->curso);
        printf("CPF: %s\n", count->CPF);
        printf("Bolsa Associada: %s\n\n", count->bolsa_associada);
        count = count->proximo_bolsista;
    }
}

// função para verificar se o cpf ja existe na bolsa
int verifica_cpf_existente(char *CPF, Bolsista *bolsistas)
{
    Bolsista *count = bolsistas;

    while (count != NULL)
    {

        if (strcmp(count->CPF, CPF) == 0)
        {
            printf("CPF ja esta cadastrado.\n");
            return FALHA; // cpf ja existe no banco de dados
        }

        count = count->proximo_bolsista;
    }

    // cpf ainda nao cadastrado
    return SUCESSO;
}

int verifica_matricula_existente(long int matricula, Bolsista *bolsistas)
{
    Bolsista *count = bolsistas;
    while (count != NULL)
    {
        if (count->matricula == matricula)
        {
            printf("Matricula ja esta cadastrada\n");
            return FALHA;
        }
        count = count->proximo_bolsista;
    }
    return SUCESSO;
}

// função para verificar que um bolsista ja foi cadastrado na bolsa
int verifica_bolsista_existente(Bolsista *bolsistas, char *nome_bolsista)
{
    Bolsista *count = bolsistas;

    while (count != NULL)
    {
        // verifica se o bolsista ja esta cadastrado na bolsa
        if (strcmp(count->nome_completo, nome_bolsista) == 0)
        {

            printf("Bolsista %s ja cadastrado!\n", nome_bolsista);
            return FALHA; // bolsita ja cadastrado
        }
        count = count->proximo_bolsista;
    }
    // bolsista nao cadastrado
    return SUCESSO;
}

// função para contar quantos bolsistas estão cadastrados em uma determinada bolsa
int quantitativo_bolsistas(Bolsista *bolsistas)
{
    int quantidade = 0;
    Bolsista *count = bolsistas;

    // conta quantos bolsistas estao cadastrados na bolsa
    while (count != NULL)
    {
        count = count->proximo_bolsista;
        quantidade++;
    }

    // retorna a quantidade de bolsistas cadastrados na bolsa
    return quantidade;
}

// função para ler os bolsistas armazenados no banco de dado
Bolsista *ler_bolsista_arquivo(FILE **banco_de_dados, Bolsista *bolsistas)
{
    char linha[100];
    Bolsista *novo_bolsista = NULL;

    // inicia a leitura dos bolsistas
    while (fgets(linha, sizeof(linha), *banco_de_dados) != NULL && !strstr(linha, "==============================="))
    {

        if (strstr(linha, "Bolsista:"))
        {

            novo_bolsista = (Bolsista *)malloc(sizeof(Bolsista));
            if (novo_bolsista == NULL)
            {
                printf("Memoria Insuficiente!\n");
                exit(1);
            }

            // armazena as informações do bolsista
            sscanf(linha, "Bolsista: %[^\n]", novo_bolsista->nome_completo);
            fgets(linha, sizeof(linha), *banco_de_dados);
            sscanf(linha, "Matricula: %ld", &novo_bolsista->matricula);
            fgets(linha, sizeof(linha), *banco_de_dados);
            sscanf(linha, "Curso: %[^\n]", novo_bolsista->curso);
            fgets(linha, sizeof(linha), *banco_de_dados);
            sscanf(linha, "CPF: %14s", novo_bolsista->CPF);
            fgets(linha, sizeof(linha), *banco_de_dados);
            sscanf(linha, "Bolsa Associada: %[^\n]", novo_bolsista->bolsa_associada);

            // adiciona o novo bolsista ao final da lista
            novo_bolsista->proximo_bolsista = NULL;
            if (bolsistas == NULL)
            {
                bolsistas = novo_bolsista;
            }
            else
            {
                Bolsista *aux = bolsistas;
                while (aux->proximo_bolsista != NULL)
                {
                    aux = aux->proximo_bolsista;
                }
                aux->proximo_bolsista = novo_bolsista;
            }
            novo_bolsista = NULL;
        }
    }

    return bolsistas;
}

// função para armazenar no arquivo os alunos de uma determinada bolsa
void insere_bolsista_arquivo(FILE **banco_de_dados, Bolsista *bolsistas)
{
    Bolsista *count = bolsistas;

    fprintf(*banco_de_dados, "BOLSISTAS:\n");

    // caso não tenha nenhum bolsista cadastrado na bolsa
    if (bolsistas == NULL)
    {
        fprintf(*banco_de_dados, "Nenhum bolsista cadastrado!\n\n");
        return;
    }

    // armazena todos os bolsistas de uma bolsa
    while (count != NULL)
    {
        fprintf(*banco_de_dados, "Bolsista: %s\n", count->nome_completo);
        fprintf(*banco_de_dados, "Matricula: %ld\n", count->matricula);
        fprintf(*banco_de_dados, "Curso: %s\n", count->curso);
        fprintf(*banco_de_dados, "CPF: %14s\n", count->CPF);
        fprintf(*banco_de_dados, "Bolsa Associada: %s\n\n", count->bolsa_associada);

        count = count->proximo_bolsista;
    }
}
