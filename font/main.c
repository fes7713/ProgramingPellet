#include <stdio.h>
#include <stdlib.h>
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

//void Asset_Icon_Draw(int IconDataWidth, char (*IconData)[IconDataWidth], int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, int Icon_Height, int letter_size, int type)
//{
//    //30 is height of icon
//    char list_Assets_Name[8][80] = {"", "Fighter", "Warship", "Advanced Fighter", "Aircraft Carrier", "Missile Base", "Naval Base", "Air Base"};
//    char print_field[80] = "Air Base";
//    sprintf(print_field, "%s",  list_Assets_Name[type]);
//    Letter_Draw_Normal(fontDataWidth, fontData, fieldWidth, field, DrawFromX, DrawFromY, print_field, letter_size);
//    for(int i = 0; i < Icon_Height; i++) 
//        memcpy(&field[DrawFromY + letter_size + i][DrawFromX], IconData[(type - 1) * Icon_Height + i], strlen(IconData[(type - 1)* Icon_Height + i]));
//}

int main(int argc, char **argv)
{
//    char table[3485][100] = {};
//    char field[100][500] = {};
//    int numarr[6] = {2, 3, 1, 5, 51, -1};
//
//    
//    Map_Import(3485, 100, table, "Cards Full Fixed.txt");
//    nTable_Draw(100, table, 500, field, 0, 0, numarr, 67);
//    printArray2(100, 500, field);
    char table[500][50] = {};
    char field[40][500] = {};
    char string1[20] = "qwertyuiop";
    char string2[20] = "asdfghjkl";
    char string3[20] = "zxcvbnm";
    char string4[20] = "29.89";
    Map_Import(500, 50, table, "font Ivrit Ext_40.txt");
//    Map_Import(500, 150, table, "font.txt");
//    Map_Import(500, 150, table, "font small slant fixed 1.txt");
//    for(int i = 0; i < 500; i++)
//        for(int j = 0; j < 150; j++)
//            if(table[i][j] == 10)
//                table[i][j] = 0;

//    for(int i = 0; i < 500; i++)
//        printf("%s", table[i]);
//    char string[80];
//    fgets(string, 80, stdin);
//    Letter_Draw_Normal(500, 150, table, 500, field, 0, 0, string1, 6);
    Letter_Draw_Normal(500, 50, table, 500, field, 0, 0, string1, 6);
    Letter_Draw_Normal(500, 50, table, 500, field, 0, 6, string2, 6);
    Letter_Draw_Normal(500, 50, table, 500, field, 0, 12, string3, 6);
    Letter_Draw_Normal(500, 50, table, 500, field, 0, 18, string4, 6);
    
    printArray2(40, 500, field);
    
    getchar();
    getchar();
    getchar();
    return;
}


//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//void Map_Import(int tableHeight, int tableWidth, char(*table)[tableWidth], char* fname)
//{
//    FILE* cfPtr;
//    if((cfPtr = fopen(fname, "r"))== NULL)
//    {
//        printf("File cannot be opened");
//        return;
//    }
//    else{
//        int p = 0;
//        while(fgets(table[p], 800, cfPtr) != NULL) {
//            p++;
//        }
//        fclose(cfPtr);
//    }
//}
//
//void Map_Import_Fix(int tableHeight, int tableWidth, char(*table)[tableWidth], char* fname, char* fname1)
//{
//    FILE* cfPtr;
//    if((cfPtr = fopen(fname, "r"))== NULL)
//    {
//        printf("File cannot be opened");
//        return;
//    }
//    FILE* cfPtr1;
//    if((cfPtr1 = fopen(fname1, "w"))== NULL)
//    {
//        printf("File cannot be opened");
//        return;
//    }
//    else{
//        int p = 0;
//        while(fgets(table[p], 800, cfPtr) != NULL) {
//            fprintf(cfPtr1, "%c%c%c%c%c%c%c%c\n", table[p][0], table[p][1], table[p][2], table[p][3], table[p][4], table[p][5], table[p][6], table[p][7]);
//            p++;
//        }
//        fclose(cfPtr);
//        fclose(cfPtr1);
//    }
//}
//
//void Letter_Draw_Italic(int fontDataHeight, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, char* string, int letter_size)
//{
//    //expect font data with all numbers and alphabets with letter size of 5 and data order according to ASCII table
//    for(int i = 0; i < fontDataHeight; i++)
//        for(int j = 0; j < fontDataWidth; j++)
//            if(fontData[i][j] == 10)
//                fontData[i][j] = 0;
//    
//    char string_field[500];
//    for(int i = 0; i < letter_size; i++) // 5 is letter hight
//    {
//        memset(string_field, 0, 500);
//        for(int p = 0; p < letter_size - i - 1; p++)
//            string_field[p] = ' ';
//        for(int j = 0; string[j] != 0; j++)
//            strcat(string_field, fontData[(string[j] == 32 ? 75 : (string[j] - 48)) * letter_size + i]);
//        strcpy(&field[DrawFromY + i][DrawFromX], string_field);
//    }
//}
//
//void Letter_Draw_Normal(int fontDataHeight, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, char* string, int letter_size)
//{
//    //expect font data with all numbers and alphabets with letter size of 5 and data order according to ASCII table
//    for(int i = 0; i < fontDataHeight; i++)
//        for(int j = 0; j < fontDataWidth; j++)
//            if(fontData[i][j] == 10)
//                fontData[i][j] = 0;
//    
//    char string_field[300];
//    for(int i = 0; i < letter_size; i++) // 5 is letter hight
//    {
//        memset(string_field, 0, 300);
//        
//        for(int j = 0; string[j] != 0; j++)
//            strcat(string_field, fontData[(string[j] == 32 ? 75 : (string[j] - 48)) * letter_size + i]);
//        strcpy(&field[DrawFromY + i][DrawFromX], string_field);
//    }
//}
//
//void printArray2(int fieldHeight, int fieldWidth, char field[fieldHeight][fieldWidth])
//{
////    for(int i = 0; i < fieldHeight; i++)
////        field[i][fieldWidth - 1] = '\0';
//    for(int i = 0; i < fieldHeight; i++)
//        for(int j = 0; j < fieldWidth; j++){
//            if(field[i][j] == 0 || field[i][j] == '\n')
//                field[i][j] = ' ';
//            if(j == fieldWidth - 1)
//                field[i][j] = 0;
//        }
//    for(int i = 0; i < fieldHeight; i++)
//    {
//        printf("%s\n", field[i]);
//    }
//}
//
//int main(int argc, char **argv)
//{
//    char table[500][50] = {};
//    char field[40][500] = {};
//    char string1[20] = "Advdadndcded";
//    char string2[20] = "ZXCVBNMqwertyuioy";
//    char string3[20] = "asdfghjklmnhytw";
//    char string4[20] = "A0  RTB";
//    Map_Import(500, 50, table, "font Ivrit.txt");
////    Map_Import(500, 150, table, "font.txt");
////    Map_Import(500, 150, table, "font small slant fixed 1.txt");
////    for(int i = 0; i < 500; i++)
////        for(int j = 0; j < 150; j++)
////            if(table[i][j] == 10)
////                table[i][j] = 0;
//
////    for(int i = 0; i < 500; i++)
////        printf("%s", table[i]);
////    char string[80];
////    fgets(string, 80, stdin);
////    Letter_Draw_Normal(500, 150, table, 500, field, 0, 0, string1, 6);
//    Letter_Draw_Normal(500, 50, table, 500, field, 100, 0, string1, 6);
//    Letter_Draw_Normal(500, 50, table, 500, field, 0, 6, string2, 6);
//    Letter_Draw_Normal(500, 50, table, 500, field, 0, 12, string3, 6);
//    Letter_Draw_Normal(500, 50, table, 500, field, 0, 18, string4, 6);
//    
//    printArray2(40, 500, field);
//
//    
//    
//    getchar();
//    getchar();
//    getchar();
//    return;
//}
//
