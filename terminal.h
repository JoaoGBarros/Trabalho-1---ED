/*
    terminal.h
    Trabalho I - Estrutura de Dados UFES 2020/2 - Patricia Dockhorn Costa
    Alunos: Joao Gabriel de Barros e Tales Viana
    Data: 17/03/2021
    github: JoaoGBarros || Talesvf
*/




#ifndef TERMINAL_H
#define TERMINAL_H

typedef struct terminal Terminal;

Terminal* CriaTerminal(char* nome, int id, char* localizacao);

char* RetornaNomeTerminal(Terminal* terminal);

int RetornaIdTerminal(Terminal *terminal);

char* RetornaLocalizacaoTerminal(Terminal* terminal);

void DestroiTerminal(Terminal *terminal);

#endif