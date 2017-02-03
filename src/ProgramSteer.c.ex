/********************************************************/
/* PROGRAM STEER                                        */
/* (C)M.M. and K.Y. GOLDBERG                            */
/* This Numerical Control Program uses linear           */
/* interpolation to provide a flow of output            */
/* pulses which can be used to steer an xy table        */
/********************************************************/
#include<stdio.h>
#include "..\inc\Std_Types.h"

char temp1[5],temp2[5],temp3[5],temp4[5],temp5[5];
char eia[10];
int feedrate,drag,oil; /* vars dealing with feedrate and delay func. */
//int x1,y1; /* starting point */
int x2,y2; /* relative position */
//int x3,y3; /* endpoint */
int xo,yo; /* direction of output: +1, -1, or 0 */
int dX,dY; /* differentials of x and y */
//int stepnum;
int fxy; /* value of function */

int rad,radrad,f,a,b,d;

void doLine(int x1, int y1, int x3, int y3);
void setDirection(int x1, int y1, int x3, int y3);
void getdir();
void doCircle(int x1, int y1, int x3, int y3);
void delay();

int main(int argc, char *argv[])
{
    int x1,y1; /* starting point */
    int x3,y3; /* endpoint */

    printf (" STEER: A NUMERICAL CONTROL PROGRAM\n");
    printf("\nInput Command line (ie, 'GOl (0,0,10,20) 100')\n: ");
    scanf ("%s (%s, %s, %s, %s) %s", eia, temp1, temp2, temp3, temp4, temp5);
    feedrate = atoi(temp5);
    x1 = atoi(temp1);
    y1 = atoi(temp2);
    x3 = atoi(temp3);
    y3 = atoi(temp4);

    if ( !strcmp (eia, "G01") )
        doLine (x1, y1, x3, y3);
    else
        doCircle(x1, y1, x3, y3);

    return 0;
}

void doLine(int x1, int y1, int x3, int y3)
{
    //printf("\n\nFor EIA code '%s' with feedrate ~ ~d",eia,feedrate);
    //printf("\nGoing from (%d,%d) to (%d,%d):\n",x1,y1,x3,y3);
    int stepnum = x2 = y2 = fxy = 0;
    drag = 100;
    oil = 1;
    setdirection(x1,y1,x2,y2);
    printf("\nStep\tFXY\tX2\tY2\t\tXO\tYO");

    while ( (x2 != dX) || (y2 != dY)) /* at endpoint? */
    {
        delay(),
        printf("\n%d\t%d\t%d\t%d\t\t", stepnum++,fxy,x2,y2);
        if(fxy > 0)
        {
            printf("%d",xo);
            ++x2;
            fxy = fxy -dY;
        }
        else
        {
            printf("\t%d",yo);
            ++y2;
            fxy = fxy + dX;
        }
    }
}
/* sets output directions and initial fxy value */
void setDirection(int x1, int y1, int x3, int y3)
{
    dY = y3 - y1;

    if(dY < 0)  yo = -1;
    else        yo = 1;

    dY = abs(dY);
    dX = x3 - x1;

    if(dX < 0)  xo = -1;
    else        xo = 1;

    dX = abs(dX);

    fxy = dX - dY;
}

/* Circle Routine */
void doCircle(int x1, int y1, int x3, int y3)
{
    int stepnum = 0;
    x2 = x1;
    y2 = y1;
    d = x3;
    rad = y3;
    radrad = rad * rad;
    printf("\n\nFor EIA code '%s' with feedrate = %d",eia,feedrate);
    printf("\nCircling from (%d,%d) in direction %d with radius %d:", x1, y1 ,d, rad);

    printf("\nStep\tx2\ty2\tradius\tfxy\tdX\tdY\tf a b d xo yo\n");

    do
    {
        delay();
        fxy = (x2*x2) + (y2*y2) - (radrad);
        dX = 2*x2;
        dY = 2*y2;
        f = (fxy < 0) ? 0 : 1;
        a = ( dX < 0) ? 0 : 1;
        b = ( dY < 0) ? 0 : 1;

        getdir();

        printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d  %d  %d  %d  %d  %d",
                stepnum++,x2,y2,rad,fxy,dX,dY,f,a,b,d,xo,yo);

        x2 = x2 + xo;
        y2 = y2 + yo;
    }
    while((x2 != x1) || (y2 = y1));
}

/* delay loop: feedrate approx = # steps/minute */
void delay()
{

    int i; i = 0;
    while (++i != ((feedrate + drag) / 30)) continue;

    if(drag > 0)/* drag increases the delay at the beginning */
                /* to allow for inertia in machine startup */
    {
        drag = drag - (oil * oil); /* falls off exponentially */
        --oil;
        if (drag < 0)
            drag = 0;
    }
}

/* creates 'mock' binary representation of d,f,a,b */
/* and uses this to determine best output */
void getdir()
{
    static const sint8 map[2][16] =
    {
    /*xo*/  {  0, -1,  1,  0,  1,  0,  0, -1, -1,  0,  0,  1,  0,  1, -1,  0 },
    /*yo*/  { -1,  0,  0,  1,  0, -1,  1,  0,  0,  1, -1,  0,  1,  0,  0, -1 }
    };

    int binrep = 0;

    if(d) binrep = binrep + 8;
    if(f) binrep = binrep + 4;
    if(a) binrep = binrep + 2;
    if(b) binrep = binrep + 1;

    if ( binrep < sizeof(map)/sizeof(map[0]) )
    {
        xo = map[0][binrep];
        yo = map[1][binrep];
    }
}


const uint32 MIN_F = 40;
const uint32 ramp

void rampFeedrate( const uint32 stepsCount, const uint32 maxFeedrate )
{


}