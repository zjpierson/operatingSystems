//--------------    dash.c    ------------//

#include "cmdArgs.h"


int main()
{
    int i;
    char input[60] = {0};
    char* cmd;
 
    //Enter command loop (Read Eval Print Loop)
    while(1)
    {
        //Print prompt and get user input
        printf("dash> ");
        fgets(input, 60, stdin);  //Note: fgets includes \n

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

        //If command does not exist; tell the user
        if(i == NUM_CMDS)
            printf("**Error: \"%s\" is not a command. Try \"help\"", input);

        printf("\n");
    }

    return 0;
}


