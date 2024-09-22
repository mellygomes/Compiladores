#include "analisadorLexico.h"
#include "tabelaSimbolos.h"

// inicioaliza o struct como um ponteiro
void InicializarAnalizadorLexico(AnalisadorLexico *lex) {
    lex->cabeca = 0;    
    lex->numLinha = 1;
    lex->lexema[300] = '\0';
    // lex->charEspecial = '+', '=';

    // abrindo arquivo de entrada e testando caso ocorra erro
    FILE *arquivoEntrada;
    arquivoEntrada = fopen("output/entrada.txt", "r");
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

void IniciarToken(Token token) {
    strcpy(token.Nome, "\0");
    strcpy(token.ValorLexema, "\0");
    token.linha = 0;
    token.coluna = 0;
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

//volta na fita contando os caracteres lidos ate encontrar o inicio dela (essa iteracao resulta no indice da coluna) 
int EncontrarColuna(AnalisadorLexico *lex) {
    char c = lex->fita[lex->cabeca];
    int temp = lex->cabeca;
    int coluna = 1;

    // Volta até o início da linha ou até encontrar um '\n' ou o fim do arquivo
    while ((temp > 0) && (c != '\n') && (c != '\0')) {
        temp--;
        coluna++;
        c = lex->fita[temp];
    }

    return coluna;  // Retorna a posição da coluna atual
}


//concatena usando como base a ultima posição (ou seja, o tamanho da palavra)
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
        return '\0';
    }
    
    return charactere;
}

//insere os tokens no arquivo "listaTokens"
void ObterToken(AnalisadorLexico *lex, Token token, char nome[300], char valor[300], int linha, char *TS[], int coluna) {
    IniciarToken(token);
    strcpy(token.Nome, nome);
    strcpy(token.ValorLexema, valor);
    token.linha = linha;
    token.coluna = coluna;

    FILE *arquivoSaida;
    arquivoSaida = fopen("listaTokens.txt", "a");
    if (arquivoSaida == NULL) { // Verifique se o arquivo foi aberto com sucesso
        printf("ERRO: Não foi possível abrir o arquivo de saída");
        exit(EXIT_FAILURE);
    }

    fprintf(arquivoSaida, "<%s, \"%s\"> - [%i - %i]\n", token.Nome, token.ValorLexema, token.linha, token.coluna);
    lex->lexema[0] = '\0';
    estadoInicial(lex, token, TS);

    fclose(arquivoSaida);
}

// ------------------------------ INICIO DA ANALISE DE ESTADOS

void estadoInicial(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    switch (c) {
        case ' ':
            estadoInicial(lex, token, TS);
        break;

        case '\n':
            estadoInicial(lex, token, TS);
        break;

        case '\t':
            estadoInicial(lex, token, TS);
        break;

        case 'p':
            q1(lex, token, TS);
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
            qID(lex, token, TS);
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
            MostrarTabela(TS);  
            printf("ERRO: caractere nao reconhecido");
            int coluna = EncontrarColuna(lex);
            printf("Linha: %i, Coluna: %i", lex->numLinha, EncontrarColuna(lex));
            exit(EXIT_FAILURE);
        break;
    }
}

void q1(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if (c == 'r') {
        q2(lex, token, TS);
    } else if (isalnum(c) != 0) {
        printf("chamar o de reconhecer identificador aaaaaaaaa");
    }
}

void q2(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'o') {
        q3(lex, token, TS);
    } else if (isalnum(c) != 0) {
        EstadoFinal(lex, token, TS);
    } else {
        printf("Nao e letra nem digito");
    }
}

void q3(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'g') {
        q4(lex, token, TS);
    } else if (isalnum(c) != 0) {
        printf("chamar o de reconhecer identificador");
    }
}

void q4(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'r') {
        q5(lex, token, TS);
    } else if (isalnum(c) != 0) {
        printf("chamar o de reconhecer identificador");
    }
}

void q5(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'a') {
        q6(lex, token, TS);
    } else if (isalnum(c) != 0) {
        printf("chamar o de reconhecer identificador");
    }
}

void q6(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'm') {
        q7(lex, token, TS);
    } else if (isalnum(c) != 0) {
        printf("chamar o de reconhecer identificador");
    }
}

void q7(AnalisadorLexico *lex, Token token, char *TS[]) {
    //reconhece o token 'program'
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if ((isalnum(c) == 0)) {
        int coluna = EncontrarColuna(lex) - (strlen(lex->lexema) + 1);
        ObterToken(lex, token, "PAL-RES", lex->lexema, lex->numLinha, TS, coluna);
    } else {
        printf("chamar o de reconhecer identificador huehuehuehuehue");
    }
}

void qID(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);

    //enquanto o caractere for alfanumerico, o lexema (token id) continuara sendo formado
    while (isalnum(c)) {
        c = ObterCharactere(lex);
    }

    //garantindo que a ultima posicao seja o caractere nulo finalizador
    int tamLex = strlen(lex->lexema);
    lex->lexema[tamLex - 1] = '\0';
    lex->cabeca -= 1;

    //inserindo o id na tabela de simbolos se ele ainda nao existir
    if(Buscar(TS, lex->lexema) == NULL) {
        Inserir(TS, lex->lexema);
    }

    int coluna = EncontrarColuna(lex) - (strlen(lex->lexema) + 1);
    ObterToken(lex, token, "ID", lex->lexema, lex->numLinha, TS, coluna); 
}

// Estado Final ---------------------------------------------------------------------------

void EstadoFinal(AnalisadorLexico *lex, Token token, char *TS[]) {
    FILE *arquivoSaid;
    arquivoSaid = fopen("TabelaTokens.txt", "a");
    if (arquivoSaid == NULL) { // Verifique se o arquivo foi aberto com sucesso
        printf("ERRO: Não foi possível abrir o arquivo de saída");
        exit(EXIT_FAILURE);
    }

    fprintf(arquivoSaid, "%s\n", lex->lexema);
    lex->lexema[0] = '\0';
    estadoInicial(lex, token, TS);

    fclose(arquivoSaid);
}

// ---------------------------------------------------------------------------------------

void teste2(AnalisadorLexico *lex, Token token, char *TS[]) {

    InicializarAnalizadorLexico(lex);
    IniciarToken(token);
    estadoInicial(lex, token, TS);

}