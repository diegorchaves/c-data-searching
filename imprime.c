#include <stdio.h>

#include "imprime.h"

void imprime_empresa (Empresa *empresa)
{
    printf("CNPJ: %s\n", empresa->cnpj);
    printf("RAZÃO SOCIAL: %s\n", empresa->nome);
    printf("NATUREZA JURÍDICA: %s\n", empresa->natureza_juridica);
    printf("QUALIFICAÇÃO DO RESPONSÁVEL: %s\n", empresa->qualificacao_responsavel);
    printf("CAPITAL SOCIAL DA EMPRESA: %s\n", empresa->capital_social);
    printf("PORTE DA EMPRESA: %s\n", empresa->porte);
    printf("ENTE FEDERATIVO RESPONSÁVEL: %s\n", empresa->ente_federativo);
}