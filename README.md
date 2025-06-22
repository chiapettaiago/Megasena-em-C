# 🎮 Simulador da Mega-Sena em C

<div align="center">
  <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/c/c-original.svg" alt="linguagem C" width="120" height="120"/>
  <br>
  <strong>Um simulador completo para testar sua sorte na Mega-Sena sem gastar dinheiro real!</strong>
  <br><br>
</div>

## 📋 Sobre o Projeto

Este simulador da Mega-Sena foi desenvolvido em linguagem C para fins educacionais e de entretenimento. Permite aos usuários simular apostas na Mega-Sena, testando diferentes combinações de números e analisando as probabilidades e retornos sem comprometer dinheiro real.

### ✨ Características

- 🎲 **Apostas Manuais**: Escolha seus próprios números de sorte (de 6 a 15 dezenas)
- 🔄 **Surpresinha**: Gere apostas aleatórias como na loteria real
- 🔁 **Teimosinha**: Repita as mesmas apostas em múltiplos concursos (2 ou 8)
- 💰 **Análise de Prêmios**: Simulação realista dos valores de premiação
- 📊 **Resumo Financeiro**: Veja o total investido e ganho em suas simulações
- 📱 **Interface Amigável**: Sistema de menu intuitivo e visual agradável

## 🚀 Como Usar

### Pré-requisitos

- Compilador GCC instalado
- Sistema operacional Linux, macOS ou Windows (com compilador configurado)

### Compilação

```bash
gcc -o megasena main.c megasena.c
```

### Execução

```bash
./megasena
```

## 🎮 Modo de Jogo

1. No menu principal, selecione a opção 1 para iniciar uma simulação
2. Escolha quantas dezenas quer apostar (6 a 15)
3. Defina quantas apostas manuais (0 a 3) e surpresinha (0 a 7) deseja fazer
4. Para apostas manuais, digite cada número individualmente
5. Escolha se quer fazer teimosinha (mesmo jogo em múltiplos concursos)
6. Confirme o valor da aposta para iniciar o sorteio
7. Observe os resultados e o resumo financeiro no final

## 💸 Valores das Apostas

| Quantidade de Dezenas | Valor (R$) |
|:---------------------:|:----------:|
| 6                     | R$ 5,00    |
| 7                     | R$ 35,00   |
| 8                     | R$ 140,00  |
| 9                     | R$ 420,00  |
| 10                    | R$ 1.050,00|
| 11                    | R$ 2.310,00|
| 12                    | R$ 4.620,00|
| 13                    | R$ 8.580,00|
| 14                    | R$ 15.015,00|
| 15                    | R$ 25.025,00|

## 🏆 Premiações

- **Sena (6 acertos)**: R$ 118.265.926,76
- **Quina (5 acertos)**: R$ 32.797,02
- **Quadra (4 acertos)**: R$ 834,93

## 📂 Estrutura do Projeto

- `main.c`: Contém o menu principal e a lógica do jogo
- `megasena.h`: Cabeçalho com declarações de funções e constantes
- `megasena.c`: Implementações das funções utilizadas no jogo

## 📝 Exemplos de Uso

### Exemplo 1: Aposta Simples
- 1 aposta manual de 6 dezenas
- Jogo em um único concurso
- Investimento: R$ 5,00

### Exemplo 2: Aposta com Surpresinha
- 2 apostas surpresinha de 8 dezenas
- Teimosinha para 2 concursos
- Investimento: R$ 560,00 (R$ 140,00 × 2 apostas × 2 concursos)

## ⚠️ Aviso Legal

Este simulador é apenas para fins de entretenimento e educação. Não está associado oficialmente à Caixa Econômica Federal ou qualquer loteria oficial. Os valores e probabilidades são baseados no jogo real, mas são apenas uma simulação.

## 👥 Desenvolvedores

- Nome dos integrantes da equipe (ver arquivo integrantes.txt)

## 📜 Licença

Este projeto é disponibilizado como software livre para fins educacionais.

---