#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define TRY 8
#define LOOP 250
#define DAY 1000

int maxArrayPos(double arr[], int size);
void printArray2(char *arr, int rows, int cols);
void printVarArray2(int rows, int cols, int MaxCols, char arr[][MaxCols]);
int Limit(int nNum, int limit);
long int sumArray(long int arr[], int size);
long int returnBoundary(long int lower, long int upper, long int Boundary1, long int Boundary2, long int Boundary3);

int main(int argc, char **argv)
{
    int pInfect = 5;
    int pRecovery = 4;
    int pDeath = 5;
    int pIsolate = 97;
    int pIsolateDeath = 2;
    int pIsolateRecover = 15;
    int horizontalShift = 7;
    int fieldHeight = 22;
    int fieldWidth = 50;
    char field[22][60] = {};
    double nY;
    double nYNext;
    long int nYCut;
    long int nYCut1;
    long int nYCut2;
    long int nYCut5;
    
    long int infected = 2;
    long int prevInfected;
    long int arrInfected[DAY] = {};
    long int arrNewInfected[DAY] = {};
    long int arrIsolated[DAY] = {};
    double printAmpY = 0;
    int arrDayDField[fieldWidth];
    float radius = 3;
    int nRecovered = 0;
    int nDeath = 0;
    int nIsolated = 0;
    long int Population = 10000000;
    
    long int MaxInfect = 0;
    int MaxInfectDay = 0;
    
    srand(time(NULL));
    
    for(int i = 1; i < DAY; i++)
    {
        //getchar();
        int effPopInRad = (infected - sumArray(arrIsolated, i)) * radius * (Population - nRecovered - nDeath - sumArray(arrIsolated, i)) / Population;
            //radius /= 1.002;
            //radius = radius / (1.001 * exp(1 / (i * 20000 + 1)));
            //radius = radius * exp(0.001 / (i * i + 1)) * exp(0.02 / (20 + i * i)) / exp(0.02 /(200 + i * i)) / exp(0.20 /(400 + i)) / exp(4 / (1000 + i));
//            radius *= 1.002;
//            radius = radius * exp(0.007 / (i * i + 1)) * exp(0.12 / (20 + i * i)) / exp(0.02 /(200 + i * i)) / exp(0.4 /(800 + i)) / exp(5 / (1200 + i));
        
//            radius *= 1.004;a
//            radius = radius * exp(0.002 / (i + 1)) * exp(0.12 / (20 + i * i)) / exp(0.02 /(200 + i * i)) / exp(0.6 /(300 + i));
     
        //int effPopInRad = Limit((int)(radius * (infected - sumArray(arrIsolated, i))), Population - nRecovered - infected - nDeath - sumArray(arrIsolated, i));
        
        
        double printAmpX = fieldWidth / (double)i;
        
        int sum = sumArray(arrIsolated, i);
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

//Recovery
        for(int j = 0; j < infected - sumArray(arrIsolated, i); j++)
        {
            if(rand() % 1000 < pRecovery)
            {
                infected--;
                nRecovered++;
            }
        }
        
//Death
        for(int j = 0; j < infected - sumArray(arrIsolated, i); j++)
        {
            if(rand() % 10000 < pDeath)
            {
                infected--;
                nDeath++;
            }
        }
//Isolated
        for(int j = 0; j < i - 10; j++)
        {
            for(int k = 0; k < arrNewInfected[j]; k++)
            {
                if(rand() % 100 < pIsolate)
                {
                    arrNewInfected[j]--;
                    arrIsolated[j]++;
                }
            }
        }
//Isolated Death
        for(int j = 0; j < i; j++)
        {
            for(int k = 0; k < arrIsolated[j]; k++)
            {
                if(rand() % 10000 < pIsolateDeath)
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
        
        arrInfected[i - 1] = infected;
        
        if(infected <= 0)
            break;
    
        
        
        
//Day calculation
        memset(arrDayDField, 0, fieldWidth * sizeof(int));
        for(int j = 0; j < (i < fieldWidth ? i : fieldWidth); j++)
        {
            if(i < fieldWidth)
                arrDayDField[j] = j;
            else
                arrDayDField[j] = (int)(round(i / (double)(fieldWidth - 1) * j)); 
        }
        
//Preperration of Writing(printAmp, horizontalShift, MaxInfected, 
        if(printAmpY < arrInfected[i - 1] / (double)fieldHeight){
            printAmpY = arrInfected[i - 1] / (double)fieldHeight;
            MaxInfect = arrInfected[i - 1];
            MaxInfectDay = i;
        }
        else{
            if(infected < sumArray(arrIsolated, i))
                infected = sumArray(arrIsolated, i);
        }
        
        horizontalShift = (int)(log10(MaxInfect)) + 1;
        
        memset(field, 0, fieldHeight * (fieldWidth + 10));

//Grid writing
        for(int j = 0; j < fieldHeight; j++)
        {
            
            nY = printAmpY * j;
            nYNext = printAmpY * (j + 1);
            nYCut1 = pow(10, floor(log10(nY)) + 1);
            nYCut2 = pow(10, floor(log10(nY / 2)) + 1) * 2;
            nYCut5 = pow(10, floor(log10(nY / 5)) + 1) * 5;
            nYCut = returnBoundary(nY, nYNext, nYCut1, nYCut2, nYCut5);
            if(nYCut > 0)
                //if(log10(nY) < floor(log10(nY)) + 1 && floor(log10(nY)) < log10(nYNext))
            {
//y Axis scale writing
                for(int k = 0; k < fieldWidth + horizontalShift; k++)
                {
                    if(k == 0)
                    {
                        char yAxisValue[horizontalShift];
                        snprintf(yAxisValue, horizontalShift, "%-4ld", nYCut);
                        strncpy(&field[fieldHeight - 2 - j][0], yAxisValue, horizontalShift);
                    }
                    if(k > horizontalShift)
                        field[fieldHeight - 2 - j][k] = '_';

                }
            }
            field[fieldHeight - 3 - j][horizontalShift] = '|';
        }
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
                    field[k][j + horizontalShift] = '*';
                    
                }
//                if(field[fieldHeight - 3][j + horizontalShift] != '*' && infected > 0)
//                        field[fieldHeight - 3][j + horizontalShift] = '*';
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


        
        system("cls");
         
        printf("Day %3d\n", i);
        printf("printAmpY %7.2lf\n", printAmpY);
        printf("Infected : %d (Day Ratio %.2lf) Recovery : %d(%f) Death : %ld(%f) Isolated : %d (%f)\n", 
            infected, (double)infected / prevInfected, nRecovered, nRecovered / (float)Population,  nDeath, nDeath / (float)nRecovered, sumArray(arrIsolated, i), sumArray(arrIsolated, i) / (float)infected);
        printf("Max infection : %d (Day %d)\n", MaxInfect, MaxInfectDay);
        prevInfected = infected;
        
        //printArray2(field, fieldHeight, fieldWidth + 10);
        printVarArray2(fieldHeight, fieldWidth + 10, fieldWidth + 10, field);
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

void printVarArray2(int rows, int cols, int MaxCols, char arr[][MaxCols])
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            printf("%c", arr[i][j]);
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

long int returnBoundary(long int lower, long int upper, long int Boundary1, long int Boundary2, long int Boundary3)
{
    if(lower < Boundary1 && Boundary1 < upper)
        return Boundary1;
    if(lower < Boundary2 && Boundary2 < upper)
        return Boundary2;
    if(lower < Boundary3 && Boundary3 < upper)
        return Boundary3;
    return 0;
}