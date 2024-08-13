#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "empresa.h"

#define TAMANHO_BLOCO 1000000

int busca_binaria(Empresa *empresas, int tamanho, const char *cnpj_procurado) 
{
    int esquerda = 0;
    int direita = tamanho - 1;

    while (esquerda <= direita) 
    {
        int meio = (esquerda + direita) / 2;
        int cmp = strcmp(empresas[meio].cnpj, cnpj_procurado);

        if (cmp == 0) {
            return meio; /* CNPJ encontrado */
        } else if (cmp < 0) {
            esquerda = meio + 1; /* CNPJ procurado está na metade direita */
        } else {
            direita = meio - 1; /* CNPJ procurado está na metade esquerda */
        }
    }

    return -1; /* CNPJ não encontrado */
}

int compara_cnpj(const void *a, const void *b) {
    return strcmp(((Empresa *)a)->cnpj, ((Empresa *)b)->cnpj);
}

void processar_bloco(FILE *file, char *cnpj_procurado, int *encontrado) 
{
    Empresa *empresas = malloc(TAMANHO_BLOCO * sizeof(Empresa));
    if (!empresas) 
    {
        fprintf(stderr, "Erro de alocação de memória.\n");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    char linha[256];

    /* Leitura do bloco */
    while (fgets(linha, sizeof(linha), file)) 
    {
        char *cnpj = strtok(linha, ";");
        char *nome = strtok(NULL, ";");
        char *natureza_juridica = strtok(NULL, ";");
        char *qualificacao_responsavel = strtok(NULL, ";");
        char *capital_social = strtok(NULL, ";");
        char *porte = strtok(NULL, ";");
        char *ente_federativo = strtok(NULL, ";");

        /* printf("%s %s %s %s %s %s \n", cnpj, nome, natureza_juridica, qualificacao_responsavel, capital_social, porte, ente_federativo); */

        /* Verificação de sucesso na tokenização */
        if (!cnpj || !nome || !natureza_juridica || !qualificacao_responsavel || !capital_social || !porte || !ente_federativo) 
        {
            continue; /*  Ignorar linha mal formatada */
        }

        /* Alocação dinâmica para cada campo */
        empresas[count].cnpj = malloc(strlen(cnpj) + 1);
        empresas[count].nome = malloc(strlen(nome) + 1);
        empresas[count].natureza_juridica = malloc(strlen(natureza_juridica) + 1);
        empresas[count].qualificacao_responsavel = malloc(strlen(qualificacao_responsavel) + 1);
        empresas[count].capital_social = malloc(strlen(capital_social) + 1);
        empresas[count].porte = malloc(strlen(porte) + 1);
        empresas[count].ente_federativo = malloc(strlen(ente_federativo) + 1);

        /* Verificação de sucesso na alocação de memória */
        if (!empresas[count].cnpj || !empresas[count].nome || !empresas[count].natureza_juridica ||
            !empresas[count].qualificacao_responsavel || !empresas[count].capital_social ||
            !empresas[count].porte || !empresas[count].ente_federativo) 
        {
            fprintf(stderr, "Erro de alocação de memória para campos.\n");
            exit(EXIT_FAILURE);
        }

        /* Copia os dados para a estrutura */
        strcpy(empresas[count].cnpj, cnpj);
        strcpy(empresas[count].nome, nome);
        strcpy(empresas[count].natureza_juridica, natureza_juridica);
        strcpy(empresas[count].qualificacao_responsavel, qualificacao_responsavel);
        strcpy(empresas[count].capital_social, capital_social);
        strcpy(empresas[count].porte, porte);
        strcpy(empresas[count].ente_federativo, ente_federativo);

        count++;
        if (count >= TAMANHO_BLOCO) 
        {
            break;
        }
    }

    qsort(empresas, count, sizeof(Empresa), compara_cnpj);

    int indice = busca_binaria(empresas, count, cnpj_procurado);

    if (indice != -1) 
    {
        imprime_empresa(&empresas[indice]);
        *encontrado = 1;
    }

    /* Libera a memória alocada */
    int i;
    for (i = 0; i < count; i++) 
    {
        free(empresas[i].cnpj);
        free(empresas[i].nome);
        free(empresas[i].natureza_juridica);
        free(empresas[i].qualificacao_responsavel);
        free(empresas[i].capital_social);
        free(empresas[i].porte);
        free(empresas[i].ente_federativo);
    }

    free(empresas);
}

void busca_cnpj(char *cnpj_procurado, FILE *file) 
{
    int encontrado = 0;

    while (!encontrado && !feof(file)) 
    {
        processar_bloco(file, cnpj_procurado, &encontrado);
    }

    fclose(file);

    if (!encontrado) 
    {
        printf("CNPJ não encontrado.\n");
    }
}
