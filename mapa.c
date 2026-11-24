#include <stdio.h>
#include "ui.h"

/*
 * Cada posicao da matriz representa um local do sertao.
 *
 * Tipos de local:
 * 0 = estrada
 * 1 = poco
 * 2 = armazem
 * 3 = emboscada
 * 4 = destino
 *
 * O primeiro indice indica a linha e o segundo, a coluna.
 * Exemplo: mapa[0][2] representa um poco.
 *
 * "static" limita o acesso direto a esta variavel ao arquivo mapa.c.
 */

static int mapa[5][5] = {
    {0, 0, 1, 0, 0},
    {0, 2, 0, 3, 0},
    {1, 0, 0, 0, 2},
    {0, 3, 1, 0, 0},
    {0, 0, 0, 2, 4}
};

/*
 * Guarda quais locais ja foram explorados:
 * 0 = ainda nao visitado
 * 1 = ja visitado
 *
 * Cada posicao corresponde a mesma posicao da matriz mapa.
 * Isso permitira impedir recompensas repetidas em pocos e armazens.
 */

static int visitado[5][5];
/*
 * Coordenadas atuais do jogador.
 * Os indices validos vao de 0 a 4.
 */
static int linhaJogador;
static int colunaJogador;

/* Prepara o mapa para uma nova partida. */
void inicializarMapa(void)
{
    /* O jogador sempre comeca no canto superior esquerdo. */
    linhaJogador = 0;
    colunaJogador = 0;

    /*
     * O primeiro for percorre as linhas.
     * Para cada linha, o segundo for percorre todas as colunas.
     * Assim, as 25 posicoes voltam a ficar nao visitadas.
     */
    for (int linha = 0; linha < 5; linha++)
    {
        for (int coluna = 0; coluna < 5; coluna++)
        {
            /* O ponto inicial ja e conhecido pelo jogador. */
            visitado[linha][coluna] = 0;
        }
    }

    visitado[0][0] = 1;
}

/* Exibe uma representacao do mapa no terminal. */
void mostrarMapa(void)
{
    printf("\n" COR_NEGRITO COR_AMARELO "=== MAPA DO SERTAO ===" COR_RESET "\n");

    for (int linha = 0; linha < 5; linha++)
    {
        for (int coluna = 0; coluna < 5; coluna++)
        {
            char simbolo;

             /*
             * A posicao do jogador tem prioridade sobre os
             * outros simbolos, inclusive sobre o destino.
             */
            if (linha == linhaJogador && coluna == colunaJogador)
            {
                simbolo = 'J';
            }
            else if (visitado[linha][coluna])
            {
            /* Mostra que o local ja foi explorado. */
                simbolo = '.';
            }
            else if (mapa[linha][coluna] == 4)
            {
                /* O destino aparece mesmo antes de ser visitado. */
                simbolo = 'D';
            }
            else
            {
                /* Esconde o tipo dos locais ainda desconhecidos. */
                simbolo = '?';
            }

            /* Cor de cada simbolo: jogador, destino, explorado e desconhecido. */
            const char *cor = COR_DIM;

            if (simbolo == 'J')
            {
                cor = COR_NEGRITO COR_AMARELO;
            }
            else if (simbolo == 'D')
            {
                cor = COR_NEGRITO COR_VERMELHO;
            }

            printf("[%s%c" COR_RESET "] ", cor, simbolo);
        }
        /* Depois de exibir uma linha inteira, passa para a proxima. */
        printf("\n");
    }

    printf(COR_AMARELO "J" COR_RESET " = jogador | " COR_VERMELHO "D" COR_RESET " = destino\n");
    printf(COR_DIM ". = explorado | ? = desconhecido" COR_RESET "\n");
}

/* 1 = norte, 2 = sul, 3 = leste, 4 = oeste.
   Retorna 1 se moveu ou 0 se o movimento foi invalido. */
int moverJogador(int direcao)
{
    /*
     * Calcula a nova posicao usando copias das coordenadas.
     * A posicao real so sera alterada depois da validacao.
     */
    int novaLinha = linhaJogador;
    int novaColuna = colunaJogador;

    switch (direcao)
    {
        case 1:
        /* Subir significa diminuir o indice da linha. */
            novaLinha--;
            break;

        case 2:
        /* Descer significa aumentar o indice da linha. */
            novaLinha++;
            break;

        case 3:
        /* Ir para a direita aumenta o indice da coluna. */
            novaColuna++;
            break;

        case 4:
        /* Ir para a esquerda diminui o indice da coluna. */
            novaColuna--;
            break;

        default:
            printf("Direcao invalida!\n");
            return 0;
    }

    /*
     * Impede coordenadas fora do intervalo de 0 a 4.
     * Essa verificacao evita acessos fora dos limites das matrizes.
     */
    if (novaLinha < 0 || novaLinha >= 5 ||
        novaColuna < 0 || novaColuna >= 5)
    {
        printf("Voce chegou ao limite do mapa!\n");
        return 0;
    }

    /* Confirma o movimento depois de verificar os limites. */
    linhaJogador = novaLinha;
    colunaJogador = novaColuna;

    /*
     * A visita ainda nao e marcada aqui.
     * Primeiro, o jogo precisa verificar se e a primeira visita
     * e executar o evento do local.
     */
    return 1;
}

/* Retorna o tipo do local onde o jogador esta, de 0 a 4. */
int consultarLocalAtual(void)
{
    return mapa[linhaJogador][colunaJogador];
}

/* Retorna 1 se o local atual ja foi visitado, ou 0 caso contrario. */
int localAtualFoiVisitado(void)
{
    return visitado[linhaJogador][colunaJogador];
}

/* Registra que o evento do local atual ja foi processado. */
void marcarLocalAtualVisitado(void)
{
    visitado[linhaJogador][colunaJogador] = 1;
}

/*
 * A comparacao produz 1 quando o jogador esta no destino
 * e 0 quando esta em qualquer outro tipo de local.
 */
int chegouAoDestino(void)
{
    return mapa[linhaJogador][colunaJogador] == 4;
}