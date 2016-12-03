#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

void runstuff(char *, int);

char * username = "darthbeep";
char * otherusername = "shpeters";
char * path = "/";
char * backup = "";
char * locations[255];
int locnum = 0;

/*======== int checkCD() ==========
  Inputs:  char * com[]
  Returns: 1 if first slot contains "cd" and the code is run. Else, 0
        Checks to see whether or not the user input uses the
	"cd" command by looking for "cd" in com[]. If so, changes the location
	based on the input in com[]. Returns 1 if sucessful.
	Returns 0 if not.
	====================*/


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
    return 1;
  }
  return 0;
}

/*======== int checkGreaterRedirect() ==========
  Inputs:  char * input
           int past
	   Returns: 1 if first slot contains ">" and the code is run. Else, 0
        Checks to see whether or not the user input uses
	">" by looking for "<" in com[]. If so, directs the stdout of the command (on left)
	into the file given (on right). Returns 1 if sucessful.
	Returns 0 if not.
	====================*/

int checkGreaterRedirect(char * input, int past){
  if (strchr(input, '>') == NULL) {
    return 0;
  }
  else {
    char *s;
    char *coms[20];
    int end = 0;
    while(input){
      s = strsep(&input, ">");
      coms[end] = s;
      end++;
    }
    int k = 0;
    while (coms[1][k] == ' ') {
      coms[1]++;
    }
    if (coms[0][strlen(coms[0])-1]==' ') {
      coms[0][strlen(coms[0])-1] = 0;
    }

    FILE *fp;
    fp = fopen(coms[1], "w");
    FILE* p = popen(coms[0], "r");
    if (!p) return 1;

    char buff[1024];
    while (fgets(buff, sizeof(buff), p)) {
      printf("");
      fprintf(fp, "%s", buff);
    }
    fclose(fp);
    pclose(p);

    return 1;
  }
}

/*int checkLesserRedirect(char * input, int path) {
  if (strchr(input)) {
    return 0;
  }
  return 1;
  }*/
/*======== int checkLesserRedirect() ==========
  Inputs:  char * input
           int past
	   Returns: 1 if first slot contains "<" and the code is run. Else, 0
        Checks to see whether or not the user input uses
	"<" by looking for "<" in com[]. If so, directs the file (right) as the stdin
	for the command given (left). Returns 1 if sucessful.
	Returns 0 if not.
	====================*/

int checkLesserRedirect(char * input, int past){
  if (strchr(input, '<') == NULL) {
    return 0;
  }
  else {
    char *s;
    char *coms[20];
    int end = 0;
    while(input){
      s = strsep(&input, "<");
      coms[end] = s;
      end++;
    }

    FILE *f = fopen(coms[1], "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, f);
    string[fsize] = 0;
    printf("%s\n",string);
    fclose(f);



    return 1;
  }
}


/*======== int checkSemi() ==========
  Inputs:  char * input
           int past
	   Returns: 1 if no ';' is present in input. Else, returns 0
        If ';' are present, parses input at instances of ';'. It runs all parsed
	components and returns 1;
	If none are present, returns 0.
	====================*/

int checkPipe(char * input, int past) {
  if (strchr(input, '|') == NULL) {
    return 0;
  }
  char *s;
  char *coms[20];
  int end = 0;

  while(input){
    s = strsep(&input, "|");
    coms[end] = s;
    end++;
  }
  if (coms[0][strlen(coms[0])-1] == ' ') {
    coms[0][strlen(coms[0])-1] = 0;
  }
  if (coms[1][0] == ' ') {
    coms[1]++;
  }
  fopen("verytemporaryfile", "w");
  char * replace = "> verytemporaryfile";
  char * new = (char *) malloc(sizeof(char));
  strcat(new, coms[0]);
  strcat(new, replace);
  checkGreaterRedirect(new, past);
  char * othernew= (char *) malloc(sizeof(coms[1]) + 20);
  strcat(othernew, coms[1]);
  strcat(othernew, " verytemporaryfile");
  runstuff(othernew, past);
  execlp("rm", "rm", "verytemporaryfile");
  return 1;
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
      coms[end] = s;
      end++;
    }
    coms[end] = 0;
    for (size_t j = 0; j < end; j++) {
      int k = 0;
      while (coms[j][k] == ' ') {
        coms[j]++;
      }

    }
    for (size_t l = 0; l < end; l++) {
      runstuff(coms[l], past);
    }
  }
  return 1;
}

/*======== int checkKill() ==========
  Inputs:  char * com[]
  Returns: 1 if exit is present in com[0] and the code is run. Else, 0.
        Sees if com[0] is "exit." If it is, it kills the current process and returns 1.
	Else, returns 0.
	====================*/

int checkKill(char * com[]) {
  if (strcmp(com[0], "exit") == 0) {
    kill(getpid(),9);
    return 1;}
  return 0;}

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
