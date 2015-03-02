/******************************    dash.c    **********************************
 * Date: 2/27/2015
 *
 * Author:
 *      Zachary Pierson
 *
 * Insittution:
 *      South Dakota School of Mines and Technology
 *
 * Course:
 *      CSC 456 Operating Systems
 *
 * Proffessor:
 *      Dr. Karlson
 *
 * Description:
 *      Dash is a program that is very similar to the Bash shell. A prompt is
 * displayed and takes user input. Then the appropriate function is called 
 * using system system functions. dash handles errors gracefully by providing
 * the user with error messages. Any signal, except for SIGSTOP and SIGKILL
 * will be caught and a message of what type of signal will be returned.
 *
 *      This is the second program in OS that demonstrates multiple processes
 * using the fork() call. It also goes over file descriptors to help with 
 * pipes and redirected input/output.
 *
 *
 * ***************************************************************************/

#include "cmdArgs.h"


/******************************************************************************
 *  Function:       main
 *
 *  Description:
 *      As the starting point of dash, the main function takes 
 *  care of the command prompt and tokenizing the users input. The first loop
 *  goes though all the signals and sets up the sig_hangler function with them
 *  so that they can be caught. In the parent process. A check for pipes and
 *  redirects in the user input is done next so that they may take effect. 
 *  Finally, a child process executes the proper command while the parent 
 *  waits for it's child. Finally a status is printed after a comand has been
 *  called.
 *
 *  Return 0:   program exited normally
 *
 * ***************************************************************************/
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

    //catch and handle all signals
    for(i = 1; i < 32; i++)
        if( signal(i, sig_handler) == SIG_ERR)
            printf("can't catch signal %d\n", i);
    
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

        //This was provided by Dr. Karlson
        printf("\nChild process %d exited with status %d\n",
                waitpid, (status >> 8)); 

        //print process status information
        proc_status();

        printf("\n");
    }

    return 0;
}


