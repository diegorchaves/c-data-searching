#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void remove_nova_linha(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') 
    {
        str[len - 1] = '\0';
    }
}

char* adicionar_aspas(const char *str_original) 
{
    /* Calcula o tamanho da nova string */
    size_t tamanho_nova = strlen(str_original) + 3;

    /* Aloca memória para a nova string */
    char *nova_str = (char *)malloc(tamanho_nova * sizeof(char));
    if (nova_str == NULL) 
    {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }

    /* Constrói a nova string com aspas duplas */
    nova_str[0] = '"';
    strcpy(&nova_str[1], str_original);
    nova_str[tamanho_nova - 2] = '"';        
    nova_str[tamanho_nova - 1] = '\0';         

    return nova_str;
}