#include "global.h"

long long int echo(char ** args)
{
	if(args[1]==NULL)
	{
		printf("\n");
		return 1;
	}
		long long int i=1;
        for(long long int j=1;args[j]!=0;j++)
        {
            printf("%s ",args[j]);
        }
		printf("\n");
}
