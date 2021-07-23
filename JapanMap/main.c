#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
void Grid_Rough(int fieldHeight, int fieldWidth, char (*field)[fieldWidth])
{
    for (int i = 0; i < fieldHeight; i++)
    {
        for (int j = 0; j < fieldWidth; j++) 
        {
            if(i % 50 == 0)
                field[i][j] = '_';
            if(j % 100 == 10)
                field[i][j] = '|';
        }
    }
}

void Grid_Normal(int fieldHeight, int fieldWidth, char (*field)[fieldWidth])
{
    for (int i = 0; i < fieldHeight; i++)
    {
        for (int j = 0; j < fieldWidth; j++) 
        {
            if(i % 10 == 0)
                field[i][j] = '_';
            if(j % 20 == 10)
                field[i][j] = '|';
        }
    }
}

void Grid_Simple(int fieldHeight, int fieldWidth, int X_Start, int Y_Start, char (*field)[fieldWidth])
{
    char alphabets[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char numbers[30] = "0123456789";
    
    for (int i = 0; i < fieldHeight; i++)
    {
        if(i % 10 == 0){
            field[i][12] = '_';
        }
        field[i][11] = '|';  
        for (int j = 0; j < fieldWidth; j++) 
        {
            if(i == 2)
                field[i][j] = '_';
            if(j % 20 == 0 && (i == 1 || i == 3))
                field[i][j] = '|';
            if(j % 20 == 0 && i % 10 == 5)
                field[i][j] = '.';
            if(i == 2 && j % 10 == 0){
                field[i][j] = alphabets[((j + X_Start) / 10 - 1) % 26];
                field[i][j - 1] = alphabets[((j + X_Start) / 260 - 1) % 26];
            }
            if(i % 5 == 0 && j == 10){
                field[i][j] = numbers[(i + Y_Start) / 5 % 10];
                field[i][j - 1] = numbers[(i + Y_Start) / 5 / 10];
            }
        }
    }
}

//void Grid_Advanced(char *field, int fieldHeight, int fieldWidth)
//{
//    char alphabets[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//    char numbers[30] = "0123456789";
//    
//    for (int i = 0; i < fieldHeight; i++)
//    {
//        for (int j = 0; j < fieldWidth; j++) 
//        {
//            if((i % 10 == 0) || (i % 10 == 5 && j % 20 == 11))
//                *field = '_';
//            if((j % 20 == 10) || (j % 20 == 0 && i % 10 == 1))
//                *field = '|';
//            if(j % 20 == 0 && i % 10 == 5)
//                *field = '.';
//            if(i == 2 && j % 10 == 0)
//                //field[2 * fieldWidth + (i+1) * 10] = alphabets[i];
//                *field = alphabets[(j / 10 - 1) % 26];
//            if(i == 2 && j % 10 == 9)
//                *field = alphabets[(j / 260 - 1) % 26];
//            if(i % 5 == 0 && j == 10)
//                *field = numbers[i / 5 % 10];
//            if(i % 5 == 0 && j == 9)
//                *field = numbers[i / 5 / 10];
//            field++;
//        }
//    }
//}

//void Grid_Advanced(int fieldHeight, int fieldWidth, char (*field)[fieldWidth])
//{
//    char alphabets[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//    char numbers[30] = "0123456789";
//    
//    for (int i = 0; i < fieldHeight; i++)
//    {
//        for (int j = 0; j < fieldWidth; j++) 
//        {
////            if(field[i][j] == 0)
////                continue;
//            //if((field[i][j] == 32 || field[i][j] == 0) && ((i % 50 == 0) || (i % 10 == 5 && j % 20 == 11 && i % 50 != 5 && i % 50 != 45)))
//            if((field[i][j] == 32 || field[i][j] == 0) && ((i % 50 == 0) || (i % 10 == 0 && j % 20 == 1)))
//                field[i][j] = '_';
//            //if((field[i][j] == 32 || field[i][j] == 0) && ((j % 100 == 10) || (j % 20 == 0 && i % 10 == 1 && j % 100 != 20 && j % 100 != 0)))
//            if((field[i][j] == 32 || field[i][j] == 0) && ((j % 100 == 10) || (j % 20 == 10 && i % 10 == 6)))
//                field[i][j] = '|';
//            if(j % 20 == 0 && i % 10 == 5 && j % 100 != 20 && j % 100 != 0 && i % 50 != 5 && i % 50 != 45)
//                field[i][j] = '.';
//            if(i % 250 == 2 && j % 10 == 0){
//                field[i][j] = alphabets[(j / 10 - 1) % 26];
//                field[i][j - 1] = alphabets[(j / 260 - 1) % 26];
//            }
//            if(i % 5 == 0 && j % 500 == 10){
//                field[i][j] = numbers[i / 5 % 10];
//                field[i][j - 1] = numbers[i / 5 / 10];
//            }
//        }
//    }
//}

void Grid_Advanced(int fieldHeight, int fieldWidth, int X_Start, int Y_Start, char (*field)[fieldWidth])
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
            if((field[i][j] == 32 || field[i][j] == 0) && ((i % 50 == 0) || (i % 10 == 5 && j % 20 == 11)))
                field[i][j] = '_';
            //if((field[i][j] == 32 || field[i][j] == 0) && ((j % 100 == 10) || (j % 20 == 0 && i % 10 == 1 && j % 100 != 20 && j % 100 != 0)))
            if((field[i][j] == 32 || field[i][j] == 0) && ((j % 100 == 10) || (j % 20 == 0 && i % 10 == 1)))
                field[i][j] = '|';
            if(j % 20 == 0 && i % 10 == 5 && j % 100 != 20 && j % 100 != 0 && i % 50 != 5 && i % 50 != 45)
                field[i][j] = '.';
            if(i % 250 == 2 && j % 10 == 0){
                field[i][j] = alphabets[((j + X_Start) / 10 - 1) % 26];
                field[i][j - 1] = alphabets[((j + X_Start) / 260 - 1) % 26];
            }
            if(i % 5 == 0 && j % 500 == 10){
                field[i][j] = numbers[(i + Y_Start) / 5 % 10];
                field[i][j - 1] = numbers[(i + Y_Start) / 5 / 10 % 10];
            }
        }
    }
}
void Grid(int fieldHeight, int fieldWidth, int X_Start, int Y_Start, char (*field)[fieldWidth], int Grid_Type)
{
    switch(Grid_Type){
        case 0: return;
        case 1: Grid_Rough(fieldHeight, fieldWidth, field); return;
        case 2: Grid_Normal(fieldHeight, fieldWidth, field); return;
        case 3: Grid_Simple(fieldHeight, fieldWidth, X_Start, Y_Start, field); return;
        case 4: Grid_Advanced(fieldHeight, fieldWidth, X_Start, Y_Start, field); return;
    }
}

void printArray2(int fieldHeight, int fieldWidth, char field[fieldHeight][fieldWidth])
{
//    for(int i = 0; i < fieldHeight; i++)
//        field[i][fieldWidth - 1] = '\0';
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

void printArray1(char *arr, int rows, int cols)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            putchar(*arr++);
        }
        printf("\n");
    }
}

int range(double num, int limit)
{
    if(0 > num || num > limit)
        return 0;
    return (int)num;
}

//void Control(Fleet *fleet, Identity as_id, int *Grid_Type, int Full_Control)
//{
//    switch(_getch())
//    {
//        case '1':  break;
//        case 'g': printf("Grid type(Plain: 0 Normal: 1 Simple: 2 Advanced: 3) : "); *Grid_Type = (_getch() - 48); printf("%d", *Grid_Type); break;
////        case 'm': Missile_Manual(fleet, as_id, Full_Control); break;
////        case 'a': Missile_Auto(fleet, as_id, Full_Control); break;
////        case 'c': Missile_Reassign(fleet, as_id, Full_Control); break;
////        case 'l': Manual_Launch[0] = Manual_Launch[0] == -1 ? 2 : 1; break;
////        case 'f': *fire = 1; printf("Fire");  break;
//    }
//}

void Map_Import(int tableHeight, int tableWidth, char(*table)[tableWidth], char* fname)
{
    FILE* cfPtr;
    if((cfPtr = fopen("banner (7)fixed.txt", "r"))== NULL)
    {
        printf("File cannot be opened");
        return;
    }
    else{
        int p = 0;
        while(fgets(table[p], 800, cfPtr) != NULL) {
            p++;
        }
        fclose(cfPtr);
    }
}

int main()
{
    char table[300][800];
    char field[57][240];
    int fieldHeight = 57;
    int fieldWidth = 240;
    
    int Grid_Type = 3;
    int X_Start = 300;
    int Y_Start = 100;
    
    memset(table, 0, fieldHeight * fieldWidth);
    
//    
//    
//    
//
//    FILE * cfPtr;
//    FILE * cfPtr1;
//    int counter = 0;
//    if((cfPtr = fopen("banner (7)fixed.txt", "r"))== NULL)
//    {
//        printf("file open error");
//    }
////    if((cfPtr1 = fopen("banner (7)fixed.txt", "w"))== NULL)
////    {
////        printf("file open error");
////    }
//    int p = 0;
//    
////    while(fgets(table[p], 802, cfPtr) != NULL) {
//////        table[p][801] == ' ';
////            fprintf(cfPtr1, "%797s", &table[p][1]);
////        p++;
////	}
//    while(fgets(table[p], 800, cfPtr) != NULL) {
//        p++;
//	}

    Map_Import(300, 800, table, "banner (7)fixed.txt");
    while(1){
        for(int i = 0; i < fieldHeight; i++)
        {
            for(int j = 0; j < fieldWidth; j++)
            {
                field[i][j] = table[Y_Start + i][X_Start + j];
            }
        }
        
        
        Grid(fieldHeight, fieldWidth, X_Start, Y_Start, field, Grid_Type);
    //    for(int i = 0; i < 560; i++)
    ////        for(int j = 0; j < 800; j++)
    //            printf("%s", table[i]);
        printArray2(fieldHeight, fieldWidth, field);
        int c;
        switch(c = _getch())
        {
            case 'w':  Y_Start = (int)range(Y_Start - 10, 289 - fieldHeight); break;
            case 'a':  X_Start = (int)range(X_Start - 20, 779 - fieldWidth); break;
            case 's':  Y_Start = (int)range(Y_Start + 10, 289 - fieldHeight); break;
            case 'd':  X_Start = (int)range(X_Start + 20, 779 - fieldWidth); break;
        }
        system("cls");

    }
    getchar();
    getchar();
    
    
    return;
}

