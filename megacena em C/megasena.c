#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "megasena.h"

void limparBuffer() {
    while (getchar() != '\n');
}

int lerInteiro(char *mensagem, int min, int max) {
    int valor;
    do {
        printf("%s", mensagem);
        scanf("%d", &valor);
        limparBuffer();
    } while (valor < min || valor > max);
    return valor;
}

int verificarRepetido(int aposta[], int tamanho, int numero) {
    for (int i = 0; i < tamanho; i++) {
        if (aposta[i] == numero) return 1;
    }
    return 0;
}

void lerApostaManual(int aposta[], int qd) {
    int num, i = 0;
    printf("Digite %d dezenas (entre 1 e 60):\n", qd);
    while (i < qd) {
        printf("Dezena %d: ", i + 1);
        scanf("%d", &num);
        if (num < 1 || num > 60 || verificarRepetido(aposta, i, num)) {
            printf("Número inválido ou repetido!\n");
            continue;
        }
        aposta[i++] = num;
    }
    ordenar(aposta, qd);
}

void gerarApostaAleatoria(int aposta[], int qd) {
    int i = 0, num;
    while (i < qd) {
        num = rand() % 60 + 1;
        if (!verificarRepetido(aposta, i, num)) {
            aposta[i++] = num;
        }
    }
    ordenar(aposta, qd);
}

void ordenar(int v[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (v[i] > v[j]) {
                int tmp = v[i];
                v[i] = v[j];
                v[j] = tmp;
            }
}

void sortearDezenas(int sorteio[]) {
    gerarApostaAleatoria(sorteio, 6);
}

int contarAcertos(int aposta[], int sorteio[], int qd) {
    int acertos = 0;
    for (int i = 0; i < qd; i++)
        for (int j = 0; j < 6; j++)
            if (aposta[i] == sorteio[j]) acertos++;
    return acertos;
}

double calcularValorAposta(int qt, int vd, int total_apostas) {
    return qt * vd * total_apostas;
}

int contarPremios(int qd, int acertos) {
    if (qd == 6 && acertos == 6) return 1;
    // Exemplo genérico para simplificação
    if (acertos == 6) return 1;
    if (acertos == 5) return 1;
    if (acertos == 4) return 1;
    return 0;
}

double calcularPremio(int qd, int acertos, double *premios) {
    if (acertos == 6) return premios[0];
    if (acertos == 5) return premios[1];
    if (acertos == 4) return premios[2];
    return 0.0;
}

void exibirAposta(int aposta[], int qd) {
    for (int i = 0; i < qd; i++) {
        printf("%02d ", aposta[i]);
    }
    printf("\n");
}
