#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void input(){
  printf("Enter command: ");
  char *a = calloc(1,255); 
  fgets(a, 255, stdin);
  a = strsep(&a, "\n"); //Remove newline since "the newline is retained."
  //printf("%s\n", a);
  
  char *s;
  char *ret[20];
  int i = 0;
  
  while(a){
    s = strsep(&a, " ");
    //printf("%s\n", s);
    ret[i] = s;
    //printf("%s\n",ret[i]);
    i++;
  }
  ret[i] = 0;
  
  free(a);

  execvp(ret[0], ret);
  
}


int main(){

  while (1){

      input();
      
    }
  
  return 0;}

