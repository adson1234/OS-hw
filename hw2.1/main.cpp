#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <math.h>
using namespace std;
int findmin(int * arr,int n){   //return min value
    int ans=2147483647;
    for(int i=1;i<=n;i++){
        if (ans>arr[i])
            ans=arr[i];
    }
    return ans;
}

int main()
{
    printf("Please input the array of 'Process vs. time'\n");
    printf(" (every number>=1)");
    printf("(or inupt -1 to use default value):\n");
    char s[3000];
    scanf("%[^\n]",s);
    char * delim=" ";
    char * splits;

    int processCount=0;
    splits=strtok(s,delim);

    int needTime[501];
    int TimeQuantum;

    if (atoi(splits)==-1){
        processCount=4;
        needTime[1]=6;
        needTime[2]=3;
        needTime[3]=1;
        needTime[4]=7;
        TimeQuantum=7;
    }else{
        while(splits!=NULL){
            processCount++;

            needTime[processCount]=atoi(splits);
            splits=strtok(NULL,delim);
            //printf("%d\n",needTime[processCount]);
        }

        printf("Please input the value of time quantum\n");
        scanf("%d",&TimeQuantum);
    }

    for(int i=1;i<=TimeQuantum;i++){
        int finishTime[processCount+1];
        int tmpneedTime[processCount+1];
        for(int j=1;j<=processCount;j++){
            tmpneedTime[j]=needTime[j];
        }
        int nowExecuting=1;
        int timeCount=0;
        int NotfinishedCounts=processCount;
        while(1){
            for(int j=1;j<=i;j++){
                if (tmpneedTime[nowExecuting]>0){
                    timeCount++;
                    tmpneedTime[nowExecuting]--;
                    if (tmpneedTime[nowExecuting]==0){
                        finishTime[nowExecuting]=timeCount;
                        NotfinishedCounts--;
                        break;
                    }
                }else{
                break;}
            }
            nowExecuting=((nowExecuting) % processCount) + 1;
            if(NotfinishedCounts==0) break;
        }

        double ans=0;
        for(int j=1;j<=processCount;j++){
            ans +=finishTime[j];
            //printf("%d ",finishTime[j]);
        }

        ans/=(double)processCount;
        printf("%llf ",ans);
    }
    //system("pause");
    return 0;
}
