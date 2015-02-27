//--------------    dash.c    ------------//

#include "cmdArgs.h"


int main()
{
    char input[100] = {0};
    char* cmd;
    char* ptr;
    char* args[10];
    int numArgs = 0;
    int i;
    int childpid;
    int waitpid;
    int status;
 
    //Enter command loop (Read Eval Print Loop)
    while(1)
    {
        //Print prompt and get user input
        printf("dash> ");
        fgets(input, 100, stdin);  //Note: fgets includes \n

        //If empty string, print prompt again
        if( !strcmp(input, "\n") )
            continue;

        //tokenize the input
        numArgs = tokenize(input, args);

        //if no user input, then continue the prompt
        if( numArgs == -1)
            continue;

        //if a pipe or redirect is required, do
        //computation and continue to prompt
        if(!redirect_pipe(args))
            continue;

        //special case cd command to actually take affect
        if(!strcmp(args[0], "cd"))
        {
            cd(args);
            continue;
        }

        //fork a new process
        childpid = fork();

        //child process should call the execvp command
        if( childpid == 0 )
        {
            call(args);
            perror("Exec failed");
            exit(2);
        }

        //wait for child process to finish
        waitpid = wait(&status);

        //exit command was called
        if( (status>>8) == (unsigned char)-1 )
            exit(0);

        printf("\nChild process %d exited with status %d\n",
                waitpid, (status >> 8)); 

        //print process status information
        proc_status();

        printf("\n");
    }

    return 0;
}


