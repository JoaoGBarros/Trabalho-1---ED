/*
    NetMap.h
    Trabalho I - Estrutura de Dados UFES 2020/2 - Patricia Dockhorn Costa
    Alunos: Joao Gabriel de Barros e Tales Viana
    Data: 17/03/2021
    github: JoaoGBarros || Talesvf
*/


#ifndef NETMAP_H
#define NETMAP_H

#include <stdio.h>
#include "ListaRoteador.h"
#include "ListaTerminal.h"

void FrequenciaTerminal(ListaT* lista, char* loc, FILE* saida);

void FrequenciaOperadora(ListaR* lista, char* op, FILE* saida);

void EnviarPacotesDados(ListaR* r, ListaT* t, char* chave1, char* chave2, int tam, FILE* saida, FILE* log);

void ImprimeNetMap(ListaR* listaRot, ListaT* listaTer, FILE* saida);

int EnlaceRoteador(CelulaR* rot1, CelulaR* rot2, int* rots, int* tam);
    
    
#endif