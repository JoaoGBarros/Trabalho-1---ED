#ifndef LISTAROT_H
#define LISTAROT_H

#include "roteador.h"

typedef struct listar ListaR;
typedef struct celular CelulaR;



ListaR* IniciaListaR();

void CadastraRoteador(ListaR* lista, char* nome, int id, char* op);

void RemoveRoteador(ListaR* lista, char* chave);

void ConectaRoteadores(CelulaR* rot1, CelulaR* rot2);

void DesconectaRoteadores(CelulaR* rot1, CelulaR* rot2);

Roteador* RetornaRoteadorLista(CelulaR* rot);

void DestroiListaR(ListaR* lista);

#endif