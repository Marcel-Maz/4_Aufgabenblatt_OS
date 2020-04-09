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
    char pmt[16];
    char *token = NULL;
    char *pre_token = NULL;//stores the last token

    strcpy(path_command,"/bin/");

    fgets(buffer, INPUT_SIZE, stdin);//die Zeile wird eingegeben

    token = strtok(buffer, " ");
    strcpy(cmd,token);
    token = strtok(NULL, " ");//Nochmals um zu pruefen ob ein parameter da ist
     
    while( token != NULL)
    {
        pre_token = token; //pre_token stores the last word of the line before enter
        token = strtok(NULL, " ");
    }

    if(pre_token == NULL)//falls immer noch pre_token sich noch nicht geändert hat  
    {
        token = strtok(cmd,"\n");
        strcpy(cmd,token);
        strcpy(pmt, " ");
    }  
    else
    {
        token = strtok(pre_token,"\n");  
        strcpy(pmt,token);
    }    

    strcat(path_command,cmd);
    exec_cmd(path_command,cmd,pmt);

    free(buffer); 
}

void exec_cmd(const char *path_command, char *cmd,  char *pmt) 
{
    int status;
    pid_t pid,x;

    char *command[] = {cmd, pmt, (char*)NULL};

    /*printf("This is the path:%s\n",path_command);
    printf("Lenght of path: %ld\n", strlen(path_command));
    printf("THis is the command:%s\n",cmd);
    printf("Lenght of command: %ld\n", strlen(cmd));
    printf("THis is the paramater:%s\n", pmt);
    printf("Lenght of parameter: %ld\n", strlen(pmt));
*/

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
        if((execv(path_command,command) < 0))
            perror("execv failed");
    }
  
}
