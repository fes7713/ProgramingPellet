#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void printArray2(char *arr, int rows, int cols);


int main(int argc, char **argv)
{
    char field[75][75] = {};
    
    int fieldHeight = 75;
    int fieldWidth = 75;
    char terrain[75][75];
    srand(time(NULL));
    
    int missilePosY = rand() % 75;
    int missilePosX = rand() % 75;
    
    
//    for(int i = 0; i < fieldHeight; i++)
//        for(int j = 0; j < fieldWidth; j++)
//            field[i][j] = '~';
    field[missilePosY][missilePosX] = '*';
        
    printArray2(field, fieldHeight, fieldWidth);
    
	return 0;
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