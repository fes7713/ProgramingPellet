#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
    
float Dictionary(char * str, char * arrKey, float * arrValue, int size, int sizeString)
{
    for(int i = 0; i < size; i++)
    {
        if(strcmp(str, arrKey) != 0)
        {
            arrKey += sizeString;
            arrValue++;
            continue;
        }
        return *arrValue;
    }
}

void set2DictionaryPrintFormat(int * arrKey, char * arrData, char * printFormat, int size, int sizeGroup, int sizeString)
{
    char * arrDataHold = arrData;
    char s[100];
    for(int i = 0; i < size; i++)
    {
        arrDataHold += sizeGroup * sizeString;
        arrData += (*arrKey) * sizeString;
        sprintf(&s, "%s  %s", printFormat,  arrData);
        puts(&s);
        arrKey++;
        printFormat += sizeString;
        arrData = arrDataHold;
    }
}
int sumDataDictionary2(int sizeLevel, int arrLevel[], int sizeDataList, int dataList[][sizeDataList])
{
    int sum = 0;
    for(int i = 0; i < sizeLevel; i++)
    {
        sum += dataList[i][arrLevel[i]];
    }
    return sum;
}
int sumDataDictionary23(int sizeLevelRows, int sizeLevelCols, int arrLevel[][sizeLevelCols], int sizeDataList, int dataList[sizeLevelRows][sizeLevelCols][sizeDataList])
{
    int sum = 0;
    for(int i = 0; i < sizeLevelRows; i++)
    {
        for(int j = 0; j < sizeLevelCols; j++)
        {
            if(arrLevel[i][j] > 0)
            {
                sum += dataList[i][j][arrLevel[i][j] - 1];
            }
        }
    }
    return sum;
}

int sumDataDictionary24(int sizeLevelRows, int sizeLevelCols, int arrLevel[][sizeLevelCols],int Selector, int sizeDataList, int dataList[sizeLevelRows][sizeLevelCols][Selector][sizeDataList], int nSelector)
{
    int sum = 0;
    for(int i = 0; i < sizeLevelRows; i++)
    {
        for(int j = 0; j < sizeLevelCols; j++)
        {
            if(arrLevel[i][j] > 0)
            {
                sum += dataList[i][j][nSelector][arrLevel[i][j] - 1];
            }
        }
    }
    return sum;
}

//if values in arrNum exceed arrLimit, modify arrNum and set it to value of limit, and output sum of exceeded values.
int maxLimit1Ptr(int *arrNum, int *arrLimit, int size)
{
    int nRemain = 0;
        for(int i = 0; i < size; i++)
        {
            if(*arrNum > *arrLimit)
            {
                nRemain += *arrNum - *arrLimit;
                *arrNum = *arrLimit;
            }
            arrNum ++;
            arrLimit ++;
        }
    
    return nRemain;
}

//if values in arrNum exceed arrLimit, modify arrNum and set it to value of limit, and output sum of exceeded values.
int maxLimit2Ptr(int *arrNum, int *arrLimit, int rows, int cols)
{
    int nRemain = 0;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(*arrNum > *arrLimit)
            {
                nRemain += *arrNum - *arrLimit;
                *arrNum = *arrLimit;
            }
            arrNum ++;
            arrLimit ++;
        }
    }
    return nRemain;
}

//initialize arrNum with arrOriginal.
void initializer2Ptr(int *arrNum, int *arrOriginal, int rows, int cols)
{
     for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            *arrNum = *arrOriginal;
            arrNum ++;
            arrOriginal ++;
        }
    }
}

int printArray2(int *p, int rows, int cols)
{
    if(rows == 0)
    {
        return;
    }
    
    for(int i = 0; i < cols; i++)
    {
        printf("%d ", p[i]);
    }
    printf("\n");
    
    return printArray2(p + cols, rows - 1, cols);
}

//Range input from 0 to infinity.
int Positive(int nNum)
{
    if(nNum < 0)
    {
        return 0;
    }
    return nNum;
}

//Range input from -infinity to 100.
int Limit100(int nNum)
{
    if(nNum > 100)
    {
        return 100;
    }
    return nNum;
}

//Add values in arrAdd to arrNum and modify arrNum.
void AddArray(int * arrNum, int * arrAdd, int rows, int cols)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            *arrNum += *arrAdd;
            arrNum++;
            arrAdd++;
        }
    }
}

//Comapre two 2D arrays and if they are identical, output true.
bool CompareArray2(int * arrNum1, int * arrNum2, int rows, int cols)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(*arrNum1 != *arrNum2)
            {
                return false;
            }
            arrNum1++;
            arrNum2++;
        }
    }
    return true;
}

//Comapre two 2D arrays and if first array does not exceed second array output true.
bool CompareLimitArray2(int * arrNum1, int * arrLimit, int rows, int cols)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(*arrNum1 > *arrLimit)
            {
                return false;
            }
            arrNum1++;
            arrLimit++;
        }
    }
    return true;
}

//Comapre two 1D arrays and output true if they are identical.
bool CompareArray(int * arrNum1, int * arrNum2, int size)
{
    for(int i = 0; i < size; i++)
    {
        if(*arrNum1 != *arrNum2)
        {
                return false;
        }
        arrNum1++;
        arrNum2++;
    }
    return true;
}

// if arrNum exceeds arrLimit, calculate arrNum - arrLimit 
int OverLimit(int num, int nLimit)
{
    if(num > nLimit)
    {
        return num - nLimit;
    }
    return num;
}

void ConstInitializer1Ptr(float *arrNum, float Constant, int size)
{
    for(int i = 0; i < size; i++)
    {
        arrNum[i] = Constant;
    }
}

void ConstInitializer2Ptr(int *arrNum, int nVal, int rows, int cols)
{
     for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            *arrNum = nVal;
            arrNum ++;
        }
    }
}

void ConstInitializer3Ptr(int *arrNum, int nVal, int height, int rows, int cols)
{
     for(int i = 0; i < cols; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            for(int k = 0; k < cols; k++)
            {
                *arrNum = nVal;
                arrNum ++;
            }
        }
    }
}

void swap(float * nNum1, float * nNum2)
{
    int temp = *nNum1;
    *nNum1 = *nNum2;
    *nNum2 = temp;
}

void swapArray1(int * arrNum1, int * arrNum2, int size)
{
    for(int i = 0; i < size; i++)
    {
        int temp = arrNum1[i];
        arrNum1[i] = arrNum2[i];
        arrNum2[i] = temp;
    }
}

void swapArray2(int * arrNum1, int * arrNum2, int rows, int cols, int * temp)
{
//    int * pHold = (int*)malloc(rows * cols * sizeof(int));
//    for(int i = 0; i < rows; i++)
//    {
//        for(int j = 0; j < cols; j++)
//        {
//            float temp = *arrNum1;
//            *arrNum1 = *arrNum2;
//            *arrNum2 = temp;
//            arrNum1++;
//            arrNum2++;
//        }
//    }
    memcpy(temp, arrNum1, rows * cols * sizeof(int));
    memcpy(arrNum1, arrNum2, rows * cols * sizeof(int));
    memcpy(arrNum2, temp, rows * cols * sizeof(int));

}

void RankingWithHistory11(int RankingInput, int HistoryInput, int * RankingArr, int * HistoryArr, int size)
{
    if(RankingInput > RankingArr[0])
    {
        RankingArr[0] = RankingInput;
        HistoryArr[0] = HistoryInput;
        
        for(int i = 0; i < size - 1; i++)
        {
            if(RankingArr[i] > RankingArr[i + 1])
            {
                swap(&RankingArr[i], &RankingArr[i + 1]);
                swap(&HistoryArr[i], &HistoryArr[i + 1]);
            }
            else{
                break;
            }
        }
    }
}

void RankingWithHistory13(int size, int rows, int cols, float RankingInput, int HistoryInput[][cols], float RankingArr[], int HistoryArr[][rows + 1][cols], int * temp)
{
    if(RankingInput > RankingArr[0])
    {
        RankingArr[0] = RankingInput;
        //initializer2Ptr(HistoryArr[0], HistoryInput, rows + 1, cols);
        memcpy(HistoryArr[0], HistoryInput, (rows + 1) * cols * sizeof(int));
        
        for(int i = 0; i < size - 1; i++)
        {
            if(RankingArr[i] > RankingArr[i + 1])
            {
                swap(&RankingArr[i], &RankingArr[i + 1]);
                swapArray2(&HistoryArr[i], &HistoryArr[i + 1], rows + 1, cols, temp);
            }
            else{
                break;
            }
        }
    }
}

int findNumArray(int numArray[], int numFind, int size)
{
    for(int i = 0; i < size; i++)
    {
        if(numArray[i] == numFind)
        {
            return 1;
        }
    }
    return 0;
}

int ifSame(int input, int CompareWith)
{
    if(input == CompareWith)
    {
        return 1;
    }
    return 0;
}