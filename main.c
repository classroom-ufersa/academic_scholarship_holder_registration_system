#include <stdio.h>
#include "System/system.h"

int main(void){
    int opcao;
    Bolsa * bolsas;

    do{
        menu_de_opcoes();
        scanf("%d", &opcao);
        switch (opcao){
        case 1:
            printf("Adicionando Bolsa...\n");
            preenche_bolsa(&bolsas);
            break;
        case 2:
            printf("Adicionando Bolsista...\n");
            break;
        case 3:
            printf("Excluindo Bolsista...\n");
            break;
        case 4:
            printf("Listando todos os bolsistas cadastrados...\n");
            break;
        case 5:
            printf("Buscando Bolsista...\n");
            break;
        case 6:
            printf("Editando Dados do Bolsista...\n");
            break;
        case 7:
            printf("Consultando Dados do Bolsista...\n");
            break;
        case 8:
            printf("Consultando as Bolsas Disponiveis...\n");
            break;
        case 9:
            printf("Saindo...\n");
            exit(1);
            break;
        
        default:
        printf("Opcao Invalida!\n");
            break;
        }
    }while(opcao != 9);
    return 0;
}