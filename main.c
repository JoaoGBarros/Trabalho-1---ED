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

void DesconectaTerminais(ListaR* r, ListaT* t, char* nome, FILE* log);

int main(){

    FILE* entrada, *saida, *log, *dot;
    char comando[20], nome[20], local[20];
    int contRot = 1, contTerm = 1, nRots = 0;
    ListaR* RotNetMap = IniciaListaR();
    ListaT* TermNetMap = IniciaListaT();

    

    entrada = fopen("entrada.txt", "r");
    saida = fopen("saida.txt", "w");
    dot = fopen("saida.dot", "w");
    log = fopen("log.txt", "w");
    
    if(entrada == NULL){ //Caso arquivo esteja vazio
        fprintf(log, "ERRO: ENTRADA NAO ENCONTRADA");
    }

    while(!feof(entrada)){ //Enquanto o arquivo nao tiver acabado

        fscanf(entrada, "%s", comando);//Le a primeira string, resposnavel pelo comando
    
        //Apos entrar no if 

        if(!strcmp(comando, "CADASTRAROTEADOR")){
            fscanf(entrada, "%s", nome);
            fscanf(entrada, "%s", local);
            CadastraRoteador(RotNetMap, nome, contRot, local);
            nRots++; //Número de roteadores cadastrados
            contRot++; //Id do roteador
        }

        if(!strcmp(comando, "CADASTRATERMINAL")){
            fscanf(entrada, "%s", nome);
            fscanf(entrada, "%s", local);
            CadastraTerminal(TermNetMap, nome, contTerm, local);
            contTerm++; // Id do terminal
        }

        if(!strcmp(comando, "REMOVEROTEADOR")){
            fscanf(entrada, "%s", nome);
            //Antes de remover o roteador do NetMap, desconectamos o roteador ligado a ele
            DesconectaTerminais(RotNetMap, TermNetMap, nome, log); 
            RemoveRoteador(RotNetMap, nome, log);
            nRots--; // Número de roteadores cadastrados 
        }

        if(!strcmp(comando, "REMOVETERMINAL")){
            fscanf(entrada, "%s", nome);
            RemoveTerminal(TermNetMap, nome, log);
        }

        if(!strcmp(comando, "CONECTAROTEADORES")){
            fscanf(entrada, "%s", nome);
            fscanf(entrada, "%s", local);
            ConectaRoteadores(RotNetMap, nome, local, log);
        }

        if(!strcmp(comando, "CONECTATERMINAL")){
            fscanf(entrada, "%s", nome);
            fscanf(entrada, "%s", local);
            ConectaTerminal(TermNetMap, RotNetMap, nome, local, log);
        }
        
        if(!strcmp(comando, "IMPRIMENETMAP")){
            ImprimeNetMap(RotNetMap, TermNetMap, dot);
        }

        if(!strcmp(comando, "DESCONECTAROTEADORES")){
            fscanf(entrada, "%s", nome);
            fscanf(entrada, "%s", local);
            DesconectaRoteadores(RotNetMap, nome, local, log);
        }

        if(!strcmp(comando, "DESCONECTATERMINAL")){
            fscanf(entrada, "%s", nome);
            DesconectaTerminal(TermNetMap, nome, log);
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
            fscanf(entrada, "%s", nome);
            fscanf(entrada, "%s", local);
            EnviarPacotesDados(RotNetMap, TermNetMap, nome, local, nRots, saida, log);
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

//função criada para desconectar todos os terminais que estejam conectados ao roteador que será excluído
void DesconectaTerminais(ListaR* r, ListaT* t, char* nome, FILE* log){
    CelulaR* rot = BuscaRoteadorLista(r, nome);//Busca o roteador na lista principal do NetMap a partir de seu nome
    if(!rot){//caso o roteador nao seja encontrado, ela apenas "ignora" a chamada
        return;
    }
    CelulaT* ter;
    for(ter = RetornaPrimeiraCelulaListaTerminal(t);ter != NULL;ter = RetornaProximaCelulaTerminal(ter)){//este for junto do if passa por todos os terminais e verifica se o id_rot deles é igual ao id do roteador a ser deletado
        if(RetornaIdRot(ter) == RetornaIdRoteador(RetornaRoteadorLista(rot))){
            DesconectaTerminal(t, RetornaNomeTerminal(RetornaTerminalLista(ter)), log);//caso seja, ele os desconecta.
        }
    }
}
