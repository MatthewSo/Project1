
#include <stdio.h>
#include <stdlib.h>
#include "execute.h"
#ifndef CHECK
#define CHECK

int checkCD(char * com[]);
int checkGreaterRedirect(char * input, int past);
int checkLesserRedirect(char * input, int past);
int checkPipe(char * input, int past);
int checkSemi(char * input, int past);
int checkKill(char * com[]);

#endif
