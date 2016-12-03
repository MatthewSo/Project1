#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "check.h"


void runstuff(char *, int);

char * username = "darthbeep";
char * otherusername = "shpeters";
char * path = "/";
char * backup = "";
char * locations[255];
int locnum = 0;



	/*======== void input() ==========
	Inputs:
	Returns: void

        Calls for command line input from user. Runs
	commands given like a terminal shell. Creates
	child processes to run commands (not including
	exit and cd) and prints the results.
	====================*/



  void input(){
    pid_t past = getpid();
    int status;


    char location[1024];
    getcwd(location, sizeof(location));
    printf("%s:%s %s$ ", username, location, otherusername);

    char *a = calloc(1,255);
    fgets(a, 255, stdin);
    a = strsep(&a, "\n"); //Remove newline since "the newline is retained."
    int pipe = checkPipe(a, past);
    int semi = 0;
    int redg = 0;
    if (pipe == 0) { semi = checkSemi(a, past);}
    if (pipe == 0) { redg = checkGreaterRedirect(a,past);}
    if (semi == 0 && redg == 0 && pipe == 0) {
    char *s;
    char *ret[20];
    int i = 0;
    runstuff(a, past);
    }
  }

        /*======== void  runstuff() ==========
	Inputs:  char * a
	int past

	Returns: void

        Parses char * a at occurences of " " and puts the
	components into char * ret[20]. After forking, will
	run the components of char * ret[20] in the process
	whose parent PID is past.
	====================*/


void runstuff(char * a, int past) {
  char * ret[20];
  char * s;
  int i = 0;
  int status;
  int add = 0;
  while(a){
    s = strsep(&a, " ");
    if (strcmp(s, "<")!=0) {
      ret[i + add] = s;
    }
    else {
      add--;
    }
    i++;
  }
  ret[i + add] = 0;

  free(a);

  if (checkKill(ret)){
    return;}
  int c = checkCD(ret);

  if (c == 0) {
    fork();
    wait(&status);

    if (getppid() == past) {

      execvp(ret[0], ret);
    }
  }
}

int main(){

locations[0] = "~";
for (size_t i = 0; i < 100; i++) {
  input();
}




  return 0;}
