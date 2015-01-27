#include "dash.h"


int main()
{
    int i;
    char* input;
    char* cmd;

    printf("\n");
    //Enter command loop (Read Eval Print Loop)
    while(1)
    {
        printf("dash> ");
        scanf("%s", input);
        
        //Get command option from user
        cmd = strtok(input, " ");

        for(i = 0; i < NUM_CMDS; i++)
        {
            if(!strcmp(cmd, commands[i]))
            {
                //Call appropriate function
                hello(input);
                printf("%s is a command!\n", cmd);
                break;
            }
        }
    }

    return 0;
}


