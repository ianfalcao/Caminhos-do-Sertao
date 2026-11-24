#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <string.h>

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

/*
 * Mostra um campo de digitacao com moldura amarela.
 * O cursor fica dentro da moldura, logo apos o rotulo.
 */
static inline void mostrarPrompt(const char *rotulo)
{
    int colunas = (int)strlen(rotulo) + 1; /* "rotulo " */

    printf(COR_AMARELO COR_NEGRITO "==============================\n" COR_RESET);
    printf(COR_AMARELO COR_NEGRITO "%s " COR_RESET "\n", rotulo);
    printf(COR_AMARELO COR_NEGRITO "==============================" COR_RESET "\n");

    /* Sobe para a linha do rotulo e posiciona o cursor depois dele. */
    printf("\033[2A\033[%dC", colunas);
    fflush(stdout);
}

/*
 * Mostra um texto em destaque, emoldurado pelas linhas amarelas.
 * A moldura acompanha o tamanho do texto, com no minimo 30 colunas.
 */
static inline void mostrarBanner(const char *cor, const char *texto)
{
    int largura = (int)strlen(texto);

    if (largura < 30)
    {
        largura = 30;
    }

    printf(COR_AMARELO COR_NEGRITO);

    for (int i = 0; i < largura; i++)
    {
        putchar('=');
    }

    printf(COR_RESET "\n%s%s" COR_RESET "\n", cor, texto);
    printf(COR_AMARELO COR_NEGRITO);

    for (int i = 0; i < largura; i++)
    {
        putchar('=');
    }

    printf(COR_RESET "\n");
}

#endif
