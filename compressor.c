#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_JANELA 32768  
#define TAMANHO_BUFFER 32 

typedef struct {
    int deslocamento;
    int comprimento;
    char proxChar;
} Correspondencia;

Correspondencia encontrarCorrespondencia(char *janela, char *buffer, int tamanhoJanela, int tamanhoBuffer) {
    Correspondencia correspondencia = {0, 0, buffer[0]};

    for (int i = 0; i < tamanhoJanela; i++) {
        int j = 0;
        while (j < tamanhoBuffer && janela[i + j] == buffer[j]) {
            j++;
        }
        if (j > correspondencia.comprimento) {
            correspondencia.deslocamento = tamanhoJanela - i;
            correspondencia.comprimento = j;
            correspondencia.proxChar = buffer[j];
        }
    }

    return correspondencia;
}

void comprimirArquivo(FILE *entrada, FILE *saida) {
    char janela[TAMANHO_JANELA] = {0};
    char buffer[TAMANHO_BUFFER] = {0};
    int tamanhoJanela = 0;
    int tamanhoBuffer = fread(buffer, 1, TAMANHO_BUFFER, entrada);
    long totalBytesLidos = 0;

    while (tamanhoBuffer > 0) {
        Correspondencia correspondencia = encontrarCorrespondencia(janela, buffer, tamanhoJanela, tamanhoBuffer);
        fwrite(&correspondencia, sizeof(Correspondencia), 1, saia);

        int tamanhoMovimento = (tamanhoJanela - correspondencia.comprimento - 1 > 0) ? tamanhoJanela - correspondencia.comprimento - 1 : 0;
        memmove(janela, janela + correspondencia.comprimento + 1, tamanhoMovimento);
        memmove(janela + tamanhoMovimento, buffer, correspondencia.comprimento + 1);

        tamanhoJanela = (tamanhoJanela + correspondencia.comprimento + 1) < TAMANHO_JANELA ? tamanhoJanela + correspondencia.comprimento + 1 : TAMANHO_JANELA;
        totalBytesLidos += tamanhoBuffer;
        
        if (totalBytesLidos % (100 * 1024 * 1024) < TAMANHO_BUFFER) { // A cada ~100 MB processados
            printf("Bytes processados: %ld MB\n", totalBytesLidos / (1024 * 1024));
        }

        tamanhoBuffer = fread(buffer, 1, TAMANHO_BUFFER, entrada);
    }

    printf("Compressão concluída.\n");
}

int main(int argc, char *argv[]) {
    // Pra executar ./compressor Empresas.EMPRECSV saida_comprimida.lz77

    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo_entrada> <arquivo_saida>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *entrada = fopen(argv[1], "rb");
    if (!entrada) {
        perror("Falha ao abrir o arquivo de entrada");
        return EXIT_FAILURE;
    }

    FILE *saida = fopen(argv[2], "wb");
    if (!saida) {
        perror("Falha ao abrir o arquivo de saída");
        fclose(entrada);
        return EXIT_FAILURE;
    }

    comprimirArquivo(entrada, saida);

    fclose(entrada);
    fclose(saida);

    printf("Programa finalizado com sucesso.\n");
    return EXIT_SUCCESS;
}
