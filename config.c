#include "config.h"


void type_prompt()
{
    long size;
    char *buf;
    char *ptr;

    size = pathconf(".",_PC_PATH_MAX);

    if( (buf = (char *)malloc((size_t)size)) != NULL )
        ptr = getcwd(buf, (size_t)size);

    struct passwd *getpwuid(uid_t uid);
    struct passwd *p;

    uid_t uid=0;

    if( (p = getpwuid(uid)) == NULL)
        perror("getpwuid error");
    
    else
    {
        printf("%s@%s> ",p->pw_name,ptr);
    }
    
    free(buf);
}

void read_command()
{
    char *buffer = (char *)malloc(sizeof(char)*INPUT_SIZE); //check if the spac is right allocate
    char path_command[16];
    char cmd[16]; 
    char parameter[16];
    int counter = 0;
    char *token;
 
    strcpy(path_command,"/bin/");

    fgets(buffer, INPUT_SIZE, stdin);

    token = strtok(buffer, " ");
    strcpy(cmd,token);
    strcat(path_command,cmd);

    while(token != NULL)
    {
        ++counter;
        if(counter == 2)
            strcpy(parameter,token);
        token = strtok( NULL," ");
    }

    if(token == NULL && counter == 1)
        strcpy(parameter, " ");

    exec_cmd(path_command,cmd,parameter);

    free(buffer);
    
}

void exec_cmd(const char *path_command, char *command,  char *parameter) 
{
    int status;
    pid_t pid,x;

    char *cmd[] = {command, parameter, (char*)NULL};

   printf("This is the path:%s\n",path_command);
    printf("THis is the command:%s\n",command);
    printf("THis is the paramater:%s\n", parameter);


    pid = fork();

    if (pid < 0)
    {
        perror("Fork failed\n");
    }

    if(pid != 0)
    {
        x = waitpid(pid, &status, 0);
        if (x < 0)
        {
            perror("waitpid failed\n");
        }  
    }
    else
    {
        if((execv(path_command,cmd) < 0))
            perror("execv failed");
    }
   
}
