//--------------    dash.c    ------------//

#include "cmdArgs.h"


int main()
{
    int i;
    char input[100] = {0};
    char* cmd;
    int args = 0;
 
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
            for(args = 0; strtok(NULL, " "); args++)
            {
            
            }
        }

        printf("\n");
    }

    return 0;
}


