#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Limpa a tela do terminal e leva o cursor ao inicio. */
void limparTela(void)
{
    printf("\033[2J\033[H");
    fflush(stdout);
}

/* Funcoes implementadas em mapa.c */
void inicializarMapa(void);
void mostrarMapa(void);
int moverJogador(int direcao);
int consultarLocalAtual(void);
int localAtualFoiVisitado(void);
void marcarLocalAtualVisitado(void);
int chegouAoDestino(void);

/* Necessaria para a recompensa do armazem. */
int alterarRemedio(int quantidade);

void inicializarInventario(void);
void iniciarCombate(int *vidaJogador);

int alterarAgua(int quantidade);
int alterarRapadura(int quantidade);

int consultarAgua(void);
int consultarRapadura(void);

void mostrarMenu(void)
{
    printf("\n=== CAMINHOS DO SERTAO ===\n");
    printf("1 - Novo Jogo\n2 - Como Jogar\n3 - Sair\nEscolha: ");
}

void comoJogar(void)
{
    printf("\n--- COMO JOGAR ---\n");
    printf("- Explore o mapa ate chegar ao destino D.\n");
    printf("- Escolha norte, sul, leste ou oeste para se mover.\n");
    printf("- Cada movimento valido gasta agua conforme o clima.\n");
    printf("- Pocos e armazens fornecem recursos na primeira visita.\n");
    printf("- Emboscadas iniciam combates na primeira visita.\n");
    printf("- Descansar recupera vida e gasta agua.\n");
    printf("- Comer rapadura recupera ate 4 de vida.\n");
    printf("- Ficar sem agua causa 3 de dano ao final da acao.\n");
    printf("- Chegue ao destino com vida para vencer.\n");
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

        printf("\nDia %d | Clima: ", dia);

        if (clima == 0)
            printf("Ameno\n");
        else if (clima == 1)
            printf("Sol forte\n");
        else
            printf("Seca severa\n");

        printf("Vida: %d/10 | Agua: %d | Rapadura: %d\n",
               vida, consultarAgua(), consultarRapadura());

        printf("1 - Explorar o mapa\n");
        printf("2 - Descansar na sombra\n");
        printf("3 - Comer rapadura\n");
        printf("Escolha: ");

        int leitura = scanf("%d", &op);

        if (leitura == EOF)
        {
            printf("\nEntrada encerrada. Voltando ao menu.\n");
            return;
        }

        if (leitura != 1)
        {
            int caractere;

            while ((caractere = getchar()) != '\n' &&
                   caractere != EOF)
            {
            }

            printf("Digite uma opcao numerica.\n");
            continue;
        }

        limparTela();
        /* O clima determina o custo de agua do movimento. */
        int consumoAgua = clima + 1;

        if (op == 1)
        {
            int direcao;

            printf("\n1 - Norte\n2 - Sul\n");
            printf("3 - Leste\n4 - Oeste\nDirecao: ");

            leitura = scanf("%d", &direcao);

            if (leitura == EOF)
            {
                printf("\nEntrada encerrada. Voltando ao menu.\n");
                return;
            }

            if (leitura != 1)
            {
                int caractere;

                while ((caractere = getchar()) != '\n' &&
                       caractere != EOF)
                {
                }

                printf("Digite uma direcao numerica.\n");
                continue;
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
                        printf("Um salteador apareceu na estrada!\n");
                        iniciarCombate(&vida);

                        if (vida <= 0)
                        {
                            break;
                        }
                    }
                    else
                    {
                        printf("Voce segue por uma estrada tranquila.\n");
                    }
                }
                else if (local == 1)
                {
                    if (alterarAgua(5))
                    {
                        printf("Voce encontrou um poco! (+5 agua)\n");
                    }
                }
                else if (local == 2)
                {
                    printf("Voce encontrou um armazem abandonado!\n");

                    if (alterarRapadura(1))
                        printf("Encontrou 1 rapadura!\n");

                    if (alterarRemedio(1))
                        printf("Encontrou 1 remedio!\n");
                }
                else if (local == 3)
                {
                    printf("Uma emboscada no caminho!\n");
                    iniciarCombate(&vida);

                    /* Encerra a jornada imediatamente se morrer. */
                    if (vida <= 0)
                        break;
                }
                else if (local == 4)
                {
                    printf("Voce encontrou a chegada!\n");
                }
            }
            else
            {
                printf("Voce voltou a um local ja explorado.\n");
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

            printf("DESIDRATACAO! Voce perdeu 3 de vida.\n");
        }

        dia++;
    }

    mostrarMapa();

    if (vida > 0 && chegouAoDestino())
    {
        printf("\nPARABENS! Voce chegou ao destino com vida!\n");
    }
    else
    {
        printf("\nFIM DE JOGO: o sertao foi implacavel...\n");
    }
}

int main()
{
    int opcao;
    srand(time(NULL));

    do
    {
        mostrarMenu();
        int leitura = scanf("%d", &opcao);

        if (leitura == EOF)
        {
            printf("\nEntrada encerrada. Ate logo!\n");
            break;
        }

        if (leitura != 1)
        {
            int caractere;

            while ((caractere = getchar()) != '\n' && caractere != EOF)
            {
            }

            opcao = 0;
        }
        limparTela();

        switch (opcao)
        {
        case 1:
            jogar();
            break;
        case 2:
            comoJogar();
            break;
        case 3:
            printf("\nAte logo!\n");
            break;
        default:
            printf("\nOpcao invalida!\n");
        }
    } while (opcao != 3);

    return 0;
}