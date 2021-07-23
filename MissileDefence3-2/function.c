#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#define MAXMISSILE 6
#define HOSPERINTE 2
#define SPE_HOS 1
#define SPE_INTE 2
typedef struct {
    double X;
    double Y;
    double speed;
    double direction;
    double X_future;
    double Y_future;
    double X_targeting;
    double Y_targeting;
    double time_impact;
    double cordinates[5][2];
    char trace[5];
    int status;
    bool lock_On;
} Missile;

char numbers[6] = {'0','1','2', '3', '4', '5'};

char lockOn[5][7] = {"  _|_  ",
                     " | | | ",
                     "--- ---",
                     " |_|_| ",
                     "   |   "};
char lockOn01[5][7] = {"  _|_  ",
                       " |   | ",
                       "--   --",
                       " |_ _| ",
                       "   |   "};
                         
char Laser[5][7] = {"  _ _  ",
                    " |   | ",
                    "       ",
                    " |_ _| ",
                    "       "};
char ImpactPoint[3][5] = {"  |  ",
                          "-- --",
                          "  |  "};

void printArray2(char *arr, int rows, int cols)
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

double to_deg360_Tri(double run, double rise)
{
    if(atan(rise / run) < 0){
        if(run > 0)
            return -1 * atan(rise / run);
        else
            return M_PI - atan(rise / run);
    }
    else{
        if(run > 0)
            return 2 * M_PI - atan(rise / run);
        else
            return M_PI - atan(rise / run);
    }
    
}

void Missile_Stationary(Missile * missile, const double *target_X, const double *target_Y)
{
    float directionPre = (float)missile->direction;
    double angle_Direct = to_deg360_Tri(*target_X - missile->X, *target_Y - missile->Y);
    if(missile->direction < 0)
        missile->direction += 2 * M_PI;
    if(missile->direction > 2 * M_PI)
        missile->direction -= 2 * M_PI;
    
    if(M_PI / 16 > fabs(angle_Direct - missile->direction))
    {
        missile->direction = angle_Direct;
    }
    else{
        if((-1 * M_PI < missile->direction - angle_Direct && missile->direction - angle_Direct < 0) || (M_PI < missile->direction - angle_Direct))
        {
            missile->direction += M_PI / 16;
            if(missile->direction > 2 * M_PI)
                missile->direction -= 2 * M_PI;
        }
        else{
            missile->direction -= M_PI / 16;
            if(missile->direction < 0)
                missile->direction += 2 * M_PI;
        }
    }
    missile->X += missile->speed * cos(missile->direction);
    missile->Y -= missile->speed * sin(missile->direction);
    if(directionPre == (float)missile->direction)
        missile->lock_On = true;
    else 
        missile->lock_On = false;
    
    record_cordinates(missile);
}

void Missile_Moving(Missile *Interceptor, const Missile *Hostile)
{
    double run = Hostile->X - Interceptor->X;
    double rise = Interceptor->Y - Hostile->Y;
    
    double Constant = Hostile->speed / Interceptor->speed * (run * sin(Hostile->direction) - (rise * cos(Hostile->direction)));
    double Square_root = sqrt(pow(rise, 2) * pow(Constant, 2) - ((pow(run, 2) + pow(rise, 2)) * (pow(Constant, 2) - pow(run, 2))));

    double angle_plus =  acos((Square_root - (rise * Constant)) / (pow(run, 2) + pow(rise, 2)));
    double angle_minus = acos(-1 * (Square_root + (rise * Constant)) / (pow(run, 2) + pow(rise, 2)));
    double time_travel_plus = run / (Interceptor->speed * cos(angle_plus) - Hostile->speed * cos(Hostile->direction));
    double time_travel_minus = run / (Interceptor->speed * cos(angle_minus) - Hostile->speed * cos(Hostile->direction));
    
    if((time_travel_plus < time_travel_minus && time_travel_plus > 0) || (time_travel_minus < 0))
        Interceptor->time_impact = time_travel_plus;
    else
        Interceptor->time_impact = time_travel_minus;

    Interceptor->X_future = Hostile->X + Hostile->speed * Interceptor->time_impact * cos(Hostile->direction);
    Interceptor->Y_future = Hostile->Y - Hostile->speed * Interceptor->time_impact * sin(Hostile->direction);
}

double Missile_Angle_Ini(Missile *Interceptor, const Missile *Hostile)
{
    double run = Hostile->X - Interceptor->X;
    double rise = Interceptor->Y - Hostile->Y;
    
    double Constant = Hostile->speed / Interceptor->speed * (run * sin(Hostile->direction) - (rise * cos(Hostile->direction)));
    double Square_root = sqrt(pow(rise, 2) * pow(Constant, 2) - ((pow(run, 2) + pow(rise, 2)) * (pow(Constant, 2) - pow(run, 2))));

    double angle_plus =  acos((Square_root - (rise * Constant)) / (pow(run, 2) + pow(rise, 2)));
    double angle_minus = acos(-1 * (Square_root + (rise * Constant)) / (pow(run, 2) + pow(rise, 2)));
    double time_travel_plus = run / (Interceptor->speed * cos(angle_plus) - Hostile->speed * cos(Hostile->direction));
    double time_travel_minus = run / (Interceptor->speed * cos(angle_minus) - Hostile->speed * cos(Hostile->direction));
    
    if((time_travel_plus < time_travel_minus && time_travel_plus > 0) || (time_travel_minus < 0))
    {
        Interceptor->time_impact = time_travel_plus;
        Interceptor->X_future = Hostile->X + Hostile->speed * Interceptor->time_impact * cos(Hostile->direction);
        Interceptor->Y_future = Hostile->Y - Hostile->speed * Interceptor->time_impact * sin(Hostile->direction);
        if(rise < 0)
            return 2* M_PI - angle_plus;
        return angle_plus;
    }
    else{
        Interceptor->time_impact = time_travel_minus;
        Interceptor->X_future = Hostile->X + Hostile->speed * Interceptor->time_impact * cos(Hostile->direction);
        Interceptor->Y_future = Hostile->Y - Hostile->speed * Interceptor->time_impact * sin(Hostile->direction);
        if(rise < 0)
            return 2* M_PI - angle_minus;
        return angle_minus;
    }

}

void record_cordinates(Missile * missile)
{
    for(int i = sizeof(missile->trace) - 2; i >= 0; i--)
    {
        for(int j = 0; j < 2; j++)
        {
            missile->cordinates[i + 1][j] = missile->cordinates[i][j];
        }
        missile->trace[i + 1] = missile->trace[i];
    }
    missile->cordinates[0][0] = missile->X;
    missile->cordinates[0][1] = missile->Y;
    
    if(fabs(tan(missile->direction)) < tan(M_PI / 8))
    {
        missile->trace[0] = '_';
    }
    else if(fabs(tan(missile->direction + M_PI / 2)) < tan(M_PI / 8))
    {
        missile->trace[0] = '|';
    }
    else if(tan(missile->direction) > 0)
    {
        missile->trace[0] = '/';
    }
    else{
//        missile->trace[0] = '\\';
        missile->trace[0] = ':';
    }
}

int range(double num, int limit)
{
    if(0 > num || num > limit)
        return 0;
    return (int)num;
}

void Generator_Hostile(Missile *Hostile, int fieldHeight, int fieldWidth)
{
    srand(time(NULL));
    Hostile->speed = SPE_HOS;
    
    int missile_side;
    switch(missile_side = rand() % 4)
        {
            case 0: 
                Hostile->X = fieldWidth - 10;
                Hostile->Y = rand() % fieldHeight;
                //Hostile.direction = to_deg360_Tri((baseX - Hostile.X), (baseY - Hostile.Y)) + 2 * sin(rand());
                Hostile->direction = rand() % 6;
                break;
            case 1:
                Hostile->X = rand() % fieldWidth;
                Hostile->Y = fieldHeight - 5;
                //Hostile.direction = to_deg360_Tri((baseX - Hostile.X), (baseY - Hostile.Y)) + 2 * sin(rand());
                Hostile->direction = rand() % 6;
                break;
            case 2:
                Hostile->X = 10;
                Hostile->Y = rand() % fieldHeight;
                //Hostile.direction = to_deg360_Tri((baseX - Hostile.X), (baseY - Hostile.Y)) + 2 * sin(rand());
                Hostile->direction = rand() % 6;
                break;
            case 3:
                Hostile->X = rand() % fieldWidth;
                Hostile->Y = 5;
                //Hostile.direction = to_deg360_Tri((baseX - Hostile.X), (baseY - Hostile.Y)) + 2 * sin(rand());
                Hostile->direction = rand() % 6;
                break;
        }
        record_cordinates(Hostile);
        return;
}

void Generator_Interceptor(Missile *Interceptor, Missile *Hostile, int fieldHeight, int fieldWidth)
{
    srand(time(NULL));
    if(rand() % 100 < 50)
        Interceptor->X = fieldWidth / 3;
    else
        Interceptor->X = fieldWidth * 2 / 3;
    
    Interceptor->Y = fieldHeight / 2;
    Interceptor->speed = SPE_INTE;
    Interceptor->direction = Missile_Angle_Ini(Interceptor, Hostile);
    record_cordinates(Interceptor);
}

int Target_Priority(const Missile *target, const double *base_X, const double *base_Y, int pair[MAXMISSILE][HOSPERINTE], const int *j)
{
    int distance[MAXMISSILE] = {};
    for(int i = 0; i < MAXMISSILE; i++)
        distance[i] = 999;
    int nMinPos = 0;
    
    for(int i = 0; i < MAXMISSILE; i++)
    {
        if(target[i].status == true && pair[i][*j] == -1)
        {
            distance[i] = hypot(*base_X - target[i].X, *base_Y - target[i].Y);
            if(distance[i] < distance[nMinPos])
            {
                nMinPos = i;
            }
        }
    }
    
    if(distance[nMinPos] == 999 || target[nMinPos].status == false)
        return -1;
    return nMinPos;
}

void Hostile_Missile_Lock(const Missile *Interceptor, Missile * Hostile, int pair[MAXMISSILE][HOSPERINTE], int *p)
{
    if(Interceptor[pair[*p][0]].lock_On == true|| Interceptor[pair[*p][1]].lock_On == true)
    {
        Hostile->lock_On = true;
    }
    else
    {
        Hostile->lock_On = false;
    }
}

void Grid_Normal(char *field, int fieldHeight, int fieldWidth)
{
    for (int i = 0; i < fieldHeight; i++)
    {
        for (int j = 0; j < fieldWidth; j++) 
        {
            if(i % 10 == 0)
                *field = '_';
            if(j % 20 == 10)
                *field = '|';
            field++;
        }
    }
}

void Grid_Simple(char *field, int fieldHeight, int fieldWidth)
{
    char alphabets[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char numbers[30] = "0123456789";
    
    for (int i = 0; i < fieldHeight; i++)
    {
        for (int j = 0; j < fieldWidth; j++) 
        {
            if(i % 10 == 5 && j % 20 == 11)
                *field = '_';
            if(j % 20 == 0 && i % 10 == 1)
                *field = '|';
            if(j % 20 == 0 && i % 10 == 5)
                *field = '.';
            if(i == 2 && j % 10 == 0)
                //field[2 * fieldWidth + (i+1) * 10] = alphabets[i];
                *field = alphabets[j / 10 - 1];
            if(i % 5 == 0 && j == 10)
                *field = numbers[i / 5 % 10];
            if(i % 5 == 0 && j == 9)
                *field = numbers[i / 5 / 10];
            field++;
        }
    }
}

void Grid_Advanced(char *field, int fieldHeight, int fieldWidth)
{
    char alphabets[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char numbers[30] = "0123456789";
    
    for (int i = 0; i < fieldHeight; i++)
    {
        for (int j = 0; j < fieldWidth; j++) 
        {
            if((i % 10 == 0) || (i % 10 == 5 && j % 20 == 11))
                *field = '_';
            if((j % 20 == 10) || (j % 20 == 0 && i % 10 == 1))
                *field = '|';
            if(j % 20 == 0 && i % 10 == 5)
                *field = '.';
            if(i == 2 && j % 10 == 0)
                //field[2 * fieldWidth + (i+1) * 10] = alphabets[i];
                *field = alphabets[j / 10 - 1];
            if(i % 5 == 0 && j == 10)
                *field = numbers[i / 5 % 10];
            if(i % 5 == 0 && j == 9)
                *field = numbers[i / 5 / 10];
            field++;
        }
    }
}

void Grid(char *field, int fieldHeight, int fieldWidth, int Grid_Type)
{
    switch(Grid_Type){
        case 0: return;
        case 1: Grid_Normal(field, fieldHeight, fieldWidth); return;
        case 2: Grid_Simple(field, fieldHeight, fieldWidth); return;
        case 3: Grid_Advanced(field, fieldHeight, fieldWidth); return;
    }
}

void Missile_Manual(Missile *Interceptor)
{
    printf("Missile :"); 
    int select = _getch();
    while(!((48 <= select && select < MAXMISSILE + 48) || (Interceptor[select].status > 0)))
        select = _getch();
    select -= 48;
    printf("%d  ", select);
    int num;
    char charactor;
    Interceptor[select].status = 2;
    printf("Target :");
    charactor = _getch();
    printf("%c ", charactor);
    scanf("%d", &num);
    
    Interceptor[select].X_targeting = (charactor - 65) * 10 + 10 + num % 10 % 3 * 3;
    Interceptor[select].Y_targeting = num / 10 * 5 + num % 10 / 3 * 2;
}

void Missile_Auto(Missile *Interceptor)
{
    printf("Missile :");
    int select = _getch();
    if(select == 'a'){
        printf("Canceled");
        return;
    }

    while(!((48 <= select && select < MAXMISSILE + 48) || (Interceptor[select].status > 0)))
        select = _getch();
    select -= 48;
    printf("%d  ", select);
    if(Interceptor[select].status == 2)
        Interceptor[select].status = 1;
}

//void Missile_Reassign(Missile *Interceptor, int pair[MAXMISSILE][HOSPERINTE])
//{
//    struct Pos{
//        int missile;
//        int X, Y;
//    };
//    struct Pos select[2] = {};
//    printf("Missile 1 :");
//    select[0].missile = _getch() - 48;
//     while(!(0 <= select[0].missile && select[0].missile < MAXMISSILE * HOSPERINTE || Interceptor[select[0].missile].status > 0))
//        select[0].missile = _getch() - 48;
//    printf("%d  ", select[0].missile);
//    printf("Missile 2 :");
//    select[1].missile = _getch() - 48;
//     while(!(0 <= select[1].missile && select[1].missile < MAXMISSILE * HOSPERINTE || Interceptor[select[1].missile].status > 0))
//        select[1].missile = _getch() - 48;
//    printf("%d  ", select[1].missile);
//    
//    for(int p = 0; p < 2; p++)
//    {
//        for(int i = 0; i < MAXMISSILE; i++)
//        {
//            for(int j = 0; j < HOSPERINTE; j++)
//            {
//                if(pair[i][j] == select[p].missile)
//                {
//                    select[p].Y = i;
//                    select[p].X = j;
//                }
//            }
//        }
//    }
//    
//    int temp = pair[select[0].Y][select[0].X];
//    pair[select[0].Y][select[0].X] = pair[select[1].Y][select[1].X];
//    pair[select[1].Y][select[1].X] = temp;
//
//}

void Missile_Reassign(Missile *Interceptor, Missile *Hostile, int pair[MAXMISSILE][HOSPERINTE])
{
    struct Pos{
        int missile;
        int X, Y;
    };
    struct Pos select = {};
    printf("Missile :");
    select.missile = _getch();
    if(select.missile == 'c'){
        printf("Canceled");
        return;
    }
    while(!((48 <= select.missile && select.missile < MAXMISSILE + 48) || (Interceptor[select.missile].status > 0)))
        select.missile = _getch();
    select.missile -= 48;
    printf("%d  ", select.missile);
    
    printf("Hostile Target :");
    int select_hos = _getch() - 48;
    while(!((0 <= select_hos && select_hos < MAXMISSILE) || (Hostile[select_hos].status > 0)))
        select_hos = _getch() - 48;
    printf("%d  ", select_hos);
    
    
    for(int i = 0; i < MAXMISSILE; i++)
    {
        for(int j = 0; j < HOSPERINTE; j++)
        {
            if(pair[i][j] == select.missile)
            {
                select.Y = i;
                select.X = j;
            }
        }
    }
    int hos_switch;
    if(pair[select_hos][1] == -1)
    {
        hos_switch = 1;
    }
    else{
        hos_switch = far_Missile(Interceptor, pair, select_hos);
    }
    int temp = pair[select_hos][hos_switch];
    pair[select_hos][hos_switch] = pair[select.Y][select.X];
    pair[select.Y][select.X] = temp;
}

int far_Missile(Missile *missile, int pair[MAXMISSILE][HOSPERINTE], int num_tag)
{
    if(missile[pair[num_tag][0]].time_impact < missile[pair[num_tag][1]].time_impact)
        return 1;
    return 0;
}