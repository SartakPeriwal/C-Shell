#include "global.h"
#include <time.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
int KeyDown()
{
    struct termios oldt,newt;
    int bytes;
    tcgetattr(STDIN_FILENO,&oldt);
    newt=oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&newt);
    ioctl(STDIN_FILENO,FIONREAD,&bytes);
    tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
    return bytes>0;
}
int nightswatch(char ** args)
{
    long long int fault=-1;
    if(strcmp(args[1],"-n")!=0)
    {
        fault =1;
    }
    /*if(strcmp(args[3],"interrupt")||strcmp(args[3],"dirty"))
    {
        fault=1;
    }*/
    if(fault==1)
    {
        printf("error in arguments passed");
        return 1;
    }
    long long int curr =-1;
    long long int n=0;
    time_t start=time(NULL);
    long long int flag=-1;
    char data[50];
    char data2[100];
    FILE *fp,*fp1;
    if(!(strcmp(args[3],"interrupt")))
    {
        flag=0;
    }
    if(!(strcmp(args[3],"dirty")))
    {
        flag=1;
    }
    long long int tim=atoi(args[2]);
    if(flag==0||flag==1)
    {
        while(2)
        {
            if(KeyDown()&&(getchar()=='q'))
            {
                break;
            }
            if((time(NULL)-start)/tim>curr)
            {
                curr++;
                if (flag==1)
                {
                    fp=fopen("/proc/meminfo","r");

                    long long int count=0;
                    while(count!=17)
                    {
                        fgets(data,50,fp);
                        count++;
                    }
                    printf("%s",data);
                }
                else if (flag==0)
                {
                    fp1=fopen("/proc/interrupts","r");
                    long long int count1=0;
                    while(count1!=9)
                    {
                        fgets(data2,100,fp1);
                        count1++;
                        if(count1==1||count1==5)
                        {
                            printf("%s\n",data2);
                        }

                    }
                }

            }
            
        }
    }
}
