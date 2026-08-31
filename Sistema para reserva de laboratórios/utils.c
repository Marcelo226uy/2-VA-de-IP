#include <stdio.h>
#include <string.h>
#include "utils.h"

int lerInteiro(int *valor) {
// Função para impedir que scanf deixe lixo no buffer (o \n principalmente) e para permitir validar entradas que não são números.
    char linha[100];
    char extra;

    if (fgets(linha, sizeof(linha), stdin) == NULL)
        return 0;

    if (sscanf(linha, " %d %c", valor, &extra) != 1)
        return 0;

    return 1;
}

void lerTexto(char *texto, int tamanho) {
// Função para ler o texto e remover o '\n' colocado pelo fgets.
    if (fgets(texto, tamanho, stdin) != NULL) {
        texto[strcspn(texto, "\n")] = '\0';
    }
}

