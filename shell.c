
#include "global.h"
#include <string.h>

void c_dir_printdir()
{
    char current_dir[1111]; 
    long long int length=sizeof(current_dir);
    getcwd(current_dir,length);
    long long int i=0;
    long long int check=0;
    char temp[200];

    strcpy(temp,dir); 

    while(temp[i] != '\0')
    {
        if(current_dir[i] != temp[i])  
        {
            check=1;
            break;
        }
        else
        {
            i++;
        }
    }
    if(!check)
    {
        printf("~");
        while(current_dir[i]!='\0')
        {
            printf("%c",current_dir[i]);
            i=i+1;
        }
        printf("> ");
    }
    else if(check!=0)
    {
        printf("%s> ",current_dir); 
    }
}
void c_dir_print()
{
    char buf[100];
    long long int len=sizeof(buf);
    long long int user = getlogin_r(buf,len);
    char hostname[1000];
    hostname[1000] = '\0';
    gethostname(hostname,sizeof(hostname));
    printf("%s",hostname);
    printf("%s@",buf);
    struct utsname buffers;

    if (uname(&buffers) != 0) {
        perror("uname");
        exit(EXIT_FAILURE);

    }
    //gethostname(hostname,1000);
    printf("%s:",buffers.sysname);
    c_dir_printdir();
}
void takecmd()
{
    long long int t=0;
    int val=1;	
    strcpy(my_builtins[1],"ls");
    strcpy(my_builtins[0],"pwd");
    strcpy(my_builtins[2],"nightswatch");
    strcpy(my_builtins[3],"cd");
    strcpy(my_builtins[4],"pinfo");
    strcpy(my_builtins[5],"history");
    strcpy(my_builtins[6],"echo");
    while(val)
    {

        long long int i=0,j=0,k=0;
        c_dir_print();
        char *takecommand;
        char **cmd;
        size_t cmdlength = 0;
        getline(&takecommand,&cmdlength,stdin);
        if (feof(stdin))  
        {
            printf("Ctrl+ D\n");
            printf("\x1b[H\x1b[J");
           // hist_write=fopen(".history.txt","wb");
            //fwrite(history_out,sizeof(history_out),1,hist_write);
            exit(0); 
        }
        //hist=fopen(".history.txt","rb");
        //fread(history_out,sizeof(history_out),1,hist);
        strcpy(history_out[list_till_now],takecommand);
        list_till_now++;
        cmd = getcommands(takecommand);
        /*while(cmd[list_till_now]!=0)
        {
            strcpy(history_out[list_till_now],cmd[list_till_now]);
            list_till_now++;
        }*/
        
        while(cmd[i]!=0)
        {
            char x[1000] ;
            strcpy(x,cmd[i]);
            char ** args = separatearguements(x);
            long long int flag=0;
            for(long long int t=0;t<4;t++)
            {
                if(args[0][t]=='e' && args[0][1]=='x' && args[0][2]=='i' && args[0][3]=='t')
                {
                    flag=1;
                }

            }
            if (flag==1)
            {
                //hist_write=fopen(".history.txt","wb");
                //fwrite(history_out,sizeof(history_out),1,hist_write);
                exit(0);
            }
            execute_command(args);
            i=i+1;
        }

    }
}
int main()
{
    signal(SIGCHLD, exit_handler);
    long long int len=sizeof(dir);
    getcwd(dir,len);//directory where code is run
    strcpy(previous,dir);
    takecmd();
    return 0;
}
