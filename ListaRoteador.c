/*
    ListaRoteador.c
    Trabalho I - Estrutura de Dados UFES 2020/2 - Patricia Dockhorn Costa
    Alunos: Joao Gabriel de Barros e Tales Viana
    Data: 17/03/2021
    github: JoaoGBarros || Talesvf
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaRoteador.h"


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

void DestroiEnlaces(CelulaR *rot){
    CelulaEnlaces* enlace = rot->enlace;
    CelulaEnlaces* ant = NULL;
    CelulaEnlaces* aux;

    
    while(enlace){
        for(aux = enlace->roteador->enlace;;aux = aux->prox){
            //printf("%s ", RetornaNomeRoteador(RetornaRoteadorLista(enlace->roteador)));
            //printf("%s ", RetornaNomeRoteador(RetornaRoteadorLista(aux->roteador)));
            //printf("\n");
            if(RetornaIdRoteador(RetornaRoteadorLista(aux->roteador)) == RetornaIdRoteador(RetornaRoteadorLista(rot))){
                if(!ant){
                    enlace->roteador->enlace = aux->prox;
                }
                else{
                    ant->prox = aux->prox;
                }
                free(aux);
                break;
            }
            ant = aux;
        }
        aux = enlace->prox;
        free(enlace);
        enlace = aux;
        ant = NULL;
    }
    printf("\n");

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

void RemoveRoteador(ListaR* lista, char* chave, FILE* log){
    CelulaR *p = lista->prim;
    CelulaR *prev = NULL;


    while(p && strcmp(RetornaNomeRoteador(p->roteador), chave)){
        prev = p;
        p = p->prox;
    }

    if(!p){
        fprintf(log, "Erro: Roteador %s inexistente no NetMap\n", chave);
    }

    else{
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
        printf("%s:", RetornaNomeRoteador(p->roteador));
        DestroiEnlaces(p);
        DestroiRoteador(p->roteador);
        free(p);
    }
}

CelulaR* BuscaRoteadorLista(ListaR* l, char* chave){
    CelulaR* p = RetornaPrimeiraCelulaListaRoteador(l);
    while(p && strcmp(RetornaNomeRoteador(RetornaRoteadorLista(p)), chave)){
        p = p->prox;
    }
    if(!p){
        return NULL;
    }
    else{
        return p;
    }
}

void ConectaRoteadores(ListaR* l, char* chave1, char* chave2, FILE* log){
    CelulaR* rot1 = BuscaRoteadorLista(l, chave1);
    CelulaR* rot2 = BuscaRoteadorLista(l, chave2);
    if(!rot1){
        fprintf(log, "Erro: Roteador %s inexistente no NetMap\n", chave1);
    }
    if(!rot2){
        fprintf(log, "Erro: Roteador %s inexistente no NetMap\n", chave2);
    }
    if(!rot1 || !rot2){
        return;
    }
    CelulaEnlaces* cel1 = (CelulaEnlaces*)malloc(sizeof(CelulaEnlaces));
    cel1->roteador = rot1;
    cel1->prox = NULL;
    CelulaEnlaces* cel2 = (CelulaEnlaces*)malloc(sizeof(CelulaEnlaces));
    cel2->roteador = rot2;
    cel2->prox = NULL;
    CelulaEnlaces* p;
    CelulaEnlaces* ant = NULL;
    for(p = rot1->enlace;p != NULL;p = p->prox){
        ant = p;
    }
    if(ant == NULL){
        rot1->enlace = cel2;
    }
    else{
        ant->prox = cel2;
    }
    ant = NULL;
    for(p = rot2->enlace;p != NULL;p = p->prox){
        ant = p;
    }
    if(ant == NULL){
        rot2->enlace = cel1;
    }
    else{
        ant->prox = cel1;
    }
}

void DesconectaRoteadores(ListaR* l, char* chave1, char* chave2, FILE* log){
    CelulaR* rot1 = BuscaRoteadorLista(l, chave1);
    CelulaR* rot2 = BuscaRoteadorLista(l, chave2);
    CelulaEnlaces* p = rot1->enlace;
    CelulaEnlaces* ant = NULL;
    while(p && strcmp(RetornaNomeRoteador(p->roteador->roteador), RetornaNomeRoteador(rot2->roteador))){
        ant = p;
        p = p->prox;
    }

    if(!rot1){
        fprintf(log, "Erro: Roteador %s inexistente no NetMap\n", chave1);
    }

    if(!rot2){
        fprintf(log, "Erro: Roteador %s inexistente no NetMap\n", chave2);
    }
    if(!p){
        fprintf(log, "Erro: Roteadores %s e %s nao estao conectados\n", RetornaNomeRoteador(RetornaRoteadorLista(rot1)), RetornaNomeRoteador(RetornaRoteadorLista(rot2)));

    }
    if(!rot1 || !rot2 || !p){
        return;
    }

    else if(!ant){
        rot1->enlace = p->prox;   
    }
    else{
        ant->prox = p->prox;
    }
    free(p);

    p = rot2->enlace;
    ant = NULL;

    while(p && strcmp(RetornaNomeRoteador(p->roteador->roteador), RetornaNomeRoteador(rot1->roteador))){
        ant = p;
        p = p->prox;
    }

    if(!p){
        fprintf(log, "Erro: Roteadores %s e %s nao estao conectados\n", RetornaNomeRoteador(RetornaRoteadorLista(rot2)), RetornaNomeRoteador(RetornaRoteadorLista(rot1)));
    }
    else if(!ant){
        rot2->enlace = p->prox;   
    }
    else{
        ant->prox = p->prox;
    }
    free(p);
}

Roteador* RetornaRoteadorLista(CelulaR* rot){
    return rot->roteador;
}

CelulaR* RetornaProxCelulaRoteador(CelulaR* cel){
    return cel->prox;
}

CelulaR* RetornaPrimeiraCelulaListaRoteador(ListaR* lista){
    return lista->prim;
}

CelulaR* RetornaUltimaCelulaListaRoteador(ListaR* lista){
    return lista->ult;
}

CelulaR* RetornaRoteadorCelulaEnlace(CelulaEnlaces* cel){
    return cel->roteador;
}

CelulaEnlaces* RetornaProximoEnlace(CelulaEnlaces *cel){
    return cel->prox;
}

CelulaEnlaces* RetornaEnlace(CelulaR* cel){
    return cel->enlace;
}


void DestroiListaR(ListaR* lista){
    CelulaR *p = lista->prim;
    CelulaR *aux;
    while(p != NULL){
        aux = p->prox;
        printf("%s  ", RetornaNomeRoteador(p->roteador));
        DestroiEnlaces(p);
        DestroiRoteador(p->roteador);
        free(p);
        p = aux;
    }
    free(lista);
}
