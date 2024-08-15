#ifndef BUSCA_H
#define BUSCA_H

int busca_binaria(Empresa *empresas, int tamanho, const char *criterio_procurado,
                  int busca_por_nome);

int compara_cnpj(const void *a, const void *b);

Empresa *aloca_empresas();

void aloca_memoria_campos(Empresa *empresa, const char *cnpj, const char *nome, const char *natureza_juridica,
                          const char *qualificacao_responsavel, const char *capital_social, const char *porte,
                          const char *ente_federativo);

void preenche_empresa(Empresa *empresa, const char *cnpj, const char *nome, const char *natureza_juridica,
                      const char *qualificacao_responsavel, const char *capital_social, const char *porte,
                      const char *ente_federativo);

int processa_linha(char *linha, Empresa *empresa);

void processar_bloco(FILE *file, char *criterio_procurado, int *encontrado, 
                    int busca_por_nome);

void free_empresas(Empresa *empresas, int count);

void busca_por_criterio(char *criterio_procurado, FILE *file, int busca_por_nome);

#endif