#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Limpa a tela e posiciona o cursor no inicio. */
void limparTela(void)
{
    printf("\033[2J\033[H");
    fflush(stdout);
}

/* Funcoes disponiveis nos outros arquivos do projeto. */
void inicializarMapa(void);
void mostrarMapa(void);
int moverJogador(int direcao);
int consultarLocalAtual(void);
int localAtualFoiVisitado(void);
void marcarLocalAtualVisitado(void);
int chegouAoDestino(void);

int alterarRemedio(int quantidade);
void inicializarInventario(void);
void iniciarCombate(int *vidaJogador);
int alterarAgua(int quantidade);
int alterarRapadura(int quantidade);
int consultarAgua(void);
int consultarRapadura(void);

/* Funcao para mostrar o Menu do game */
void mostrarMenu(void)
{
    printf("\n=== CAMINHOS DO SERTAO ===\n");
    printf("1 - Novo Jogo\n2 - Como Jogar\n3 - Sair\nEscolha: ");
}

/* Funcao explicativa de como jogar */
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

/* Declara a funcao de jogo, implementada em jogo.c. */
void jogar(void);

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
            printf("\nAte logo!\n");
            break;
        default:
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 3); /* Repete o menu ate escolher sair. */

    return 0;
}