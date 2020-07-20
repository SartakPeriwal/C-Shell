#include "global.h"

int background_checker(char ** args)
{
	int i=0;
    for(i=0;args[i]!=0;i+=1)
	{
		if(!(strcmp(args[i],"&")))
		{
			args[i] = NULL;
			return 1;
		}
	}
	return 0;
}
void exit_handler (int sig)
{
    int status,i;
    int chek = 0;
    pid_t pid,wpid;
    wpid = waitpid(-1, &status, WNOHANG);
    if(wpid!=0) // Checks for the child processes which have changed there status. 
	{
		if(WIFEXITED(status)!=0 )
            //Evaluates to a non-zero value if status was returned for a child process that terminated normally. 
		{
			i = 1;
			while(i<=backprocs)
            {
				if(back_procs[i].proc_id == wpid)
					{
						chek = 1;
						{
							printf("[%d]+   Done\t\t%s pid %d\n process exited normally\n",back_procs[i].j_id,  back_procs[i].cmd, wpid);
						}
					}
                i+=1;
			}
			if(chek!=0)
			c_dir_print();
			fflush (stdout);
		}

		else if(WIFSIGNALED(status)!=0)
		{
            i=1;
            while(i<=backprocs)
			{
				if(back_procs[i].proc_id == wpid)
                    //Evaluates to a non-zero value if status was returned for a child process that terminated due to the receipt of a signal that was not caught
					{
						chek=1;
						{
							printf("[%d]+   Done\t\t%s with pid %d\n process exited normally\n",back_procs[i].j_id,  back_procs[i].cmd , wpid);
						}
					}
			}
			if(chek!=0)
			c_dir_print();
			fflush (stdout);
		}
	}
	return;
}

void addbg_proc(char ** str,int pid)
{
    backprocs++;
	back_procs[backprocs].proc_id = pid;
	back_procs[backprocs].j_id = backprocs;
	back_procs[backprocs].cmd = str[0];
	printf("process %s with pid %d has started in the background\n",str[0],pid);
	printf("[%d] %d\n",back_procs[backprocs].j_id,pid);
	return;
}
int restcommands(char ** args)
{
	pid_t proc_id, wpid;
	int proc_status;
	int i=0;
	int checker = background_checker(args);
	proc_id = fork();
	if(!(proc_id ))
	{
		if(execvp(args[0],args) >= 0)
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("exec");
		}
	}
	else if(proc_id <= -1)
	{
		printf("Forking error in non inbuilt commands\n");
	}
	else
	{
		if(!checker)
		{
			sigid = proc_id;
			wait(NULL); 
		    sigid=0;
		}
		else
		{	
			addbg_proc(args,proc_id);
		}
	return 1;
	}
}
int execute_command(char ** args)
{
	int i;
	int t =0;
	for(i=0;i<builtins;i+=1)
	{
		if(!(strcmp(args[0],my_builtins[i])))
		{
			if(!(strcmp(args[0],"ls")))
			{
				ls(args);
				return 1;
			}
			else if(!(strcmp(args[0],"cd")))
			{
				int y= change_dir(args);
				return 1;
			}
			else if(!(strcmp(args[0],"pwd")))
			{
				pwd(args);
				return 1;
			}
			else if(!(strcmp(args[0],"nightswatch")))
			{
			    int x=nightswatch(args);
				return 1;
			}
            
			else if(!(strcmp(args[0],"pinfo")))
			{
				pinfo(args);
				return 1;
			}
			else if(!(strcmp(args[0],"history")))
			{
				history(args);
				return 1;
			}
            
			else if(!(strcmp(args[0],"echo")))
			{
				echo(args);
				return 1;
			}
		}
	}
	return restcommands(args);
}
