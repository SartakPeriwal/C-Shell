#include <pwd.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <signal.h>
#include <langinfo.h>
#include <stdint.h>
#include <stdio.h> 
#include <dirent.h>
#include <fcntl.h>
#include <sys/utsname.h>
#include "global.h"

int change_dir(char ** args)
{
    char cu_dir[400];
    long long int c_len=sizeof(cu_dir);
    getcwd(cu_dir,c_len);
    char run_dir[400];
    strcpy(run_dir,dir);
    if(args[1]==NULL)
    {
        chdir(dir);
        return 2;
    }
    else if(args[1]!=NULL)
    {
        if(strcmp(args[1],"\n") == 0||strcmp(args[1],"~")==0)
        {
            chdir(run_dir);
            return 1;
        }
        else if(!(strcmp(args[1],"-")))
        {
            chdir(previous);
            printf("%s\n",previous);
            strcpy(previous,cu_dir);
            return 1;
        }
        else if(!(strcmp(args[1],".")))
        {
            chdir(cu_dir);
            return 1;
        }
        else
        {
            chdir(args[1]);
            return 1;
        }
    }
}
