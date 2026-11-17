#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    printf("- Atravesse o sertao percorrendo 20 etapas.\n");
    printf("- Gerencie sua Vida (max 10), Agua e Rapadura.\n");
    printf("- O clima muda a cada dia e afeta o consumo de agua.\n");
    printf("- 'Andar' avanca mas gasta recursos e tem riscos.\n");
    printf("- 'Descansar' recupera vida, mas gasta agua.\n");
    printf("- 'Comer rapadura' recupera bem sua energia.\n");
}

void jogar(void)
{
    int dia = 1, dist = 0, vida = 10, op;
    int clima = 0; // 0 = Normal, 1 = Sol Forte, 2 = Seca Severa
    inicializarInventario();

    printf("\nVoce comeca sua jornada pelo sertao inclemente...\n");

    while (dist < 20 && vida > 0)
    {
        // Sorteia o clima do dia (0: Normal 60%, 1: Sol Forte 25%, 2: Seca Severa 15%)
        int rClima = rand() % 100;
        if (rClima < 60)
            clima = 0;
        else if (rClima < 85)
            clima = 1;
        else
            clima = 2;

        printf("\n----------------------------------------\n");
        printf("Dia %d | Distancia: %d/20 | Clima: ", dia, dist);
        if (clima == 0)
            printf("Ameno\n");
        else if (clima == 1)
            printf("Sol Forte [Atencao!]\n");
        else
            printf("Seca Severa [Perigoso!]\n");

        printf("Vida: %d/10 | Agua: %d | Rapadura: %d\n",
               vida, consultarAgua(), consultarRapadura());
        printf("1 - Andar\n2 - Descansar na sombra\n3 - Comer rapadura\nEscolha: ");

        int leitura = scanf("%d", &op);

        if (leitura == EOF)
        {
            printf("\nEntrada encerrada. Voltando ao menu.\n");
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

        int consumoAgua = 1;
        if (clima == 1)
            consumoAgua = 2;
        if (clima == 2)
            consumoAgua = 3;

        if (op == 1)
        {
            dist += (clima == 2) ? 1 : 2; // Na seca severa, avanca mais devagar
            int aguaAtual = consultarAgua();
            if (aguaAtual >= consumoAgua)
            {
                alterarAgua(-consumoAgua);
            }
            else
            {
                alterarAgua(-aguaAtual);
            }

            printf("Voce caminha sob o sol do sertao...\n");

            // Eventos aleatorios ao andar
            int evento = rand() % 5;
            if (evento == 0)
            {
                alterarAgua(2);
                printf("Boa noticia! Voce encontrou um poco de agua! (+2 agua)\n");
            }
            else if (evento == 1)
            {
                iniciarCombate(&vida);

                if (vida <= 0)
                {
                    break;
                }
            }
            else if (evento == 2)
            {
                int achouRap = rand() % 2;
                if (achouRap)
                {
                    alterarRapadura(1);
                    printf("Voce passou por um armazem abandonado e achou rapadura! (+1 rapadura)\n");
                }
                else
                {
                    printf("O terreno pedregoso feriu seus pes. (-1 vida)\n");
                    vida--;
                }
            }
            else
            {
                printf("Caminhada tranquila, mas desgastante.\n");
            }
        }
        else if (op == 2)
        {
            int gastoDescanso = (consumoAgua > 1 ? 2 : 1);
            int aguaAtual = consultarAgua();

            if (aguaAtual >= gastoDescanso)
            {
                alterarAgua(-gastoDescanso);
            }
            else
            {
                alterarAgua(-aguaAtual);
            }
            vida += 2;
            if (vida > 10)
                vida = 10;
            printf("Voce descansa debaixo de uma arvore. (+2 vida)\n");
        }
        else if (op == 3)
        {
            if (consultarRapadura() > 0)
            {
                alterarRapadura(-1);
                vida += 4;
                if (vida > 10)
                    vida = 10;
                printf("Voce come rapadura e recupera energias! (+4 vida)\n");
            }
            else
            {
                printf("Voce procura na mochila, mas a rapadura acabou!\n");
                continue; // Nao passa o dia se so tentou comer sem ter
            }
        }
        else
        {
            printf("Opcao invalida!\n");
            continue;
        }

        // Verificacao de desidratacao
        if (consultarAgua() <= 0)
        {
            vida -= 3;
            printf("VOCE ESTA DESIDRATADO! A sede consome suas forcas (-3 vida)\n");
        }

        dia++;
    }

    if (vida > 0)
    {
        printf("\n========================================\n");
        printf(" PARABENOS! Voce sobreviveu e cruzou o sertao!\n");
        printf("========================================\n");
    }
    else
    {
        printf("\n========================================\n");
        printf(" FIM DE JOGO: O sertao foi implacavel desta vez...\n");
        printf("========================================\n");
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