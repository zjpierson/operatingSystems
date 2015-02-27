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

        //Extract command from user
        //fgets includes \n character so we need to make it a delimiter
        cmd = strtok(input, " \n\t");
        if( cmd == NULL )
            continue;

        //Loop though and call the function that was typed in.
        for(i = 0; i < NUM_CMDS; i++)
        {
            if(!strcmp(cmd, commands[i]))
            {
                //Store the next command in cmd
                cmd = strtok(NULL, "\n");
                
                //Call appropriate function
                (*func[i]) (cmd);
                break;
            }
        }


        //If not a recognized command, pass arguments to execvp()
        if(i == NUM_CMDS)
        {
            //store all arguments from the command line into args
            while( cmd != NULL )
            {
                args[numArgs] = cmd;
                cmd = strtok(NULL, " \n\t");
                numArgs++;
            }

            args[numArgs] = NULL;

            printf("\ninput: %s\n", input);
//            ptr = strchr()

//            printf("the arguments are: \n");
//            for( i = 0; i < numArgs; i++ )
//                printf("%s ", args[i]);

            //fork a new process
            childpid = fork();

            //child process should call the execvp command
            if( childpid == 0 )
            {
                execvp(args[0], args);
                perror("Exec failed");
                exit(2);
            }

            //wait for child process to finish
            waitpid = wait(&status);
            printf("\nChild process %d exited with status %d\n",
                    waitpid, (status >> 8)); 

            //print process status information
            proc_status();

            //reset numArgs
            numArgs = 0;
        }

        printf("\n");
    }

    return 0;
}


