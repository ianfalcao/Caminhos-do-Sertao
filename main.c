#include <stdlib.h>
#include <time.h>

/* Funcao implementada em menu.c. */
void executarMenu(void);

int main(void)
{
    /* Inicializa os sorteios uma vez ao abrir o programa. */
    srand((unsigned int)time(NULL));

    executarMenu();

    return 0;
}