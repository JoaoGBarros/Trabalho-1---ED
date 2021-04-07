/*
    terminal.c
    Trabalho I - Estrutura de Dados UFES 2020/2 - Patricia Dockhorn Costa
    Alunos: Joao Gabriel de Barros e Tales Viana
    Data: 17/03/2021
    github: JoaoGBarros || Talesvf
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "terminal.h"
#include "roteador.h"

struct terminal{
    char* nome;
    int id;
    char* localizacao;
};


Terminal* CriaTerminal(char* nome, int id, char* localizacao){
    Terminal *t;
    t = (Terminal*)malloc(sizeof(Terminal));
    t->nome = strdup(nome);
    t->id = id;
    t->localizacao = strdup(localizacao);
    return t;
}


char* RetornaNomeTerminal(Terminal* terminal){
    return terminal->nome;
}

int RetornaIdTerminal(Terminal *terminal){
    return terminal->id;
}

char* RetornaLocalizacaoTerminal(Terminal* terminal){
    return terminal->localizacao;
}

void DestroiTerminal(Terminal *terminal){
    printf("%s, %d, %s\n", terminal->nome, terminal->id, terminal->localizacao);
    free(terminal->nome);
    free(terminal->localizacao);
    free(terminal);
}