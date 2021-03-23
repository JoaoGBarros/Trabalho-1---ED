/*
    Trabalho I - Estrutura de Dados UFES 2020/2 - Patricia Dockhorn Costa
    Alunos: Joao Gabriel de Barros Rocha e Tales Viana
    Data: 17/03/2021
    github: JoaoGBarros || Talesvf
*/



#include <stdio.h>
#include <stdlib.h>


int main(){

    FILE* arq;
    char* comando;

    arq = fopen("entrada.txt", "r");

    while(1){
        fscanf(arq, "%s", comando);

        if(!strcmp(comando, "FIM")){
            break;
        }
    }
    return 0;
}



