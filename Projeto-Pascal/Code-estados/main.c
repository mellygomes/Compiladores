#include "analisadorLexico.h" 
#include "tabelaSimbolos.h"

int main() {
    AnalisadorLexico lex;
    Token token;
    char *TS[TAM];
    IniciarAnaliseLexica(&lex, token, TS);
    return 0;
}