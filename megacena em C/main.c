#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "megasena.h"

// Menu de opções para o usuário
typedef enum {
    MENU_SAIR = 0,
    MENU_JOGAR = 1,
    MENU_AJUDA = 2
} OpcaoMenu;

// Estrutura para armazenar os dados da aposta
typedef struct {
    int dezenas[MAX_DEZENAS];
    int quantidade;
    char tipo;  // 'M' para manual, 'S' para surpresinha
} Aposta;

// Estrutura para armazenar os resultados
typedef struct {
    int dezenas_sorteadas[6];
    int acertos;
    double premio;
} Resultado;

// Funções locais do menu
void exibirBanner();
OpcaoMenu exibirMenu();
void exibirAjuda();
void realizarSimulacao();
void coletarApostas(Aposta apostas[], int *total_apostas, int *qd, int *qt);
void processarSorteios(Aposta apostas[], int total_apostas, int qd, int qt, double *valor_total, double *premio_total);
void exibirResultados(double valor_total, double premio_total);

int main() {
    srand(time(NULL));
    
    OpcaoMenu opcao;
    do {
        exibirBanner();
        opcao = exibirMenu();
        
        switch (opcao) {
            case MENU_JOGAR:
                realizarSimulacao();
                break;
            case MENU_AJUDA:
                exibirAjuda();
                break;
            case MENU_SAIR:
                printf("\nObrigado por utilizar o Simulador da Mega-Sena!\n");
                break;
        }
    } while (opcao != MENU_SAIR);
    
    return 0;
}

// Exibe um banner decorativo
void exibirBanner() {
    system("clear || cls"); // Limpa a tela (funciona em Linux/Windows)
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃                                                    ┃\n");
    printf("┃             SIMULADOR DA MEGA-SENA                 ┃\n");
    printf("┃                                                    ┃\n");
    printf("┃           Teste Sua Sorte Virtualmente!            ┃\n");
    printf("┃                                                    ┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n");
}

// Exibe o menu principal e retorna a opção escolhida
OpcaoMenu exibirMenu() {
    int opcao;
    printf("Escolha uma opção:\n");
    printf("1. Realizar uma simulação de apostas\n");
    printf("2. Ajuda sobre o jogo\n");
    printf("0. Sair do simulador\n");
    printf("\nSua escolha: ");
    scanf("%d", &opcao);
    limparBuffer();
    
    if (opcao < 0 || opcao > 2) {
        printf("Opção inválida! Pressione ENTER para continuar...");
        getchar();
        return exibirMenu();
    }
    
    return (OpcaoMenu)opcao;
}

// Exibe informações de ajuda
void exibirAjuda() {
    printf("\n=== AJUDA DO SIMULADOR DA MEGA-SENA ===\n\n");
    printf("A Mega-Sena é o jogo que paga milhões para o acertador dos 6 números sorteados.\n\n");
    printf("Neste simulador você pode:\n");
    printf("- Apostar de 6 a 15 dezenas por cartela\n");
    printf("- Realizar até 3 apostas manuais\n");
    printf("- Gerar até 7 apostas 'surpresinha' (números aleatórios)\n");
    printf("- Fazer 'teimosinhas': 0 (único sorteio), 2 ou 8 concursos consecutivos\n\n");
    
    printf("Prêmios:\n");
    printf("- Sena (6 acertos): R$ 118.265.926,76\n");
    printf("- Quina (5 acertos): R$ 32.797,02\n");
    printf("- Quadra (4 acertos): R$ 834,93\n\n");
    
    printf("Pressione ENTER para voltar ao menu principal...");
    getchar();
}

// Função principal de simulação
void realizarSimulacao() {
    Aposta apostas[MAX_APOSTAS];
    int total_apostas = 0;
    int qd = 0, qt = 0;
    double valor_total = 0.0, premio_total = 0.0;
    
    coletarApostas(apostas, &total_apostas, &qd, &qt);
    
    // Tabela de valores baseada na quantidade de dezenas
    const double valores[] = {5, 35, 140, 420, 1050, 2310, 4620, 8580, 15015, 25025};
    valor_total = calcularValorAposta(qt == 0 ? 1 : qt, valores[qd - 6], total_apostas);
    
    printf("\nValor total da aposta: R$ %.2f\n", valor_total);
    printf("Deseja continuar com o sorteio? (S/N): ");
    char confirma;
    scanf(" %c", &confirma);
    limparBuffer();
    
    if (toupper(confirma) != 'S') {
        printf("\nSimulação cancelada!\n");
        printf("Pressione ENTER para continuar...");
        getchar();
        return;
    }
    
    processarSorteios(apostas, total_apostas, qd, qt, &valor_total, &premio_total);
    exibirResultados(valor_total, premio_total);
    
    printf("\nPressione ENTER para voltar ao menu principal...");
    getchar();
}

// Coleta as apostas do usuário
void coletarApostas(Aposta apostas[], int *total_apostas, int *qd, int *qt) {
    *qd = lerInteiro("Quantas dezenas deseja apostar por cartela (6-15)? ", 6, 15);
    
    int qm = lerInteiro("Quantas apostas manuais deseja fazer (0-3)? ", 0, 3);
    
    // Processa apostas manuais
    for (int i = 0; i < qm; i++) {
        apostas[i].quantidade = *qd;
        apostas[i].tipo = 'M';
        printf("\nAposta manual %d:\n", i + 1);
        lerApostaManual(apostas[i].dezenas, *qd);
    }
    
    int qs = lerInteiro("Quantas apostas Surpresinha deseja gerar (0-7)? ", 0, 7);
    
    // Processa apostas surpresinha
    for (int i = 0; i < qs; i++) {
        apostas[qm + i].quantidade = *qd;
        apostas[qm + i].tipo = 'S';
        gerarApostaAleatoria(apostas[qm + i].dezenas, *qd);
        printf("Aposta Surpresinha %d: ", i + 1);
        exibirAposta(apostas[qm + i].dezenas, *qd);
    }
    
    *total_apostas = qm + qs;
    
    if (*total_apostas == 0) {
        printf("Erro: É necessário fazer pelo menos uma aposta!\n");
        coletarApostas(apostas, total_apostas, qd, qt);
        return;
    }
    
    *qt = lerInteiro("Quantos concursos deseja jogar (0, 2 ou 8)? ", 0, 8);
    if (*qt != 0 && *qt != 2 && *qt != 8) {
        printf("Valor inválido. Considerando apenas um concurso.\n");
        *qt = 0;
    }
}

// Processa os sorteios e calcula prêmios
void processarSorteios(Aposta apostas[], int total_apostas, int qd, int qt, double *valor_total, double *premio_total) {
    const double premios[] = {118265926.76, 32797.02, 834.93};
    int num_concursos = (qt == 0) ? 1 : qt;
    
    *premio_total = 0.0;
    
    for (int c = 1; c <= num_concursos; c++) {
        int sorteio[6];
        sortearDezenas(sorteio);
        
        printf("\n======== CONCURSO %04d ========\n", c);
        printf("Dezenas sorteadas: ");
        exibirAposta(sorteio, 6);
        printf("==============================\n");
        
        for (int i = 0; i < total_apostas; i++) {            const char* tipo_aposta = apostas[i].tipo == 'M' ? "Manual" : "Surpresinha";
            int acertos = contarAcertos(apostas[i].dezenas, sorteio, qd);
            
            printf("Aposta %d (%s): %d/6 acertos", i + 1, tipo_aposta, acertos);
              double premio = calcularPremio(qd, acertos, (double*)premios);
            if (premio > 0) {
                printf(" -> PRÊMIO: R$ %.2f", premio);
                *premio_total += premio;
            }
            printf("\n");
        }
    }
}

// Exibe os resultados finais
void exibirResultados(double valor_total, double premio_total) {
    double saldo = premio_total - valor_total;
    
    printf("\n======== RESULTADO FINAL ========\n");
    printf("Valor investido:  R$ %12.2f\n", valor_total);
    printf("Prêmios ganhos:   R$ %12.2f\n", premio_total);
    printf("Saldo final:      R$ %12.2f ", saldo);
    
    if (saldo > 0) {
        printf("(LUCRO)\n");
    } else if (saldo < 0) {
        printf("(PREJUÍZO)\n");
    } else {
        printf("(EMPATE)\n");
    }
    printf("================================\n");
}
