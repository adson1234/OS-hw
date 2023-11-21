#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <math.h>
using namespace std;

int main()
{
    printf("Please input the array of 'Process vs. CPU burst time'\n");
    printf(" (every number>=1)");
    printf("(or inupt -1 to use default value):\n");
    char s[3000];
    scanf("%[^\n]",s);
    char * delim=" ";
    char * splits;

    int bursts=0;
    double burstTime[501];
    double guess[501];

    splits=strtok(s,delim);
    if (atoi(splits)==-1){
        bursts=7;
        guess[0]=10.0;
        burstTime[1]=6.0;
        burstTime[2]=4.0;
        burstTime[3]=6.0;
        burstTime[4]=4.0;
        burstTime[5]=13.0;
        burstTime[6]=13.0;
        burstTime[7]=13.0;
    }else{
        while(splits!=NULL){
            bursts++;
            burstTime[bursts]=atof(splits);
            splits=strtok(NULL,delim);
        }

        printf("Please input the first guess of burstTime:");
        scanf("%lf",&guess[0]);
    }

    for(int i=1;i<=bursts;i++){
        guess[i]=(guess[i-1]+burstTime[i])/2;

    }
    for(int i=1;i<=bursts;i++){
        printf("turn %d: guess: %lf burst: %lf\n",i,guess[i-1],burstTime[i]);
    }
    printf("turn %d: guess: %lf\n",bursts+1,guess[bursts]);
    //system("pause");
    return 0;
}

