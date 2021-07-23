#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#define BOX 4
typedef struct{
    int Start_X;
    int Start_Y;
    int Lenght_X;
    int Lenght_Y;
} Box;

char status_Stack[BOX][20] = {"check", "call", "raise", "fold", "No Status"}; 

void Letter_Draw_Normal(int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, char* string, int letter_size);
void Get_Mouse_Pos(int *x, int *y);
void printArray3(int fieldHeight, int fieldWidth, char field[fieldHeight][fieldWidth]);
bool Click_Box(int m_x, int m_y, int m_x_Sht, int m_y_Sht, int Start_X, int Start_Y, int Lenght_X, int Lenght_Y, float Coe);
Box Box_Init(int Start_X, int Start_Y, int Lenght_X, int Lenght_Y);
char kb_m_Input(Box *Clicks, Box *Clicks_Show, int *x, int *y, int fieldWidth, char (*field)[fieldWidth], int fieldWidth_display, int displayWidth, int displayHeight_Shift, int displayWidth_Shift, int *cnt, int *pre_cnt, int size_box);
void Box_Draw(Box *Clicks, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int size_box, int letter_size);

int main(){
	
    Box Clicks[BOX];
    Box Clicks_Show[BOX];
	int cnt=0;
    int pre_cnt = 0;
    int x;
    int y;
    char field[163][634] = {};
    int fieldHeight = 163;
    int fieldWidth = 634;
    int fieldHeight_display = 163;
    int fieldWidth_display = 634;
    int displayHeight = 780;
    int displayHeight_Shitf = 25;
    int displayWidth = 1520;
    int status = 0;
    
    
    char table[600][50] = {};
    char fontData[600][50] = {};
    int fontDataHeight = 600;
    int fontDataWidth = 50;
    int font_size = 6;
    char string1[20] = "okay";

    Map_Import(fontDataHeight, fontDataWidth, fontData, "font Ivrit Ext_40.txt");

    for(int i = 0; i < BOX; i++)
    {
        Clicks_Show[i] = Box_Init(i * 80, 20, 40, 20);
        Clicks[i] = Box_Init((i % 2) * fieldWidth_display / 2, (i / 2) * fieldHeight_display / 2, fieldWidth_display / 2, fieldHeight_display / 2);
    }
    while(1){
        memset(field, 0, fieldHeight * fieldWidth);
        status = kb_m_Input(Clicks, Clicks, &x, &y, fieldWidth, field, fieldWidth_display, displayWidth, displayHeight_Shitf, 0, &cnt, &pre_cnt, BOX);
        Box_Draw(Clicks, fontDataWidth, fontData, fieldWidth, field, BOX, font_size);
        memset(string1, 0, 20);
        sprintf(string1, "%s", status_Stack[status]);
        Letter_Draw_Normal(fontDataWidth, fontData, fieldWidth, field, 0, 50, string1, font_size);
        system("cls");
        printArray3(fieldHeight, fieldWidth, field);
	}
    getchar();
    getchar();
	return 0;
}

void Get_Mouse_Pos(int *x, int *y)
{
	POINT pt;
	GetCursorPos(&pt);
    *x = pt.x;
    *y = pt.y;
}

void printArray3(int fieldHeight, int fieldWidth, char field[fieldHeight][fieldWidth])
{
    for(int i = 0; i < fieldHeight; i++)
        for(int j = 0; j < fieldWidth; j++){
            if(field[i][j] == 0 || field[i][j] == '\n')
                field[i][j] = ' ';
            if(j == fieldWidth - 1)
                field[i][j] = '\n';
        }
    field[fieldHeight - 1][fieldWidth - 1] = 0;
    printf("%s", field);
}



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

void Letter_Draw_Normal(int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, char* string, int letter_size)
{
    char string_field[800];
    for(int i = 0; string[i] != 0; i++)
        if(string[i] < 40 && string[i] != 32)
            string[i] = 32;

    for(int i = 0; i < letter_size; i++) // 5 is letter hight
    {
        memset(string_field, 0, 800);
        
        for(int j = 0; string[j] != 0; j++)
            strcat(string_field, fontData[(string[j] == 32 ? 83 : (string[j] - 40)) * letter_size + i]);
//        strcpy(&field[DrawFromY + i][DrawFromX], string_field);
        memcpy(&field[DrawFromY + i][DrawFromX], string_field, strlen(string_field));
    }
}

char kb_m_Input(Box *Clicks, Box *Clicks_Show, int *x, int *y, int fieldWidth, char (*field)[fieldWidth], int fieldWidth_display, int displayWidth, int displayHeight_Shift, int displayWidth_Shift, int *cnt, int *pre_cnt, int size_box)
{
    int status = 0;
    while(1){
        
		if(GetAsyncKeyState(VK_LBUTTON)){
			(*cnt)++;
		}
        if((*cnt) != *pre_cnt || _kbhit()){
            
            if((*cnt) != *pre_cnt){
                Get_Mouse_Pos(x, y);
                status = 0;
                for(int p = 0; p < size_box; p++)
                {
                    if(Click_Box(*x, *y, displayWidth_Shift, displayHeight_Shift, Clicks[p].Start_X, Clicks[p].Start_Y, Clicks[p].Lenght_X, Clicks[p].Lenght_Y, displayWidth / (float)fieldWidth_display) == true)
                    {
                        status = p;
                            for(int i = Clicks_Show[p].Start_Y; i < Clicks_Show[p].Lenght_Y + Clicks_Show[p].Start_Y; i++)
                                for(int j = Clicks_Show[p].Start_X; j < Clicks_Show[p].Lenght_X + Clicks_Show[p].Start_X; j++)
                                    field[i][j] = '*';
                    }
                }
                *pre_cnt = (*cnt);
                return status;
            }
            else{
                int p = _getch() - 49;
                status = p;
                if(p < size_box)
                    for(int i = Clicks_Show[p].Start_Y; i < Clicks_Show[p].Lenght_Y + Clicks_Show[p].Start_Y; i++)
                        for(int j = Clicks_Show[p].Start_X; j < Clicks_Show[p].Lenght_X + Clicks_Show[p].Start_X; j++)
                            field[i][j] = '*';
                return status;
            }
        }
        Sleep(50);
	}
}

bool Click_Box(int m_x, int m_y, int m_x_Sht, int m_y_Sht, int Start_X, int Start_Y, int Lenght_X, int Lenght_Y, float Coe)
{
    if(Start_X * Coe < m_x - m_x_Sht && m_x - m_x_Sht < (Start_X + Lenght_X) * Coe && Start_Y * Coe * 2 < m_y - m_y_Sht && m_y - m_y_Sht < (Start_Y + Lenght_Y) * Coe * 2) 
        return true;
    return false;
}

Box Box_Init(int Start_X, int Start_Y, int Lenght_X, int Lenght_Y)
{
    Box box;
    box.Start_X = Start_X;
    box.Start_Y = Start_Y;
    box.Lenght_X = Lenght_X;
    box.Lenght_Y = Lenght_Y;
    
    return box;
}

void Box_Draw(Box *Clicks, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int size_box, int letter_size)
{
    for(int p = 0; p < size_box; p++)
    {
        for(int i = Clicks[p].Start_X; i < Clicks[p].Lenght_X + Clicks[p].Start_X; i++){
            field[Clicks[p].Start_Y][i] = '*';
            field[Clicks[p].Lenght_Y + Clicks[p].Start_Y][i] = '*';
        }
        for(int i = Clicks[p].Start_Y; i < Clicks[p].Lenght_Y + Clicks[p].Start_Y; i++){
            field[i][Clicks[p].Start_X] = '*';
            field[i][Clicks[p].Lenght_X + Clicks[p].Start_X] = '*';
        }
        Letter_Draw_Normal(fontDataWidth, fontData, fieldWidth, field, Clicks[p].Start_X, Clicks[p].Start_Y, status_Stack[p], letter_size);
    }
}