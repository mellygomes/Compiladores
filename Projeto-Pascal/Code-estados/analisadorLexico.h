#ifndef ANALISADORLEXICO_H
#define ANALISADORLEXICO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1

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
void IniciarAnaliseLexica(AnalisadorLexico *lex, Token token, char *TS[]); 
// void AvancarCabeca(AnalisadorLexico *lex);
// int ObterPosicaoDaCabeca(AnalisadorLexico *lex);
void AtualizarLinhaColuna(AnalisadorLexico *lex, char c);
// int EncontrarColuna(AnalisadorLexico *lex);
char ObterCharactere(AnalisadorLexico *lex);
void ObterToken(AnalisadorLexico *lex, Token token, char nome[300], char valor[300], int linha, char *TS[], int coluna);

// estados
void EstadoInicial(AnalisadorLexico *lex, Token token, char *TS[]);
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
void q11(AnalisadorLexico *lex, Token token, char *TS[]);
void q12(AnalisadorLexico *lex, Token token, char *TS[]);
void q13(AnalisadorLexico *lex, Token token, char *TS[]);
void q14(AnalisadorLexico *lex, Token token, char *TS[]);
void q15(AnalisadorLexico *lex, Token token, char *TS[]);
void q16(AnalisadorLexico *lex, Token token, char *TS[]);
void q17(AnalisadorLexico *lex, Token token, char *TS[]);
void q18(AnalisadorLexico *lex, Token token, char *TS[]);
void q19(AnalisadorLexico *lex, Token token, char *TS[]);
void q20(AnalisadorLexico *lex, Token token, char *TS[]);
void q21(AnalisadorLexico *lex, Token token, char *TS[]);
void q22(AnalisadorLexico *lex, Token token, char *TS[]);
void q23(AnalisadorLexico *lex, Token token, char *TS[]);
void q24(AnalisadorLexico *lex, Token token, char *TS[]);
void q25(AnalisadorLexico *lex, Token token, char *TS[]);
void q26(AnalisadorLexico *lex, Token token, char *TS[]);
void q27(AnalisadorLexico *lex, Token token, char *TS[]);
void q28(AnalisadorLexico *lex, Token token, char *TS[]);
void q29(AnalisadorLexico *lex, Token token, char *TS[]);
void q30(AnalisadorLexico *lex, Token token, char *TS[]);
void q31(AnalisadorLexico *lex, Token token, char *TS[]);
void q32(AnalisadorLexico *lex, Token token, char *TS[]);
void q33(AnalisadorLexico *lex, Token token, char *TS[]);
void q34(AnalisadorLexico *lex, Token token, char *TS[]);
void q35(AnalisadorLexico *lex, Token token, char *TS[]);
void q36(AnalisadorLexico *lex, Token token, char *TS[]);
void q37(AnalisadorLexico *lex, Token token, char *TS[]);
void q38(AnalisadorLexico *lex, Token token, char *TS[]);
void q39(AnalisadorLexico *lex, Token token, char *TS[]);
void q40(AnalisadorLexico *lex, Token token, char *TS[]);
void q41(AnalisadorLexico *lex, Token token, char *TS[]);
void q42(AnalisadorLexico *lex, Token token, char *TS[]);
void q43(AnalisadorLexico *lex, Token token, char *TS[]);
void q44(AnalisadorLexico *lex, Token token, char *TS[]);
void q45(AnalisadorLexico *lex, Token token, char *TS[]);
void EstadoFinal(AnalisadorLexico *lex, Token token, char *TS[]);

//outros utilitarios
char *concatenarLetra(char texto[], char letra);

#endif