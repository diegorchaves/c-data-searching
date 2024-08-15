#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "empresa.h"
#include "busca.h"

#define TAMANHO_BLOCO 10000

int busca_binaria(Empresa *empresas, int tamanho, const char *criterio_procurado,
                  int busca_por_nome) 
{

    int esquerda = 0;
    int direita = tamanho - 1;
    int cmp;

    while (esquerda <= direita) 
    {
        int meio = (esquerda + direita) / 2;

        if(busca_por_nome)
        {
            cmp = strcmp(empresas[meio].nome, criterio_procurado);
        }
        else
        {
            cmp = strcmp(empresas[meio].cnpj, criterio_procurado);
        }
        if (cmp == 0) 
        {
            return meio; /* Criterio encontrado */
        } 
        else if (cmp < 0) 
        {
            esquerda = meio + 1; /* Criterio procurado está na metade direita */
        } 
        else 
        {
            direita = meio - 1; /* Criterio procurado está na metade esquerda */
        }
    }

    return -1; /* Criterio não encontrado */
}

Empresa *aloca_empresas()
{
    Empresa *empresas = malloc(TAMANHO_BLOCO * sizeof(Empresa));
    if (!empresas) 
    {
        fprintf(stderr, "Erro de alocação de memória.\n");
        exit(EXIT_FAILURE);
    }

    return empresas;
}

void aloca_memoria_campos(Empresa *empresa, const char *cnpj, const char *nome, const char *natureza_juridica,
                          const char *qualificacao_responsavel, const char *capital_social, const char *porte,
                          const char *ente_federativo) 
{
    empresa->cnpj = malloc(strlen(cnpj) + 1);
    empresa->nome = malloc(strlen(nome) + 1);
    empresa->natureza_juridica = malloc(strlen(natureza_juridica) + 1);
    empresa->qualificacao_responsavel = malloc(strlen(qualificacao_responsavel) + 1);
    empresa->capital_social = malloc(strlen(capital_social) + 1);
    empresa->porte = malloc(strlen(porte) + 1);
    empresa->ente_federativo = malloc(strlen(ente_federativo) + 1);

    if (!empresa->cnpj || !empresa->nome || !empresa->natureza_juridica ||
        !empresa->qualificacao_responsavel || !empresa->capital_social ||
        !empresa->porte || !empresa->ente_federativo) 
    {
        fprintf(stderr, "Erro de alocação de memória para campos.\n");
        exit(EXIT_FAILURE);
    }
}

void preenche_empresa(Empresa *empresa, const char *cnpj, const char *nome, const char *natureza_juridica,
                      const char *qualificacao_responsavel, const char *capital_social, const char *porte,
                      const char *ente_federativo) 
{
    strcpy(empresa->cnpj, cnpj);
    strcpy(empresa->nome, nome);
    strcpy(empresa->natureza_juridica, natureza_juridica);
    strcpy(empresa->qualificacao_responsavel, qualificacao_responsavel);
    strcpy(empresa->capital_social, capital_social);
    strcpy(empresa->porte, porte);
    strcpy(empresa->ente_federativo, ente_federativo);
}

int processa_linha(char *linha, Empresa *empresa) 
{
    char *cnpj = strtok(linha, ";");
    char *nome = strtok(NULL, ";");
    char *natureza_juridica = strtok(NULL, ";");
    char *qualificacao_responsavel = strtok(NULL, ";");
    char *capital_social = strtok(NULL, ";");
    char *porte = strtok(NULL, ";");
    char *ente_federativo = strtok(NULL, ";");

    if (!cnpj || !nome || !natureza_juridica || !qualificacao_responsavel || !capital_social || !porte || !ente_federativo) 
    {
        return 0; /* Linha mal formatada */
    }

    aloca_memoria_campos(empresa, cnpj, nome, natureza_juridica, qualificacao_responsavel, capital_social, porte, ente_federativo);
    preenche_empresa(empresa, cnpj, nome, natureza_juridica, qualificacao_responsavel, capital_social, porte, ente_federativo);
    
    return 1; /* Linha processada com sucesso */
}


void free_empresas(Empresa *empresas, int count)
{
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

int compara_nome(const void *a, const void *b) 
{
    return strcmp(((Empresa *)a)->nome, ((Empresa *)b)->nome);
}

void processar_bloco(FILE *file, char *criterio_procurado, int *encontrado, 
                    int busca_por_nome) 
{
    Empresa *empresas = aloca_empresas();
    int count = 0;
    char linha[256];

    while (fgets(linha, sizeof(linha), file)) 
    {
        if (processa_linha(linha, &empresas[count])) 
        {
            count++;
            if (count >= TAMANHO_BLOCO) 
            {
                break;
            }
        }
    }

    if(busca_por_nome)
    {
        qsort(empresas, count, sizeof(Empresa), compara_nome);
    }

    int indice = busca_binaria(empresas, count, criterio_procurado, busca_por_nome);

    if (indice != -1) 
    {
        imprime_empresa(&empresas[indice]);
        *encontrado = 1;
    }

    free_empresas(empresas, count);
}

void busca_por_criterio(char *criterio_procurado, FILE *file, int busca_por_nome)
{
    int encontrado = 0;

    while (!encontrado && !feof(file)) 
    {
        processar_bloco(file, criterio_procurado, &encontrado, busca_por_nome);
    }

    fclose(file);

    if (!encontrado) 
    {
        printf("Criterio não encontrado.\n");
    }
}
