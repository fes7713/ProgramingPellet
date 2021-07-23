#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

typedef struct{
    int Start_X;
    int Start_Y;
    int Lenght_X;
    int Lenght_Y;
} Box;

void Get_Mouse_Pos(int *x, int *y);
void printArray3(int fieldHeight, int fieldWidth, char field[fieldHeight][fieldWidth]);
bool Click_Box(int m_x, int m_y, int m_x_Sht, int m_y_Sht, int Start_X, int Start_Y, int Lenght_X, int Lenght_Y, float Coe);
Box Box_Init(int Start_X, int Start_Y, int Lenght_X, int Lenght_Y);

int main(){
	
    Box Clicks[5];
	int cnt=0;
    int pre_cnt = 0;
    int x;
    int y;
    char field[163][634] = {};
    int fieldHeight_real = 163;
    int fieldWidth_real = 634;
    int fieldHeight = 163;
    int fieldWidth = 634;
    int displayHeight = 780;
    int displayHeight_Shitf = 25;
    int displayWidth = 1520;
    int Box_Start_X = 100;
    int Box_Start_Y = 50;
    int Box_Lenght_X = 40;
    int Box_Lenght_Y = 20;
    
    for(int i = 0; i < 5; i++)
    {
        Clicks[i] = Box_Init(i * 80, 20, 40, 20);
    }
//    for(int i = 0; i < fieldHeight; i++)
//        field[i][fieldWidth / 2] = '*';
//    for(int j = 0; j < fieldWidth; j++)
//        field[fieldHeight / 2][j] = '*';
        
//	printArray3(fieldHeight, fieldWidth, field);
    while(1){
		if(GetAsyncKeyState(VK_LBUTTON)){
			cnt++;
		}
        if(cnt != pre_cnt || _kbhit()){
            memset(field, 0, fieldHeight_real * fieldWidth_real);
            for(int p = 0; p < 5; p++)
            {
                for(int i = Clicks[p].Start_X; i < Clicks[p].Lenght_X + Clicks[p].Start_X; i++){
                    field[Clicks[p].Start_Y][i] = '*';
                    field[Clicks[p].Lenght_Y + Clicks[p].Start_Y][i] = '*';
                }
                for(int i = Clicks[p].Start_Y; i < Clicks[p].Lenght_Y + Clicks[p].Start_Y; i++){
                    field[i][Clicks[p].Start_X] = '*';
                    field[i][Clicks[p].Lenght_X + Clicks[p].Start_X] = '*';
                }
            }
            if(cnt != pre_cnt){
                Get_Mouse_Pos(&x, &y);

                for(int p = 0; p < 5; p++)
                {
                    if(Click_Box(x, y, 0, displayHeight_Shitf, Clicks[p].Start_X, Clicks[p].Start_Y, Clicks[p].Lenght_X, Clicks[p].Lenght_Y, displayWidth / (float)fieldWidth) == true)
                    {
                            for(int i = Clicks[p].Start_Y; i < Clicks[p].Lenght_Y + Clicks[p].Start_Y; i++)
                                for(int j = Clicks[p].Start_X; j < Clicks[p].Lenght_X + Clicks[p].Start_X; j++)
                                    field[i][j] = '*';
                    }
                }
    //            printf("\n%d, %d\n", x, y);
                pre_cnt = cnt;
            }
            else{
                int p = _getch() - 49;
                if(p < 5)
                    for(int i = Clicks[p].Start_Y; i < Clicks[p].Lenght_Y + Clicks[p].Start_Y; i++)
                        for(int j = Clicks[p].Start_X; j < Clicks[p].Lenght_X + Clicks[p].Start_X; j++)
                            field[i][j] = '*';
                
            }
            system("cls");
            printArray3(fieldHeight_real, fieldWidth_real, field);
        }
        Sleep(50);
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
//    for(int i = 0; i < fieldHeight; i++)
//        field[i][fieldWidth - 1] = '\0';
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

bool Click_Box(int m_x, int m_y, int m_x_Sht, int m_y_Sht, int Start_X, int Start_Y, int Lenght_X, int Lenght_Y, float Coe)
{
    if(Start_X * Coe < m_x - m_x_Sht && m_x - m_x_Sht < (Start_X + Lenght_X) * Coe && Start_Y * Coe * 2 < m_y - m_y_Sht && m_y - m_y_Sht < (Start_Y + Lenght_Y) * Coe * 2) 
        return true;
    return false;
}

//while(1){
//		if(GetAsyncKeyState(VK_LBUTTON)){
//			cnt++;
//		}
//        if(cnt != pre_cnt){
//            Get_Mouse_Pos(&x, &y);
//            
//            memset(field, 0, fieldHeight_real * fieldWidth_real);
//            for(int i = 0; i < fieldHeight; i++)
//                field[i][fieldWidth / 2] = '*';
//            for(int j = 0; j < fieldWidth; j++)
//                field[fieldHeight / 2][j] = '*';
//            if(displayWidth  / 3 > x)
//            {
//                if(displayHeight / 3 + displayHeight_Shitf > y)
//                    for(int i = 0; i < fieldHeight / 3; i++)
//                        for(int j = 0; j < fieldWidth / 3; j++)
//                            field[i][j] = '*';
//                else if(displayHeight / 3 * 2  + displayHeight_Shitf > y && y > displayHeight / 3 + displayHeight_Shitf)
//                    for(int i = fieldHeight / 3; i < fieldHeight / 3 * 2; i++)
//                        for(int j = 0; j < fieldWidth / 3; j++)
//                            field[i][j] = '*';
//                else
//                    for(int i = fieldHeight / 3 * 2; i < fieldHeight; i++)
//                        for(int j = 0; j < fieldWidth / 3; j++)
//                            field[i][j] = '*';
//            }
//            else if(displayWidth / 3 * 2 > x && x > displayWidth / 3)
//            {
//                if(displayHeight / 3  + displayHeight_Shitf > y)
//                    for(int i = 0; i < fieldHeight / 3; i++)
//                        for(int j = fieldWidth / 3; j < fieldWidth / 3 * 2; j++)
//                            field[i][j] = '*';
//                else if(displayHeight / 3 * 2  + displayHeight_Shitf > y && y > displayHeight / 3 + displayHeight_Shitf)
//                    for(int i = fieldHeight / 3; i < fieldHeight / 3 * 2; i++)
//                        for(int j = fieldWidth / 3; j < fieldWidth / 3 * 2; j++)
//                            field[i][j] = '*';
//                else
//                    for(int i = fieldHeight / 3 * 2; i < fieldHeight; i++)
//                        for(int j = fieldWidth / 3; j < fieldWidth / 3 * 2; j++)
//                            field[i][j] = '*';
//            }
//            else
//            {
//                if(displayHeight / 3  + displayHeight_Shitf > y)
//                    for(int i = 0; i < fieldHeight / 3; i++)
//                        for(int j = fieldWidth / 3 * 2; j < fieldWidth; j++)
//                            field[i][j] = '*';
//                else if(displayHeight / 3 * 2  + displayHeight_Shitf > y && y > displayHeight / 3 + displayHeight_Shitf)
//                    for(int i = fieldHeight / 3; i < fieldHeight / 3 * 2; i++)
//                        for(int j = fieldWidth / 3 * 2; j < fieldWidth; j++)
//                            field[i][j] = '*';
//                else
//                    for(int i = fieldHeight / 3 * 2; i < fieldHeight; i++)
//                        for(int j = fieldWidth / 3 * 2; j < fieldWidth; j++)
//                            field[i][j] = '*';
//            }
//            system("cls");
//            printArray3(fieldHeight_real, fieldWidth_real, field);
////            printf("\n%d, %d\n", x, y);
//            pre_cnt = cnt;
//        }

Box Box_Init(int Start_X, int Start_Y, int Lenght_X, int Lenght_Y)
{
    Box box;
    box.Start_X = Start_X;
    box.Start_Y = Start_Y;
    box.Lenght_X = Lenght_X;
    box.Lenght_Y = Lenght_Y;
    
    return box;
}

char kb_m_Input(int fieldHeight, int fieldWidth, char field[fieldHeight][fieldWidth], )
{
    while(1){
		if(GetAsyncKeyState(VK_LBUTTON)){
			cnt++;
		}
        if(cnt != pre_cnt || _kbhit()){
            memset(field, 0, fieldHeight_real * fieldWidth_real);
            for(int p = 0; p < 5; p++)
            {
                for(int i = Clicks[p].Start_X; i < Clicks[p].Lenght_X + Clicks[p].Start_X; i++){
                    field[Clicks[p].Start_Y][i] = '*';
                    field[Clicks[p].Lenght_Y + Clicks[p].Start_Y][i] = '*';
                }
                for(int i = Clicks[p].Start_Y; i < Clicks[p].Lenght_Y + Clicks[p].Start_Y; i++){
                    field[i][Clicks[p].Start_X] = '*';
                    field[i][Clicks[p].Lenght_X + Clicks[p].Start_X] = '*';
                }
            }
            if(cnt != pre_cnt){
                Get_Mouse_Pos(&x, &y);

                for(int p = 0; p < 5; p++)
                {
                    if(Click_Box(x, y, 0, displayHeight_Shitf, Clicks[p].Start_X, Clicks[p].Start_Y, Clicks[p].Lenght_X, Clicks[p].Lenght_Y, displayWidth / (float)fieldWidth) == true)
                    {
                            for(int i = Clicks[p].Start_Y; i < Clicks[p].Lenght_Y + Clicks[p].Start_Y; i++)
                                for(int j = Clicks[p].Start_X; j < Clicks[p].Lenght_X + Clicks[p].Start_X; j++)
                                    field[i][j] = '*';
                    }
                }
    //            printf("\n%d, %d\n", x, y);
                pre_cnt = cnt;
            }
            else{
                int p = _getch() - 49;
                if(p < 5)
                    for(int i = Clicks[p].Start_Y; i < Clicks[p].Lenght_Y + Clicks[p].Start_Y; i++)
                        for(int j = Clicks[p].Start_X; j < Clicks[p].Lenght_X + Clicks[p].Start_X; j++)
                            field[i][j] = '*';
                
            }
            system("cls");
            printArray3(fieldHeight_real, fieldWidth_real, field);
        }
        Sleep(50);
	}
}