#include <stdio.h>
#include <limits.h>

/* Quantidade de itens do jogador */
int agua = 0;
int rapadura = 0;
int remedio = 0;
int farinha = 0;


void alterarAgua(int quantidade) {
    if (quantidade == 0) {
        return;
    }

    if (quantidade > 0 && agua > INT_MAX - quantidade) {
        printf("Quantidade de agua muito grande!\n");
        return;
    }

    if ((long long)agua + quantidade < 0) {
        printf("Agua insuficiente no inventario!\n");
        return;
    }

    agua += quantidade;
}



void alterarRapadura(int quantidade) {
    if (quantidade == 0) {
        return;
    }

    if (quantidade > 0 && rapadura > INT_MAX - quantidade) {
        printf("Quantidade de rapadura muito grande!\n");
        return;
    }

    if ((long long)rapadura + quantidade < 0) {
        printf("Rapadura insuficiente no inventario!\n");
        return;
    }

    rapadura += quantidade;
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


void alterarFarinha(int quantidade) {
    if (quantidade == 0) {
        return;
    }

    if (quantidade < 0 && farinha < -quantidade) {
        printf("Farinha insuficiente no inventario!\n");
    } else {
        farinha += quantidade;
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


int consultarAgua(void) {
    return agua;
}