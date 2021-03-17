#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaRoteador.h"

typedef struct celular CelulaR;

typedef struct celulaenlaces CelulaEnlaces;

struct celular{
    Roteador* roteador;
    CelulaR* prox;
    CelulaEnlaces* enlace;
};

struct celulaenlaces{
    CelulaR* roteador;
    CelulaEnlaces* prox;
};

struct listar{
    CelulaR* prim;
    CelulaR* ult;
};

ListaR* IniciaListaR(){
    ListaR* lista = (ListaR*)malloc(sizeof(ListaR));
    lista->prim = NULL;
    lista->ult = NULL;
    return lista;
}

void CadastraRoteador(ListaR* lista, char* nome, int id, char* op){
    CelulaR* cel = (CelulaR*)malloc(sizeof(CelulaR));
    cel->roteador = CriaRoteador(nome, id, op);
    cel->prox = NULL;
    cel->enlace = NULL;

    if(lista->prim == NULL){
        lista->prim = cel;
        lista->ult = cel;
    }
    else{
        lista->ult->prox = cel;
        lista->ult = cel;
    }
}

void RemoveRoteador(ListaR* lista, char* chave){
    CelulaR *p = lista->prim;
    CelulaR *prev = NULL;


    while(p && strcmp(retornaNomeRoteador(p->roteador), chave)){
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
    free(p->roteador);
    free(p);
}

void DestroiListaR(ListaR* lista){
    CelulaR *p = lista->prim;
    CelulaR *aux;
    while(p != NULL){
        aux = p->prox;
        free(p->roteador);
        free(p);
        p = aux;
    }
    free(lista);
}
