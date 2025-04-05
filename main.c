#include <stdio.h>  // entrada e saída padrão (ex: printf, scanf)
#include <stdlib.h> // funções como rand()
#include <time.h>   // tempo (ex: time, difftime)
#include <string.h> // manipulação de strings (ex: strcpy, strlen, strcmp)

#define MAX_PALAVRAS 7000     // Número máximo de palavras no arquivo
#define TAMANHO_MAX_PALAVRA 6 // Tamanho máximo de cada palavra

//* Assinatura das funções
void sortearPalavra(char dicionario_palavras[MAX_PALAVRAS][TAMANHO_MAX_PALAVRA], char sortear_palavra[TAMANHO_MAX_PALAVRA], int total_palavras);
void mostrarResultadoFinal(char palavra_sorteada[TAMANHO_MAX_PALAVRA], int contador_tentativas, double tempo_decorrido);
void jogo(char dicionario_palavras[MAX_PALAVRAS][TAMANHO_MAX_PALAVRA], char palavra_sorteada[TAMANHO_MAX_PALAVRA], int total_palavras);
double calcularTempoDecorrido(time_t inicio);

int main()
{
    FILE *file;

//! Abre o arquivo
    file = fopen("sem_acentos.txt", "r");

//* Verifica se houve um erro ao abrir o arquivo
    if (!file)
    {
        printf("Erro ao ler o arquivo.\n");
        return 1; // Encerra o programa com erro
    }

    char palavra[TAMANHO_MAX_PALAVRA]; // Variável temporária para armazenar cada palavra lida do arquivo
    char dicionario_palavras[MAX_PALAVRAS][TAMANHO_MAX_PALAVRA]; // Vetor que irá armazenar todas as palavras válidas (de 5 letras)
    int total_palavras = 0; // Contador de palavras válidas que foram lidas

//* Lê o arquivo até o final ou até atingir o número máximo de palavras
    while (fscanf(file, "%s", palavra) == 1 && total_palavras < MAX_PALAVRAS)
    {
        int tamanho = strlen(palavra); //* Calcula o tamanho da palavra

    //* Ignora palavras que não têm exatamente 5 letras
        if (tamanho != 5)
        {
            continue; //* pula para a próxima palavra
        }

    //* Copia a palavra válida (de 5 letras) para o dicionário
        strcpy(dicionario_palavras[total_palavras], palavra);
        total_palavras++; //* Aumenta o contador de palavras válidas
    }

//! Fecha o arquivo
    fclose(file); 

    //* Inicializa o gerador de números aleatórios com base no tempo atual
    //* Isso garante que cada execução sorteie palavras diferentes
    srand(time(NULL));
    
    char palavra_sorteada[TAMANHO_MAX_PALAVRA]; //* Variável que irá armazenar a palavra sorteada aleatoriamente
    
    sortearPalavra(dicionario_palavras, palavra_sorteada, total_palavras); //* Função que escolhe uma palavra aleatória do dicionário

    jogo(dicionario_palavras, palavra_sorteada, total_palavras); //* Inicia o jogo com a palavra sorteada

    return 0;
}

//* Função que vai sortear uma palavra
void sortearPalavra(char dicionario_palavras[MAX_PALAVRAS][TAMANHO_MAX_PALAVRA], char sortear_palavra[TAMANHO_MAX_PALAVRA], int total_palavras)
{
    int indice = rand() % total_palavras;
    strncpy(sortear_palavra, dicionario_palavras[indice], 5);
    sortear_palavra[5] = '\0';
}


//* Função que solicita o nome do jogador e imprime o resultado final do jogo
void mostrarResultadoFinal(char palavra_sorteada[TAMANHO_MAX_PALAVRA], int contador_tentativas, double tempo_decorrido)
{
    char nome_jogador[30];


//* Começa digitando o nome do jogador para em seguida mostrar o resultado final
    printf("Digite o nome do jogador: ");
    fgets(nome_jogador, sizeof(nome_jogador), stdin);
    nome_jogador[strcspn(nome_jogador, "\n")] = '\0'; // Remover o '\n' do final

//* Resultado final
    printf("Nome do jogador: %s", nome_jogador);
    printf("Palavra: %s\n", palavra_sorteada);
    printf("Tentativas: %d\n", contador_tentativas);
    printf("Tempo em segundos: %.2lfs\n", tempo_decorrido);
}


//* Função que calcula o tempo decorrido em segundos
double calcularTempoDecorrido(time_t inicio)
{
    time_t fim;                   // time_t é um tipo de dado definido na biblioteca <time.h> usado para armazenar valores de tempo
    time(&fim);                   // função do <time.h> que armazena o fim do tempo
    return difftime(fim, inicio); // Calcula a diferença entre dois instantes de tempo
}

//* Função principal do jogozef
void jogo(char dicionario_palavras[MAX_PALAVRAS][TAMANHO_MAX_PALAVRA], char palavra_sorteada[TAMANHO_MAX_PALAVRA], int total_palavras)
{
    char palavra_usuario[6];     // variável que armazena as palavras que o usuário digitar
    int contador_tentativas = 0; // variável que armazena a quantidade de tentativas que o usuário teve
    time_t inicio;               // variáveis para armazenar o inicio e o fim do tempo
    double tempo_decorrido;      // variável que irá armazenar o tempo decorrido (fazendo o cálculo de fim - inicio)

    time(&inicio); // obtém o tempo inicial

//* Enquanto o número de tentativas for menor que 6, o jogo rodará normalmente
    int tentativas = 6;  
    while (tentativas > 0)
    {
    //! Início do jogo
        int letra_encontrada = 0; // Variável que vai detectar se a letra certa foi encontrada (na posição certa ou não)
        int palavra_valida = 0;   // Variável que vai detectar se a palavra está no dicionário ou não

        //* Fazer o usuário digitar a palavra que ele acha que é
        printf("Adivinhe a palavra (tentativas restantes: %d): ", tentativas);
        scanf("%s", palavra_usuario);
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);


    //* Se o usuário digitar uma palavra que não tenha exatamente 5 letras
        if (strlen(palavra_usuario) != 5)
        {
            printf("A palavra deve ter exatamente 5 letras. Tente novamente.\n");
            continue; // Não desconta a tentativa
        }

    //* Verificar se a palavra está no arquivo
        for (int i_dicionario = 0; i_dicionario < total_palavras; i_dicionario++)
        {
            // resetar a variavel a cada loop para funcionar a leitura letra a letra
            letra_encontrada = 0;

            //? Se a palavra estiver no arquivo, então ela foi encontrada
            if (strcmp(palavra_usuario, dicionario_palavras[i_dicionario]) == 0)
            {
                palavra_valida = 1; // palavra foi encontrada
                break;              // Sai do loop
            }
        }

    //* Caso a palavra não seja encontrada, pedir pro usuário digitar outra palavra
        if (!palavra_valida)
        {
            printf("Ops, palavra nao foi encontrada no dicionario, digite novamente\n");
            continue; // Pede para o usuário tentar novamente
        }

        contador_tentativas++; // contar a quantidade de tentativas que o usuario teve

    //* laço principal que percorre cada letra da palavra digitada pelo usuário
        for (int i_letra_usuario = 0; i_letra_usuario < 5; i_letra_usuario++)
        {

            letra_encontrada = 0;

        //* Se o caractere da palavra digitada pelo usuário é igual ao caractere na mesma posição que a palavra sorteada, imprime ^
            if (palavra_usuario[i_letra_usuario] == palavra_sorteada[i_letra_usuario])
            {
                printf("^ "); // Letra na posição correta
                letra_encontrada = 1;
            }  
            else
            {
        //* Se não for igual ao caractere da mesma posição, vai verificar se aquela letra tem na palavra          
        //* verificar todas as posições da palavra sorteada para ver se essa letra existe, mas em outro lugar.
                for (int i_letra_sorteada = 0; i_letra_sorteada < 5; i_letra_sorteada++)
                {
                //* Se tem a letra na palavra, mas na posição errada, imprime !
                    if (palavra_usuario[i_letra_usuario] == palavra_sorteada[i_letra_sorteada] && i_letra_usuario != i_letra_sorteada)
                    {
                        printf("! "); // Letra existe, mas está na posição errada
                        letra_encontrada = 1;
                        break;
                    }
                }
            }

        //* Se a letra não for encontrada na palavra, imprime x
            if (!letra_encontrada)
            {
                printf("x "); // Letra não existe na palavra
            }
        }

        printf("\n\n"); // Quebra de linha para melhorar a exibição

    //* Se o usuário acertar a palavra, aparece na tela "Palavra encontrada", e mostra o resultado final
        if (strcmp(palavra_usuario, palavra_sorteada) == 0) // Caso o usuário acerte a palavra
        {
            printf("Palavra encontrada!\n");
            tempo_decorrido = calcularTempoDecorrido(inicio);                              // Cálculo do tempo
            mostrarResultadoFinal(palavra_sorteada, contador_tentativas, tempo_decorrido); // entrada do nome do jogador e imprimir
            return;
        }

        tentativas--; // Decrementar a variável tentativas a cada tentativa
    }

//* Se o usuário não conseguir acertar a palavra, aparece na tela a palavra correta, e mostra o resultado final
    printf("Fim de jogo! A palavra correta era: %s\n", palavra_sorteada);
    tempo_decorrido = calcularTempoDecorrido(inicio);
    mostrarResultadoFinal(palavra_sorteada, contador_tentativas, tempo_decorrido);
}