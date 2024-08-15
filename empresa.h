#ifndef EMPRESA_H
#define EMPRESA_H

typedef struct empresa Empresa;

struct empresa 
{
    char *cnpj;
    char *nome;
    char *natureza_juridica;
    char *qualificacao_responsavel;
    char *capital_social;
    char *porte;
    char *ente_federativo;

    Empresa *next;
};

#endif