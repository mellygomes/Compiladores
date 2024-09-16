```C
#include "analisadorLexico.h"

// inicioaliza o struct como um ponteiro (assim poderá ser usado nas demais funcoes)
void InicializarAnalizadorLexico(AnalisadorLexico *lex) {
    lex->cabeca = 0;    
    lex->numLinha = 1;
    lex->lexema[300] = '\0';
    // lex->charEspecial = '+', '=';

    // abrindo arquivo de entrada e testando caso ocorra erro
    FILE *arquivoEntrada;
    arquivoEntrada = fopen("C:/Users/emanuelly.queiroz/Desktop/test/Compiladores/Projeto-Pascal/Code/output/entrada.txt", "r");
    if (arquivoEntrada == NULL) {
        printf("\nErro ao abrir o arquivo aaa\n");
        exit(EXIT_FAILURE);
    }

    if (lex->fita == NULL) {
        printf("ERRO ao alocar memória para a fita");
        exit(EXIT_FAILURE);
    }

    size_t bufferSize = 1024;
    size_t contentSize = 0;
    char *buffer = malloc(bufferSize);
    if (buffer == NULL) {
        printf("Erro ao alocar memória\n");
        fclose(arquivoEntrada);
        exit(EXIT_FAILURE);
    }

    /* Aloca memória para armazenar o conteúdo do arquivo
    criando um buffer para colocar o conteudo do arquivo em fita
    Inicialmente, alocamos um tamanho fixo e depois redimensionamos se necessário */
    size_t bytesRead;
    while ((bytesRead = fread(buffer + contentSize, 1, bufferSize - contentSize - 1, arquivoEntrada)) > 0) {
        contentSize += bytesRead;
        if (contentSize + 1 >= bufferSize) {
            bufferSize *= 2;
            buffer = realloc(buffer, bufferSize);
            if (buffer == NULL) {
                printf("Erro ao realocar memória\n");
                fclose(arquivoEntrada);
                exit(EXIT_FAILURE);
            }
        }
    }
    
    // Adiciona o terminador nulo ao final da string
    buffer[contentSize] = '\0';

    // Copia o conteúdo do buffer para lex->fita
    strncpy(lex->fita, buffer, sizeof(lex->fita) - 1);
    lex->fita[sizeof(lex->fita) - 1] = '\0'; // Garantir que a string está terminada

    // Libera a memória do buffer
    free(buffer);
    free(lex->fita);
    fclose(arquivoEntrada);

    /* Aloca memória para armazenar o conteúdo do arquivo
    criando um buffer para colocar o conteudo do arquivo em fita
    Inicialmente, alocamos um tamanho fixo e depois redimensionamos se necessário */
    // size_t bufferSize = 1024;
    // char *buffer = malloc(bufferSize);
    // if (buffer == NULL) {
    //     printf("Erro ao alocar memória\n");
    //     fclose(arquivoEntrada);
    //     exit(EXIT_FAILURE);
    // }

    // // Lê o arquivo em blocos e armazena no buffer
    // size_t bytesRead = fread(lex->fita, 1, sizeof(lex->fita) - 1, arquivoEntrada);
    // if (bytesRead == 0 && ferror(arquivoEntrada)) {
    //     printf("Erro ao ler o arquivo\n");
    //     fclose(arquivoEntrada);
    //     exit(EXIT_FAILURE);
    // }

    // // Adiciona o terminador nulo ao final da string
    // lex->fita[bytesRead] = '\0';

    // fclose(arquivoEntrada);
}

void AvancarCabeca(AnalisadorLexico *lex, int qtd) {
    lex->cabeca += qtd;
}

int ObterPosicaoDaCabeca(AnalisadorLexico *lex) {
    return lex->cabeca;
}

void AtualizarLinha(AnalisadorLexico *lex) {
    lex->numLinha += 1;
}

//concatena usando como base a ultima posição (ou seja, o tamanho) da palavra
char *concatenar_letra(char texto[], char letra){
    size_t tamanho = strlen(texto);
    texto[tamanho] = letra;
    texto[tamanho + 1] = '\0'; //recolocar terminador
    return texto;
}

//retorna o caractere na posicao da cabeca da fita, concatena para formar o lexema e chama avancarCabeca
char ObterCharactere(AnalisadorLexico *lex) {
    char charactere;
    size_t tamanhoFita = strlen(lex->fita);

    if ((size_t)lex->cabeca < tamanhoFita + 1) {
        charactere = lex->fita[lex->cabeca];

        //concatena o character aceito para formar o lexema
        if ((charactere != '\0') && (charactere != '\n')) {
            concatenar_letra(lex->lexema, charactere);
        }

    } else {
        printf("ERRO: A fita acabou!");
        return '\n';
    }
    
    return charactere;
}

// INICIO DA ANALISE DE ESTADOS

void estado_inicial(AnalisadorLexico *lex) {
    switch (ObterCharactere(lex)) {
    case 'p':
        q1(lex);  
        AvancarCabeca(lex, 1); 
    break;

    case 'v':
        q2(lex);    
    break;

    case 'w':
        q3(lex);    
    break;

    case 'r':
        q4(lex);    
    break;

    case 'd':
        q5(lex);    
    break;

    case 'b':
        q6(lex);    
    break;

    case 'i':
        q7(lex);    
    break;

    case 'e':
        q8(lex);    
    break;
    
    default:
        printf("Deu algo errado");
        break;
    }
}

void q2(AnalisadorLexico *lex) {

    switch (ObterCharactere(lex)) {
    case 'r':
        if (lex->fita[7] == "m") {
            printf("Program reconhecido");
            AvancarCabeca(*lex, 4);
        } else {
            printf("Deu ruim");
        }
    break;
    
    default:
        break;
    }
}



// ------------------------------------------------------ so pq bugou aaaaaaaaaaaaaaaaaaaah

void teste1(AnalisadorLexico *lex) {

    FILE *arquivoSaida;
    arquivoSaida = fopen("teste.txt", "w");
    if (arquivoSaida != NULL) { // Verifique se o arquivo foi aberto com sucesso
        fprintf(arquivoSaida, "%s", lex->fita); // escreve o conteúdo da fita no arquivo
        fclose(arquivoSaida); // Feche o arquivo
    } else {
        // Trate o erro de abertura do arquivo, se necessário
        printf("Não foi possível abrir o arquivo para escrita");
        exit(EXIT_FAILURE);
    }

    printf("\tTeste 1\nVerificando o funcionamento geral do inicio do projeto (utilizando a chamada da funcao obterCharactere 3 vezes)\n");
    printf("Verificacoes feitas: \n");
    printf("- leitura correta do arquivo;\n");
    printf("- utilizacao da variavel fita;\n");
    printf("- concatenacao dos caracteres para a obtencao do lexema;\n\n");

    printf("Inicio:\n");
    printf("Posicao da cabeca da fita: %i\nNum da linha: %i\n\n", lex->cabeca, lex->numLinha);

    ObterCharactere(lex);
    ObterCharactere(lex);
    ObterCharactere(lex);
    ObterCharactere(lex);
    ObterCharactere(lex);
    ObterCharactere(lex);
    ObterCharactere(lex);
    ObterCharactere(lex);
    ObterCharactere(lex);
    ObterCharactere(lex);
    printf("Depois da chamada de funcao 3 vezes:\n");
    printf("Poicao da cabeca: %i\nUltimo caractere: %c\n", ObterPosicaoDaCabeca(lex), ObterCharactere(lex));
    printf("Lexema lido: %s", lex->lexema);
}

int main() {
    AnalisadorLexico lex;
    
    InicializarAnalizadorLexico(&lex);
    teste1(&lex);
    return 0;
}
```