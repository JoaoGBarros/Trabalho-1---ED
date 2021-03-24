/*
    ListaTerminal.c
    Trabalho I - Estrutura de Dados UFES 2020/2 - Patricia Dockhorn Costa
    Alunos: Joao Gabriel de Barros e Tales Viana
    Data: 17/03/2021
    github: JoaoGBarros || Talesvf
*/





#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListaTerminal.h"
#include "ListaRoteador.h"


struct celula{
    Terminal *terminal;
    int id_rot;
    CelulaT* prox;
};

struct lista{
    CelulaT *prim;
    CelulaT *ult;
};



ListaT *iniciaListaT(){
    ListaT *tt;
    tt = (ListaT *)malloc(sizeof(ListaT));
    tt->prim = NULL;
    tt->ult = NULL;

    return tt;
}


void CadastraTerminal(ListaT *lista, char* nome, int id, char* localizacao){
    CelulaT *n;

    n = (CelulaT*)malloc(sizeof(CelulaT));
    
    n->terminal = CriaTerminal(nome, id, localizacao);
    n->prox = NULL;
    n->id_rot = 0;

    if(lista->prim == NULL){
        lista->prim = n;
        lista->ult = n;
    }else{
        lista->ult->prox = n;
        lista->ult = n;
    }
}


void RemoveTerminal(ListaT *lista, char* chave){
    CelulaT *p = lista->prim;
    CelulaT *prev = NULL;


    while(p && strcmp(RetornaNomeTerminal(p->terminal), chave)){
        prev = p;
        p = p->prox;
    }

    if(!p){
        return NULL;
    }

    if(p == lista->prim && p == lista->ult){
        lista->prim = NULL;
        lista->ult = NULL;
    }else if(p == lista->prim){
        lista->prim = p->prox;
    }else if(p == lista->ult){
        lista->ult = prev;
        lista->ult->prox = NULL;
    }else{
        prev->prox = p->prox;
    }
    free(p->terminal);
    free(p);
}

void ConectaTerminal(ListaT* l, char* terminal, char* roteador){
    CelulaT* term = buscaTerminalLista(l, terminal);
    CelulaR* rot = buscaRotLista(l, roteador);
    term->id_rot = RetornaIdRoteador(RetornaRoteadorLista(rot));
}

void DesconctaTerminal(ListaT*l, char *terminal){
    CelulaT* term = buscaTerminalLista(l, terminal);
    term->id_rot = 0;
}

CelulaT *RetornaProximaCelulaTerminal(CelulaT *p){
    return p->prox;
}

CelulaT* RetornaPrimeiraCelulaListaTerminal(ListaT* lista){
    return lista->prim;
}

CelulaT* RetornaUltimaCelulaListaTerminal(ListaT* lista){
    return lista->ult;
}

Terminal *RetormaTerminalLista(CelulaT* p){
    return p->terminal;
}

int RetornaIdRot(CelulaT *p){
    return p->id_rot;
}

void DestroiListaT(ListaT *lista){
    CelulaT *p = lista->prim;
    CelulaT *aux;
    while(p != NULL){
        aux = p->prox;
        free(p->terminal);
        free(p);
        p = aux;
    }
    free(lista);
}

CelulaT* BuscaTerminalLista(ListaT* l, char* chave){
    CelulaT* p;

    while(p && strcmp(RetornaNomeTerminal(p), chave)){
        p = p->prox;
    }

    if(p == NULL){
        //Erro
    }else{
        return p;
    }
}
