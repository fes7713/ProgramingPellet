#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
int Dictionary(char * str, char * arrKey, int * arrValue, int size, int sizeString);
void set1DictionaryPrint(int * arrKey, char * arrData, int size, int sizeString);
void set2DictionaryPrint(int * arrKey, char * arrData, int size, int sizeGroup, int sizeString);
void set2DictionaryPrintFormat(int * arrKey, char * arrData, char * printFormat, int size, int sizeGroup, int sizeString);
float * createArrayFloats(int size);

void printArray2(char *arr, int rows, int cols);
int main(int argc, char **argv)
{
    char string1[][4][20] = {{"Long Sword", "Dual Blade", "Long Bow", "Thor Hammer"}, {"Great Bow", "Elementary Sword", "Trapper", "Heavy Bowgun"}};
    char string2[2][20];
    char string0[5][20];
    int values[4] = {3, 1};
    char format[][20] = {"Helm", "Chest"};
    char strInput[] = "Thor Hammer";
    //char string3 = string[0];
    
    char * string1Ptr = &string1[0][0];
    char * string1Ptr1 = &string1[1][0];
    if(strcmp(string1Ptr, string1Ptr1) == 0)
    {
        printf("The same strings\n");
    }
    else{
        printf("The different strings\n");
    }
    
//    set1DictionaryPrint(values, string1, 4, 20);
    set2DictionaryPrint(values, string1, 2, 4, 20);
    set2DictionaryPrintFormat(values, string1, format, 2, 4, 20);
    
    int nNum1[5] = {1, 2, 3, 4, 5};
    int nNum2[5] = {0};
    char string03[20] = "This is a pen";
    char string04[20];
    
    memcpy(string04, string03, 20);
    memcpy(nNum2, nNum1, 5 * 4);
    memset(nNum2, -1, 5* 4);
    printf("%s\n", string04);
    for(int i = 0; i < 5; i++)
    {
        printf("%d\n", nNum2[i]);
    }
    
    printf("%f\n", (1.52 - 1.5) / 0.5);
    
    char field[5][5];
    memset(field,0 ,5*5);
    
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            field[i][j] = 'a';
        }
    }

//    for(int i = 0; i < 5; i++)
//    {
//        for(int j = 0; j < 5; j++)
//        {
//            printf("%c", field[i][j]);
//        }
//        printf("\n");
//    }
    printArray2(field, 5, 5);
    
//int result = Dictionary(strInput, string1, values, 4, 20);
//
//printf("%d\n", result);
//for(; *string1Ptr != '\0'; string1Ptr += 20)
//{
//    puts(string1Ptr);
//}
    char string05[][2] = {"a", "b"};
    char string06[2][2];
    
    strcpy(string06, "c");
    printf("%s\n", string06);
    char * string07[3];
    string07[0] = "apple";
    //malloc
    char string08[20] = "grape";
    string07[1] = string08;
//    strcpy(string07[0], "apple");
//    strcpy(string07[1], "grape");
//    strcpy(string07[2], "pine");
    //strcpy(&string07[2][1], "ale");
    //printf("%s\n%s\n%s\n", string07[0], string07[1], string07[2]);
    printf("%s\n", string07[1]);
    
    char numStr[2];
 
    double num = 0.200;
 
    sprintf(numStr, "%1.0lf", num * 10);
 
    char * numField[2];
    numField[1] = numStr;
    printf("%s\n", numField[1]);
    for(int i = 0; i < 20; i++)
    {
        printf("%d :%d\n", i + 1, (int)((float)100 / (i + 1)));
    }
    
    float * p = createArrayFloats(5);
    
    p[0] = 3.21;
    p[1] = 2.1;
    
    printf("float 0 %f", p[0]);
    
    printf("float 1 %f", p[1]);
return 0;
}

int Dictionary(char * str, char * arrKey, int * arrValue, int size, int sizeString)
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

void set1DictionaryPrint(int * arrKey, char * arrData, int size, int sizeString)
{
    char * arrDataHold = arrData;
    for(int i = 0; i < size; i++)
    {
        arrData += (*arrKey) * sizeString;
        puts(arrData);
        arrKey++;
        arrData = arrDataHold;
    }
}

void set2DictionaryPrint(int * arrKey, char * arrData, int size, int sizeGroup, int sizeString)
{
    char * arrDataHold = arrData;
    for(int i = 0; i < size; i++)
    {
        arrDataHold += sizeGroup * sizeString;
        arrData += (*arrKey) * sizeString;
        puts(arrData);
        arrKey++;
        arrData = arrDataHold;
    }
}

void set2DictionaryPrintFormat(int * arrKey, char * arrData, char * printFormat, int size, int sizeGroup, int sizeString)
{
    char * arrDataHold = arrData;
    char s[20];
    for(int i = 0; i < size; i++)
    {
        arrDataHold += sizeGroup * sizeString;
        arrData += (*arrKey) * sizeString;
        sprintf(&s, "%s :%s", printFormat,  arrData);
        puts(&s);
        arrKey++;
        printFormat += sizeString;
        arrData = arrDataHold;
    }
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

int computeAverage(int arr[], int size)
{
    int sum = 0;
    for(int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    
    return sum / (float)size;
}

float * createArrayFloats(int size)
{
    float * p = (float *)malloc(sizeof(float)* size);
    
    return p;
}
void Grid_Advanced(int fieldHeight, int fieldWidth, char (*field)[fieldWidth])
{
    char alphabets[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char numbers[30] = "0123456789";
    
    for (int i = 0; i < fieldHeight; i++)
    {
        for (int j = 0; j < fieldWidth; j++) 
        {
//            if(field[i][j] == 0)
//                continue;
            //if((field[i][j] == 32 || field[i][j] == 0) && ((i % 50 == 0) || (i % 10 == 5 && j % 20 == 11 && i % 50 != 5 && i % 50 != 45)))
            if((field[i][j] == 32 || field[i][j] == 0) && ((i % 50 == 0) || (i % 10 == 0 && j % 20 == 1)))
                field[i][j] = '_';
            //if((field[i][j] == 32 || field[i][j] == 0) && ((j % 100 == 10) || (j % 20 == 0 && i % 10 == 1 && j % 100 != 20 && j % 100 != 0)))
            if((field[i][j] == 32 || field[i][j] == 0) && ((j % 100 == 10) || (j % 20 == 10 && i % 10 == 6)))
                field[i][j] = '|';
            if(j % 20 == 0 && i % 10 == 5 && j % 100 != 20 && j % 100 != 0 && i % 50 != 5 && i % 50 != 45)
                field[i][j] = '.';
            if(i % 250 == 2 && j % 10 == 0){
                field[i][j] = alphabets[(j / 10 - 1) % 26];
                field[i][j - 1] = alphabets[(j / 260 - 1) % 26];
            }
            if(i % 5 == 0 && j % 500 == 10){
                field[i][j] = numbers[i / 5 % 10];
                field[i][j - 1] = numbers[i / 5 / 10];
            }
        }
    }
}