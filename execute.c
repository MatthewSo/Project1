#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void runstuff(char *, int);

char * username = "darthbeep";
char * otherusername = "shpeters";
char * path = "/";
char * backup = "";
char * locations[255];
int locnum = 0;

int checkCD(char * com[]) {
  if (strcmp(com[0], "cd") == 0) {
    if (com[1] == NULL) {
      path = backup;
      locations[0] = "~";
      locnum = 0;
      chdir(getenv("HOME"));
    }
    else {
      path = (char *) malloc(sizeof(char) + sizeof(com[1]) + 1);
      strcat(path, com[1]);
      strcat(path, "/");
      if (strcmp(com[1], "..") == 0) {
        locnum--;
      }
      else {
         locnum++;
         locations[locnum] = com[1];
       }
       int chd = chdir(path);
       if (chd == -1) {
         locnum--;
       }
     }
     //chdir(path);
     return 1;
   }
   return 0;
 }

int checkSemi(char * input, int past) {
  if (strchr(input, ';') == NULL) {
    return 0;
  }
  else {
    char *s;
    char *coms[20];
    int end = 0;

    while(input){
      s = strsep(&input, ";");
      //printf("%s\n", s);
      coms[end] = s;
      //printf("%s\n",ret[i]);
      end++;
    }
    coms[end] = 0;
    for (size_t j = 0; j < end; j++) {
      //printf("%s\n", coms[j]);
      int k = 0;
      while (coms[j][k] == ' ') {
        coms[j]++;
        //k++;
      }

      //printf("%s\n", coms[j]);
    }
    for (size_t l = 0; l < end; l++) {
        runstuff(coms[l], past);
      }
  }
}

 int checkKill(char * com[]) {
   if (strcmp(com[0], "exit") == 0) {
    kill(getpid(),9);
    return 1;}
  return 0;}

void input(){
  pid_t past = getpid();
  int status;



  printf("%s:%s %s$ ", username, locations[locnum], otherusername);
  char *a = calloc(1,255);
  fgets(a, 255, stdin);
  a = strsep(&a, "\n"); //Remove newline since "the newline is retained."
  //printf("%s\n", a);
  int semi = checkSemi(a, past);
  if (semi == 0) {
  char *s;
  char *ret[20];
  int i = 0;
  runstuff(a, past);
  /*while(a){
    s = strsep(&a, " ");
    //printf("%s\n", s);
    ret[i] = s;
    //printf("%s\n",ret[i]);
    i++;
  }
  ret[i] = 0;

  free(a);
  if (checkKill(ret)){
    return;}
  int c = checkCD(ret);

  if (c == 0) {
    fork();
    wait(&status);
    //printf("PPid: %d, Pid: %d\n", getppid(), getpid());

    if (getppid() == past) {
      //printf("%d\n",c);

      execvp(ret[0], ret);
    }
  }*/
  }
}

void runstuff(char * a, int past) {
  char * ret[20];
  char * s;
  int i = 0;
  int status;
  while(a){
    s = strsep(&a, " ");
    //printf("%s\n", s);
    ret[i] = s;
    //printf("%s\n",ret[i]);
    i++;
  }
  ret[i] = 0;

  free(a);
  if (checkKill(ret)){
    return;}
  int c = checkCD(ret);

  if (c == 0) {
    fork();
    wait(&status);
    //printf("PPid: %d, Pid: %d\n", getppid(), getpid());

    if (getppid() == past) {
      //printf("%d\n",c);

      execvp(ret[0], ret);
    }
  }
}

int main(){
  /*uid_t uid=geteuid();
  struct passwd *pw = getpwuid(uid);
  printf("%s\n", pw->pw_name);
  printf("%s\n", uid);*/

locations[0] = "~";
for (size_t i = 0; i < 100; i++) {
  //printf("%d\n", i);
  input();
}




  return 0;}
