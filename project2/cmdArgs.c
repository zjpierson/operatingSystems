/******************************    cmdArgs.c    *********************************/

#include "cmdArgs.h"


void (*func[NUM_CMDS]) (char* args[]) = {quit, quit, cmdnm, pid, systat, help,
    cd, send_signal};
const char commands[NUM_CMDS][LEN_CMD] = 
{
    "quit", "exit", "cmdnm", "pid", "systat", "help",
    "cd", "signal"
};

/******************************************************************************
 *  Function:       quit
 *
 *  Description:
 *      exits the current process with status -1
 *
 *  Param[in]:  args - Not used
 *
 * ***************************************************************************/
void quit(char* args[])
{
    printf("Now exiting...\n");
    exit(-1);
}


/******************************************************************************
 *  Function:       cmdnm
 *
 *  Description:
 *      Finds all the cmd names of the processes using the proc file system
 * if no arguments specifyed. if a process id is provided, find all cmd 
 * names of the processes that match any substring.
 * 
 *  Param[in]:  args - list of tokenized arguments
 *
 * ***************************************************************************/
void cmdnm(char* args[])
{
    char path[50] = {"/proc/"};
    char cmdname[50];
    FILE *fp = NULL; 

    if(args[1] == NULL)
    {
        printf("Please specify pid. Here is a list of all cmd names:\n");
        display_cmdNames();
        return;
    }

    //add pid to the file path: "/proc/<pid>"
    strcat(path, args[1]);

    //add the comm file to the path:"/proc/<pid>"
    strcat(path, "/comm");

    //open the file
    fp = fopen(path, "r");
    if( fp == NULL )
    {
        printf("*Error: invalid <pid>");
        return;
    }

    //the command name is the first thing inside the comm file
    fscanf(fp, "%s", cmdname);
    //print the command name that belongs to <pid>
    printf("%s", cmdname);

    fclose(fp);
}

/******************************************************************************
 *  Function:       dispaly_cmdNames
 *
 *  Description:
 *      Finds all sub directories using dirent.h. Credit should be given to:
 * http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
 *
 *  Param[in]:  args - list of tokenized arguments
 *
 * ***************************************************************************/
void display_cmdNames()
{
    DIR * dir;
    int count = 1;
    char path[50] = {"/proc/"};
    char cmdname[50];
    char file[50];
    char *pid = NULL;
    FILE *fp = NULL; 
    struct dirent *ent;

    if( (dir = opendir("/proc")) == NULL )
    {
        printf("**Error: could not open /proc directory");
        return;
    }

    //print all command names
    while( (ent = readdir(dir)) != NULL )
    {
        strcpy(path, "/proc/");
        strcpy(file, ent->d_name);

        //if file is not a pid, continue
        if(strspn(file, "1234567890") != strlen(file))
            continue;

        //create path to /proc/<pid>/comm
        strcat(path, file);
        strcat(path, "/comm");

        //open /proc/<pid>/comm
        fp = fopen(path, "r");
        if( fp == NULL )
        {
            printf("*Error: invalid <pid>");
            return;
        }

        //the command name is the first thing inside the comm file
        fscanf(fp, "%s", cmdname);

        printf("%-20s", cmdname);
        fclose(fp);

        if( (count % 5) == 0 )
            printf("\n");

        count++;
    }

    closedir(dir);
}

/******************************************************************************
 *  Function:       pid
 *
 *  Description:
 *      Loop though all pid directories and return pid numbers that match any
 * substring of the given command. If no argument is specigyed, then all 
 * process id's will be dispalyed using file names in the proc directory.
 * credit should again be given to:
 * http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
 *
 *  Param[in]:  args - list of tokenized arguments
 *
 * ***************************************************************************/
void pid(char* args[])
{
    DIR * dir;
    FILE * fp;
    char path[50];
    char cmdname[50];
    char file[50];
    struct dirent *ent;


    if(args[1] == NULL)
    {
        printf("Please specify cmd name. Here is a list of all pid's:\n");
        display_pid();
        return;
    }


    if( (dir = opendir("/proc")) == NULL )
    {
        printf("**Error: could not open /proc directory");
        return;
    }

    //find all pids that match any substring of the given command
    while( (ent = readdir(dir)) != NULL )
    {
        strcpy(path, "/proc/");
        strcpy(file, ent->d_name);

        //if file is not a pid, continue
        if(strspn(file, "1234567890") != strlen(file))
            continue;

        //create path to /proc/<pid>/comm
        strcat(path, file);
        strcat(path, "/comm");

        //open /proc/<pid>/comm
        fp = fopen(path, "r");
        if( fp == NULL )
        {
            printf("*Error: invalid <pid>");
            return;
        }

        //if the input is a substring of the value in the comm file:
        //return pid with command name

        //the command name is the first thing inside the comm file
        fscanf(fp, "%s", cmdname);

        //if no match, continue though the loop
        if( strstr(cmdname, args[1]) == NULL )
            continue;

        //print the command name that belongs to <pid>
        printf("PID:  %-7s%-s\n", file, cmdname);

        fclose(fp);
    }

    closedir(dir);
}

/******************************************************************************
 *  Function:       display_pid
 *
 *  Description:
 *      Find all sub directories using dirent.h.
 * credit should again be given to:
 * http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
 *
 *  Param[in]:  args - list of tokenized arguments
 *
 * ***************************************************************************/
void display_pid()
{
    int count = 1;
    DIR * dir;
    char file[50];
    struct dirent *ent;

    if( (dir = opendir("/proc")) == NULL )
    {
        printf("**Error: could not open /proc directory");
        return;
    }

    //print all pid's
    while( (ent = readdir(dir)) != NULL )
    {
        strcpy(file, ent->d_name);

        //if file is not a pid, continue
        if(strspn(file, "1234567890") != strlen(file))
            continue;

        printf("%-8s", file);

        if( (count % 8) == 0 )
            printf("\n");

        count++;
    }

    closedir(dir);
}

/******************************************************************************
 *  Function:       systat
 *
 *  Description:
 *      systat prints the following process information:
 *
 *   Linux Version information
 *   System uptime
 * memory usage information:
 *   memtotal
 *   memfree
 * CPU information:
 *   vendor id though cache size
 *
 *  Param[in]:  args - list of tokenized arguments
 *
 * ***************************************************************************/
void systat(char* args[])
{
    char linuxVersion[30] = {"/proc/version"};
    char systemUptime[30] = {"/proc/uptime"};
    char memInfo[30] = {"/proc/meminfo"};
    char cpuInfo[30] = {"/proc/cpuinfo"};
    char buffer[100] = {0};
    FILE *fp = NULL; 
    int i;  //loop variable

//--open linux version file
    fp = fopen(linuxVersion, "r");
    if( fp == NULL )
    {
        printf("*Error: could not open file");
        return;
    }

    //get linux version information and print to terminal
    fgets(buffer, 100, fp);  //Note: fgets includes \n

    //find and change the first occurance of '(' to '\0'
    *strchr(buffer, '(') = 0;
    printf("%s\n", buffer);

    //close file
    fclose(fp);


//--open uptime file
    fp = fopen(systemUptime, "r");
    if( fp == NULL )
    {
        printf("*Error: could not open file");
        return;
    }

    //get system uptime information and print to terminal
    fgets(buffer, 100, fp);  //Note: fgets includes \n
    
    printf("System uptime %s", buffer);

    //close file
    fclose(fp);


//--open meminfo file
    fp = fopen(memInfo, "r");
    if( fp == NULL )
    {
        printf("*Error: could not open file");
        return;
    }

    //get total memory information and print to terminal
    fgets(buffer, 100, fp);  //Note: fgets includes \n
    printf("%s", buffer);


    //get free memory information and print to terminal
    fgets(buffer, 100, fp);  //Note: fgets includes \n
    printf("%s", buffer);

    //close file
    fclose(fp);


//--open cpuinfo file
    fp = fopen(cpuInfo, "r");
    if( fp == NULL )
    {
        printf("*Error: could not open file");
        return;
    }

    //get CPU information and print to terminal
    fgets(buffer, 100, fp);  //do not include the first line in the file
    for(i = 0; i < 8; i++)
    {
        fgets(buffer, 100, fp);  //Note: fgets includes \n
        printf("%s", buffer);
    }    

    //close file
    fclose(fp);
}

/******************************************************************************
 *  Function:       help
 *
 *  Description:
 *      prints usage information.
 *
 *  Param[in]:  args - list of tokenized arguments (Not used)
 *
 * ***************************************************************************/
void help(char* args[])
{
    printf("Usage Options:");
    printf("\n\tcmdnm  <pid>\t - return name of a given process id");
    printf("\n\tpid  <command>\t - return pid of a given command");
    printf("\n\tsystat\t\t - print process information\n");
}

/******************************************************************************
 *  Function:       proc_status
 *
 *  Description:
 *      Makes a call to getrusage() and displays the following information:
 * User time, System time, Page Faults (hard and soft), and Swaps.
 * 
 * ***************************************************************************/
void proc_status()
{
    struct rusage usage;
    double t = 0;

    getrusage(RUSAGE_CHILDREN, &usage);
    printf("User time:   %ld.", usage.ru_utime.tv_sec);
    printf("%06ld\n", usage.ru_utime.tv_usec);
    printf("System time:   %ld.", usage.ru_stime.tv_sec);
    printf("%06ld\n", usage.ru_stime.tv_usec);
    printf("Faults (hard): %ld\n", usage.ru_majflt);
    printf("Faults (soft): %ld\n", usage.ru_minflt);
    printf("Swaps: %ld\n", usage.ru_nswap);

}

/******************************************************************************
 *  Function:       cd
 *
 *  Description:
 *      Changes the current working directory.
 * 
 *  Param[in]:  args - list of tokenized arguments 
 *
 * ***************************************************************************/
void cd(char* args[])
{
    //if unsuccessful, print error and return 
    if(chdir(args[1])) 
        printf("Error cd: %s- No such file or directory", args[1]);
}

/******************************************************************************
 *  Function:       redierect_pipe
 *
 *  Description:
 *      This function checks all tokenized arguments for a '|' or '<' or '>'
 * If one of these symbols is found, then a call to the appropriate function
 * shall be made and a return status of 0 will be returned on success.
 * 
 *  Param[in]:  args - list of tokenized arguments
 *  Return: 0 - pipe or redirect was found and succesfully executed
 *  Return: 1 - did not find a pipe or redirect
 *
 * ***************************************************************************/
int redirect_pipe(char* args[])
{
    int i;

    for( i = 0; args[i] != NULL; i++ )
    {
        //redirected output
        if(!strcmp(args[i], ">"))
        {
            args[i] = NULL;
            redirected_output(args, args[i+1]);
            proc_status();
            return 0;
        }

        //redirected input
        if(!strcmp(args[i], "<"))
        {
            args[i] = NULL;
            redirected_input(args, args[i+1]);
            proc_status();
            return 0;
        }

        //Pipes
        if(!strcmp(args[i], "|"))
        {
            args[i] = NULL;
            do_pipe(args, i);
            proc_status();
            return 0;
        }
    }

    
    return 1;
}

/******************************************************************************
 *  Function:       redirected_output
 *
 *  Description:
 *      This function creates an output file where the output of the previos
 * command should be put. This is done by loading the file descripter of the
 * newly created file into position 1 using dup2. this will automatically 
 * close stdout and replace it with the current file discriptor. After that,
 * the call to the appropriate function can be made.
 * 
 *  Param[in]:  args - list of tokenized arguments
 *  Param[in]:  fileName - redirected output file name
 *
 * ***************************************************************************/
void redirected_output(char *args[], char* fileName)
{
    int fd;
    int pid;
    int status;

    if( fork() == 0 )   //Child Process
    {
        //check if succesfully created file discriptor for reading
        if( (fd = creat(fileName, 0644)) == -1)
            printf("Error: could not open %s for writting\n", fileName);

        //redirect standard output to the file descriptor
        dup2(fd, 1);
        
        //call the appropriate function
        call(args);
    }
    
    //wait for child process to finish
    pid = wait(&status);
    printf("\nChild process %d exited with status %d\n",
            pid, (status >> 8)); 

}

/******************************************************************************
 *  Function:       redirected_input
 *
 *  Description:
 *      This function opens an input file where the contents shall be used
 * as arguments to the previous command. This is done by loading the file 
 * descripter of the opend file into position 0 using dup2. this will 
 * automatically close stdin and replace it with the current file discriptor.
 * After that, the call to the appropriate function can be made.
 * 
 *  Param[in]:  args - list of tokenized arguments
 *  Param[in]:  fileName - redirected input file name
 *
 * ***************************************************************************/
void redirected_input(char *args[], char* fileName)
{
    int fd;
    int pid;
    int status;

    if( fork() == 0 )   //Child Process
    {
        //check if succesfully created file discriptor for reading
        if( (fd = open(fileName, O_RDONLY)) == -1)
            printf("Error: could not open %s for reading\n", fileName);

        //redirect standard output to the file descriptor
        dup2(fd, 0);
        
        //call the appropriate function
        call(args);
    }
    
    //wait for child process to finish
    pid = wait(&status);
    printf("\nChild process %d exited with status %d\n",
            pid, (status >> 8)); 

}

/******************************************************************************
 *  Function:       do_pipe
 *
 *  Description:
 *      This function redirects the output of one command to the input of
 * another. The grandchild is used to redirect the input of the second
 * comand while it's parent is used to redirect the output of the first
 * comand.
 *
 * @ Todo: make function capable of using multiple pipes e.g.
 *          cmd | cmd | cmd
 * 
 *  Param[in]:  args - list of tokenized arguments
 *  Param[in]:  index - position of '|' in args
 *
 * ***************************************************************************/
void do_pipe(char* args[], int index)
{
    int fd[2];
    int pid;
    int status;
    char** cmd = &args[index+1];

    //child process
    if( fork() == 0)
    {
        //create the pipe
        pipe(fd);

        //output side of pipe (grand child process)
        if( fork() == 0 )
        {
            dup2(fd[1], 1);     //redirect output
            close(fd[0]);       //close read end
            call(args);
            exit(2);
        }

        //input side of pipe (child process)
        dup2(fd[0], 0);     //redirect the input
        close(fd[1]);       //close write end
        call(cmd);
        exit(2);
    }

    //wait for child process to finish
    pid = wait(&status);
    printf("\nChild process %d exited with status %d\n",
            pid, (status >> 8)); 

}


/******************************************************************************
 *  Function:       call
 *
 *  Description:
 *      In the first version of this program, this same structure was directly
 * used in main. This code migrated to a function because now it acts as a
 * wrapper for the exec system call which included user defined functions.
 * A loop first checks to see if the comand could be found in the user
 * defined functions; if found, then the appropriate function will be called
 * using function pointers.
 * 
 *  Param[in]:  args - list of tokenized arguments
 *
 * ***************************************************************************/
void call(char *args[])
{
    int i;

    //Loop though and call the function that was typed in.
    for(i = 0; i < NUM_CMDS; i++)
    {
        //check for matches with current commands
        if(!strcmp(args[0], commands[i]))   //match found
        {
            //Call appropriate function
            (*func[i]) (args);
            break;
        }
    }
    //exit properly if command succesfull
    if ( i != NUM_CMDS)
        exit(0);

    printf("%s: Comand failed to be recognized", args[0]);

    //pass arguments to a system call
    execvp(args[0], args);
    //exec failed to terminate properly
    exit(1);
}


/******************************************************************************
 *  Function:       tokenize
 *
 *  Description:
 *      This function takes user input as a string and tokenizes the commands
 * based on white space.
 * 
 *  Param[in]:  input - sring of user input
 *  Param[out]:  args - an arrary of strings to store the tokenized arguements
 *  Return -1:  no arguments specifyed
 *  Return n:   number of arguments from the command line
 *
 * ***************************************************************************/
int tokenize(char* input, char* args[])
{
    int numArgs = 0;
    char* tok = NULL;

    tok = strtok(input, " \n\t");
    if( tok == NULL )
        return -1;

    while( tok != NULL )
    {
        args[numArgs] = tok;
        tok = strtok(NULL, " \n\t");
        numArgs++;
    }

    //set the next argument to NULL
    args[numArgs] = NULL;

    return numArgs;
}

/******************************************************************************
 *  Function:       send_signal
 *
 *  Description:
 *      send signal is a wrapper function for the system kill command.
 * it calls execvp with the proper arguments to the kill function. cmd is
 * used to hold the command that will be executed by the execvp call.
 * 
 *  Param[in]:  args - list of tokenized arguments
 *
 * ***************************************************************************/
//send signal is a wrapper function for the system kill command
void send_signal(char* args[])
{
    int pid;
    int status;
    int i;
    char* cmd[10] = {NULL};
    
    //set up the command for sending a signal
    //to a process using the kill command
    cmd[0] = "kill";
    cmd[1] = "-s";

    //copy the rest of the arguments to cmd
    for(i = 1; args[i] != NULL; i++)
        cmd[i+1] = args[i];

    //child process calls kill command to send signal
    if( fork() == 0 )
    {
        execvp(cmd[0], cmd);
        exit(2);
    }

    //wait for child process to finish
    pid = wait(&status);

    //pass on the status
    exit(status >> 8);
}

/******************************************************************************
 *  Function:       sig_handler
 *
 *  Description:
 *      This function will be called when a signal is sent to dash. it can 
 * catch all signals except for the SIGKILL(9) and SIGSTOP(19) signals. 
 * when a signal is received, dash will display what signal was received.
 * 
 *  Param[in]:  signo - signal number 
 *
 * ***************************************************************************/
//Not complete: need to include all the signal numbers
void sig_handler(int signo)
{
    switch(signo)
    {
    case 1:
        printf("received SIGHUP signal");
        break;
    case 2:
        printf("received 2 signal");
        break;
    }
}
