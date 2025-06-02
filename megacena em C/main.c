#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "megasena.h"

int main() {
    int qd, qm, qs, qt, total_apostas;
    int apostas[MAX_APOSTAS][MAX_DEZENAS];
    double premios[] = {118265926.76, 32797.02, 834.93};

    srand(time(NULL));

    printf("=== Simulador de Apostas da Mega-Sena ===\n\n");

    qd = lerInteiro("Quantas dezenas irá apostar (6-15)? ", 6, 15);
    qm = lerInteiro("Quantas apostas manuais irá fazer (0-3)? ", 0, 3);

    for (int i = 0; i < qm; i++) {
        printf("Aposta manual %d:\n", i + 1);
        lerApostaManual(apostas[i], qd);
    }

    qs = lerInteiro("Quantas apostas Surpresinha irá fazer (0-7)? ", 0, 7);

    for (int i = 0; i < qs; i++) {
        gerarApostaAleatoria(apostas[qm + i], qd);
        printf("Aposta Surpresinha %d: ", i + 1);
        exibirAposta(apostas[qm + i], qd);
    }

    qt = lerInteiro("Quantas Teimosinhas (0, 2 ou 8)? ", 0, 8);
    if (qt != 0 && qt != 2 && qt != 8) qt = 0;

    total_apostas = qm + qs;

    double valores[] = {5, 35, 140, 420, 1050, 2310, 4620, 8580, 15015, 25025};
    int index = qd - 6;
    double valor_aposta = calcularValorAposta(qt == 0 ? 1 : qt, valores[index], total_apostas);

    printf("Valor total da aposta: R$ %.2f\n", valor_aposta);
    char confirma;
    printf("Deseja continuar (S/N)? ");
    scanf(" %c", &confirma);
    if (confirma != 'S' && confirma != 's') {
        printf("Obrigado por participar das Loterias Caixa!\n");
        return 0;
    }

    double total_premio = 0.0;
    for (int c = 1; c <= (qt == 0 ? 1 : qt); c++) {
        int sorteio[6];
        sortearDezenas(sorteio);
        printf("\nConcurso %04d - Dezenas sorteadas: ", c);
        exibirAposta(sorteio, 6);

        for (int i = 0; i < total_apostas; i++) {
            int acertos = contarAcertos(apostas[i], sorteio, qd);
            printf("Aposta %d: %d/6 acertos", i + 1, acertos);
            double premio = calcularPremio(qd, acertos, premios);
            if (premio > 0) {
                printf(" -> PRÊMIO: R$ %.2f", premio);
                total_premio += premio;
            }
            printf("\n");
        }
    }

    printf("\nTotal da aposta: R$ %.2f\n", valor_aposta);
    printf("Total dos prêmios: R$ %.2f\n", total_premio);
    printf("Valor líquido: R$ %.2f\n", total_premio - valor_aposta);
    printf("Obrigado por participar das Loterias Caixa!\n");

    return 0;
}
