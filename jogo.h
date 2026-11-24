#ifndef JOGO_H
#define JOGO_H

/* Funcoes compartilhadas entre os arquivos do projeto. */

/* main.c */
void limparTela(void);
void jogar(void);

/* mapa.c */
void inicializarMapa(void);
void mostrarMapa(void);
int moverJogador(int direcao);
int consultarLocalAtual(void);
int localAtualFoiVisitado(void);
void marcarLocalAtualVisitado(void);
int chegouAoDestino(void);

/* inventory.c */
void inicializarInventario(void);
void mostrarInventario(void);
int alterarAgua(int quantidade);
int alterarRapadura(int quantidade);
int alterarRemedio(int quantidade);
int alterarFarinha(int quantidade);
int consultarAgua(void);
int consultarRapadura(void);
int consultarRemedio(void);
int consultarFarinha(void);
int consumirRemedio(void);

/* combat.c */
void iniciarCombate(int *vidaJogador);

#endif
