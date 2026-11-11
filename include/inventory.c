#include <stdio.h>

/* Quantidade de itens do jogador */
int agua = 0;
int rapadura = 0;
int remedio = 0;
int farinha = 0;

/* Dinheiro do jogador */
int moedas = 0;


void alterarAgua(int quantidade) {
    if (quantidade == 0) {
        return;
    }

    if (agua + quantidade < 0) {
        printf("Agua insuficiente no inventario!\n");
    } else {
        agua += quantidade;
    }
}
