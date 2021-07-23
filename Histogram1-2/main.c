#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define ROWS 51
#define COLS 25
#define TRY 5
#define LOOP 250

int maxArrayPos(double arr[], int size);
//void printArray2(char *arr, int rows, int cols);
//void printArray2(char *arr, int rows, int cols);
void printArray2(char **arr, int rows, int cols);


int main(int argc, char **argv)
{
    int frequency[TRY] = {};
    double ratioFrequency[TRY] = {};
    int p = 70;
    int fieldHeight = 21;
    int fieldWidth = 25;
    int horizontalShift = 4;
    int ColWidth = (fieldWidth - horizontalShift)/ TRY;
    char * field[21][25] = {};
    double Limit = 0.3;
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
        for(int j = 0; j < fieldHeight; j++)
        {
            for(int k = 0; k < fieldWidth; k++)
            {
                field[j][k] = " ";
            }
        }
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
        double fRatioMax = ratioFrequency[nPos];
        printAmp = fRatioMax / fieldHeight;
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
                        field[fieldHeight - 2 - j][k] = "_";
                }
            }
        }
//        
//        int counter = 1;
//        char fYAxisValue[1];
//        for(int j = fieldHeight - 2; j >= 0 ; j--)
//        {
//            if(field[j][0] == "_")
//            {
//                snprintf(fYAxisValue, 1, "%1d", counter);
//                field[j][0] = "0";
//                field[j][1] = ".";
//                field[j][2] = fYAxisValue;
//                field[j][3] = "";
//                field[j][4] = "";
//                counter++;
////                memset(fYAxisValue, 0, 1);
//            }
//        }
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
                        //field[k][j * ColWidth + w] = '*';
                        field[k][j * ColWidth + w + horizontalShift] = "*";
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
//            printf("%c", *arr);
//            *arr++;
//        }
//        printf("\n");
//    }
//}

void printArray2(char **arr, int rows, int cols)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            printf("%s", *arr);
            *arr++;
        }
        printf("\n");
    }
}