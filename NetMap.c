/*
    NetMap.c
    Trabalho I - Estrutura de Dados UFES 2020/2 - Patricia Dockhorn Costa
    Alunos: Joao Gabriel de Barros e Tales Viana
    Data: 17/03/2021
    github: JoaoGBarros || Talesvf
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NetMap.h"


void FrequenciaTerminal(ListaT* lista, char* loc, FILE* saida){
    CelulaT *p;
    int nTerm = 0;

    for(p = RetornaPrimeiraCelulaListaTerminal(lista); p != NULL; p = RetornaProximaCelulaTerminal(p)){
        if(!strcmp(RetornaLocalizacaoTerminal(RetornaTerminalLista(p)), loc)){
            nTerm++;
        }
    }
    fprintf(saida, "FREQUENCIATERMINAL %s: %d\n", loc, nTerm);
}

void FrequenciaOperadora(ListaR* lista, char* op, FILE* saida){
    CelulaR* p;
    int nRot = 0;
    for(p = RetornaPrimeiraCelulaListaRoteador(lista);p != NULL;p = RetornaProxCelulaRoteador(p)){
        if(!strcmp(RetornaOperadoraRoteador(RetornaRoteadorLista(p)), op)){
            nRot++;
        }
    }
    fprintf(saida, "FREQUENCIAOPERADORA %s: %d \n", op, nRot);
}

int EnlaceRoteador(CelulaR* rot1, CelulaR* rot2, int* rots, int* tam){
    CelulaEnlaces* enlace;
    int i = 0;
    int jaFoi = 0;
    //printf("Rot 1: %d Rot 2: %d ", RetornaIdRoteador(RetornaRoteadorLista(rot1)), RetornaIdRoteador(RetornaRoteadorLista(rot2)));
    enlace = RetornaEnlace(rot1);
    for(enlace = RetornaEnlace(rot1);enlace != NULL;enlace = RetornaProximoEnlace(enlace)) {
        if (RetornaRoteadorCelulaEnlace(enlace) == rot2) {
            return 1;
        }
    }

    for(enlace = RetornaEnlace(rot1);enlace != NULL;enlace = RetornaProximoEnlace(enlace)){
        jaFoi = 0;
        for(i = 0; i < *tam ;i++){
            if(RetornaIdRoteador(RetornaRoteadorLista(RetornaRoteadorCelulaEnlace(enlace))) == rots[i]){
                jaFoi++;
            }
        }
        if(jaFoi == 0){
            *tam = *tam + 1;
            rots = (int*)realloc(rots, *tam * sizeof(int));
            rots[*tam - 1] = RetornaIdRoteador(RetornaRoteadorLista(RetornaRoteadorCelulaEnlace(enlace)));
            if(EnlaceRoteador(RetornaRoteadorCelulaEnlace(enlace), rot2, rots, tam)){
                return 1;
            }
            
            }
    
        }
    
    

    return 0;

}

void EnviarPacotesDados(ListaR* r, ListaT* t, char* chave1, char* chave2, FILE* saida, FILE* log){
    CelulaT* ter1 = BuscaTerminalLista(t, chave1);
    CelulaT* ter2 = BuscaTerminalLista(t, chave2);
    CelulaR* rot1 = NULL, *rot2 = NULL;
    CelulaR* p;

    int tam = 2;
    int* tamPointer = &tam;
    if(ter1 && ter2){
        //printf("    %s %s    ", RetornaNomeTerminal(RetornaTerminalLista(ter1)), RetornaNomeTerminal(RetornaTerminalLista(ter2)));
        if(!RetornaIdRot(ter1) || !RetornaIdRot(ter2)){
            fprintf(saida, "ENVIARPACOTESDADOS %s %s: NAO\n", chave1, chave2);
            return;
        }
        for(p = RetornaPrimeiraCelulaListaRoteador(r);p != NULL;p = RetornaProxCelulaRoteador(p)){
            if(RetornaIdRoteador(RetornaRoteadorLista(p)) == RetornaIdRot(ter1)){
                rot1 = p;
            }
            if(RetornaIdRoteador(RetornaRoteadorLista(p)) == RetornaIdRot(ter2)){
                rot2 = p;
            }
            if(rot1 && rot2) break;
        }
    }else{
        if(!ter1){
            fprintf(log, "Erro: Terminal %s inexistente no NetMap", chave1);
        }
        if(!ter2){
            fprintf(log, "Erro: Terminal %s inexistente no NetMap", chave2);
        }
        return;
    }
     
    int* rots = (int*)calloc(tam, sizeof(int));
    /*
     * Procura o roteador conectado ao terminal
     * comparando o ID da celula do terminal com 
     * o id unico do roteador e atribui a variavel
     * rot1/rot2 esse roteador.
     * 
     * */
    if(EnlaceRoteador(rot1, rot2, rots, tamPointer)){
        fprintf(saida, "ENVIARPACOTESDADOS %s %s: SIM\n", chave1, chave2);
    }else{
        fprintf(saida, "ENVIARPACOTESDADOS %s %s: NAO\n", chave1, chave2);
    }

    free(rots);
    
}


void ImprimeNetMap(ListaR* listaRot, ListaT* listaTer, FILE* saida){
    CelulaT* terminal = RetornaPrimeiraCelulaListaTerminal(listaTer);
    CelulaR* roteador;
    CelulaEnlaces* enlace;
    fprintf(saida, "strict graph { ");
    printf("strict graph { ");

    for(terminal; terminal != NULL; terminal = RetornaProximaCelulaTerminal(terminal)){
        roteador = RetornaPrimeiraCelulaListaRoteador(listaRot);
        fprintf(saida, "%s", RetornaNomeTerminal(RetornaTerminalLista(terminal)));
        printf("%s", RetornaNomeTerminal(RetornaTerminalLista(terminal)));

        for(roteador; roteador != NULL; roteador = RetornaProxCelulaRoteador(roteador)){
            if(RetornaIdRoteador(RetornaRoteadorLista(roteador)) == RetornaIdRot(terminal)){
                fprintf(saida, " -- %s", RetornaNomeRoteador(RetornaRoteadorLista(roteador)));
                printf(" -- %s", RetornaNomeRoteador(RetornaRoteadorLista(roteador)));
            }
        }
        fprintf(saida, ";");
        printf(";");
    }
    for(roteador = RetornaPrimeiraCelulaListaRoteador(listaRot); roteador != NULL; roteador = RetornaProxCelulaRoteador(roteador)){
        enlace = RetornaEnlace(roteador);
    
        if(!enlace){
            fprintf(saida, "%s; ", RetornaNomeRoteador(RetornaRoteadorLista(roteador)));
            printf("%s; ", RetornaNomeRoteador(RetornaRoteadorLista(roteador)));
        }
        for(enlace;enlace != NULL;enlace = RetornaProximoEnlace(enlace)){
            fprintf(saida, "%s -- %s; \n", RetornaNomeRoteador(RetornaRoteadorLista(roteador)), RetornaNomeRoteador(RetornaRoteadorLista(RetornaRoteadorCelulaEnlace(enlace))));
            printf("%s -- %s; ", RetornaNomeRoteador(RetornaRoteadorLista(roteador)), RetornaNomeRoteador(RetornaRoteadorLista(RetornaRoteadorCelulaEnlace(enlace))));
        }
    }
    fprintf(saida, " }\n");
    printf(" }\n\n");
}