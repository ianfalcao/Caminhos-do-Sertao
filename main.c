#include <stdio.h>

void mostrarMenu(void) {
    printf("\n=== CAMINHOS DO SERTAO ===\n");
    printf("1 - Novo Jogo\n");
    printf("2 - Como Jogar\n");
    printf("3 - Sair\n");
    printf("Escolha: ");
}

void comoJogar(void) {
    printf("\n--- COMO JOGAR ---\n");
    printf("(coloca o texto de como jogar aqui)\n");
}

int main() {
    int opcao;

    do {
        mostrarMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: printf("\nIniciando jogo...\n"); break;
            case 2: comoJogar(); break;
            case 3: printf("\nAte logo!\n"); break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (opcao != 3);

    return 0;
}