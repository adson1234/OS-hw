#include <graphics.h>
#include <conio.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <math.h>
#include<float.h>
#include<algorithm>
using namespace std;
double findmin(double * arr,int s,int t){   //return min value
    double ans=DBL_MAX;
    for(int i=s;i<=t;i++){
        if (ans>arr[i])
            ans=arr[i];
    }
    return ans;
}
double findmax(double * arr,int s,int t){   //return min value
    double ans=DBL_MIN;
    for(int i=s;i<=t;i++){
        if (ans<arr[i])
            ans=arr[i];
    }
    return ans;
}

void draw(double* guess, double* burstTime, int bursts)
{
    initwindow(800, 600, "First Sample");
    const int textOffset=5;
    int maxX, maxY;
    maxX = getmaxx(); // graphics.h
    maxY = getmaxy();

    const int Ydivides=12+4;    //上下各留2倍的座標間距空間
    int YdivideLen=maxY/Ydivides;
    double maxval=max(findmax(guess,0,bursts),findmax(burstTime,1,bursts));
    double minval=min(findmin(guess,0,bursts),findmin(burstTime,1,bursts));
    cout<<" "<<minval<<" "<<maxval<<endl;
    double totaldiff=maxval-minval;
    //cout<<totaldiff;
    long long normalmin=(minval-totaldiff*0.1)/12*12;
    long long normaldiff=totaldiff*1.2/12;
    if (normaldiff==0) normaldiff=1;
    //double NEWtotaldiff=normaldiff*12;
    //cout<<normaldiff;
    long long normalmax=normalmin+normaldiff*12;

    int Xdivides=bursts+1-1+4;
    int XdivideLen=maxX/Xdivides;
    for(int i=1;i<=bursts+1;i++){
        setcolor(LIGHTGREEN);
        line(XdivideLen*(2+i-1), YdivideLen*2, XdivideLen*(2+i-1), YdivideLen*(Ydivides-2));
    }
    for(int i=1;i<=Ydivides-4+1;i++){
        setcolor(LIGHTGREEN);
        line(XdivideLen*(2), YdivideLen*(2+i-1), XdivideLen*(Xdivides-2), YdivideLen*(2+i-1));
    }

    setcolor(LIGHTRED);
    char buf[50];
    for(int i=1;i<=bursts;i++){
        sprintf(buf, "%d", i);
        outtextxy(XdivideLen*(2+i-1)-textOffset, YdivideLen*(Ydivides-2)+textOffset, buf); // 請注意 座標值 (315,100) 指定了印出文字的左上角
    }
    for(int i=1;i<=12+1;i++){
        sprintf(buf, "%d", normalmax-(i-1)*normaldiff);
        outtextxy(XdivideLen*(2)-textOffset*4-2, YdivideLen*(2+i-1)-textOffset-3, buf); // 請注意 座標值 (315,100) 指定了印出文字的左上角
    }

    setlinestyle(SOLID_LINE, 0, 3);
    setcolor(WHITE);
    for(int i=1;i<=bursts-1;i++){
        //line(XdivideLen*(2+i-1),YdivideLen*(Ydivides-2-(burstTime[i]-normalmin)/(double)normaldiff)
        //     ,XdivideLen*(2+i),YdivideLen*(Ydivides-2-(burstTime[i+1]-normalmin)/(double)normaldiff));
        //不畫斜線，畫橫直線、垂直線
        int sx=XdivideLen*(2+i-1);
        int dx=XdivideLen*(2+i);
        int sy=YdivideLen*(Ydivides-2-(burstTime[i]-normalmin)/(double)normaldiff);
        int dy=YdivideLen*(Ydivides-2-(burstTime[i+1]-normalmin)/(double)normaldiff);
        line(sx,sy,dx,sy);
        line(dx,sy,dx,dy);
    }
    //最後一次burst
    int sx=XdivideLen*(2+bursts-1);
    int dx=XdivideLen*(2+bursts);
    int sy=YdivideLen*(Ydivides-2-(burstTime[bursts]-normalmin)/(double)normaldiff);
    line(sx,sy,dx,sy);

    //guess line
    setcolor(LIGHTBLUE);
    for(int i=1;i<=bursts;i++){
        line(XdivideLen*(2+i-1),YdivideLen*(Ydivides-2-(guess[i-1]-normalmin)/(double)normaldiff)
             ,XdivideLen*(2+i),YdivideLen*(Ydivides-2-(guess[i]-normalmin)/(double)normaldiff));

    }

    sprintf(buf,"x:time steps, y:CPU burst and guess");
    outtextxy(10,10, buf);

    while (!kbhit())
        delay(200);
    closegraph();
}

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

    draw(guess,burstTime,bursts);
    //system("pause");
    return 0;
}

