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

/*
*Faz uma busca na lista de terminais e compara seu atributo localizacao com a chave "loc" dada, 
*para cada terminal que possua a igualdade de strings eh somado +1 ao contador(nTerm). 
*Logo apos verificar a lista toda, o valor do contador eh impresso no arquivo
*/
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

/*
*Faz uma busca na lista de roteadores e compara seu atributo operadora com a chave "op" dada, 
*para cada roteador que possua a igualdade de strings eh somado +1 ao contador(nRot). 
*Logo apos verificar a lista toda, o valor do contador eh impresso no arquivo
*/

void FrequenciaOperadora(ListaR* lista, char* op, FILE* saida){
    CelulaR* p;
    int nRot = 0;
    for(p = RetornaPrimeiraCelulaListaRoteador(lista);p != NULL;p = RetornaProxCelulaRoteador(p)){
        if(!strcmp(RetornaOperadoraRoteador(RetornaRoteadorLista(p)), op)){
            nRot++;
        }
    }
    fprintf(saida, "FREQUENCIAOPERADORA %s: %d\n", op, nRot);
}

//função recursiva criada para verificar se há ligação de enlaces entre dois roteadores
int EnlaceRoteador(CelulaR* rot1, CelulaR* rot2, int* rots, int* tam){
    CelulaEnlaces* enlace;
    int i = 0;
    int jaFoi = 0;
    enlace = RetornaEnlace(rot1);
    //este for passa uma vez pela lista de enlaces de rot1 e o if verifica se o rot2 esta presente nela
    for(enlace = RetornaEnlace(rot1);enlace != NULL;enlace = RetornaProximoEnlace(enlace)) {
        if (RetornaRoteadorCelulaEnlace(enlace) == rot2) {
            return 1;
        }
    }
    //caso rot2 nao esteja diretamente ligado ao rot1, esse for é ativado e ele percorre novamente a lista de enlaces do rot1
    for(enlace = RetornaEnlace(rot1);enlace != NULL;enlace = RetornaProximoEnlace(enlace)){
        jaFoi = 0;
        //este for percorre o vetor de inteiros com os ids dos roteadores ja verificados para ver se o id do roteador em questao esta presente nele
        for(i = 0; i < *tam ;i++){
            if(RetornaIdRoteador(RetornaRoteadorLista(RetornaRoteadorCelulaEnlace(enlace))) == rots[i]){
                jaFoi++;//caso esteja presente, a variavel jaFoi passa a ter o valor 1 e o loop é quebrado
                break;
            }
        }
        //caso o roteador nao tenha sido verificado, ele entra neste bloco
        if(jaFoi == 0){
            *tam = *tam + 1;//o número de roteadores verificados aumenta em 1
            rots[*tam - 1] = RetornaIdRoteador(RetornaRoteadorLista(RetornaRoteadorCelulaEnlace(enlace)));//a proxíma célula do vetor é preenchida com o id do roteador que será verificado em seguida
            //este if chama recursivamente a função para que o roteador seja verificado
            if(EnlaceRoteador(RetornaRoteadorCelulaEnlace(enlace), rot2, rots, tam)){ 
                return 1;
            }
            
        }
    
    }
    
    
    
    return 0;

}

//Funcao incilizadora do processo de verificar se existe a possibilidade do envio de dados entre terminais
void EnviarPacotesDados(ListaR* r, ListaT* t, char* chave1, char* chave2, int tam, FILE* saida, FILE* log){
    
    /*
    *Eh feita uma busca pelos terminais utilizando suas respectivas chaves, caso ambos terminais existam
    *Eh visto se eles estao conectados a algum roteador, caso a afirmacao seja verdadeira, eh feita uma busca para descobrir 
    *qual roteador esta conectado aos terminais e atribuindo esse ponteiro às celuals rot1 e rot2. 
    *Para execessões como: terminais nao conectados a algum roteador e terminais nao encontrados, 
    *eh impressa uma mensagem de erro
    */
   
    CelulaT* ter1 = BuscaTerminalLista(t, chave1);
    CelulaT* ter2 = BuscaTerminalLista(t, chave2);
    CelulaR* rot1 = NULL, *rot2 = NULL;
    CelulaR* p;

    int cont = 1;
    int* contPointer = &cont;
    if(ter1 && ter2){
        if(!RetornaIdRot(ter1) || !RetornaIdRot(ter2)){
            fprintf(saida, "ENVIAPACOTEDADOS %s %s: NAO\n", chave1, chave2);
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
     
    int* rots = (int*)calloc(tam, sizeof(int)); //Aloca o vetor rots de tamanho igual ao numero de roteadores conectados ao NetMap
    
    rots[0] = RetornaIdRoteador(RetornaRoteadorLista(rot1));


    if(EnlaceRoteador(rot1, rot2, rots, contPointer)){
        fprintf(saida, "ENVIAPACOTEDADOS %s %s: SIM\n", chave1, chave2);
    }else{
        fprintf(saida, "ENVIAPACOTEDADOS %s %s: NAO\n", chave1, chave2);
    }
    free(rots);
}

//Funcao responsavel pela impressao do NetMap no .dot
void ImprimeNetMap(ListaR* listaRot, ListaT* listaTer, FILE* saida){
    CelulaT* terminal = RetornaPrimeiraCelulaListaTerminal(listaTer);
    CelulaR* roteador;
    CelulaEnlaces* enlace;
    fprintf(saida, "strict graph {\n");

    /*
    *Percorre os terminais, imprimindo primeiro seu nome, depois adentra na lista de roteadores 
    *e verfica se esta conectado a algum utilizando a id_rot e comparando com a id do roteador.
    *Caso esteja, ele imprime o nome do roteador conectado.
    */

    for(terminal; terminal != NULL; terminal = RetornaProximaCelulaTerminal(terminal)){
        roteador = RetornaPrimeiraCelulaListaRoteador(listaRot);
        fprintf(saida, "    %s", RetornaNomeTerminal(RetornaTerminalLista(terminal)));

        for(roteador; roteador != NULL; roteador = RetornaProxCelulaRoteador(roteador)){
            if(RetornaIdRoteador(RetornaRoteadorLista(roteador)) == RetornaIdRot(terminal)){
                fprintf(saida, " -- %s", RetornaNomeRoteador(RetornaRoteadorLista(roteador)));
            }
        }
        fprintf(saida, ";\n");
    }

    /*
    *Adentra na lista de roteadores e verifica sua lista de enlaces, caso nao possua eh apenas impresso seu nome,
    *caso contrario, imprime cada conexao direta que possui.
    */

    for(roteador = RetornaPrimeiraCelulaListaRoteador(listaRot); roteador != NULL; roteador = RetornaProxCelulaRoteador(roteador)){
        enlace = RetornaEnlace(roteador);
    
        if(!enlace){
            fprintf(saida, "    %s;", RetornaNomeRoteador(RetornaRoteadorLista(roteador)));
        }
        for(enlace;enlace != NULL;enlace = RetornaProximoEnlace(enlace)){
            fprintf(saida, "    %s -- %s;\n", RetornaNomeRoteador(RetornaRoteadorLista(roteador)), RetornaNomeRoteador(RetornaRoteadorLista(RetornaRoteadorCelulaEnlace(enlace))));
        }
    }
    fprintf(saida, "}\n");

}