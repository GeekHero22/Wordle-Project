#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Assinaturas das funções
#define MAX_PALAVRAS 7000     // Número máximo de palavras
#define TAMANHO_MAX_PALAVRA 6 // Tamanho máximo de cada palavra
void sortearPalavra(char dicionario_palavras[MAX_PALAVRAS][TAMANHO_MAX_PALAVRA], char sortear_palavra[MAX_PALAVRAS]);
void finalJogada(char palavra_sorteada[TAMANHO_MAX_PALAVRA], int contador_tentativas, double tempo_decorrido);
void jogo(char dicionario_palavras[MAX_PALAVRAS][TAMANHO_MAX_PALAVRA], char palavra_sorteada[TAMANHO_MAX_PALAVRA]);
double calcularTempoDecorrido(time_t inicio);

int main()
{
    FILE *file;

    char palavra[TAMANHO_MAX_PALAVRA];
    char dicionario_palavras[MAX_PALAVRAS][TAMANHO_MAX_PALAVRA];
    file = fopen("palavras.txt", "r");
    int i = 0;
    // Lógica do sorteio das palavras
    // char dicionario_palavras[5][6]; // Palavras de teste

    while (fscanf(file, "%s", palavra) != EOF && i < MAX_PALAVRAS)
    { // inserindo as palavras no dicionario
        // Remove o caractere de nova linha (se houver) ao final de cada palavra
        palavra[strcspn(palavra, "\n")] = 0;
        // Armazenar a palavra no dicionário
        strcpy(dicionario_palavras[i], palavra);
        i++;
    }

    // Fechar o arquivo
    fclose(file);

    srand(time(NULL)); // Seed do rand (necessário para o funcionamento do rand())

    char palavra_sorteada[6]; // variável que vai pegar a palavra sorteada

    sortearPalavra(dicionario_palavras, palavra_sorteada);

    jogo(dicionario_palavras, palavra_sorteada);

    return 0;
}

// Função que vai sortear uma palavra
void sortearPalavra(char dicionario_palavras[MAX_PALAVRAS][TAMANHO_MAX_PALAVRA], char sortear_palavra[TAMANHO_MAX_PALAVRA])
{
    int indice = rand() % MAX_PALAVRAS;
    strncpy(sortear_palavra, dicionario_palavras[indice], 5);
    sortear_palavra[5] = '\0'; // Garantir que a palavra termina corretamente
}

// Função que solicita o nome do jogador e imprime umas paradas
void finalJogada(char palavra_sorteada[6], int contador_tentativas, double tempo_decorrido)
{
    char nome_jogador[30];

    while (getchar() != '\n')
        ; // Limpar o buffer '\n'

    printf("Digite o nome do jogador: ");
    fgets(nome_jogador, sizeof(nome_jogador), stdin);

    // Saidas
    printf("Nome do jogador: %s", nome_jogador);
    printf("Palavra: %s\n", palavra_sorteada);
    printf("Tentativas: %d\n", contador_tentativas);
    printf("Tempo em segundos: %.2lfs\n", tempo_decorrido);
}

// Função que calcula o tempo decorrido em segundos
double calcularTempoDecorrido(time_t inicio)
{
    time_t fim;                   // time_t é um tipo de dado definido na biblioteca <time.h> usado para armazenar valores de tempo
    time(&fim);                   // função do <time.h> que armazena o fim do tempo
    return difftime(fim, inicio); // Calcula a diferença entre dois instantes de tempo
}

// Função principal do jogozef
void jogo(char dicionario_palavras[MAX_PALAVRAS][TAMANHO_MAX_PALAVRA], char palavra_sorteada[6])
{
    int tentativas = 6;          // variável que armazena as tentativas
    char palavra_usuario[6];     // variável que armazena as palavras que o usuário digitar
    int contador_tentativas = 0; // variável que armazena a quantidade de tentativas que o usuário teve
    time_t inicio;               // variáveis para armazenar o inicio e o fim do tempo
    double tempo_decorrido;      // variável que irá armazenar o tempo decorrido (fazendo o cálculo de fim - inicio)

    time(&inicio); // obtém o tempo inicial

    // Enquanto o número de tentativas for menor que 6, o jogo rodará normalmente
    while (tentativas > 0)
    {
        int letra_encontrada = 0; // Variável que vai detectar se a letra certa foi encontrada (na posição certa ou não)
        int palavra_valida = 0;   // Variável que vai detectar se a palavra está no dicionário ou não
        contador_tentativas++;    // contar a quantidade de tentativas que o usuario teve

        // Fazer o usuário digitar a palavra que ele acha que é
        printf("Adivinhe a palavra (tentativas restantes: %d): ", tentativas);
        scanf("%s", palavra_usuario);

        // Se o usuário digitar uma palavra que não está no dicionário
        for (int i_dicionario = 0; i_dicionario < 5; i_dicionario++)
        {
            // resetar a variavel a cada loop para funcionar a leitura letra a letra
            letra_encontrada = 0;

            // função da biblioteca <string.h> que compara duas strings caractere por caractere e retorna um valor baseado na diferença entre elas
            if (strcmp(palavra_usuario, dicionario_palavras[i_dicionario]) == 0)
            {
                palavra_valida = 1; // palavra foi encontrada
                break;              // Sai do loop
            }
        }

        // Caso a palavra não seja encontrada
        if (!palavra_valida)
        {
            printf("Ops, palavra nao foi encontrada no dicionario, digite novamente\n");
            continue; // Pede para o usuário tentar novamente
        }

        // laço principal que percorre cada letra da palavra digitada pelo usuário
        for (int i_letra_usuario = 0; i_letra_usuario < 5; i_letra_usuario++)
        {
            letra_encontrada = 0;

            // Se o caractere da palavra digitada pelo usuário é igual ao caractere na mesma posição que a palavra sorteada
            if (palavra_usuario[i_letra_usuario] == palavra_sorteada[i_letra_usuario])
            {
                printf("^"); // Letra na posição correta
                letra_encontrada = 1;
            }
            else
            {
                // verificar todas as posições da palavra sorteada para ver se essa letra existe, mas em outro lugar.
                for (int i_letra_sorteada = 0; i_letra_sorteada < 5; i_letra_sorteada++)
                {
                    if (palavra_usuario[i_letra_usuario] == palavra_sorteada[i_letra_sorteada] && i_letra_usuario != i_letra_sorteada)
                    {
                        printf("!"); // Letra existe, mas está na posição errada
                        letra_encontrada = 1;
                        break;
                    }
                }
            }

            if (!letra_encontrada)
            {
                printf("x"); // Letra não existe na palavra
            }
        }

        printf("\n\n"); // Quebra de linha para melhorar a exibição

        if (strcmp(palavra_usuario, palavra_sorteada) == 0) // Caso o usuário acerte a palavra
        {
            printf("Palavra encontrada!\n");
            tempo_decorrido = calcularTempoDecorrido(inicio);                    // Cálculo do tempo
            finalJogada(palavra_sorteada, contador_tentativas, tempo_decorrido); // entrada do nome do jogador e imprimir
            return;
        }

        tentativas--; // Decrementar a variável tentativas a cada tentativa
    }

    // Caso o usuário não consiga acertar a palavra
    printf("Fim de jogo! A palavra correta era: %s\n", palavra_sorteada);
    tempo_decorrido = calcularTempoDecorrido(inicio);
    finalJogada(palavra_sorteada, contador_tentativas, tempo_decorrido);
}