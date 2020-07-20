#include "global.h"

void pinfo(char ** args)
{
    char str[999]; 
    char exec_path[999];
    long long int pid;
    if(!args[1])
    {
        pid = getpid();
    }
    else if(args[1])
    {
        pid = atoi(args[1]);
        if(kill(pid,0)!=0)
        {
            perror("Invalid PID");
            return;
        }
    }
    char s;
    printf("pid -- %lld\n", pid);
    sprintf(str ,"/proc/%lld/status",pid);
    FILE* file = fopen(str, "r");
    char lin[999];
    /*if(file==NULL)
    {
        printf("\nCAN NOT OPEN FILE");
        //getch();
        exit(0);

    }
    do
    {
        s=getc(file);
        printf("%c",s);

    }
    while(s!=EOF);
    fclose(file);
    //getch();*/
    long long int l = 0;
    while (fgets(lin, sizeof(lin), file))
    {
        if(l == 2 )
        {
            l+=1;
            printf("Process %s",lin);
        }
        else if (l==17)
        {
            
            l+=1;
            printf("%s",lin);
            break;
        }
        else
        {
            l+=1;
        }   
    }

    fclose(file);
    sprintf(str ,"/proc/%lld/exe",pid);
    int p =readlink(str , exec_path , sizeof(exec_path));
    exec_path[p] = '\0';
    printf("Executable Path -- %s\n", exec_path);
}






