#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "empresa.h"
#include "busca.h"
#include "string_utils.h"

int main ()
{
    FILE *file = fopen("data/Empresas.EMPRECSV", "r");

    if(!file)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char cnpj_procurado[20];
    printf("Digite o CNPJ buscado: ");
    scanf("%s", cnpj_procurado);
    busca_cnpj(adicionar_aspas(cnpj_procurado), file);
}