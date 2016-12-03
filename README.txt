Getting Out of Our Shell!
by Matt and Shaina, The Dynamic Duo

Features:
	Forks and executes commands.
	Runs multiple commands on one line divided by ';.
	Tells user current folder
	Uses <,> to redirect.
	Uses | to pipe.

Attempted:
	We tried to get the following to work:
	Getting name of user

Bugs:
	Putting two ;'s next to each other will lead to errors.
	Incorrect commands will lead to additional forked processes
	that will need to be exited.
	Redirecting to a file that does not exist occasionally
		    does not work.
		    	 
			 
Files & Function Headers:
int checkCD(char * []) ;
int checkGreaterRedirect(char * , int );
int checkLesserRedirect(char * , int );
int checkPipe(char * , int ) ;
int checkSemi(char * , int ) ;
int checkKill(char * []) ;
void input();
void runstuff(char * , int ) ;
execute.c
	Handles all line parsing fucntions
	
        /*======== int checkCD() ==========
	Inputs:  char * com[]
        	   
		   Returns: 1 if first slot contains "cd" and the code is run. Else, 0

        Checks to see whether or not the user input uses the 
	"cd" command by looking for "cd" in com[]. If so, changes the location
	based on the input in com[]. Returns 1 if sucessful. 
	Returns 0 if not.
	====================*/

	
        /*======== int checkGreaterRedirect() ==========
	Inputs:  char * input
	         int past
		 Returns: 1 if first slot contains ">" and the code is run. Else, 0
        Checks to see whether or not the user input uses
	">" by looking for "<" in com[]. If so, directs the stdout of the command (on left)
	into the file given (on right). Returns 1 if sucessful.
	Returns 0 if not.
	====================*/

	        /*======== int checkLesserRedirect() ==========
		Inputs:  char * input
		         int past
			 Returns: 1 if first slot contains "<" and the code is run. Else, 0
        Checks to see whether or not the user input uses
	"<" by looking for "<" in com[]. If so, directs the file (right) as the stdin
	for the command given (left). Returns 1 if sucessful.
	Returns 0 if not.
	====================*/

                

        /*======== int checkPipe() ==========
      		  Inputs:  char * input
                         int past

                Parses input at	|. Then	uses the return	of the first command
		       as the stdin of	the second command.

        ====================*/

		/*======== int checkSemi() ==========
		Inputs:  char * input
		         int past

			 Returns: 1 if no ';' is present in input. Else, returns 0

        If ';' are present, parses input at instances of ';'. It runs all parsed
	components and returns 1;
	If none are present, returns 0.
	
	====================*/

		/*======== int checkKill() ==========
		Inputs:  char * com[]
		Returns: 1 if exit is present in com[0] and the code is run. Else, 0.

        Sees if com[0] is "exit." If it is, it kills the current process and returns 1.
	Else, returns 0.
	====================*/


	/*======== void input() ==========
	Inputs:  
	Returns: void

        Calls for command line input from user. Runs
	commands given like a terminal shell. Creates
	child processes to run commands (not including
	exit and cd) and prints the results.
	====================*/

        /*======== void  runstuff() ==========
	Inputs:  char * a
	int past
              
	      Returns: void

        Parses char * a at occurences of " " and puts the 
	components into char * ret[20]. After forking, will 
	run the components of char * ret[20] in the process
	whose parent PID is past.
	====================*/
