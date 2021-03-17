#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "roteador.h"

struct roteador{
    char* nome;
    int id;
    char* operadora;
};

Roteador* CriaRoteador(char* nome, int id, char* op){
    Roteador* rot = (Roteador*)malloc(sizeof(Roteador));
    rot->nome = strdup(nome);
    rot->id = id;
    rot->operadora = strdup(op);
    return rot;
}

char* RetornaNomeRoteador(Roteador* roteador){
    return roteador->nome;
}

int RetornaIdRoteador(Roteador* roteador){
    return roteador->id;
}

char* RetornaOperadoraRoteador(Roteador* roteador){
    return roteador->operadora;
}

void DestroiRoteador(Roteador* roteador){
    free(roteador->nome);
    free(roteador->operadora);
    free(roteador);
}