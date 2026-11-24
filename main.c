#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ui.h"
#include "jogo.h"

/* Limpa a tela e posiciona o cursor no inicio. */
void limparTela(void)
{
    printf("\033[2J\033[H");
    fflush(stdout);
}

/* Funcao para mostrar o Menu do game */
void mostrarMenu(void)
{
    printf("\n" COR_AMARELO COR_NEGRITO);
    printf("==============================\n");
    printf("CAMINHOS DO SERTAO\n");
    printf("==============================\n" COR_RESET);
    printf(COR_VERDE "1" COR_RESET " - Novo Jogo\n");
    printf(COR_CIANO "2" COR_RESET " - Como Jogar\n");
    printf(COR_VERMELHO "3" COR_RESET " - Sair\n");
    mostrarPrompt("Escolha:");
}

/* Funcao explicativa de como jogar */
void comoJogar(void)
{
    printf("\n");
    mostrarBanner(COR_NEGRITO COR_AMARELO, "COMO JOGAR");
    printf("- Explore o mapa ate chegar ao destino D.\n");
    printf("- Ande com W (norte), S (sul), D (leste) ou A (oeste).\n");
    printf("- Ou escolha 1 para explorar e depois a direcao.\n");
    printf("- Cada movimento valido gasta agua conforme o clima.\n");
    printf("- Pocos e armazens fornecem recursos na primeira visita.\n");
    printf("- Emboscadas iniciam combates na primeira visita.\n");
    printf("- Descansar recupera vida e gasta agua.\n");
    printf("- Comer rapadura recupera ate 4 de vida.\n");
    printf("- Ficar sem agua causa 3 de dano ao final da acao.\n");
    printf("- Tecle I para ver o inventario.\n");
    printf("- Chegue ao destino com vida para vencer.\n");
}

int main(void)
{
    int opcao;

    /* Inicializa os sorteios usando o horario atual. */
    srand(time(NULL));

    do
    {
        mostrarMenu();
        int leitura = scanf("%d", &opcao);

        /* Encerra o programa se a entrada for fechada. */
        if (leitura == EOF)
        {
            printf("\nEntrada encerrada. Ate logo!\n");
            break;
        }

        /* Descarta a entrada invalida quando nao for um numero. */
        if (leitura != 1)
        {
            int caractere;

            while ((caractere = getchar()) != '\n' && caractere != EOF)
            {
            }

            opcao = 0;
        }

        limparTela();

        /* Executa a acao correspondente a opcao escolhida. */
        switch (opcao)
        {
        case 1:
            jogar();
            break;
        case 2:
            comoJogar();
            break;
        case 3:
            printf("\n" COR_DIM "Ate logo!" COR_RESET "\n");
            break;
        default:
            printf("\n" COR_VERMELHO "Opcao invalida!" COR_RESET "\n");
        }

    } while (opcao != 3); /* Repete o menu ate escolher sair. */

    return 0;
}
