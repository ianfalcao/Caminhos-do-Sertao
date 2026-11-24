#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "jogo.h"

/* O ponteiro permite alterar a vida original do jogador. */
void iniciarCombate(int *vidaJogador)
{
    int vidaInimigo = 5;
    int opcao;

    printf("\nUm salteador bloqueia sua passagem!\n");

    /* O combate continua enquanto os dois estiverem vivos. */
    while (*vidaJogador > 0 && vidaInimigo > 0)
    {
        printf("\n" COR_NEGRITO COR_AMARELO "=== COMBATE ===" COR_RESET "\n");
        printf("Voce:      ");
        mostrarBarra(*vidaJogador, 10, 10, COR_VERDE);
        printf(" %d/10\n", *vidaJogador);
        printf("Salteador: ");
        mostrarBarra(vidaInimigo, 5, 10, COR_VERMELHO);
        printf(" %d/5\n", vidaInimigo);
        printf("1 - Atacar\n2 - Usar remedio\n3 - Fugir\nEscolha: ");

        int leitura = scanf("%d", &opcao);

        /* Finaliza a partida se a entrada for encerrada. */
        if (leitura == EOF)
        {
            *vidaJogador = 0;
            printf("\nEntrada encerrada. A partida sera finalizada.\n");
            return;
        }

        /* Descarta texto invalido e pede outra escolha. */
        if (leitura != 1)
        {
            int caractere;

            while ((caractere = getchar()) != '\n' && caractere != EOF)
            {
            }

            printf("Digite uma opcao numerica.\n");
            continue;
        }

        limparTela();

        if (opcao == 1)
        {
            /* Sorteia um ataque de 1 a 3 de dano. */
            int dano = 1 + rand() % 3;
            vidaInimigo -= dano;

            if (vidaInimigo < 0)
            {
                vidaInimigo = 0;
            }

            printf(COR_VERDE "Voce causou %d de dano!" COR_RESET "\n", dano);
        }
        else if (opcao == 2)
        {
            /* Vida cheia ou falta de remedio nao gastam o turno. */
            if (*vidaJogador >= 10)
            {
                printf("Sua vida ja esta cheia!\n");
                continue;
            }

            if (!consumirRemedio())
            {
                continue;
            }

            /* Recupera ate 3 pontos, sem ultrapassar 10 de vida. */
            int recuperacao = 10 - *vidaJogador;

            if (recuperacao > 3)
            {
                recuperacao = 3;
            }

            *vidaJogador += recuperacao;
            printf("Voce recuperou %d de vida!\n", recuperacao);
        }
        else if (opcao == 3)
        {
            /* A fuga tem 50% de chance e nao entrega recompensa. */
            if (rand() % 2 == 0)
            {
                printf("Voce conseguiu fugir!\n");
                return;
            }

            printf("Voce tentou fugir, mas o salteador te alcancou!\n");
        }
        else
        {
            printf("Opcao invalida!\n");
            continue;
        }

        /* Se sobreviver, o inimigo contra-ataca com 1 ou 2 de dano. */
        if (vidaInimigo > 0)
        {
            int dano = 1 + rand() % 2;
            *vidaJogador -= dano;

            if (*vidaJogador < 0)
            {
                *vidaJogador = 0;
            }

            printf(COR_VERMELHO "O salteador causou %d de dano!" COR_RESET "\n", dano);
        }
    }

    /* A derrota encerra a funcao antes do sorteio de recompensa. */
    if (*vidaJogador <= 0)
    {
        printf("\n" COR_NEGRITO COR_VERMELHO "Voce foi derrotado pelo salteador." COR_RESET "\n");
        return;
    }

    printf("\n" COR_NEGRITO COR_VERDE "Voce derrotou o salteador!" COR_RESET "\n");

    /* Sorteia entre agua, rapadura e remedio. */
    int recompensa = rand() % 3;
    int recebeu;

    if (recompensa == 0)
    {
        recebeu = alterarAgua(2);

        if (recebeu)
        {
            printf("Voce encontrou 2 unidades de agua!\n");
        }
    }
    else if (recompensa == 1)
    {
        recebeu = alterarRapadura(1);

        if (recebeu)
        {
            printf("Voce encontrou 1 rapadura!\n");
        }
    }
    else
    {
        recebeu = alterarRemedio(1);

        if (recebeu)
        {
            printf("Voce encontrou 1 remedio!\n");
        }
    }

    /* A funcao alterar ja informou o motivo da falha, se houve. */
    if (!recebeu)
    {
        printf(COR_DIM "Nao foi possivel guardar o item." COR_RESET "\n");
    }
}