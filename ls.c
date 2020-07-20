
#include "global.h"


struct dirent **namelist;
struct stat buf;
int n;

int perms(mode_t perm)
{
	char file_type = '?';

	if (S_ISREG(perm)!=0)
    {
        file_type = '-'; //regular file
    }
	else if (S_ISDIR(perm)!=0)
    { 
        file_type = 'd';
    }// directory
	else if (S_ISBLK(perm)!=0)
    {
        file_type = 'b';
    }// block device
	else if (S_ISLNK(perm)!=0)
    {
        file_type = 'l';
    }//symbolic link
	else if (S_ISSOCK(perm)!=0)
    {
        file_type = 's';
    }// Socket
	else if (S_ISCHR(perm)!=0)
    {
        file_type = 'c';
    }// character device
	else if (S_ISFIFO(perm)!=0)
    {
        file_type = '|';
    }// Pipe(FIFO)
	int allperms = 0;
	printf("%c",file_type);
	if((perm & S_IRUSR)!=0 )
	{
		printf("r");
	}
	else if(!(perm &S_IRUSR))
	{
		printf("-");
	}
	if((perm & S_IWUSR)!=0 )
	{
		printf("w");
	}
    else if(!(perm & S_IWUSR) )
	{
		printf("-");
	}
	if((perm & S_IXUSR)!=0 )
	{
		printf("x");
	}
    else if(!(perm & S_IXUSR) )
	{
		printf("-");
	}
	if((perm & S_IRGRP)!=0 )
	{
		printf("r");
	}
    else if(!(perm & S_IRGRP) )
	{
		printf("-");
	}
	if((perm & S_IWGRP)!=0 )
	{
		printf("w");
	}
    else if(!(perm & S_IWGRP) )
	{
		printf("-");
	}
	
	if((perm & S_IXGRP)!=0 )
	{
		printf("x");
	}
	if(!(perm & S_IXGRP) )
	{
		printf("-");
	}
	if((perm & S_IROTH)!=0 )
	{
		printf("r");
	}
    else if(!(perm & S_IROTH) )
	{
		printf("-");
	}
	
	if((perm & S_IWOTH)!=0 )
	{
		printf("w");
	}
    else if(!(perm & S_IWOTH) )
	{
		printf("-");
	}
	if((perm & S_IXOTH)!=0 )
	{
		printf("x");
	}
    else if(!(perm & S_IXOTH) )
	{
		printf("-");
	}
	
		if((perm & S_IXOTH)!=0)
		{
			allperms++;
		}
	return allperms;
}
int selector(const struct dirent *namelist)
{
	if(namelist->d_name[0]=='.')
		return 0;
	else
	{
		return 1;
	}
}
void lstot(int checker,char * mydir)
{
	    int x =0;
	if (checker==1)
	{
		n = scandir(mydir, &namelist, selector, alphasort);	
	}
	else if(!(checker))
	{
		n = scandir(mydir, &namelist,NULL, alphasort);
	}
			 
    long long int total=0;
		    if (n < 0) 
		    {
		    	perror("scandir has encountered fault in input");
		    }
            else
            {
            for(x=0;x<n;x+=1)
		    {
		        struct group * grp;
		        struct tm time;
		        char date[300];
		        char usr[400];
		        stat(namelist[x]->d_name,&buf);
                total+=buf.st_blocks;
		        int allperms = perms(buf.st_mode);
		        printf(" %2lu",buf.st_nlink);
                int usr_len=sizeof(usr);
		        int user = getlogin_r(usr,usr_len); //get name of owner
		        grp = getgrgid(buf.st_gid); //get group name
		        printf(" %s",usr ); 
		        printf(" %s",grp->gr_name);
		        printf(" %7ld ",buf.st_size );
		        localtime_r(&buf.st_mtime, &time);
		        strftime(date, sizeof(date), "%b %d %H:%M ", &time);
				printf("  %s ", date);
				if (S_ISDIR(buf.st_mode)!=0) 
					printf("%s\n",namelist[x]->d_name);
				else if((allperms)!=0)  
					printf("%s\n",namelist[x]->d_name);
                else 
					printf("%s\n",namelist[x]->d_name);
		        free(namelist[x]);
		    }
		     free(namelist);
            printf("Total %lld\n",total/2);
            }
}
void ls_simple(int checker,char * mydir)
{
	if (checker==1)
	{
		n = scandir(mydir, &namelist, selector, alphasort);	
	}
	else if(!(checker))
	{
		n = scandir(mydir, &namelist,NULL, alphasort);
	}
	    int x =0;
	    if (n < 0) 
	    {
	    	perror("scandir has encountered error fault in input");
	    }
        else
        {
            for(x=0;x<n;x+=1)
	        {
	            printf("%s\n", namelist[x]->d_name);
	            free(namelist[x]);
	        }
	        free(namelist);
        }
}
void ls(char ** args)
{
	
	
    if(args[1]==NULL)
    {	
    	ls_simple(1,".");
	}
	else
    {
        if (args[2]==NULL)
        {
	
		    if (!(strcmp(args[1],"-l")))
		    {
			    lstot(1,".");
		    }
		    else if ((!(strcmp(args[1],"-la")))||(!(strcmp(args[1],"-al"))))
		    {
			    lstot(0,".");
		    }
            else if(!(strcmp(args[1],"-a")))
		    {
			    ls_simple(0,".");
		    }
		    else
		    {   
				char *mydir = args[1];
				ls_simple(1,mydir);
				
		    }
        
	    }
        else
        {
	        if(args[3]==NULL)
	        {
		        if( (!(strcmp(args[1],"-l")))&&(!(strcmp(args[2],"-a"))) || (!(strcmp(args[1],"-a")))&&(!(strcmp(args[2],"-l")) ))
		        {
			        lstot(0,".");
		        }
		        else if ((! (strcmp(args[1],"-l"))) && (strcmp(args[2],"-a")))
		        {
			        ls_simple(1,args[2]);
		        }
		        else if ((! (strcmp(args[1],"-a"))) && (strcmp(args[2],"-l")))
		        {
			        ls_simple(0,args[2]);
		        }
		        else if ( (!(strcmp(args[1],"-la"))) || (!(strcmp(args[1],"-al")) ))
		        {
			        lstot(0,args[2]);
		        }
        
	        }
    
        }
    }
}
