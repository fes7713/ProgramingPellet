#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define TRY 8
#define LOOP 250
#define DAY 600

int maxArrayPos(double arr[], int size);
void printArray2(char *arr, int rows, int cols);
int Limit(int nNum, int limit);
long int sumArray(long int arr[], int size);

int main(int argc, char **argv)
{
    int pInfect = 20;
    int pRecovery = 4;
    int pDeath = 2;
    int pIsolate = 98;
    int pIsolateDeath = 1;
    int pIsolateRecover = 15;
    int horizontalShift = 4;
    int fieldHeight = 22;
    int fieldWidth = 50;
    char field[22][50] = {};
    double nY;
    double nYNext;
    double nYCut;
    
    long int infected = 10;
    long int arrInfected[DAY] = {};
    long int arrNewInfected[DAY] = {};
    long int arrIsolated[DAY] = {};
    double printAmpY = 0;
    int arrDayDField[fieldWidth];
    float radius = 3;
    int nRecovered = 0;
    int nDeath = 0;
    int nIsolated = 0;
    long int Population = 70000000;
    
    long int MaxInfect = 0;
    int MaxInfectDay = 0;
    
    srand(time(NULL));
    
    for(int i = 0; i < DAY; i++)
    {
        //getchar();

        if(infected % 500 == 0)
        {
            radius /= 1.01;
        }
        int effPopInRad = Limit((int)(radius * (infected - sumArray(arrIsolated, i + 1))), Population - nRecovered - infected - nDeath);
        if(printAmpY < infected / (double)fieldHeight){
            printAmpY = infected / (double)fieldHeight;
            MaxInfect = infected;
            MaxInfectDay = i;
        }
        double printAmpX = fieldWidth / (double)i;

//Probability simulation
//Infection
        for(int j = 0; j < effPopInRad; j++)
        {
            if(rand() % 100 < pInfect)
            {
                infected++;
                arrNewInfected[i]++;
            }
        }
        arrInfected[i] = infected;
        
//Recovery
        for(int j = 0; j < infected - sumArray(arrIsolated, i + 1); j++)
        {
            if(rand() % 1000 < pRecovery)
            {
                infected--;
                nRecovered++;
            }
        }
        
//Death
        for(int j = 0; j < infected; j++)
        {
            if(rand() % 1000 < pDeath)
            {
                infected--;
                nDeath++;
            }
        }
//Isolated
        for(int j = 0; j < i - 2; j++)
        {
            for(int k = 0; k < arrNewInfected[j]; k++)
            {
                if(rand() % 100 < pIsolate)
                {
                    arrNewInfected[j]--;
                    arrIsolated[i]++;
                }
            }
        }
//Isolated Death
        for(int j = 0; j < i; j++)
        {
            for(int k = 0; k < arrIsolated[j]; k++)
            {
                if(rand() % 1000 < pIsolateDeath)
                {
                    arrIsolated[j]--;
                    infected--;
                    nDeath++;
                }
            }
        }
//Isolated Recovered
        for(int j = 0; j < i; j++)
        {
            for(int k = 0; k < arrIsolated[j]; k++)
            {
                if(rand() % 1000 < pIsolateRecover)
                {
                    arrIsolated[j]--;
                    infected--;
                    nRecovered++;
                }
            }
        }
        if(infected == 0)
            break;
    
        system("cls");
         
        printf("Day %3d\n", i);
        printf("printAmpY %7.2lf\n", printAmpY);
        printf("Infected : %d Recovery : %d Death : %ld Isolated : %d\n", infected, nRecovered, nDeath,  sumArray(arrIsolated, i + 1));
        printf("Max infection : %d (Day %d)\n", MaxInfect, MaxInfectDay);
        
        
//Day calculation
        memset(arrDayDField, 0, fieldWidth * sizeof(int));
        for(int j = 0; j < (i < fieldWidth ? i : fieldWidth); j++)
        {
            if(i < fieldWidth)
                arrDayDField[j] = j;
            else
                arrDayDField[j] = (int)(round(i / (double)fieldWidth * j)); 
        }


//Grid writing
//        for(int j = 0; j < fieldHeight - 2; j++)
//        {
//            for(int k = 0; k < fieldWidth; k++)
//            {
//                nY = printAmpY * j;
//                nYNext = printAmpY * (j + 1);
//                nYCut = pow(10, floor(log10(nY)) + 1);
//                
//                if(nY < nYCut && nYCut < nYNext)
//                {
//                    if(k > horizontalShift)
//                        field[fieldHeight - 3 - j][k] = '_';
//                        
////y Axis scale writing
//                    if(k == 0)
//                    {
//                        char yAxisValue[horizontalShift];
//                        snprintf(yAxisValue, horizontalShift, "%4.1lf", nYCut);
//                        strncpy(&field[fieldHeight - 3 - j][0], yAxisValue, horizontalShift);
//                    }
//                }
//            }
//            field[fieldHeight - 3 - j][horizontalShift] = '|';
//        }

//x Axis scale writing
//        for(int j = 0; j < fieldWidth; j++)
//        {
//            field[fieldHeight - 2][j] = '_';
//            double nXCut = fmodf(arrDayDField[j], 50) * 50 + 50;
//            if(i < 50 ? j % 5 == 0 : arrDayDField[j] < nXCut && nXCut < arrDayDField[j + 1])
//            {
//                char xAxisValue[3];
//                snprintf(xAxisValue, 1, "%3d", i);
//                strncpy(&field[fieldHeight - 1][j], xAxisValue, 3);
//            }
//        }

//Field writing
        //for(int j = 0; j < (i < fieldWidth ? i : fieldWidth); j++)
        memset(field, 0, fieldHeight * (fieldWidth));
        
//        for(int j = 0; j < fieldHeight; j++)
//        {
//            for(int k = 0; k < fieldWidth; k++)
//            {
//                field[j][k] = 'a';
//            }
//        }
        for(int j = 0; j < (i < fieldWidth ? i : fieldWidth); j++)
        {
                for(int k = fieldHeight - 3; k > fieldHeight - 3 - (int)((arrInfected[arrDayDField[j]]) / printAmpY) ; k--)
                //for(int k = 0; k < (int)(ratioFrequency[j] / printAmpY); k++)
                {
                    field[k][j] = '*';
                    
                }
                if(field[fieldHeight - 3][j] != '*' && infected > 0)
                        field[fieldHeight - 3][j] = '*';
        }
        
//        for(int j = 0; j < (i < fieldWidth ? i : fieldWidth); j++)
//        {
//                for(int k = fieldHeight - 3 - (int)(arrInfected[arrDayDField[j]] / printAmpY); k > fieldHeight - 3 - (int)((arrInfected[arrDayDField[j]] + arrIsolated[arrDayDField[j]]) / printAmpY) ; k--)
//                //for(int k = 0; k < (int)(ratioFrequency[j] / printAmpY); k++)
//                {
//                    field[k][j] = '+';
//                    
//                }
//        }
//        for(int j = 0; j < TRY; j++)
//        {
//            for(int k = fieldHeight - 1; k > fieldHeight - 1 - (int)(ratioFrequency[j] / printAmpY); k--)
//            {
//                field[k][j] = '*';
//            }
//        }
        
        
        
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

int Limit(int nNum, int limit)
{
    if(nNum > limit)
    {
        return limit;
    }
    return nNum;
}

//for (int i = 0; i < ROWS; i++)
//            for (int j = 0; j < COLS; j++) {
//                if (fmodf(i, nYPrecision * nYGridDens) == 0)
//                    field[i][j] = '_';
//                if (fmodf(j, (nXPrecision * nXGridDens)) == 0)
//                    field[i][j] = '|';
//            }

long int sumArray(long int arr[], int size)
{
    long int sum = 0;
    for(int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    
    return sum;
}