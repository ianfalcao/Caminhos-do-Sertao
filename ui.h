#ifndef UI_H
#define UI_H

#include <stdio.h>

/* Codigos ANSI de cor e estilo para o terminal. */
#define COR_RESET    "\033[0m"
#define COR_NEGRITO  "\033[1m"
#define COR_DIM      "\033[2m"
#define COR_VERMELHO "\033[31m"
#define COR_VERDE    "\033[32m"
#define COR_AMARELO  "\033[33m"
#define COR_CIANO    "\033[36m"

/*
 * Desenha uma barra proporcional ao valor atual:
 * [#####-----] para atual = 5, maximo = 10 e largura = 10.
 */
static inline void mostrarBarra(int atual, int maximo, int largura, const char *cor)
{
    int preenchido = 0;

    if (maximo > 0 && atual > 0)
    {
        preenchido = (atual * largura) / maximo;

        if (preenchido > largura)
        {
            preenchido = largura;
        }
    }

    printf("[%s", cor);

    for (int i = 0; i < largura; i++)
    {
        putchar(i < preenchido ? '#' : '-');
    }

    printf(COR_RESET "]");
}

/* Linha discreta para separar blocos de informacao. */
static inline void mostrarSeparador(void)
{
    printf(COR_DIM "------------------------------------------" COR_RESET "\n");
}

#endif
