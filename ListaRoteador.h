#ifndef LISTAROT_H
#define LISTAROT_H

#include "roteador.h"

typedef struct listar ListaR;

typedef struct celular CelulaR;

typedef struct celulaenlaces CelulaEnlaces;

ListaR* IniciaListaR();

void CadastraRoteador(ListaR* lista, char* nome, int id, char* op);

void RemoveRoteador(ListaR* lista, char* chave);

void DestroiListaR(ListaR* lista);

#endif