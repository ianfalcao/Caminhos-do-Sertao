#include <stdio.h>
#include <stdlib.h>

/* Funcao implementada em main.c. */
void limparTela(void);

/* Funcoes implementadas em inventory.c */
int consumirRemedio(void);
int alterarAgua(int quantidade);
int alterarRapadura(int quantidade);
int alterarRemedio(int quantidade);

void iniciarCombate(int *vidaJogador)
{
    int vidaInimigo = 5;
    int opcao;

    printf("\nUm salteador bloqueia sua passagem!\n");

    while (*vidaJogador > 0 && vidaInimigo > 0)
    {
        printf("\n=== COMBATE ===\n");
        printf("Sua vida: %d/10 | Vida do salteador: %d/5\n",
               *vidaJogador, vidaInimigo);
        printf("1 - Atacar\n2 - Usar remedio\n3 - Fugir\nEscolha: ");

        int leitura = scanf("%d", &opcao);

        if (leitura == EOF)
        {
            *vidaJogador = 0;
            printf("\nEntrada encerrada. A partida sera finalizada.\n");
            return;
        }

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
            int dano = 1 + rand() % 3;
            vidaInimigo -= dano;

            if (vidaInimigo < 0)
            {
                vidaInimigo = 0;
            }

            printf("Voce causou %d de dano!\n", dano);
        }
        else if (opcao == 2)
        {
            if (*vidaJogador >= 10)
            {
                printf("Sua vida ja esta cheia!\n");
                continue;
            }

            if (!consumirRemedio())
            {
                continue;
            }

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

        /* O inimigo so ataca se ainda estiver vivo. */
        if (vidaInimigo > 0)
        {
            int dano = 1 + rand() % 2;
            *vidaJogador -= dano;

            if (*vidaJogador < 0)
            {
                *vidaJogador = 0;
            }

            printf("O salteador causou %d de dano!\n", dano);
        }
    }

    if (*vidaJogador <= 0)
    {
        printf("\nVoce foi derrotado pelo salteador.\n");
        return;
    }

    printf("\nVoce derrotou o salteador!\n");

    /* Sorteia exatamente uma recompensa. */
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

    if (!recebeu)
    {
        printf("Seu estoque desse item esta cheio.\n");
    }
}