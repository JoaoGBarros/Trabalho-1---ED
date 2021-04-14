/*
    roteador.c
    Trabalho I - Estrutura de Dados UFES 2020/2 - Patricia Dockhorn Costa
    Alunos: Joao Gabriel de Barros e Tales Viana
    Data: 17/03/2021
    github: JoaoGBarros || Talesvf
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "roteador.h"

struct roteador{
    char* nome;
    int id;
    char* operadora;
}; //Estrutura roteador, contendo suas informacoes.


// Responsavel por fazer a alocacao de memoria para o roteador
Roteador* CriaRoteador(char* nome, int id, char* op){
    Roteador* rot = (Roteador*)malloc(sizeof(Roteador));
    rot->nome = strdup(nome);
    rot->id = id;
    rot->operadora = strdup(op);
    return rot;
}

//Funcoes retorna para que seja possivel utilizar esses dados em outros TADs
char* RetornaNomeRoteador(Roteador* roteador){
    return roteador->nome;
}

int RetornaIdRoteador(Roteador* roteador){
    return roteador->id;
}

char* RetornaOperadoraRoteador(Roteador* roteador){
    return roteador->operadora;
}

// Responsavel por liberar a memoria de determinado roteador
void DestroiRoteador(Roteador* roteador){
    free(roteador->nome);
    free(roteador->operadora);
    free(roteador);
}