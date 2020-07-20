#include "global.h"
int history(char ** args)
{
    if(!args[1])
    {
        if(list_till_now>=20)
        {
            for(int i = list_till_now;i>=list_till_now-20;i--)
            {
                printf("%s",history_out[i]);
            }
            
        }
        else
        {
            for(int i=list_till_now;i>0;i-=1)
            {
                printf("%s",history_out[i]);
            }
        }
    }
    else
    {
        for(int i=list_till_now;i>=list_till_now-atoi(args[1]);i-=1)
        {
            printf("%s",history_out[i]);
        }
    }
    
}
