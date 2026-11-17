
#include <stdio.h>

/* Funcoes do inventario */
void alterarAgua(int quantidade);
void alterarRapadura(int quantidade);
void alterarRemedio(int quantidade);
void alterarFarinha(int quantidade);

void mostrarInventario(void);

int consultarAgua(void);
int consultarRapadura(void);
int consultarRemedio(void);
int consultarFarinha(void);

/* Funcoes de consumo do inventario */
int consumirAgua(void);
int consumirRapadura(void);
int consumirRemedio(void);
int consumirFarinha(void);

int main(void) {

    printf("=== TESTE DO INVENTARIO ===\n");

    /* Teste 1: Inventario vazio */
    printf("\nTeste 1 - Inventario inicial:\n");
    mostrarInventario();

    /* Teste 2: Adicionar itens */
    printf("\nTeste 2 - Adicionando itens:\n");

    alterarAgua(10);
    alterarRapadura(5);
    alterarRemedio(3);
    alterarFarinha(8);

    mostrarInventario();

    /* Teste 3: Remover itens */
    printf("\nTeste 3 - Removendo itens:\n");

    alterarAgua(-3);
    alterarRapadura(-2);
    alterarRemedio(-1);
    alterarFarinha(-4);

    mostrarInventario();

    /* Teste 4: Quantidades insuficientes */
    printf("\nTeste 4 - Remocao invalida:\n");

    alterarAgua(-100);
    alterarRapadura(-100);
    alterarRemedio(-100);
    alterarFarinha(-100);

    mostrarInventario();

    /* Teste 5: Consultar quantidades */
    printf("\nTeste 5 - Consultando itens:\n");

    printf("Agua: %d\n", consultarAgua());
    printf("Rapadura: %d\n", consultarRapadura());
    printf("Remedio: %d\n", consultarRemedio());
    printf("Farinha: %d\n", consultarFarinha());

    /* Teste 6: Alteracao com zero */
    printf("\nTeste 6 - Alterando com zero:\n");
    alterarAgua(2);

    alterarAgua(0);
    alterarRapadura(0);
    alterarRemedio(0);
    alterarFarinha(0);

    mostrarInventario();

    /* Teste 7: Consumo */
    printf("\n=== TESTE DE CONSUMO ===\n");

    /* Adicionando itens */
    alterarAgua(3);
    alterarRapadura(2);
    alterarRemedio(1);
    alterarFarinha(3);

    printf("\nAntes do consumo:\n");
    mostrarInventario();

    /* Consumindo uma unidade de cada item */
    consumirAgua();
    consumirRapadura();
    consumirRemedio();
    consumirFarinha();

    printf("\nDepois do consumo:\n");
    mostrarInventario();

    /* Testando item vazio */
    consumirRemedio();


    return 0;
}
