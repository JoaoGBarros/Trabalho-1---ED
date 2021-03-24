/*
    roteador.h
    Trabalho I - Estrutura de Dados UFES 2020/2 - Patricia Dockhorn Costa
    Alunos: Joao Gabriel de Barros e Tales Viana
    Data: 17/03/2021
    github: JoaoGBarros || Talesvf
*/



#ifndef ROTEADOR_H
#define ROTEADOR_H

typedef struct roteador Roteador;

Roteador* CriaRoteador(char* nome, int id, char* op);

char* RetornaNomeRoteador(Roteador* roteador);

int RetornaIdRoteador(Roteador* roteador);

char* RetornaOperadoraRoteador(Roteador* roteador);

void DestroiRoteador(Roteador* roteador);

#endif