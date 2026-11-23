#include <stdio.h>

/* 0 = estrada, 1 = poco, 2 = armazem,
   3 = emboscada, 4 = destino */
static int mapa[5][5] = {
    {0, 0, 1, 0, 0},
    {0, 2, 0, 3, 0},
    {1, 0, 0, 0, 2},
    {0, 3, 1, 0, 0},
    {0, 0, 0, 2, 4}
};

static int visitado[5][5];
static int linhaJogador;
static int colunaJogador;

void inicializarMapa(void)
{
    linhaJogador = 0;
    colunaJogador = 0;

    for (int linha = 0; linha < 5; linha++)
    {
        for (int coluna = 0; coluna < 5; coluna++)
        {
            visitado[linha][coluna] = 0;
        }
    }

    visitado[0][0] = 1;
}