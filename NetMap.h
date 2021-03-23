#ifndef NETMAP_H
#define NETMAP_H

#include <stdio.h>
#include "ListaRoteador.h"
#include "ListaTerminal.h"

int FrequenciaTerminal(ListaT* lista, char* loc);

int FrequenciaOperadora(ListaR* lista, char* op);

void EnviaPacotesDados(CelulaT* ter1, CelulaT* ter2);

void ImprimeNetMap(ListaR* listaRot, ListaT* listaTer);
    
    
#endif