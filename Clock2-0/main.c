#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

void printArray2(char *arr, int rows, int cols);
void printTime();
double to_deg(double r);
double to_deg360(double run, double rise);
bool clockRegion(double p, double run, double rise);
int clockRegion_dial(double angle, int partition);
void clock_needle(int fieldHeight, int fieldWidth, char field[][fieldWidth], double angle, double length, char pen);

typedef struct{
    int Value;
    int Next;
    double Expected;
}   Axis;

Axis nY;
Axis nX;


int main(int argc, char **argv)
{
    time_t oldtm;
    time_t t = time(NULL);
    struct tm local;
    localtime_r(&t, &local);
    int startH = (local.tm_hour + 9) * 3600;
    int startM = (local.tm_min + 45) * 60;
    int startS = local.tm_sec + 45;
    
    char fieled[35][35] = {};
    int fieldHeight = 35;
    int fieldWidth = 35;
    int x_centre = fieldWidth / 2;
    int y_centre = fieldHeight / 2;
    
    int distance_centre;
    int p = 0;
    int r;

    char num[] = {'3', '4', '5', '6', '7', '8', '9', 'J', 'Q', 'K', '1', '2'};
    while(1)
    {
        p++;
        memset(fieled, 0, fieldHeight * fieldWidth);
        
        oldtm = time(NULL);

        for(int i = 0; i < fieldHeight; i++)
        {
            for(int j = 0; j < fieldWidth; j++)
            {
                double run = j - x_centre;
                double rise = i - y_centre;
                if(distance_centre = (int)hypot(rise, run) == fieldWidth / 2 - 1)
                    fieled[i][j] = '\'';

                if(distance_centre = (int)hypot(rise, run) == fieldWidth / 2)
                    fieled[i][j] = num[clockRegion_dial(to_deg360(run, rise), 12)];
            }
        }
        
        clock_needle(fieldHeight, fieldWidth, fieled, (p + startH) / 120, fieldWidth / 4, '-');
        clock_needle(fieldHeight, fieldWidth, fieled, (p + startM) / 10, fieldWidth / 2 - 2, '+');
        clock_needle(fieldHeight, fieldWidth, fieled, (p + startS) * 6, fieldWidth / 3 - 1, '*');

        printTime();
        printArray2(fieled, fieldHeight, fieldWidth);

        while (time(NULL) - oldtm < 1)
            Sleep(100);
        system("cls");
    }

	return 0;
}
double to_deg(double r) {
    return r* 180 / M_PI;
}

bool clockRegion(double p, double run, double rise)
{
    int num = ((int)p / 90) % 4;
    
    switch(num)
    {
        case 0: if(run > -2 && rise > -2) return true; else return false;
        case 1: if(run < 2 && rise > -2) return true; else return false;
        case 2: if(run < 2 && rise < 2) return true; else return false;
        case 3: if(run > -2 && rise < 2) return true; else return false;
    }
}

double to_deg360(double run, double rise)
{
    if(atan((double)rise / run) > 0)
        if(run > 0)
            return to_deg(atan((double)rise / run));
        else
            return to_deg(atan((double)rise / run)) + 180;
    else
        if(run > 0)
            return to_deg(atan((double)rise / run)) + 360;
        else
            return to_deg(atan((double)rise / run)) + 180;
}

int clockRegion_dial(double angle, int partition)
{
    angle = fmodf(angle, 360);
    for(int i = 0; i < partition; i++)
        if((double)360 / partition * i < angle && angle < (double)360 / partition * (i + 1))
            return fmodf(angle, 30) < 3.4 ? i : partition;

}

void printArray2(char *arr, int rows, int cols)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            printf("%c", *arr++);
        }
        printf("\n");
    }
}

void printTime()
{
    time_t t = time(NULL);  
    struct tm *local = localtime(&t);
    char * const wdays[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    
    printf("%04d/", local->tm_year + 1900);
    printf("%02d/", local->tm_mon + 1);
    printf("%02d", local->tm_mday);
    printf("(%03s)", wdays[local->tm_wday]);
    
    printf(" ");

    printf("%02d:", local->tm_hour);
    printf("%02d:", local->tm_min);
    printf("%02d\n", local->tm_sec);

}

void clock_needle(int fieldHeight, int fieldWidth, char field[][fieldWidth], double angle, double length, char pen)
{
    for(int i = 0; i < fieldHeight; i++)
    {
        for(int j = 0; j < fieldWidth; j++)
        {
            int x_centre = fieldWidth / 2 + 1;
            int y_centre = fieldHeight / 2 + 1;
            double run = j - x_centre;
            double rise = i - y_centre;

            if((int)hypot(rise, run) < length)
            {
                if(clockRegion(angle, run, rise)){  
                    nY.Value = rise;
                    nY.Next = rise + 1;
                    nY.Expected = tan(angle * M_PI / 180) * run;
                    nX.Value = run;
                    nX.Next = run + 1;
                    nX.Expected = rise / tan(angle * M_PI / 180);
                    if(nY.Value < nY.Expected && nY.Expected < nY.Next || nX.Value < nX.Expected && nX.Expected < nX.Next)
                        field[i][j] = pen;
                }
            }
        }
    }
}

