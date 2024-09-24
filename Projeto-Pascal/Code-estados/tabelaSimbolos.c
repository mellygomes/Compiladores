#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelaSimbolos.h"

#define TAM 199

void InicializarTabela(char *ts[]) {
    for (int i = 0; i < TAM; i++) {
        ts[i] = NULL;
    }
}

int FuncHash(int chave) {
    return chave % TAM;
}

int FuncHashStr(char str[]) {
    int tamStr = strlen(str);
    unsigned int hash = 0;

    for (int i = 0; i < tamStr; i++) {
        hash += str[i] * (i+1);
    }

    return hash % TAM;
}

void Inserir(char *ts[], char *str) {
    int id = FuncHashStr(str);

    while (ts[id] != NULL) {
        id = FuncHash(id + 1);
    }

    // Aloca memória para a string e a copia para a tabela
    ts[id] = malloc(strlen(str) + 1); 
    if (ts[id] != NULL) {
        strcpy(ts[id], str);  // Copia a string para a posição correta na tabela
    } else {
        printf("Erro ao alocar memória para str na tabela\n");
    }

}

char *Buscar(char *ts[], char chave[]) {
    int id = FuncHashStr(chave);
    int idInicial = id;  // Armazena o índice inicial (para fazer uma verificacao e evitar um loop infinito no while)

    while (ts[id] != NULL) {
        if (strcmp(ts[id], chave) == 0) {
            return ts[id];
        } else {
            id = FuncHash(id + 1);
            if (id == idInicial) {  // Se voltarmos ao índice original, a tabela foi completamente percorrida
                break;
            }
        }
    }
    return NULL;
}

void MostrarTabela(char *ts[]) {
    for (int i = 0; i < TAM; i++) {
        if (ts[i] != NULL) {
            printf("[%d:\t%s\t\t]\n", i, ts[i]);
        }
    }
}

//A tabela sera iniciada com todas as palavras reservadas
void InserirPalavrasReservadas(char *ts[]) {
    InicializarTabela(ts);
    Inserir(ts, "program");
    Inserir(ts, "var");
    Inserir(ts, "integer");
    Inserir(ts, "real");
    Inserir(ts, "begin");
    Inserir(ts, "end");
    Inserir(ts, "if");
    Inserir(ts, "then");
    Inserir(ts, "else");
    Inserir(ts, "while");
    Inserir(ts, "do");
}

// int main() {
//     char *tabelaSimbolos[TAM];
    
//     InicializarTabela(tabelaSimbolos);  // Inicializa a tabela
//     InserirPalavrasReservadas(tabelaSimbolos);
//     MostrarTabela(tabelaSimbolos);  // Mostra as strings armazenadas na tabela

//     printf("\nBuscar: %s\n", Buscar(tabelaSimbolos, "then"));
//     return 0;
// }