#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#ifndef RUN
#define RUN

int checkCD(char * []) ;
int checkGreaterRedirect(char * , int );
int checkLesserRedirect(char * , int );
int checkPipe(char * , int ) ;
int checkSemi(char * , int ) ;
int checkKill(char * []) ;
void input();
void runstuff(char * , int ) ;



#endif
