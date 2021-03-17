#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListaTerminal.h"
#include "ListaRoteador.h"

typedef struct celula CelulaT;

struct celula{
    Terminal *terminal;
    int id_rot;
    CelulaT* prox;
};

struct lista{
    CelulaT *prim;
    CelulaT *ult;
};



ListaT *iniciaLista(){
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


    while(p && strcmp(retornaNomeTerminal(p->terminal), chave)){
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