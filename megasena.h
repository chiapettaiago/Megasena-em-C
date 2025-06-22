#ifndef MEGASENA_H
#define MEGASENA_H

#define MAX_DEZENAS 15
#define MAX_APOSTAS 10
#define MAX_CONCURSOS 8

void limparBuffer();
int lerInteiro(char *mensagem, int min, int max);
void lerApostaManual(int aposta[], int qd);
int verificarRepetido(int aposta[], int tamanho, int numero);
void gerarApostaAleatoria(int aposta[], int qd);
void ordenar(int v[], int n);
int contarAcertos(int aposta[], int sorteio[], int qd);
void sortearDezenas(int sorteio[]);
double calcularValorAposta(int qt, int vd, int total_apostas);
double calcularPremio(int qd, int acertos, double *premios);
int contarPremios(int qd, int acertos);
void exibirAposta(int aposta[], int qd);

#endif