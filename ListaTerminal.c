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
}; //Estrutua celula, formada por um terminal, o id do roteador que esse terminal esta conectado e a prox celula

struct lista{
    CelulaT *prim;
    CelulaT *ult;
};//Estrutua lista, formada por duas celulas, uma apontando para a primeira celula da lista e a outra para a ultima



//Faz a alocacao de memoria da lista e inicia os ponteiros prim e ult
ListaT *IniciaListaT(){
    ListaT *tt;
    tt = (ListaT *)malloc(sizeof(ListaT));
    tt->prim = NULL;
    tt->ult = NULL;

    return tt;
}


//Inclui o terminal a sua respectiva lista, recebendo as informacoes dele e 
//chamando a funcao responsavel por alocar o roteador dentro da funcao
void CadastraTerminal(ListaT *lista, char* nome, int id, char* localizacao){
    CelulaT *n;

    n = (CelulaT*)malloc(sizeof(CelulaT));
    
    n->terminal = CriaTerminal(nome, id, localizacao);
    n->prox = NULL;
    n->id_rot = 0; 
    //id_rot = 0 siginifica que ele ainda esta desconectado de qualquer roteador. 
    //Os id's dos roteadores sao n >= 1

    if(lista->prim == NULL){
        lista->prim = n;
        lista->ult = n;
    }else{
        lista->ult->prox = n;
        lista->ult = n;
    }
}

//Responsavel por remover o terminal da lista
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

//Conecta um Terminal a um roteador
void ConectaTerminal(ListaT* t, ListaR* r, char* terminal, char* roteador, FILE* log){
    CelulaT* term = BuscaTerminalLista(t, terminal); 
    CelulaR* rot = BuscaRoteadorLista(r, roteador);
    //Realiza a busca utilizando a chave de qual terminal e roteador deseja conectar, caso nao seja encontrado 
    //eh informado um erro.

    if(!term){ 
        fprintf(log, "Erro: Terminal %s inexistente no NetMap\n", terminal);
    }

    if(!rot){
        fprintf(log, "Erro: Roteador %s inexistente no NetMap\n", roteador);  
    }
    if(!term || !rot){
        return;
    }

    //Se for encontrado, o id_rot da celula recebe o valor do id do roteador
    if(term != NULL && rot != NULL){
        term->id_rot = RetornaIdRoteador(RetornaRoteadorLista(rot));
    }

}

//Desonecta o terminal do roteador 
void DesconectaTerminal(ListaT*l, char *terminal, FILE* log){
    CelulaT* term = BuscaTerminalLista(l, terminal);
    if(!term){
        fprintf(log, "Erro: Terminal %s inexistente no NetMap", terminal);
        return;
    }
    term->id_rot = 0; //Roteador desconectado -> id_rot = 0
}


//Funcoes de retorno para que os dados possam ser usados em outros partes do codigo
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

//Libera a memoria ocupada pela lista.
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

//Realiza a busca por meio de uma chave, retornando NULL, caso nao encontre, 
//ou um ponteiro pra CelulaTerminal que possui a informacao desejada 
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
