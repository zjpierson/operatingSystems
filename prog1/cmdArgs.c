//--------------    cmdArgs.c    ------------//
#include "cmdArgs.h"


void (*func[NUM_CMDS]) (char* input) = {quit, quit, cmdnm, pid, systat, help};
const char commands[NUM_CMDS][LEN_CMD] = 
{
    "quit", 
    "exit", 
    "cmdnm", 
    "pid", 
    "systat", 
    "help"
};

void quit(char* input)
{
    printf("Now exiting...\n");
    exit(0);
}


void cmdnm(char* input)
{
    char path[50] = {"/proc/"};
    char cmdname[50];
    char *pid = NULL;
    FILE *fp = NULL; 

    //Get the next command
    pid = strtok(input, " \t");
    if(pid == NULL)
    {
        printf("Please specify pid. Here is a list of all cmd names:\n");
        display_cmdNames();
        return;
    }

    //add pid to the file path: "/proc/<pid>"
    strcat(path, pid);

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

//finding all sub directories using dirent.h should be given credit to:
//http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
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

//loop though all pid directories and return pid numbers that match 
//any substring of the given command
//finding all sub directories using dirent.h should be given credit to:
//http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
//
void pid(char* input)
{
    DIR * dir;
    FILE * fp;
    char * cmd = NULL;
    char path[50];
    char cmdname[50];
    char file[50];
    struct dirent *ent;


    //Get the next command
    cmd = strtok(input, " \t");
    if(cmd == NULL)
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
        if( strstr(cmdname, cmd) == NULL )
            continue;

        //print the command name that belongs to <pid>
        printf("PID:  %-7s%-s\n", file, cmdname);

        fclose(fp);
    }

    closedir(dir);
}

//finding all sub directories using dirent.h should be given credit to:
//http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
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

//Print to stdout:
//  Linux Version information
//  System uptime
//memory usage information:
//  memtotal
//  memfree
//CPU information:
//  vendor id though cache size
void systat(char* input)
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



//    //the command name is the first thing inside the comm file
//    fscanf(fp, "%s", cmdname);
//    //print the command name that belongs to <pid>
//    printf("%s", cmdname);
//
//    fclose(fp);
}

void help(char* input)
{
    printf("Usage Options:");
    printf("\n\tcmdnm  <pid>\t - return name of a given process id");
    printf("\n\tpid  <command>\t - return pid of a given command");
    printf("\n\tsystat\t\t - print process information\n");
}
