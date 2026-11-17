#include <stdio.h>
#include <limits.h>

/* Quantidade de itens do jogador */
int agua = 0;
int rapadura = 0;
int remedio = 0;
int farinha = 0;



int alterarAgua(int quantidade) {
    if (quantidade == 0) {
        return 1;
    }

    if (quantidade > 0 && agua > INT_MAX - quantidade) {
        printf("Quantidade de agua muito grande!\n");
        return 0;
    }

    if ((long long)agua + quantidade < 0) {
        printf("Agua insuficiente no inventario!\n");
        return 0;
    }

    agua += quantidade;
    return 1;
}

int alterarRapadura(int quantidade) {
    if (quantidade == 0) {
        return 1;
    }

    if (quantidade > 0 && rapadura > INT_MAX - quantidade) {
        printf("Quantidade de rapadura muito grande!\n");
        return 0;
    }

    if ((long long)rapadura + quantidade < 0) {
        printf("Rapadura insuficiente no inventario!\n");
        return 0;
    }

    rapadura += quantidade;
    return 1;
}

int alterarRemedio(int quantidade) {
    if (quantidade == 0) {
        return 1;
    }

    if (quantidade > 0 && remedio > INT_MAX - quantidade) {
        printf("Quantidade de remedio muito grande!\n");
        return 0;
    }

    if ((long long)remedio + quantidade < 0) {
        printf("Remedio insuficiente no inventario!\n");
        return 0;
    }

    remedio += quantidade;
    return 1;
}

int alterarFarinha(int quantidade) {
    if (quantidade == 0) {
        return 1;
    }

    if (quantidade > 0 && farinha > INT_MAX - quantidade) {
        printf("Quantidade de farinha muito grande!\n");
        return 0;
    }

    if ((long long)farinha + quantidade < 0) {
        printf("Farinha insuficiente no inventario!\n");
        return 0;
    }

    farinha += quantidade;
    return 1;
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

int consultarRapadura(void) {
    return rapadura;
}

int consultarRemedio(void) {
    return remedio;
}

int consultarFarinha(void) {
    return farinha;
}

int consumirAgua(void) {
    if (agua <= 0) {
        printf("Voce nao possui agua!\n");
        return 0;
    }

    alterarAgua(-1);

    printf("Voce consumiu uma unidade de agua!\n");
    return 1;
}

int consumirRapadura(void) {
    if (rapadura <= 0) {
        printf("Voce nao possui rapadura!\n");
        return 0;
    }

    alterarRapadura(-1);

    printf("Voce consumiu uma rapadura!\n");
    return 1;
}

int consumirRemedio(void) {
    if (remedio <= 0) {
        printf("Voce nao possui remedio!\n");
        return 0;
    }

    alterarRemedio(-1);

    printf("Voce utilizou um remedio!\n");
    return 1;
}

int consumirFarinha(void) {
    if (farinha <= 0) {
        printf("Voce nao possui farinha!\n");
        return 0;
    }

    alterarFarinha(-1);

    printf("Voce consumiu uma porcao de farinha!\n");
    return 1;
}
