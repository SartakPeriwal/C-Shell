#include <stdio.h> 
#include <sys/wait.h>
#include <fcntl.h>
#include <pwd.h> 
#include <sys/types.h> 
#include <string.h>
#include <signal.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <grp.h>
#include <dirent.h>
#include <unistd.h> 
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#include <sys/utsname.h>
#define command_sep " \t\n\r\a\f"
#define builtins 7
char history_out[500][500];
/*struct history_keeper
{
    char comnd[100];
}
struct history_keeper hstr[100];*/
char dir[400];
char previous[400];
char my_builtins[7][20];
int backprocs,sigid;
int list_till_now;
FILE *hist;
FILE *hist_write;
int nightswatch(char ** args);
int KeyDown();
void pinfo(char ** args);
int history(char ** args);
int execute_command(char ** args);
char **getcommands(char * takecmd);
void c_dir_printdir();
void c_dir_print();
void takecmd();
void ls(char ** args);
char ** separatearguements(char * cmd);
void ls_simple(int checker,char * mydir);
void lstot(int checker,char * mydir);
int change_dir(char ** args);
int pwd(char ** args);
long long int echo(char ** args);
void exit_handler (int sig);
int restcommands(char ** args);
void addbg_proc(char ** str,int pid);
int background_checker(char ** args);
void  SIGINT_handler(int signal_num);
typedef struct bgp{
	int proc_id;
	int j_id;
	char * cmd;
}bgp;

bgp back_procs[100];
