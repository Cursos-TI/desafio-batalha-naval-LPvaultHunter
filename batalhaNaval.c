#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5

void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++)
        for (int j = 0; j < TAM_TABULEIRO; j++)
            tabuleiro[i][j] = 0;
}

void posicionarNavios(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    tabuleiro[4][4] = 0;
    tabuleiro[4][5] = 0;
    tabuleiro[5][4] = 0;
    tabuleiro[5][5] = 0;
}

void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\nTABULEIRO:\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void criarCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++)
        for (int j = 0; j < TAM_HABILIDADE; j++)
            matriz[i][j] = 0;

    matriz[0][2] = 1;
    matriz[1][1] = 1; matriz[1][2] = 1; matriz[1][3] = 1;
    for (int j = 0; j < TAM_HABILIDADE; j++)
        matriz[2][j] = 1;
}

void criarCruz(int matriz[5][5]) {
    // Zera matriz
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matriz[i][j] = 0;

    matriz[0][2] = 1;            // linha 0, coluna 2 (topo da cruz)
    for (int j = 0; j < 5; j++) // linha 1 toda preenchida
        matriz[1][j] = 1;
    matriz[2][2] = 1;            // linha 2, coluna 2
    matriz[3][2] = 1;            // linha 3, coluna 2 (extensão para baixo)
}

void criarOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++)
        for (int j = 0; j < TAM_HABILIDADE; j++)
            matriz[i][j] = 0;

    matriz[0][2] = 1;
    matriz[1][1] = 1; matriz[1][2] = 1; matriz[1][3] = 1;
    for (int j = 0; j < TAM_HABILIDADE; j++)
        matriz[2][j] = 1;
    matriz[3][1] = 1; matriz[3][2] = 1; matriz[3][3] = 1;
    matriz[4][2] = 1;
}

void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                       int habilidade[TAM_HABILIDADE][TAM_HABILIDADE],
                       int origemLinha, int origemColuna,
                       int valorHabilidade) {
    int offset = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int linha = origemLinha - offset + i;
            int coluna = origemColuna - offset + j;

            if (linha >= 0 && linha < TAM_TABULEIRO &&
                coluna >= 0 && coluna < TAM_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[linha][coluna] != 3) {
                    tabuleiro[linha][coluna] = valorHabilidade;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int habilidade[TAM_HABILIDADE][TAM_HABILIDADE];

    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);

    // Aplica CONE (5) na posição (2, 2)
    criarCone(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 2, 2, 5);

    // Aplica CRUZ (6) na posição (1, 7)
    criarCruz(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 4, 7, 4);

    // Aplica OCTAEDRO (7) na posição (7, 4)
    criarOctaedro(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 7, 5, 7);

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
