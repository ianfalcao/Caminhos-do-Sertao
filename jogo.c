#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ui.h"
#include "jogo.h"


/* Converte W/A/S/D (ou 1 a 4) na direcao usada por moverJogador. Retorna 0 se nao for valida. */
static int direcaoDeTecla(char tecla)
{
    switch (tecla)
    {
        case '1': case 'w': case 'W': return 1;
        case '2': case 's': case 'S': return 2;
        case '3': case 'd': case 'D': return 3;
        case '4': case 'a': case 'A': return 4;
        default: return 0;
    }
}

void jogar(void)
{
    int dia = 1;
    int vida = 10;
    int op;

    /* Cada partida comeca com inventario e mapa reiniciados. */
    inicializarInventario();
    inicializarMapa();

    printf("\nEncontre o destino no mapa para cruzar o sertao!\n");

    /* A jornada termina ao chegar ao destino ou perder toda a vida. */
    while (!chegouAoDestino() && vida > 0)
    {
        /* Sorteia o clima: 60% ameno, 25% sol e 15% seca. */
        int sorteio = rand() % 100;
        int clima;

        if (sorteio < 60)
            clima = 0;
        else if (sorteio < 85)
            clima = 1;
        else
            clima = 2;

        mostrarMapa();

        mostrarSeparador();
        printf(COR_NEGRITO "Dia %d" COR_RESET " | Clima: ", dia);

        if (clima == 0)
            printf(COR_VERDE "Ameno" COR_RESET "\n");
        else if (clima == 1)
            printf(COR_AMARELO "Sol forte" COR_RESET "\n");
        else
            printf(COR_VERMELHO "Seca severa" COR_RESET "\n");

        printf("Vida:      ");
        mostrarBarra(vida, 10, 10, COR_VERMELHO);
        printf(" %d/10\n", vida);

        printf("Agua: %d | Rapadura: %d | Remedio: %d\n",
               consultarAgua(), consultarRapadura(), consultarRemedio());

        char tecla = 0;

        printf("1 - Explorar o mapa\n");
        printf("2 - Descansar na sombra\n");
        printf("3 - Comer rapadura\n");
        printf("W/A/S/D - Andar direto\n");
        printf("I - Inventario\n");
        mostrarPrompt("Escolha:");

        /* Le um caractere, ignorando espacos e quebras de linha. */
        int leitura = scanf(" %c", &tecla);
        int direcaoRapida = 0;

        if (leitura == EOF)
        {
            printf("\nEntrada encerrada. Voltando ao menu.\n");
            return;
        }

        /* WASD anda direto; 1, 2 e 3 escolhem a acao do menu. */
        if (isalpha((unsigned char)tecla) && direcaoDeTecla(tecla) != 0)
        {
            op = 1;
            direcaoRapida = direcaoDeTecla(tecla);
        }
        else if (tecla >= '1' && tecla <= '3')
        {
            op = tecla - '0';
        }
        else if (tecla == 'i' || tecla == 'I')
        {
            op = 4;
        }
        else
        {
            op = 0;
        }

        limparTela();
        /* O clima determina o custo de agua do movimento. */
        int consumoAgua = clima + 1;

        if (op == 1)
        {
            int direcao = direcaoRapida;

            /* Sem tecla WASD no menu principal, pergunta a direcao. */
            if (direcaoRapida == 0)
            {
                printf("\n1 (W) - Norte\n2 (S) - Sul\n");
                printf("3 (D) - Leste\n4 (A) - Oeste\n");
                mostrarPrompt("Direcao:");

                leitura = scanf(" %c", &tecla);

                if (leitura == EOF)
                {
                    printf("\nEntrada encerrada. Voltando ao menu.\n");
                    return;
                }

                direcao = direcaoDeTecla(tecla);

                if (direcao == 0)
                {
                    printf("Use W, A, S, D ou 1 a 4.\n");
                    continue;
                }
            }

            limparTela();

            /*
             * Movimento invalido nao gasta agua nem avanca o dia.
             * moverJogador verifica os limites da matriz.
             */
            if (!moverJogador(direcao))
            {
                continue;
            }

            /* Gasta somente a agua disponivel, sem saldo negativo. */
            int aguaAtual = consultarAgua();
            int gasto = consumoAgua;

            if (gasto > aguaAtual)
                gasto = aguaAtual;

            alterarAgua(-gasto);

            /*
             * Consulta visitado antes de marcar a casa.
             * Assim, eventos e recompensas acontecem uma unica vez.
             */
            if (!localAtualFoiVisitado())
            {
                int local = consultarLocalAtual();

                marcarLocalAtualVisitado();

                if (local == 0)
                {
                    /*
                     * Cada estrada tem 30% de chance de encontro
                     * na primeira visita. O restante e caminhada tranquila.
                     */
                    if (rand() % 100 < 30)
                    {
                        printf(COR_VERMELHO COR_NEGRITO "Um salteador apareceu na estrada!" COR_RESET "\n");
                        iniciarCombate(&vida);

                        if (vida <= 0)
                        {
                            break;
                        }
                    }
                    else
                    {
                        printf(COR_DIM "Voce segue por uma estrada tranquila." COR_RESET "\n");
                    }
                }
                else if (local == 1)
                {
                    if (alterarAgua(5))
                    {
                        printf(COR_CIANO "Voce encontrou um poco! (+5 agua)" COR_RESET "\n");
                    }
                }
                else if (local == 2)
                {
                    printf(COR_AMARELO COR_NEGRITO "Voce encontrou um armazem abandonado!" COR_RESET "\n");

                    if (alterarRapadura(1))
                        printf("Encontrou 1 rapadura!\n");

                    if (alterarRemedio(1))
                        printf("Encontrou 1 remedio!\n");
                }
                else if (local == 3)
                {
                    printf(COR_VERMELHO COR_NEGRITO "Uma emboscada no caminho!" COR_RESET "\n");
                    iniciarCombate(&vida);

                    /* Encerra a jornada imediatamente se morrer. */
                    if (vida <= 0)
                        break;
                }
                else if (local == 4)
                {
                    printf(COR_VERDE COR_NEGRITO "Voce encontrou a chegada!" COR_RESET "\n");
                }
            }
            else
            {
                printf(COR_DIM "Voce voltou a um local ja explorado." COR_RESET "\n");
            }
        }
        else if (op == 2)
        {
            int gasto = consumoAgua > 1 ? 2 : 1;
            int aguaAtual = consultarAgua();

            if (gasto > aguaAtual)
                gasto = aguaAtual;

            alterarAgua(-gasto);

            vida += 2;

            if (vida > 10)
                vida = 10;

            printf("Voce descansou. Vida atual: %d/10\n", vida);
        }
        else if (op == 3)
{
    if (vida >= 10)
    {
        printf("Sua vida ja esta cheia!\n");
        continue;
    }

    if (consultarRapadura() <= 0)
    {
        printf("A rapadura acabou!\n");
        continue;
    }

    alterarRapadura(-1);
    vida += 4;

    if (vida > 10)
        vida = 10;

    printf("Voce comeu rapadura. Vida atual: %d/10\n", vida);
}
        else if (op == 4)
        {
            /* Ver o inventario nao gasta agua nem avanca o dia. */
            mostrarInventario();
            continue;
        }
        else
        {
            printf("Opcao invalida!\n");
            continue;
        }

        /*
         * Mantem a regra da jornada: depois da acao e do evento,
         * ficar sem agua causa dano, inclusive na chegada.
         */
        if (consultarAgua() == 0)
        {
            vida -= 3;

            if (vida < 0)
                vida = 0;

            printf(COR_VERMELHO COR_NEGRITO "DESIDRATACAO!" COR_RESET " Voce perdeu 3 de vida.\n");
        }

        dia++;
    }

    mostrarMapa();

    if (vida > 0 && chegouAoDestino())
    {
        printf("\n");
        mostrarBanner(COR_NEGRITO COR_VERDE, "PARABENS! Voce chegou ao destino com vida!");
    }
    else
    {
        printf("\n");
        mostrarBanner(COR_NEGRITO COR_VERMELHO, "FIM DE JOGO: o sertao foi implacavel...");
    }
}