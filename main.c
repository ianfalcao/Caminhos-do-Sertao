#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mostrarMenu(void) {
    printf("\n=== CAMINHOS DO SERTAO ===\n");
    printf("1 - Novo Jogo\n2 - Como Jogar\n3 - Sair\nEscolha: ");
}

void comoJogar(void) {
    printf("\n--- COMO JOGAR ---\n");
    printf("- Atravesse o sertao percorrendo 20 etapas.\n");
    printf("- Gerencie sua Vida (max 10), Agua e Rapadura.\n");
    printf("- O clima muda a cada dia e afeta o consumo de agua.\n");
    printf("- 'Andar' avanca mas gasta recursos e tem riscos.\n");
    printf("- 'Descansar' recupera vida, mas gasta agua.\n");
    printf("- 'Comer rapadura' recupera bem sua energia.\n");
}

void jogar(void) {
    int dia = 1, dist = 0, vida = 10, agua = 8, rapadura = 3, op;
    int clima = 0; // 0 = Normal, 1 = Sol Forte, 2 = Seca Severa

    printf("\nVoce comeca sua jornada pelo sertao inclemente...\n");

    while (dist < 20 && vida > 0) {
        // Sorteia o clima do dia (0: Normal 60%, 1: Sol Forte 25%, 2: Seca Severa 15%)
        int rClima = rand() % 100;
        if (rClima < 60) clima = 0;
        else if (rClima < 85) clima = 1;
        else clima = 2;

        printf("\n----------------------------------------\n");
        printf("Dia %d | Distancia: %d/20 | Clima: ", dia, dist);
        if (clima == 0) printf("Ameno\n");
        else if (clima == 1) printf("Sol Forte [Atencao!]\n");
        else printf("Seca Severa [Perigoso!]\n");

        printf("Vida: %d/10 | Agua: %d | Rapadura: %d\n", vida, agua, rapadura);
        printf("1 - Andar\n2 - Descansar na sombra\n3 - Comer rapadura\nEscolha: ");

        if (scanf("%d", &op) != 1) { 
            while (getchar() != '\n'); 
            continue; 
        }

        int consumoAgua = 1;
        if (clima == 1) consumoAgua = 2;
        if (clima == 2) consumoAgua = 3;

        if (op == 1) {
            dist += (clima == 2) ? 1 : 2; // Na seca severa, avanca mais devagar
            agua -= consumoAgua;
            printf("Voce caminha sob o sol do sertao...\n");

            // Eventos aleatorios ao andar
            int evento = rand() % 5;
            if (evento == 0) {
                agua += 2;
                printf("Boa noticia! Voce encontrou um poco de agua! (+2 agua)\n");
            } else if (evento == 1) {
                vida -= 2;
                printf("Azar! Uma cobra jararaca te picou! (-2 vida)\n");
            } else if (evento == 2) {
                int achouRap = rand() % 2;
                if (achouRap) {
                    rapadura++;
                    printf("Voce passou por um armazem abandonado e achou rapadura! (+1 rapadura)\n");
                } else {
                    printf("O terreno pedregoso feriu seus pes. (-1 vida)\n");
                    vida--;
                }
            } else {
                printf("Caminhada tranquila, mas desgastante.\n");
            }
        } 
        else if (op == 2) {
            agua -= (consumoAgua > 1 ? 2 : 1);
            vida += 2;
            if (vida > 10) vida = 10;
            printf("Voce descansa debaixo de uma arvore. (+2 vida)\n");
        } 
        else if (op == 3) {
            if (rapadura > 0) {
                rapadura--;
                vida += 4;
                if (vida > 10) vida = 10;
                printf("Voce come rapadura e recupera energias! (+4 vida)\n");
            } else {
                printf("Voce procura na mochila, mas a rapadura acabou!\n");
                continue; // Nao passa o dia se so tentou comer sem ter
            }
        } 
        else {
            printf("Opcao invalida!\n");
            continue;
        }

        // Verificacao de desidratacao
        if (agua <= 0) {
            agua = 0;
            vida -= 3;
            printf("VOCE ESTA DESIDRATADO! A sede consome suas forcas (-3 vida)\n");
        }

        dia++;
    }

    if (vida > 0) {
        printf("\n========================================\n");
        printf(" PARABENOS! Voce sobreviveu e cruzou o sertao!\n");
        printf("========================================\n");
    } else {
        printf("\n========================================\n");
        printf(" FIM DE JOGO: O sertao foi implacavel desta vez...\n");
        printf("========================================\n");
    }
}

int main() {
    int opcao;
    srand(time(NULL));

    do {
        mostrarMenu();
        if (scanf("%d", &opcao) != 1) { 
            while (getchar() != '\n'); 
            opcao = 0; 
        }
        switch (opcao) {
            case 1: jogar(); break;
            case 2: comoJogar(); break;
            case 3: printf("\nAte logo!\n"); break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (opcao != 3);

    return 0;
}