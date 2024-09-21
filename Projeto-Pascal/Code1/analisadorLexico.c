#include "analisadorLexico.h"

// inicioaliza o struct como um ponteiro
void InicializarAnalizadorLexico(AnalisadorLexico *lex) {
    lex->cabeca = 0;    
    lex->numLinha = 1;
    lex->lexema[300] = '\0';
    // lex->charEspecial = '+', '=';

    // abrindo arquivo de entrada e testando caso ocorra erro
    FILE *arquivoEntrada;
    arquivoEntrada = fopen("entrada.txt", "r");
    if (arquivoEntrada == NULL) {
        printf("\nErro ao abrir o arquivo aaa\n");
        exit(EXIT_FAILURE);
    }

    //TEM QUE ALOCAR A MEMORIA
    if (lex->fita == NULL) {
        printf("ERRO: ao alocar memória para a fita");
        exit(EXIT_FAILURE);
    }

    // Aloca memória para armazenar o conteúdo do arquivo
    // Inicialmente, alocamos um tamanho fixo e depois redimensionamos se necessário
    size_t bufferSize = 1024;
    size_t contentSize = 0;
    char *buffer = malloc(bufferSize);
    if (buffer == NULL) {
        printf("Erro ao alocar memória\n");
        fclose(arquivoEntrada);
        exit(EXIT_FAILURE);
    }

    // Lê o arquivo em blocos e armazena no buffer
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
    fclose(arquivoEntrada);
}

void AvancarCabeca(AnalisadorLexico *lex) {
    lex->cabeca += 1;
}

int ObterPosicaoDaCabeca(AnalisadorLexico *lex) {
    return lex->cabeca;
}

void AtualizarLinha(AnalisadorLexico *lex) {
    lex->numLinha += 1;
}

//concatena usando como base a ultima posição (ou seja, o tamanho) da palavra
char *concatenarLetra(char texto[], char letra){
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
        AvancarCabeca(lex);

        //concatena o character aceito para formar o lexema (se o caractere for '/n' o numero de linha sera iterado)
        if (charactere == '\n') {
            AtualizarLinha(lex);
        } else if ((charactere != ' ') && (charactere != '\t')  && (charactere != '\0')) {
            concatenarLetra(lex->lexema, charactere);
        }

    } else {
        printf("ERRO: A fita acabou!");
        return '\n';
    }
    
    return charactere;
}

// INICIO DA ANALISE DE ESTADOS

void EstadoFinal(AnalisadorLexico *lex) {
    FILE *arquivoSaid;
    arquivoSaid = fopen("TabelaTokens.txt", "a");
    if (arquivoSaid == NULL) { // Verifique se o arquivo foi aberto com sucesso
        printf("ERRO: Não foi possível abrir o arquivo de saída");
        exit(EXIT_FAILURE);
    }

    fprintf(arquivoSaid, "%s\n", lex->lexema);
    lex->lexema[0] = '\0';
    estadoInicial(lex);

    fclose(arquivoSaid);
}

void estadoInicial(AnalisadorLexico *lex) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    switch (c) {
        case ' ':
            estadoInicial(lex);
        break;

        case '\n':
            estadoInicial(lex);
        break;

        case '\t':
            estadoInicial(lex);
        break;

        case '\0':
            estadoInicial(lex);
        break;

        case 'p':
            q1(lex);
        break;

        case 'v':
            printf("v");
            // q1(lex);
        break;

        case 'i':
            printf("v");
            // q1(lex);
        break;

        case 'r':
            printf("r");
            // q1(lex);
        break;

        case 'b':
            printf("b");
            // q1(lex);
        break;

        case 'e':
            printf("e");
            // q1(lex);
        break;

        case 't':
            printf("t");
            // q1(lex);
        break;

        case 'w':
            printf("w");
            // q1(lex);
        break;

        case 'd':
            printf("d");
            // q1(lex);
        break;  

        default:
        printf("ERRO: caractere não reconhecido");
        exit(EXIT_FAILURE);
        break;
    }
}

void q1(AnalisadorLexico *lex) {
    char c = ObterCharactere(lex);
    if (c == 'r') {
        q2(lex);
    } else if (isalnum(c) != 0) {
        printf("chamar o de reconhecer identificador aaaaaaaaa");
    }
}

void q2(AnalisadorLexico *lex) {
    char c = ObterCharactere(lex);
    if(c == 'o') {
        q3(lex);
    } else if (isalnum(c) != 0) {
        EstadoFinal(lex);
    } else {
        printf("Nao e letra nem digito");
    }
}

void q3(AnalisadorLexico *lex) {
    char c = ObterCharactere(lex);
    if(c == 'g') {
        q4(lex);
    } else if (isalnum(c) != 0) {
        printf("chamar o de reconhecer identificador");
    }
}

void q4(AnalisadorLexico *lex) {
    char c = ObterCharactere(lex);
    if(c == 'r') {
        q5(lex);
    } else if (isalnum(c) != 0) {
        printf("chamar o de reconhecer identificador");
    }
}

void q5(AnalisadorLexico *lex) {
    char c = ObterCharactere(lex);
    if(c == 'a') {
        q6(lex);
    } else if (isalnum(c) != 0) {
        printf("chamar o de reconhecer identificador");
    }
}

void q6(AnalisadorLexico *lex) {
    char c = ObterCharactere(lex);
    if(c == 'm') {
        q7(lex);
    } else if (isalnum(c) != 0) {
        printf("chamar o de reconhecer identificador");
    }
}

void q7(AnalisadorLexico *lex) {
    //reconhece o token 'program'
    char c = ObterCharactere(lex);
    if ((isalnum(c) == 0)) {
        EstadoFinal(lex);
    } else {
        printf("chamar o de reconhecer identificador huehuehuehuehue");
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

    for (int i = 0; i < 14; i++) {
        ObterCharactere(lex);    
    }
    ObterCharactere(lex);
    printf("Depois da chamada de funcao 3 vezes:\n");
    printf("Poicao da cabeca: %i\nUltimo caractere: %c\n", ObterPosicaoDaCabeca(lex), ObterCharactere(lex));
    printf("Lexema lido: %s\n", lex->lexema);
    printf("n de linhas: %i", lex->numLinha);
}

int main() {
    AnalisadorLexico lex;
    
    InicializarAnalizadorLexico(&lex);
    estadoInicial(&lex);
    return 0;
}