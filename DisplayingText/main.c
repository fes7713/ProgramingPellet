#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

void Map_Import(int tableHeight, int tableWidth, char(*table)[tableWidth], char* fname)
{
    FILE* cfPtr;
    if((cfPtr = fopen(fname, "r"))== NULL)
    {
        printf("File cannot be opened");
        return;
    }
    else{
        int p = 0;
        while(fgets(table[p], 1600, cfPtr) != NULL) {
            
            p++;
        }
        fclose(cfPtr);
    }
    for(int i = 0; i < tableHeight; i++)
        for(int j = 0; j < tableWidth; j++)
            if(table[i][j] == 10)
                table[i][j] = 32;
}

void nTable_Draw(int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, int *nums, int letter_size)
{

    char string_field[1600];
    for(int i = 0; i < letter_size; i++) // 5 is letter hight
    {
        memset(string_field, 0, 1600);
        
        for(int j = 0; nums[j] != -1; j++)
            strcat(string_field, fontData[nums[j] * letter_size + i]);
        strcpy(&field[DrawFromY + i][DrawFromX], string_field);
    }
}

void Letter_Draw_Normal(int fontDataHeight, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, char* string, int letter_size)
{
    //expect font data with all numbers and alphabets with letter size of 5 and data order according to ASCII table
    for(int i = 0; i < fontDataHeight; i++)
        for(int j = 0; j < fontDataWidth; j++)
            if(fontData[i][j] == 10)
                fontData[i][j] = 0;
    
    char string_field[300];
    for(int i = 0; i < letter_size; i++) // 5 is letter hight
    {
        memset(string_field, 0, 300);
        
        for(int j = 0; string[j] != 0; j++)
            strcat(string_field, fontData[(string[j] == 32 ? 83 : (string[j] - 40)) * letter_size + i]);
        strcpy(&field[DrawFromY + i][DrawFromX], string_field);
    }
}


void printArray2(int fieldHeight, int fieldWidth, char field[fieldHeight][fieldWidth])
{
    for(int i = 0; i < fieldHeight; i++)
        for(int j = 0; j < fieldWidth; j++){
            if(field[i][j] == 0 || field[i][j] == '\n')
                field[i][j] = ' ';
            if(j == fieldWidth - 1)
                field[i][j] = 0;
        }
    for(int i = 0; i < fieldHeight; i++)
    {
        printf("%s\n", field[i]);
    }
}

int main(int argc, char **argv)
{
    char table[500][50] = {};
    char field[10][500] = {};
    char string1[200] = "Welcome to Text Displayer";
    char field_code[1700][300];
    Map_Import(500, 50, table, "font Ivrit Ext_40.txt");
    Map_Import(1700, 300, field_code, "CardGame1-9/main.c");
    Letter_Draw_Normal(500, 50, table, 500, field, 0, 0, string1, 6);
    printArray2(10, 500, field);
    while(1){
        memset(field, 0, 10 * 500);
        fgets(string1, 200, stdin);
        if(strcmp(string1, "\n") == 0)
            system("cls");
        if(strcmp(string1, "end\n") == 0)
            break;
        Letter_Draw_Normal(500, 50, table, 500, field, 0, 0, string1, 6);
        printArray2(10, 500, field);
        if(strcmp(string1, "CardGame1-9/main.c\n") == 0)
            printArray2(1700, 300, field_code);
    }
    Letter_Draw_Normal(500, 50, table, 500, field, 0, 0, string1, 6);
    printArray2(10, 500, field);
    
    getchar();
    return;
}
