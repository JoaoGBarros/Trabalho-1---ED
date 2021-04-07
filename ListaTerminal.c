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



ListaT *IniciaListaT(){
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


void RemoveTerminal(ListaT *lista, char* chave, FILE* log){
    CelulaT *p = lista->prim;
    CelulaT *prev = NULL;


    while(p && strcmp(RetornaNomeTerminal(p->terminal), chave)){
        prev = p;
        p = p->prox;
    }

    if(!p){
        fprintf(log, "Erro: Terminal %s inexistente no NetMap", chave);
        return;
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
    DestroiTerminal(p->terminal);
    free(p);
}

void ConectaTerminal(ListaT* t, ListaR* r, char* terminal, char* roteador, FILE* log){
    CelulaT* term = BuscaTerminalLista(t, terminal);
    CelulaR* rot = BuscaRoteadorLista(r, roteador);

    if(!term){
        fprintf(log, "Erro: Terminal %s inexistente no NetMap\n", terminal);
    }

    if(!rot){
        fprintf(log, "Erro: Roteador %s inexistente no NetMap\n", roteador);  
    }
    if(!term || !rot){
        return;
    }

    if(term != NULL && rot != NULL){
        term->id_rot = RetornaIdRoteador(RetornaRoteadorLista(rot));
    }

}

void DesconectaTerminal(ListaT*l, char *terminal, FILE* log){
    CelulaT* term = BuscaTerminalLista(l, terminal);
    if(!term){
        fprintf(log, "Erro: Terminal %s inexistente no NetMap", terminal);
        return;
    }
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

Terminal *RetornaTerminalLista(CelulaT* p){
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
        DestroiTerminal(p->terminal);
        free(p);
        p = aux;
    }
    free(lista);
}

CelulaT* BuscaTerminalLista(ListaT* l, char* chave){
    CelulaT* p = l->prim;

    while(p && strcmp(RetornaNomeTerminal(p->terminal), chave)){
        p = p->prox;
    }

    if(p == NULL){
        return NULL;
    }else{
        return p;
    }
}
