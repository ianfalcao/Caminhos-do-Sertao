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

void alterarRapadura(int quantidade) {
    if (quantidade == 0) {
        return;
    }

    if (rapadura + quantidade < 0) {
        printf("Rapadura insuficiente no inventario!\n");
    } else {
        rapadura += quantidade;
    }
}


void alterarRemedio(int quantidade) {
    if (quantidade == 0) {
        return;
    }

    if (remedio + quantidade < 0) {
        printf("Remedio insuficiente no inventario!\n");
    } else {
        remedio += quantidade;
    }
}


void mostrarInventario(void) {
    printf("\n===== INVENTARIO =====\n");

    printf("Agua: %d\n", agua);
    printf("Rapadura: %d\n", rapadura);
    printf("Remedio: %d\n", remedio);
    printf("Farinha: %d\n", farinha);

    printf("======================\n");
}