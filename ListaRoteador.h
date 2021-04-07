/*
    ListaRoteador.h
    Trabalho I - Estrutura de Dados UFES 2020/2 - Patricia Dockhorn Costa
    Alunos: Joao Gabriel de Barros e Tales Viana
    Data: 17/03/2021
    github: JoaoGBarros || Talesvf
*/



#ifndef LISTAROT_H
#define LISTAROT_H

#include "roteador.h"

typedef struct listar ListaR;
typedef struct celular CelulaR;
typedef struct celulaenlaces CelulaEnlaces;


ListaR* IniciaListaR();

void CadastraRoteador(ListaR* lista, char* nome, int id, char* op);

void RemoveRoteador(ListaR* lista, char* chave, FILE* log);

CelulaR* BuscaRoteadorLista(ListaR* l, char* chave);

void ConectaRoteadores(ListaR* l, char* chave1, char* chave2, FILE* log);

void DesconectaRoteadores(ListaR* l, char* chave1, char* chave2, FILE* log);

Roteador* RetornaRoteadorLista(CelulaR* rot);

void DestroiListaR(ListaR* lista);

CelulaR* RetornaProxCelulaRoteador(CelulaR* cel);

CelulaR* RetornaPrimeiraCelulaListaRoteador(ListaR* lista);

CelulaR* RetornaUltimaCelulaListaRoteador(ListaR* lista);

CelulaR* RetornaRoteadorCelulaEnlace(CelulaEnlaces* cel);

CelulaEnlaces* RetornaProximoEnlace(CelulaEnlaces *cel);

CelulaEnlaces* RetornaEnlace(CelulaR* cel);







#endif