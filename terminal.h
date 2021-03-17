#ifndef TERMINAL_H
#define TERMINAL_H

typedef struct terminal Terminal;

Terminal* CriaTerminal(char* nome, int id, char* localizacao);

char* retornaNomeTerminal(Terminal* terminal);

int retornaIdTerminal(Terminal *terminal);

char* retornaLocalizacaoTerminal(Terminal* terminal);

void DestroiTerminal(Terminal *terminal);

#endif