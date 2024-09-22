#ifndef ANALISADORLEXICO_H
#define ANALISADORLEXICO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    int cabeca, numLinha, coluna;
    char charEspecial;
    char fita[1000], lexema[300];
    
}  AnalisadorLexico;

typedef struct {
    char Nome[300];
    char ValorLexema[300];
    int linha, coluna;
} Token;

void InicializarAnalizadorLexico(AnalisadorLexico *lex);
void IniciarToken(Token token);
void teste2(AnalisadorLexico *lex, Token token, char *TS[]); 
void AvancarCabeca(AnalisadorLexico *lex);
int ObterPosicaoDaCabeca(AnalisadorLexico *lex);
void AtualizarLinha(AnalisadorLexico *lex);
int EncontrarColuna(AnalisadorLexico *lex);
char ObterCharactere(AnalisadorLexico *lex);
void ObterToken(AnalisadorLexico *lex, Token token, char nome[300], char valor[300], int linha, char *TS[], int coluna);

// estados
void estadoInicial(AnalisadorLexico *lex, Token token, char *TS[]);
void q1(AnalisadorLexico *lex, Token token, char *TS[]);
void q2(AnalisadorLexico *lex, Token token, char *TS[]);
void q3(AnalisadorLexico *lex, Token token, char *TS[]);
void q4(AnalisadorLexico *lex, Token token, char *TS[]);
void q5(AnalisadorLexico *lex, Token token, char *TS[]);
void q6(AnalisadorLexico *lex, Token token, char *TS[]);
void q7(AnalisadorLexico *lex, Token token, char *TS[]);
void q8(AnalisadorLexico *lex, Token token, char *TS[]);
void q9(AnalisadorLexico *lex, Token token, char *TS[]);
void q10(AnalisadorLexico *lex, Token token, char *TS[]);
void q11(AnalisadorLexico *lex);
void q12(AnalisadorLexico *lex);
void q13(AnalisadorLexico *lex);
void q14(AnalisadorLexico *lex);
void q15(AnalisadorLexico *lex);
void q16(AnalisadorLexico *lex);
void q17(AnalisadorLexico *lex);
void q18(AnalisadorLexico *lex);
void q19(AnalisadorLexico *lex);
void q20(AnalisadorLexico *lex);
void qID(AnalisadorLexico *lex, Token token, char *TS[]);
void EstadoFinal(AnalisadorLexico *lex, Token token, char *TS[]);

//outros utilitarios
char *concatenarLetra(char texto[], char letra);

#endif