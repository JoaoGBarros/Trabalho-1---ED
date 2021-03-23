#ifndef TERMINAL_H
#define TERMINAL_H

typedef struct terminal Terminal;

Terminal* CriaTerminal(char* nome, int id, char* localizacao);

char* RetornaNomeTerminal(Terminal* terminal);

int RetornaIdTerminal(Terminal *terminal);

char* RetornaLocalizacaoTerminal(Terminal* terminal);

void DestroiTerminal(Terminal *terminal);

#endif