#include <graphics.h>
#include <conio.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <math.h>
#include<float.h>
using namespace std;
double findmin(double * arr,int n){   //return min value
    double ans=DBL_MAX;
    for(int i=1;i<=n;i++){
        if (ans>arr[i])
            ans=arr[i];
    }
    return ans;
}
double findmax(double * arr,int n){   //return min value
    double ans=DBL_MIN;
    for(int i=1;i<=n;i++){
        if (ans<arr[i])
            ans=arr[i];
    }
    return ans;
}

void draw(double* ret,int TimeQuantum)
{
    initwindow(800, 600, "First Sample");
    const int textOffset=5;
    int maxX, maxY;
    maxX = getmaxx(); // graphics.h
    maxY = getmaxy();

    const int Ydivides=12+4;    //上下各留2倍的座標間距空間
    int YdivideLen=maxY/Ydivides;
    double maxRet=findmax(ret,TimeQuantum);
    double minRet=findmin(ret,TimeQuantum);
    cout<<" "<<minRet<<" "<<maxRet<<endl;
    double totaldiff=maxRet-minRet;
    //cout<<totaldiff;
    long long normalmin=(minRet-totaldiff*0.1)/12*12;
    long long normaldiff=totaldiff*1.2/12;
    if (normaldiff==0) normaldiff=1;
    //double NEWtotaldiff=normaldiff*12;
    //cout<<normaldiff;
    long long normalmax=normalmin+normaldiff*12;

    int Xdivides=TimeQuantum-1+4;
    int XdivideLen=maxX/Xdivides;
    for(int i=1;i<=TimeQuantum;i++){
        setcolor(LIGHTGREEN);
        line(XdivideLen*(2+i-1), YdivideLen*2, XdivideLen*(2+i-1), YdivideLen*(Ydivides-2));
    }
    for(int i=1;i<=Ydivides-4+1;i++){
        setcolor(LIGHTGREEN);
        line(XdivideLen*(2), YdivideLen*(2+i-1), XdivideLen*(Xdivides-2), YdivideLen*(2+i-1));
    }

    setcolor(LIGHTRED);
    char buf[50];
    for(int i=1;i<=TimeQuantum;i++){
        sprintf(buf, "%d", i);
        outtextxy(XdivideLen*(2+i-1)-textOffset, YdivideLen*(Ydivides-2)+textOffset, buf); // 請注意 座標值 (315,100) 指定了印出文字的左上角
    }
    for(int i=1;i<=12+1;i++){
        sprintf(buf, "%d", normalmax-(i-1)*normaldiff);
        outtextxy(XdivideLen*(2)-textOffset*4-2, YdivideLen*(2+i-1)-textOffset-3, buf); // 請注意 座標值 (315,100) 指定了印出文字的左上角
    }

    for(int i=1;i<=TimeQuantum-1;i++){
        line(XdivideLen*(2+i-1),YdivideLen*(Ydivides-2-(ret[i]-normalmin)/(double)normaldiff)
             ,XdivideLen*(2+i),YdivideLen*(Ydivides-2-(ret[i+1]-normalmin)/(double)normaldiff));
    }

    sprintf(buf,"x:time quantum, y:average turn around time");
    outtextxy(10,10, buf);

    while (!kbhit())
        delay(200);
    closegraph();
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

    double ret[TimeQuantum+1];

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

        double ans=0.0;
        for(int j=1;j<=processCount;j++){
            ans +=finishTime[j];
            printf("%d ",finishTime[j]);
        }
        //printf("\n");
        //printf("%lf %d ",ans,processCount);//bug
        ans/=(double)processCount;
        cout <<ans <<","<<processCount<<endl;

        ret[i]=ans;
    }

    draw(ret,TimeQuantum);
    return 0;
}


