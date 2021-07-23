#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define TRY 8
#define LOOP 250

int maxArrayPos(double arr[], int size);
void printArray2(char *arr, int rows, int cols);

int main(int argc, char **argv)
{
    int frequency[TRY] = {};
    double ratioFrequency[TRY] = {};
    int p = 20;
    int fieldHeight = 22;
    int fieldWidth = 50;
    int horizontalShift = 4;
    int ColWidth = (fieldWidth - horizontalShift)/ TRY;
    char  field[22][50] = {};
    double Limit = 0.5;
    double nY;
    double nYNext;
    double nYCut;
    
    srand(time(NULL));
    
    for(int i = 0; i < LOOP; i++)
    {
        //getchar();
        system("cls");
        int success = 0;
        double printAmp;
        memset(field, 0, fieldHeight * fieldWidth);
//Probability simulation
        for(int j = 0; j < TRY; j++)
        {
            if(rand() % 100 < p)
            {
                success++;
            }
        }
        frequency[success]++;

//Ration convertion
        for(int j = 0; j < TRY; j++)
        {
            ratioFrequency[j] = frequency[j] / (double)(i+1);
        }

//Max Limit setting
        int nPos = maxArrayPos(ratioFrequency, TRY);
        printAmp = ratioFrequency[nPos] / fieldHeight;

//Grid writing
        for(int j = 0; j < fieldHeight - 2; j++)
        {
            for(int k = 0; k < fieldWidth; k++)
            {
                nY = printAmp * j;
                nYNext = printAmp * (j + 1);
                //nYCut = (int)(nY * 10) / (double)10 + 0.1;
                nYCut = floor(nY * 10) / 10 + 0.1;
                if(nY < nYCut && nYCut < nYNext)
                {
                    if(k > horizontalShift)
                        field[fieldHeight - 3 - j][k] = '_';
                        
//y Axis scale writing
                    if(k == 0)
                    {
                        char yAxisValue[horizontalShift];
                        snprintf(yAxisValue, horizontalShift, "%4.1lf", nYCut);
                        strncpy(&field[fieldHeight - 3 - j][0], yAxisValue, horizontalShift);
                    }
                }
            }
            field[fieldHeight - 3 - j][horizontalShift] = '|';
        }

//x Axis scale writing
        for(int j = 0; j < fieldWidth; j++)
        {
            field[fieldHeight - 2][j] = '_';
            if(j % ColWidth ==  (int)(ColWidth / 2) )
            {
                char xAxisValue[1];
                snprintf(xAxisValue, 1, "%1d", j / ColWidth);
                strncpy(&field[fieldHeight - 1][j], xAxisValue, 1);
            }
        }

//Field writing
        for(int j = 0; j < TRY; j++)
        {
                for(int k = fieldHeight - 3; k > fieldHeight - 3 - (int)(ratioFrequency[j] / printAmp); k--)
                //for(int k = 0; k < (int)(ratioFrequency[j] / printAmp); k++)
                {
                    for(int w = 0; w < ColWidth; w++)
                    {
                        if(w == 0 || w == ColWidth)
                        {
                            continue;
                        }
                        field[k][j * ColWidth + w + horizontalShift] = '*';
                    }
                    
                }
            
            
        }
//        for(int j = 0; j < TRY; j++)
//        {
//            for(int k = fieldHeight - 1; k > fieldHeight - 1 - (int)(ratioFrequency[j] / printAmp); k--)
//            {
//                field[k][j] = '*';
//            }
//        }
        
        
        printf("No of Try %3d\n", i);
        printArray2(field, fieldHeight, fieldWidth);
    }
    return 0;
}

int maxArrayPos(double arr[], int size)
{
    double nMax = arr[0];
    int nMaxPos = 0;
    for(int i = 1; i < size; i++)
    {
        if(nMax < arr[i])
        {
            nMax = arr[i];
            nMaxPos = i;
        }
    }
    return nMaxPos;
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