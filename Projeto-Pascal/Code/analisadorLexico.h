#ifndef ANALISADORLEXICO_H
#define ANALISADORLEXICO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

//estados
// void estado_inicial(AnalisadorLexico *lex);
// void q1(AnalisadorLexico *lex);
// void q2(AnalisadorLexico *lex);
// void q3(AnalisadorLexico *lex);
// void q4(AnalisadorLexico *lex);
// void q20(AnalisadorLexico *lex);
// void estado_final(AnalisadorLexico *lex);

#endif