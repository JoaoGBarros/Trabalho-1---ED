/*  
    main.c
    Trabalho I - Estrutura de Dados UFES 2020/2 - Patricia Dockhorn Costa
    Alunos: Joao Gabriel de Barros e Tales Viana
    Data: 17/03/2021
    github: JoaoGBarros || Talesvf
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NetMap.h"

void DesconectaTerminais(ListaR* r, ListaT* t, char* nome);

int main(){

    FILE* entrada, *saida, *log, *dot;
    char comando[20], nome[20], local[20];
    int contRot = 1, contTerm = 1;
    ListaR* RotNetMap = IniciaListaR();
    ListaT* TermNetMap = IniciaListaT();

    

    entrada = fopen("entrada.txt", "r");
    saida = fopen("saida.txt", "w");
    dot = fopen("saida.dot", "w");
    log = fopen("log.txt", "w");
    
    if(entrada == NULL){
        //Error
    }

    while(!feof(entrada)){
        fscanf(entrada, "%s", comando);
        //printf("%s", comando);
        if(!strcmp(comando, "CADASTRAROTEADOR")){
            fscanf(entrada, "%s", nome);
            fscanf(entrada, "%s", local);
            CadastraRoteador(RotNetMap, nome, contRot, local);
            contRot++;
        }

        if(!strcmp(comando, "CADASTRATERMINAL")){
            fscanf(entrada, "%s", nome);
            fscanf(entrada, "%s", local);
            CadastraTerminal(TermNetMap, nome, contTerm, local);
            contTerm++;
        }

        if(!strcmp(comando, "REMOVEROTEADOR")){
            fscanf(entrada, "%s", nome);
            DesconectaTerminais(RotNetMap, TermNetMap, nome);
            RemoveRoteador(RotNetMap, nome);
        }

        if(!strcmp(comando, "REMOVETERMINAL")){
            fscanf(entrada, "%s", nome);
            RemoveTerminal(TermNetMap, nome);
        }

        if(!strcmp(comando, "CONECTAROTEADORES")){
            fscanf(entrada, "%s", nome);
            fscanf(entrada, "%s", local);
            ConectaRoteadores(RotNetMap, nome, local);
        }

        if(!strcmp(comando, "CONECTATERMINAL")){
            fscanf(entrada, "%s", nome);
            fscanf(entrada, "%s", local);
            ConectaTerminal(TermNetMap, RotNetMap, nome, local);
        }
        
        if(!strcmp(comando, "IMPRIMENETMAP")){
            ImprimeNetMap(RotNetMap, TermNetMap, dot);
        }

        if(!strcmp(comando, "DESCONECTAROTEADORES")){
            fscanf(entrada, "%s", nome);
            fscanf(entrada, "%s", local);
            DesconectaRoteadores(RotNetMap, nome, local);
        }

        if(!strcmp(comando, "DESCONECTATERMINAL")){
            fscanf(entrada, "%s", nome);
            DesconectaTerminal(TermNetMap, nome);
        }

        if(!strcmp(comando, "FREQUENCIATERMINAL")){
            fscanf(entrada, "%s", local);
            FrequenciaTerminal(TermNetMap, local, saida);
        }

        if(!strcmp(comando, "FREQUENCIAOPERADORA")){
            fscanf(entrada, "%s", local);
            FrequenciaOperadora(RotNetMap, local, saida);
        }

        if(!strcmp(comando, "ENVIARPACOTESDADOS")){
            printf("entrou");
            fscanf(entrada, "%s", nome);
            fscanf(entrada, "%s", local);
            printf("%s", nome);
            printf("%s", local);
            EnviarPacotesDados(RotNetMap, TermNetMap, nome, local, saida);
            printf("envou\n");
        }

        if(!strcmp(comando, "FIM")){
            break;
        }
    }

    fclose(entrada);
    fclose(saida);
    fclose(dot);
    fclose(log);
    DestroiListaR(RotNetMap);
    DestroiListaT(TermNetMap);
    return 0;
}


void DesconectaTerminais(ListaR* r, ListaT* t, char* nome){
    CelulaR* rot = BuscaRoteadorLista(r, nome);
    CelulaT* ter;
    for(ter = RetornaPrimeiraCelulaListaTerminal(t);ter != NULL;ter = RetornaProximaCelulaTerminal(ter)){
        if(RetornaIdRot(ter) == RetornaIdRoteador(RetornaRoteadorLista(rot))){
            DesconectaTerminal(t, RetornaNomeTerminal(RetornaTerminalLista(ter)));
        }
    }
}
