/*
    ListaTerminal.h
    Trabalho I - Estrutura de Dados UFES 2020/2 - Patricia Dockhorn Costa
    Alunos: Joao Gabriel de Barros e Tales Viana
    Data: 17/03/2021
    github: JoaoGBarros || Talesvf
*/




#ifndef LISTA_TERMINAL_H
#define LISTA_TEMRINAL_H

#include "ListaRoteador.h"
#include "terminal.h"


typedef struct lista ListaT;
typedef struct celula CelulaT;


ListaT *IniciaListaT();

void CadastraTerminal(ListaT *lsta, char* nome, int id, char* localizacao);

void RemoveTerminal(ListaT *lista, char* chave);

void DestroiListaT(ListaT *lista);

void DesconectaTerminal(ListaT*l, char *terminal);

void ConectaTerminal(ListaT* t, ListaR* r, char* terminal, char* roteador);

CelulaT* RetornaPrimeiraCelulaListaTerminal(ListaT* lista);

CelulaT* RetornaUltimaCelulaListaTerminal(ListaT* lista);

CelulaT *RetornaProximaCelulaTerminal(CelulaT *p);

Terminal* RetornaTerminalLista(CelulaT* p);

CelulaT* BuscaTerminalLista(ListaT* l, char* chave);

int RetornaIdRot(CelulaT *p);

CelulaT* BuscaTerminalLista(ListaT* l, char* chave);

#endif