#include <stdio.h>

/*
 * Cada posicao da matriz representa um local do sertao.
 *
 * Tipos de local:
 * 0 = estrada
 * 1 = poco
 * 2 = armazem
 * 3 = emboscada
 * 4 = destino
 *
 * O primeiro indice indica a linha e o segundo, a coluna.
 * Exemplo: mapa[0][2] representa um poco.
 *
 * "static" limita o acesso direto a esta variavel ao arquivo mapa.c.
 */

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

void mostrarMapa(void)
{
    printf("\n=== MAPA DO SERTAO ===\n");

    for (int linha = 0; linha < 5; linha++)
    {
        for (int coluna = 0; coluna < 5; coluna++)
        {
            char simbolo;

            if (linha == linhaJogador && coluna == colunaJogador)
            {
                simbolo = 'J';
            }
            else if (visitado[linha][coluna])
            {
                simbolo = '.';
            }
            else if (mapa[linha][coluna] == 4)
            {
                simbolo = 'D';
            }
            else
            {
                simbolo = '?';
            }

            printf("[%c] ", simbolo);
        }

        printf("\n");
    }

    printf("J = jogador | D = destino\n");
    printf(". = explorado | ? = desconhecido\n");
}