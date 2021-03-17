#ifndef ROTEADOR_H
#define ROTEADOR_H

typedef struct roteador Roteador;

Roteador* CriaRoteador(char* nome, int id, char* op);

char* RetornaNomeRoteador(Roteador* roteador);

int RetornaIdRoteador(Roteador* roteador);

char* RetornaOperadoraRoteador(Roteador* roteador);

void DestroiRoteador(Roteador* roteador);

#endif