#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


void breakUp(char * a, char * ret[]){
  a = strsep(&a, "\n"); //Remove newline since "the newline is retained."
  //printf("%s\n", a);

  char *s;
 
  int i = 0;

  while(a){
    s = strsep(&a, " ");
    //printf("%s\n", s);
    ret[i] = s;
    //printf("%s\n",ret[i]);
    i++;
  }
  ret[i] = 0;
}
  

 int runCD(char * s, char * full[]){ 
  if (s[0] == 'c' && s[1] == 'd' && s[2] == ' '){ 
    
     execvp(full[0], full);  
     return 1; 
   } 
   else{ 
     return 0;}
 }


  void input(){
    pid_t past = getpid();
    int status;
  
    fork();
    wait(&status);
    //printf("PPid: %d, Pid: %d\n", getppid(), getpid());
    printf("Enter command: ");
    char *a = calloc(1,255);
    fgets(a, 255, stdin);
    char* ret[20];
    breakUp(a, ret);
    free(a);
  
    if (getppid() == past) {
      execvp(ret[0], ret); 
    }
    if (getpid() == past){
      runCD(a, ret);
    }
  }


int main(){
  int i = 0;
  for (; i < 10; i++) {
    input();
  }
  



  return 0;}
