#include "analisadorLexico.h" 
#include "tabelaSimbolos.h"

int main() {
    AnalisadorLexico lex;
    Token token;
    char *TS[TAM];
    
    InserirPalavrasReservadas(TS);
    teste2(&lex, token, TS);
    MostrarTabela(TS);
    return 0;
}