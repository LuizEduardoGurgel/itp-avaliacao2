#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 3           
#define MAX_NOME 30     
#define MIN_PARTIDAS 1
#define MAX_PARTIDAS 5
#define VAZIO ' '

/* Le uma linha respeitando a capacidade 'cap' e descarta o excesso. */
static int ler_linha(char *dest, size_t cap)
{
    if (fgets(dest, (int)cap, stdin) == NULL) {
        printf("\nEntrada encerrada. Saindo do programa.\n");
        exit(EXIT_FAILURE);
    }
    size_t len = strlen(dest);
    if (len > 0 && dest[len - 1] == '\n') {
        dest[len - 1] = '\0';
    } else {
        int c;                                  /* linha maior que o vetor: */
        while ((c = getchar()) != '\n' && c != EOF) { } /* descarta o resto */
    }
    return 1;
}

/* Le um texto nao vazio (ignora entradas so com espacos). */
void ler_texto(const char *mensagem, char *dest, size_t cap)
{
    for (;;) {
        printf("%s", mensagem);
        ler_linha(dest, cap);

        int vazio = 1;
        for (size_t i = 0; dest[i] != '\0'; i++) {
            if (!isspace((unsigned char)dest[i])) {
                vazio = 0;
                break;
            }
        }
        if (!vazio) {
            return;
        }
        printf("O nome nao pode ser vazio. Tente novamente.\n");
    }
}

/* Le um inteiro entre min e max; repete ate a entrada ser valida. */
int ler_inteiro(const char *mensagem, int min, int max)
{
    char buffer[32];
    for (;;) {
        printf("%s", mensagem);
        ler_linha(buffer, sizeof buffer);

        char *fim;
        long valor = strtol(buffer, &fim, 10);
        while (isspace((unsigned char)*fim)) {
            fim++;
        }
        if (fim == buffer || *fim != '\0') {
            printf("Digite apenas um numero inteiro.\n");
        } else if (valor < min || valor > max) {
            printf("Valor fora do intervalo (%d a %d).\n", min, max);
        } else {
            return (int)valor;
        }
    }
}

/* ---------- Tabuleiro ---------- */

void reiniciar_tabuleiro(char tab[TAM][TAM])
{
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tab[i][j] = VAZIO;
        }
    }
}

void exibir_tabuleiro(char tab[TAM][TAM])
{
    printf("\n     1   2   3\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d    ", i + 1);
        for (int j = 0; j < TAM; j++) {
            printf("%c", tab[i][j]);
            if (j < TAM - 1) {
                printf(" | ");
            }
        }
        printf("\n");
        if (i < TAM - 1) {
            printf("    ---+---+---\n");
        }
    }
    printf("\n");
}

/* Devolve 'X' ou 'O' se houver vencedor; caso contrario, VAZIO. */
char verificar_vencedor(char tab[TAM][TAM])
{
    for (int i = 0; i < TAM; i++) {
        if (tab[i][0] != VAZIO && tab[i][0] == tab[i][1] && tab[i][1] == tab[i][2]) {
            return tab[i][0];                       /* linha */
        }
        if (tab[0][i] != VAZIO && tab[0][i] == tab[1][i] && tab[1][i] == tab[2][i]) {
            return tab[0][i];                       /* coluna */
        }
    }
    if (tab[1][1] != VAZIO) {
        if (tab[0][0] == tab[1][1] && tab[1][1] == tab[2][2]) {
            return tab[1][1];                       /* diagonal principal */
        }
        if (tab[0][2] == tab[1][1] && tab[1][1] == tab[2][0]) {
            return tab[1][1];                       /* diagonal secundaria */
        }
    }
    return VAZIO;
}

int tabuleiro_cheio(char tab[TAM][TAM])
{
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tab[i][j] == VAZIO) {
                return 0;
            }
        }
    }
    return 1;
}

/* ---------- Partida ---------- */

/*
 * Joga uma partida completa e escreve o resultado em *resultado
 * (0 = empate, 1 = vitoria do primeiro jogador, 2 = vitoria do segundo).
 * O ponteiro aponta para uma posicao do vetor dinamico do chamador.
 */
void jogar_partida(char tab[TAM][TAM], char nomes[2][MAX_NOME], int *resultado)
{
    const char simbolos[2] = { 'X', 'O' };
    int vez = 0;                       /* 0 = primeiro jogador (X comeca) */

    reiniciar_tabuleiro(tab);

    for (;;) {
        exibir_tabuleiro(tab);
        printf("Vez de %s (%c)\n", nomes[vez], simbolos[vez]);

        int linha  = ler_inteiro("Linha (1 a 3): ", 1, TAM);
        int coluna = ler_inteiro("Coluna (1 a 3): ", 1, TAM);

        if (tab[linha - 1][coluna - 1] != VAZIO) {
            printf("Posicao ja ocupada! Escolha outra, %s.\n", nomes[vez]);
            continue;                  /* mantem a vez do mesmo jogador */
        }
        tab[linha - 1][coluna - 1] = simbolos[vez];

        if (verificar_vencedor(tab) != VAZIO) {
            exibir_tabuleiro(tab);
            printf("%s venceu a partida!\n", nomes[vez]);
            *resultado = vez + 1;
            return;
        }
        if (tabuleiro_cheio(tab)) {
            exibir_tabuleiro(tab);
            printf("Empate!\n");
            *resultado = 0;
            return;
        }
        vez = 1 - vez;                 /* alterna o jogador */
    }
}

/* ---------- Resumo final ---------- */

void exibir_resumo(const int *resultados, int n, char nomes[2][MAX_NOME])
{
    int vitorias[2] = { 0, 0 };
    int empates = 0;

    for (int i = 0; i < n; i++) {
        if (resultados[i] == 1) {
            vitorias[0]++;
        } else if (resultados[i] == 2) {
            vitorias[1]++;
        } else {
            empates++;
        }
    }

    printf("\n===== RESUMO DA SERIE (%d partida(s)) =====\n", n);
    for (int i = 0; i < n; i++) {
        printf("Partida %d: ", i + 1);
        if (resultados[i] == 0) {
            printf("empate\n");
        } else {
            printf("vitoria de %s\n", nomes[resultados[i] - 1]);
        }
    }
    /* 100.0 forca divisao com double (evita divisao inteira) */
    printf("\n%s: %d vitoria(s) - %.1f%%\n", nomes[0], vitorias[0], 100.0 * vitorias[0] / n);
    printf("%s: %d vitoria(s) - %.1f%%\n", nomes[1], vitorias[1], 100.0 * vitorias[1] / n);
    printf("Empates: %d\n", empates);
}

/* ---------- Programa principal ---------- */

int main(void)
{
    char tabuleiro[TAM][TAM];
    char nomes[2][MAX_NOME];

    printf("=== JOGO DA VELHA ===\n");
    ler_texto("Nome do jogador 1 (X): ", nomes[0], MAX_NOME);
    ler_texto("Nome do jogador 2 (O): ", nomes[1], MAX_NOME);
    int n = ler_inteiro("Quantidade de partidas (1 a 5): ", MIN_PARTIDAS, MAX_PARTIDAS);

    int *resultados = calloc((size_t)n, sizeof *resultados);   /* heap */
    if (resultados == NULL) {
        printf("Erro: memoria insuficiente.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        printf("\n########## PARTIDA %d de %d ##########\n", i + 1, n);
        jogar_partida(tabuleiro, nomes, &resultados[i]);
    }

    exibir_resumo(resultados, n, nomes);

    free(resultados);
    resultados = NULL;
    return EXIT_SUCCESS;
}