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


char* retornaNomeTerminal(Terminal* terminal){
    return terminal->nome;
}

int retornaIdTerminal(Terminal *terminal){
    return terminal->id;
}

char* retornaLocalizacaoTerminal(Terminal* terminal){
    return terminal->localizacao;
}

void DestroiTerminal(Terminal *terminal){
    free(terminal->nome);
    free(terminal->localizacao);
    free(terminal);
}