#ifndef LISTA_TERMINAL_H
#define LISTA_TEMRINAL_H

#include "terminal.h"


typedef struct lista ListaT;
typedef struct celula CelulaT;


ListaT *iniciaLista();

void CadastraTerminal(ListaT *lista, char* nome, int id, char* localizacao);

void RemoveTerminal(ListaT *lista, char* chave);

void DestroiListaT(ListaT *lista);


#endif