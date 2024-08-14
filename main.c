#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "empresa.h"
#include "busca.h"
#include "string_utils.h"

int main ()
{
    char criterio_procurado[200];
    int busca_por_nome = 0;
    FILE *file = fopen("data/Empresas.EMPRECSV", "r");

    if(!file)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("Deseja buscar por CNPJ ou nome? (0 - CNPJ, 1 - nome): ");
    scanf("%d", &busca_por_nome);
    if(busca_por_nome != 0 && busca_por_nome != 1)
    {
        printf("Opcao invalida. Tente novamente.\n");
    }
    else if(busca_por_nome)
    {
        printf("Digite o nome procurado: ");
        getchar();
        fgets(criterio_procurado, 200, stdin);
        remove_nova_linha(criterio_procurado);
        /* printf("Voce busca pelo nome %s\n", criterio_procurado);
        printf("Com aspas fica %s\n", adicionar_aspas(criterio_procurado));
        getchar(); */
    }
    else
    {
        printf("Digite o CNPJ procurado: ");
        scanf("%s", criterio_procurado);
    }
    busca_por_criterio(adicionar_aspas(criterio_procurado), file, busca_por_nome);

    return 0;
}