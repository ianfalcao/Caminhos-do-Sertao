#include <stdio.h>
#include "jogo.h"

/* Limpa a tela e posiciona o cursor no inicio. */
void limparTela(void)
{
    printf("\033[2J\033[H");
    fflush(stdout);
}