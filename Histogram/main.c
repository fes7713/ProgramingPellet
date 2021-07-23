#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define ROWS 51
#define COLS 25
#define TRY 5
#define LOOP 250

int maxArrayPos(double arr[], int size);
//void printArray2(char *arr, int rows, int cols);
void printArray2(char *arr, int rows, int cols);
int main(int argc, char **argv)
{
    int frequency[TRY] = {};
    double ratioFrequency[TRY] = {};
    int p = 70;
    int fieldHeight = 21;
    int fieldWidth = 21;
    int ColWidth = fieldWidth / TRY;
    char * field[21][21] = {};
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
        double printAmp; //= Limit / fieldHeight;
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
        //if(ratioFrequency[nPos] > Limit)
        //{
            printAmp = ratioFrequency[nPos] / fieldHeight;
        //}
        
//Field writing
//        for(int j = 0; j < TRY; j++)
//        {
//            for(int w = 0; w < ColWidth; w++)
//            {
//                for(int k = fieldHeight - 1; k > fieldHeight - 1 - (int)(ratioFrequency[j] / printAmp); k--)
//                {
//                    field[k][j * ColWidth + w] = '*';
//                }
//            }
//            
//        }
        for(int j = 0; j < fieldHeight - 1; j++)
        {
            for(int k = 0; k < fieldWidth; k++)
            {
                nY = printAmp * j;
                nYNext = printAmp * (j + 1);
                //nYCut = (int)(nY * 10) / (double)10 + 0.1;
                nYCut = floor(nY * 10) / 10 + 0.1;
                if(nY < nYCut && nYCut < nYNext)
                {
                    //strcpy(field[fieldHeight - 2 - j][k][0], "_");
                    field[fieldHeight - 2 - j][k] = "_";

                }
            }
        }
        
        for(int j = 0; j < TRY; j++)
        {
            
                for(int k = fieldHeight - 2; k > fieldHeight - 2 - (int)(ratioFrequency[j] / printAmp); k--)
                //for(int k = 0; k < (int)(ratioFrequency[j] / printAmp); k++)
                {
                    for(int w = 0; w < ColWidth; w++)
                    {
                        if(w == 0 || w == ColWidth)
                        {
                            continue;
                        }
                        //strcpy(field[k][j * ColWidth + w][0], "*");
                        field[k][j * ColWidth + w] = "*";
                    }
                    
                }
            
            
        }
//        for(int j = 0; j < 20; j++)
//        {
//            for(int r = 0; r < 6; r++)
//            {
//                printf("a");
//            }
//            printf("\n");
//        }
        
//        for(int j = 0; j < TRY; j++)
//        {
//            for(int k = fieldHeight - 1; k > fieldHeight - 1 - (int)(ratioFrequency[j] / printAmp); k--)
//            {
//                field[k][j] = '*';
//            }
//        }
        
        
        printf("No of Try %3d\n", i);
        
        for(int j = 0; j < TRY; j++)
        {
            printf("%-3d", j + 1); 
            for(int k = 0; k < (int)(ratioFrequency[j] / printAmp); k++)
            {
                printf("*");
            }
            printf("\n");
        }
        
            
        printArray2(field, fieldHeight, fieldWidth);
            
//        for(int i = 0; i < TRY; i++)
//        {
//            printf("%-3d", i + 1); 
//            for(int j = 0; j < frequency[i]; j++)
//            {
//                printf("*");
//            }
//            printf("\n");
//        }
//        getchar();
    }
    
//    for(int i = 0; i < TRY; i++)
//    {
//        printf("%-3d", i); 
//        for(int j = 0; j < frequency[i]; j++)
//        {
//            printf("*");
//        }
//        printf("\n");
//    }
    getchar();
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

//void printArray2(char *arr, int rows, int cols)
//{
//    for(int i = 0; i < rows; i++)
//    {
//        for(int j = 0; j < cols; j++)
//        {
//            printf("%s", *arr++);
//        
//        }
//        printf("\n");
//    }
//}

void printArray2(char *arr, int rows, int cols)
{
    int nLen = sizeof(char *);
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            printf("%s", *arr);
            arr += nLen;
        }
        
        printf("\n");
    }
}