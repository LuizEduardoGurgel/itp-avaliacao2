# ITP – Segunda Avaliação (Projeto em C)

## Identificação
- **Nome:** Luiz Eduardo Gurgel Marcelino de Oliveira
- **Projeto escolhido:** Opção 4 – Jogo da velha para dois jogadores

## Descrição
Programa em C que permite a duas pessoas jogarem uma série de 1 a 5 partidas de jogo da velha no terminal.

Funcionalidades implementadas:
- leitura do nome dos dois jogadores (validando que não estão vazios e respeitando a capacidade do vetor de caracteres);
- leitura da quantidade de partidas (1 a 5);
- tabuleiro representado por uma matriz de caracteres 3 × 3; o jogador 1 usa `X` e começa todas as partidas, o jogador 2 usa `O`;
- jogadas por linha e coluna (1 a 3), rejeitando posições fora do tabuleiro, posições ocupadas e entradas que não são números — nesses casos o jogador mantém a vez;
- detecção de vitória por linha, coluna e diagonal, e de empate;
- resultado de cada partida (0 = empate, 1 = jogador 1, 2 = jogador 2) guardado em um vetor alocado dinamicamente (`calloc`), liberado com `free`;
- resumo final com vitórias, empates e porcentagem de vitórias de cada jogador sobre todas as partidas da série.

## Compilação e execução
Com GCC (Linux/macOS, ou Windows com MinGW/WSL):

```bash
gcc -std=c11 -Wall -Wextra main.c -o programa
./programa
```

## Testes

### Teste 1 – funcionamento normal (vitória por linha e empate)
Entradas: jogador 1 = `Ana`, jogador 2 = `Bruno`, partidas = `2`.

- Partida 1 (linha, coluna): Ana 1 1 · Bruno 2 1 · Ana 1 2 · Bruno 2 2 · Ana 1 3
  **Esperado:** "Ana venceu a partida!" (linha 1).
- Partida 2: Ana 1 1 · Bruno 1 2 · Ana 1 3 · Bruno 2 2 · Ana 2 1 · Bruno 2 3 · Ana 3 2 · Bruno 3 1 · Ana 3 3
  **Esperado:** "Empate!"
- **Resumo esperado:** Ana 1 vitória (50,0%), Bruno 0 vitórias (0,0%), Empates: 1.

### Teste 2 – entradas inválidas e limites
- Nome vazio (só Enter) → **esperado:** "O nome nao pode ser vazio" e o nome é pedido de novo.
- Quantidade de partidas `9` → **esperado:** "Valor fora do intervalo (1 a 5)" e a pergunta se repete.
- Jogada na linha `4` ou texto como `abc` → **esperado:** mensagem de erro e a jogada é pedida novamente.
- Jogada em posição já ocupada → **esperado:** "Posicao ja ocupada!" e a vez do mesmo jogador é mantida.

## Vídeo
Link da apresentação no YouTube: LINK

## Referências
- Material das aulas 6 a 11 da disciplina (matrizes, tipos de dados, strings, memória, ponteiros e alocação dinâmica).