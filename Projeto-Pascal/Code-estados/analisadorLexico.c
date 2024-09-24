/* 
    Operacao geral do codigo:

    O seguinte codigo opera de forma comumente utilizada para a implementacao de automatos finitos e/ou maquinas de turing, onde
    o conteudo do arquivo a ser analisado e lido e inserdo numa variavel (fita), que por sua vez e percorrida por outra variavel (cabeca)
    toda vez que a funcao obtercaractere() e chamada.
    Cada estado (qn) direciona para o proximo de acordo com o caractere lido, sendo que:

    Se e lido um caractere esperado para palavra reservada: chama o proximo para a palavra ate que esta seja identificada
    Se e lido caractere mas nao o da palavra reservada ou se le numero: chama o estado que identifica ids
    Se e lido espaco ou tab ou fim de linha ou caractere nulo: o identificador ja esta formado, chama obtertoken()
    Se e lido simbolo: verifica se o proximo e Tab ou \0 ou EOL ou \n, se sim, identifica o simbolo ou operador
    Se o proximo depois de simbolo for outro simbolo: verifica se o proximo e Tab ou \0 ou EOL ou \n, se sim, identifica OPs com simbolos duplos
    qualquer coisa fora disso, apresenta erro
*/

#include "analisadorLexico.h"
#include "tabelaSimbolos.h"

// inicioaliza o struct como um ponteiro
void InicializarAnalizadorLexico(AnalisadorLexico *lex) {
    lex->cabeca = 0;    
    lex->numLinha = 1;
    lex->lexema[300] = '\0';
    lex->coluna = 1;

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

void AtualizarLinhaColuna(AnalisadorLexico *lex, char c) {
    if (c == '\n') {
        lex->numLinha++;
        lex->coluna = 1;
    } else if (c == '\0') {
        lex->coluna = 1;
    } else {
        lex->coluna++;
    }
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
        AtualizarLinhaColuna(lex, charactere);
        lex->cabeca++;

        //concatena o character aceito para formar o lexema (se o caractere for '/n' o numero de linha sera iterado)
        if ((charactere != ' ') && (charactere != '\t')  && (charactere != '\0') && (charactere != '\n')) {
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
    token.coluna = (coluna - strlen(token.ValorLexema)) - 2;

    FILE *arquivoSaida;
    arquivoSaida = fopen("listaTokens.txt", "a");
    if (arquivoSaida == NULL) { // Verifique se o arquivo foi aberto com sucesso
        printf("ERRO: Não foi possível abrir o arquivo de saída");
        exit(EXIT_FAILURE);
    }

    fprintf(arquivoSaida, "<%s, \"%s\"> %i : %i\n", token.Nome, token.ValorLexema, token.linha, token.coluna);
    lex->lexema[0] = '\0';
    EstadoInicial(lex, token, TS);

    fclose(arquivoSaida);
}

// ------------------------------ INICIO DA ANALISE DE ESTADOS
void EstadoInicial(AnalisadorLexico *lex, Token token, char *TS[]) {

    size_t tamanhoFita = strlen(lex->fita);
    if ((size_t)lex->cabeca < tamanhoFita) {

        char c = ObterCharactere(lex);
        if (isupper(c)) {
            c = tolower(c);
        }

        if (c ==' ') {
            EstadoInicial(lex, token, TS);

        } else if (c =='\n') {
            EstadoInicial(lex, token, TS);

        } else if (c =='\t') {
            EstadoInicial(lex, token, TS);

        } else if (c == 'p') {
            q1(lex, token, TS);

        } else if (c == 'v') {
            q8(lex, token, TS);

        } else if (c == 'i') {
            q11(lex, token, TS);

        } else if (c == 'r') {
            q18(lex, token, TS);

        } else if (c == 'b') {
            q22(lex, token, TS);

        } else if (c == 'e') {
            q27(lex, token, TS);

        } else if (c == 't') {
            printf("t");
            q31(lex, token, TS);

        } else if (c == 'w') {
            printf("w");
            q38(lex, token, TS);
            
        } else if (c == 'd') {
            printf("d");
            q43(lex, token, TS);

        } else if (isalnum(c)) {
            q45(lex, token, TS);
        } else {
            MostrarTabela(TS);  
            printf("ERRO: caractere nao reconhecido");
            printf("Linha: %i, Coluna: %i", lex->numLinha, lex->coluna);
            exit(EXIT_FAILURE);
        }

    } else {
        printf("\nAnalise lexica finalizada com sucesso! Um arquivo 'listaTokens' foi gerado.\n");
        printf("Confira tambem a tabela de simbolos gerada: \n");
        //mostrar tabela de simbolos
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
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
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
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
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
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
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
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
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
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
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
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q7(AnalisadorLexico *lex, Token token, char *TS[]) {
    //reconhece o token 'program'
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if ((isalnum(c) == 0)) {
        ObterToken(lex, token, "PAL-RES", lex->lexema, lex->numLinha, TS, lex->coluna);

    } else if ((isalnum(c) != 0)) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q8(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'a') {
        q9(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q9(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'r') {
        q10(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q10(AnalisadorLexico *lex, Token token, char *TS[]) {
    //reconhece o token 'var'
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if ((isalnum(c) == 0)) {
        ObterToken(lex, token, "PAL-RES", lex->lexema, lex->numLinha, TS, lex->coluna);

    } else if ((isalnum(c) != 0)) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q11(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'n') {
        q12(lex, token, TS);
    } else if (c == 'f') {
        q30(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q12(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 't') {
        q13(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q13(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'e') {
        q14(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q14(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'g') {
        q15(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q15(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'e') {
        q16(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q16(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'r') {
        q17(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q17(AnalisadorLexico *lex, Token token, char *TS[]) {
    //reconhece o token 'integer'
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if ((isalnum(c) == 0)) {
        ObterToken(lex, token, "PAL-RES", lex->lexema, lex->numLinha, TS, lex->coluna);

    } else if ((isalnum(c) != 0)) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q18(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'e') {
        q19(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q19(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'a') {
        q20(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q20(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'l') {
        q21(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q21(AnalisadorLexico *lex, Token token, char *TS[]) {
    //reconhece o token 'real'
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if ((isalnum(c) == 0)) {
        ObterToken(lex, token, "PAL-RES", lex->lexema, lex->numLinha, TS, lex->coluna);

    } else if ((isalnum(c) != 0)) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q22(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'e') {
        q23(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q23(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'g') {
        q24(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q24(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'i') {
        q25(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q25(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'n') {
        q26(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q26(AnalisadorLexico *lex, Token token, char *TS[]) {
    //reconhece o token 'begin'
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if ((isalnum(c) == 0)) {
        ObterToken(lex, token, "PAL-RES", lex->lexema, lex->numLinha, TS, lex->coluna);

    } else if ((isalnum(c) != 0)) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q27(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'n') {
        q28(lex, token, TS);
    } else if (c == 'l') {
        q35(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q28(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'd') {
        q29(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

//reconhece o token 'end'
void q29(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if ((isalnum(c) == 0)) {
        ObterToken(lex, token, "PAL-RES", lex->lexema, lex->numLinha, TS, lex->coluna);

    } else if ((isalnum(c) != 0)) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

//reconhece o token 'if'
void q30(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if ((isalnum(c) == 0)) {
        ObterToken(lex, token, "PAL-RES", lex->lexema, lex->numLinha, TS, lex->coluna);

    } else if ((isalnum(c) != 0)) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q31(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'h') {
        q32(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q32(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'e') {
        q33(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q33(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'n') {
        q34(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

//reconhece o token 'then'
void q34(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if ((isalnum(c) == 0)) {
        ObterToken(lex, token, "PAL-RES", lex->lexema, lex->numLinha, TS, lex->coluna);

    } else if ((isalnum(c) != 0)) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q35(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 's') {
        q36(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q36(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'e') {
        q37(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

//reconhece o token 'else'
void q37(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if ((isalnum(c) == 0)) {
        ObterToken(lex, token, "PAL-RES", lex->lexema, lex->numLinha, TS, lex->coluna);

    } else if ((isalnum(c) != 0)) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q38(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'h') {
        q39(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q39(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'i') {
        q40(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q40(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'l') {
        q41(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q41(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'e') {
        q42(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

//reconhece o token 'while'
void q42(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if ((isalnum(c) == 0)) {
        ObterToken(lex, token, "PAL-RES", lex->lexema, lex->numLinha, TS, lex->coluna);

    } else if ((isalnum(c) != 0)) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

void q43(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if(c == 'o') {
        q44(lex, token, TS);
    } else if (isalnum(c) != 0) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

//reconhece o token 'do'
void q44(AnalisadorLexico *lex, Token token, char *TS[]) {
    char c = ObterCharactere(lex);
    if (isupper(c)) {
        c = tolower(c);
    }

    if ((isalnum(c) == 0)) {
        ObterToken(lex, token, "PAL-RES", lex->lexema, lex->numLinha, TS, lex->coluna);

    } else if ((isalnum(c) != 0)) {
        q45(lex, token, TS);
    } else if (isalnum(c) == 0) {
        q45(lex, token, TS);
    }
}

//reconhece identificadores
void q45(AnalisadorLexico *lex, Token token, char *TS[]) {
    //precisa voltar 1 para fazer a analise do caractere anterior novamente (pois se for um espaco ou simbolo, o caractere ja esta formado, e nao deve entrar no while)
    int tamLex1 = strlen(lex->lexema);
    lex->lexema[tamLex1 - 1] = '\0';
    lex->cabeca -= 1;
    char c = ObterCharactere(lex);

    //enquanto o caractere for alfanumerico, o lexema (token id) continuara sendo formado
    while (isalnum(c)) {
        c = ObterCharactere(lex);
    }

    // garantindo que a ultima posicao seja o caractere nulo finalizador
    int tamLex2 = strlen(lex->lexema);
    lex->lexema[tamLex2] = '\0';
    lex->cabeca -= 1; //precisa voltar uma posicao na cabeca, pois o while sempre tera avancado um a mais do id para verificar que isalnum(c) e falso
    
    //isso e gambiarra - tem que arrumar
    if (lex->fita[lex->cabeca] == '\n') {
        lex->numLinha--;
    } 

    //inserindo o id na tabela de simbolos se ele ainda nao existir
    if(Buscar(TS, lex->lexema) == NULL) {
        Inserir(TS, lex->lexema);
    }

    // int coluna = (EncontrarColuna(lex) - (strlen(lex->lexema)));
    ObterToken(lex, token, "ID", lex->lexema, lex->numLinha, TS, lex->coluna); 
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
    EstadoInicial(lex, token, TS);

    fclose(arquivoSaid);
}

// ---------------------------------------------------------------------------------------
void IniciarAnaliseLexica(AnalisadorLexico *lex, Token token, char *TS[]) {
    InicializarAnalizadorLexico(lex);
    IniciarToken(token);
    InserirPalavrasReservadas(TS);
    EstadoInicial(lex, token, TS);
}