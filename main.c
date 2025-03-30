#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// Assinaturas das variáveis
void sortear_palavra(char dicionario_palavras[3][6], char sortear_palavra[6]); // Assinatura da função sortear_palavra
void jogo(char dicionario_palavras[3][6], char palavra_sorteada[6]);
char nome_jogador[];

int main()
{
    // Lógica do sorteio das palavras
    char dicionario_palavras[5][6] = {"areia", "areio", "casar", "ceasar", "tcg"}; // Palavras de teste

    srand(time(NULL)); // Seed do rand (necessário para o funcionamento do rand())

    char palavra_sorteada[6]; // variável que vai pegar a palavra sorteada

    sortear_palavra(dicionario_palavras, palavra_sorteada);
    // printf("%s\n", palavra_sorteada); // Printf para testar que a variável palavra_sorteada está armazenando uma palavra aleatória

    jogo(dicionario_palavras, palavra_sorteada);

    return 0;
}

// Função que vai sortear uma palavra
void sortear_palavra(char dicionario_palavras[3][6], char sortear_palavra[6])
{
    int indice = rand() % 3; // gerar um indice aleatório entre 0 e 2

    // Loop para ir na matriz palavras[][] e armazenar uma palavra qualquer
    for (int i = 0; i < 6; i++)
    {
        sortear_palavra[i] = dicionario_palavras[indice][i];
    }
}

// Função principal do jogo
void jogo(char dicionario_palavras[3][6], char palavra_sorteada[6])
{
    int tentativas = 6;      // variável que armazena as tentativas
    char palavra_usuario[6]; // variável que armazena as palavras que o usuário digitar

    // Enquanto o número de tentativas for menor que 6, o jogo rodará normalmente
    while (tentativas > 0)
    {
        int letra_encontrada = 0; // Variável que vai detectar se a letra certa foi encontrada (na posição certa ou não)
        int palavra_valida = 0;   // Variável que vai detectar se a palavra está no dicionário ou não

        printf("Adivinhe a palavra (tentativas restantes: %d): ", tentativas);
        scanf("%s", &palavra_usuario);

        // Se o usuário digitar uma palavra que não está no dicionário
        for (int i_dicionario = 0; i_dicionario < 3; i_dicionario++)
        {
            // resetar a variavel a cada loop para funcionar a leitura letra a letra    
            letra_encontrada = 0;

            if (strcmp(palavra_usuario, dicionario_palavras[i_dicionario]) == 0)
            {
                palavra_valida = 1; // palavra foi encontrada
                break;              // Sai do loop
            }
        }

        if (!palavra_valida)
        {
            printf("Ops, palavra não encontrada no dicionário, digite novamente\n");
            continue; // Pede para o usuário tentar novamente
        }

        for (int i_letra_usuario = 0; i_letra_usuario < 5; i_letra_usuario++)
        {
            // Caso o usuário acerte a letra e ela está no lugar certo!
            if (palavra_usuario[i_letra_usuario] == palavra_sorteada[i_letra_usuario])
            {
                printf("^");
                letra_encontrada = 1;
            }
            else
            {
                // Caso o usuário acerte a letra mas ela está no lugar errado
                for (int i_letra_sorteada = 0; i_letra_sorteada < 5; i_letra_sorteada++)
                {
                    if (palavra_usuario[i_letra_usuario] == palavra_sorteada[i_letra_sorteada] && i_letra_usuario != i_letra_sorteada)
                    {
                        printf("!");
                        letra_encontrada = 1;
                    }
                }
            }

            // Caso o usuário erre a letra
            if (!letra_encontrada)
            {
                printf("x");
            }

            if (strcmp(palavra_usuario, palavra_sorteada) == 0)
            {
                printf("Palavra encontrada!");
                return;
            }
        }

        tentativas--; // Decrementar a variável tentativas a cada tentativa
    }
}