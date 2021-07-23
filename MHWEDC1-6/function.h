#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
float Dictionary(char * str, char * arrKey, float * arrValue, int size, int sizeString);
void set2DictionaryPrintFormat(int * arrKey, char * arrData, char * printFormat, int size, int sizeGroup, int sizeString);
int sumDataDictionary2(int sizeLevel, int arrLevel[], int sizeDataList, int dataList[][sizeDataList]);
int sumDataDictionary23(int sizeLevelRows, int sizeLevelCols, int arrLevel[][sizeLevelCols], int sizeDataList, int dataList[sizeLevelRows][sizeLevelCols][sizeDataList]);
int sumDataDictionary24(int sizeLevelRows, int sizeLevelCols, int arrLevel[][sizeLevelCols],int Selector, int sizeDataList, int dataList[sizeLevelRows][sizeLevelCols][Selector][sizeDataList], int nSelector);
int maxLimit1Ptr(int *arrNum, int *arrLimit, int size);
int maxLimit2Ptr(int *arrNum, int *arrLimit, int rows, int cols);
void initializer2Ptr(int *arrNum, int *arrOriginal, int rows, int cols);
int printArray2(int *p, int rows, int cols);
int Positive(int nNum);
int Limit100(int nNum);
void AddArray(int * arrNum, int * arrAdd, int rows, int cols);
bool CompareLimitArray2(int * arrNum1, int * arrLimit, int rows, int cols);
bool CompareArray2(int * arrNum1, int * arrNum2, int rows, int cols);
bool CompareArray(int * arrNum1, int * arrNum2, int size);
int OverLimit(int num, int nLimit);
void ConstInitializer1Ptr(float *arrNum, float Constant, int size);
void ConstInitializer2Ptr(int *arrNum, int nVal, int rows, int cols);
void ConstInitializer3Ptr(int *arrNum, int nVal, int height, int rows, int cols);
void swap(float * nNum1, float * nNum2);
void swapArray1(int * arrNum1, int * arrNum2, int size);
void swapArray2(int * arrNum1, int * arrNum2, int rows, int cols, int * temp);
void RankingWithHistory11(int RankingInput, int HistoryInput, int * RankingArr, int * HistoryArr, int size);
void RankingWithHistory13(int size, int rows, int cols, float RankingInput, int HistoryInput[][cols], float RankingArr[], int HistoryArr[][rows][cols], int * temp);
int findNumArray(int numArray[], int numFind, int size);
int ifSame(int input, int CompareWith);