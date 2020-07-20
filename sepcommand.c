#include <string.h>
#include "global.h"
char ** getcommands(char * takecmd)
{
	char ** buf = malloc(100*sizeof(char*));
	long long int i=0;
	if(!(buf))
	{
		printf("Failed to allocate memory in getcommands\n");
	}
	char* token = strtok(takecmd, "\n;");
	while (token) 
	{
		buf[i] = token;
		//printf("%s\n",buf[i]);
		i=i+1;
		if(i >= sizeof(buf)/sizeof(char*))
		{
			buf = realloc(buf,100*sizeof(char*));
			if(!(buf))
			{
				printf("Failed to reallocate in getcommands\n");
				//exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, "\n;");
	}
	buf[i]=NULL;
	return buf;
}
char ** separatearguements(char * cmd)
{

	char ** buf = malloc(100*sizeof(char*));
	long long int i=0;
	if(!(buf))
	{
		printf("Failed to allocate memory in separguements\n");
	}
		char * token = strtok(cmd,command_sep);
		while (token) 
	    {
		    buf[i] = token;
		    //printf("%s\n",buf[i]);
		    i+=1;
		    if(i >= sizeof(buf)/sizeof(char*))
		    {
			    buf = realloc(buf,100*sizeof(char*));
			    if(!(buf))
			    {
				    printf("Fail to reallocate in separguements\n");
			    }
		    }
		token = strtok(NULL,command_sep);
	    }   
	    buf[i]=NULL;
	    return buf;
}
