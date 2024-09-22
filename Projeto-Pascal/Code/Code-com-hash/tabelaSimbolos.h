#ifndef TABELASIMBOLOS_H
#define TABELASIMBOLOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 41

void InicializarTabela(char *t[]);
void InserirPalavrasReservadas(char *ts[]);
int FuncHash(int chave);
int FuncHashStr(char str[]);
void Inserir(char *t[], char *str);
char *Buscar(char *t[], char chave[]);
void MostrarTabela(char *t[]);

#endif