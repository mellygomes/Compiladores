#ifndef ANALISADORLEXICO_H
#define ANALISADORLEXICO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    int cabeca, numLinha;
    char charEspecial;
    char fita[1000], lexema[300];
    
}  AnalisadorLexico;

void InicializarAnalizadorLexico(AnalisadorLexico *lex);
void teste1(AnalisadorLexico *lex); 
void AvancarCabeca(AnalisadorLexico *lex);
int ObterPosicaoDaCabeca(AnalisadorLexico *lex);
void AtualizarLinha(AnalisadorLexico *lex);
char ObterCharactere(AnalisadorLexico *lex);

// estados
void estadoInicial(AnalisadorLexico *lex);
void q1(AnalisadorLexico *lex);
void q2(AnalisadorLexico *lex);
void q3(AnalisadorLexico *lex);
void q4(AnalisadorLexico *lex);
void q5(AnalisadorLexico *lex);
void q6(AnalisadorLexico *lex);
void q7(AnalisadorLexico *lex);
void q8(AnalisadorLexico *lex);
void q9(AnalisadorLexico *lex);
void q10(AnalisadorLexico *lex);
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
void estadoFinal(AnalisadorLexico *lex);

//outros utilitarios
char *concatenarLetra(char texto[], char letra);

#endif