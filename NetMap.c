#include <stdio.h>
#include <stdlib.h>
#include "NetMap.h"


int FrequenciaTerminal(ListaT* lista, char* loc){
    CelulaT *p;
    int nTerm = 0;

    for(p = RetornaPrimeiraCelulaListaTerminal(lista); p != NULL; p = RetornaProximaCelulaTerminal(p)){
        if(!strcmp(RetornaLocalizacaoTerminal((RetormaTerminalLista(p))), loc)){
            nTerm++;
        }
    }
    return nTerm;
}

int FrequenciaOperadora(ListaR* lista, char* op){
    CelulaR* p;
    int nRot = 0;
    for(p = RetornaPrimeiraCelulaListaRoteador(lista);p != NULL;p = RetornaProxCelulaRoteador(p)){
        if(!strcmp(RetornaOperadoraRoteador(RetornaRoteadorLista(p)), op)){
            nRot++;
        }
    }
    return nRot;
}

void EnviaPacotesDados(CelulaT* ter1, CelulaT* ter2){

}


void ImprimeNetMap(ListaR* listaRot, ListaT* listaTer){

}