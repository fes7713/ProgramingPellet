#include "function.h"
#define MAXMISSILE 6
#define HOSPERINTE 2

int main(int argc, char **argv)
{
    //32:9 230:57 font 14
    char field[57][230] = {};
    int fieldHeight = 57;
    int fieldWidth = 230;
    
    double baseX = fieldWidth / 2;
    double baseY = fieldHeight / 2;
    
    int Hostile_active = 0;
    int pair[MAXMISSILE][HOSPERINTE];
    int interval = 0;
    int Grid_Type = 1;
    int fire = 0;
    int Manual_Launch[3] = {}; //Switch Interceptor Hostile
    for(int i = 0; i < 3; i++)
        Manual_Launch[i] = -1;
    for(int i = 0; i < MAXMISSILE; i++)
        for(int j = 0; j < HOSPERINTE; j++)
            pair[i][j] = -1;
    Missile Interceptor[MAXMISSILE];
    Missile Hostile[MAXMISSILE];
    time_t oldtm;
    
    memset(&Interceptor, 0, sizeof(Interceptor));
    memset(&Hostile, 0, sizeof(Hostile));
    
    srand(time(NULL));

    while(1)
    {
        oldtm = time(NULL);

        if((Hostile_active < MAXMISSILE && rand() % 100 < 5) || (Hostile_active == 0))
        {
            for(int i = 0; i < MAXMISSILE; i++)
            {
                if(Hostile[i].status == false)
                {
                    Hostile[i].status = true;
                    Hostile_active++;
                    Generator_Hostile(&Hostile[i], fieldHeight, fieldWidth);
                    break;
                }
            }
        }
        
        if(Manual_Launch[0] != -1)
            Missile_Manual_Launch(Interceptor, Hostile, Manual_Launch, pair, fieldHeight, fieldWidth, &interval, &fire);
        
        for(int j = 0; j < HOSPERINTE; j++)
        {
            interval = range(--interval, 30);
            if(!(interval == 0))
                    break;
            int i = Target_Priority(Hostile, &baseX, &baseY, pair, &j);
            if(i == -1)
                continue;
            int num = -1;
//            if(Manual_Launch[0] != 0){
//                Missile_Manual_Launch(Interceptor, Hostile, pair, &Manual_Launch, &interval, fieldHeight, fieldWidth);
//                break;
//            }
            for(int k = 0; k < 6; k++)
            {
                
//                if(Interceptor[k].status == false || (Interceptor[k].status == 2 && Manual_Launch != 0))
                if(Interceptor[k].status == false)
                {
                    num = k;
                    Interceptor[k].status = true;
                    Generator_Interceptor(&Interceptor[k], &Hostile[i], fieldHeight, fieldWidth);
                    interval += 13;
                    break;
                }
            }
            pair[i][j] = num;
            break;
        }

        memset(field, 0, fieldHeight * fieldWidth);
//Grid writing
        Grid(field, fieldHeight, fieldWidth, Grid_Type);
            
        for(int p = 0; p < MAXMISSILE; p++)
        {
            if(Hostile[p].status != true)
                continue;
            
            Missile_Stationary(&Hostile[p], &baseX, &baseY);
            
            for(int q = 0; q < HOSPERINTE; q++)
            {
//                if(pair[p][q] == -1 || Manual_Launch != 0)
                if(pair[p][q] == -1)
                    break;
                //if(!(Manual_Launch[0] != 0 && Manual_Launch[1] == pair[p][q])){
                if(!(Manual_Launch[0] != -1 && Manual_Launch[1] == pair[p][q])){
                    if(Interceptor[pair[p][q]].status == 2)
                        Missile_Stationary(&Interceptor[pair[p][q]], &Interceptor[pair[p][q]].X_targeting, &Interceptor[pair[p][q]].Y_targeting);
                    else
                        Missile_Stationary(&Interceptor[pair[p][q]], &Interceptor[pair[p][q]].X_future, &Interceptor[pair[p][q]].Y_future);
                }
                Missile_Moving(&Interceptor[pair[p][q]], &Hostile[p]);
                Hostile_Missile_Lock(Interceptor, &Hostile[p], pair, &p);
                
//Missile destroyed
                if(fabs(Hostile[p].X - Interceptor[pair[p][q]].X) < 1.5 && fabs(Hostile[p].Y - Interceptor[pair[p][q]].Y) < 1.5)
                {
                    Hostile_active--;
                    memset(&Hostile[p], 0, sizeof(Missile));
                    memset(&Interceptor[pair[p][q]], 0, sizeof(Missile));
                    
                    for(int i = 0; i < MAXMISSILE && pair[p][!(q)] != -1; i++)
                    {
                        if(Hostile[i].status == true && pair[i][1] == -1) //For second missile
                        {
//Reassigning remained missile
                            pair[i][pair[i][0] != -1] = pair[p][!(q)];
                            pair[p][!(q)] = -1;
                            break;
                        }
                        
                        if(i == MAXMISSILE - 1) // If program does not reach breakpoint before this, clear both missile, if so switch missiles.
                        {
                            memset(&Interceptor[pair[p][!(q)]], 0, sizeof(Missile));
                            pair[p][!(q)] = -1;
                        }
                    }
                    pair[p][q] = -1;
                    break;
                }
            }
//Base hit (Game over)
            if(fabs(Hostile[p].X - baseX) < 1.5 && fabs(Hostile[p].Y - baseY) < 1.5)
            {
                memset(&Interceptor, 0, sizeof(Interceptor));
                memset(&Hostile, 0, sizeof(Hostile));
                Hostile_active = 0;
                for(int i = 0; i < MAXMISSILE; i++)
                        for(int j = 0; j < HOSPERINTE; j++)
                            pair[i][j] = -1;
                break;
            }
//Hostile missile trace
            for(int i = 0; i < sizeof(Hostile[p].trace); i++)
            {
                field[range(Hostile[p].cordinates[i][1], fieldHeight)][range(Hostile[p].cordinates[i][0], fieldWidth)] = Hostile[p].trace[i];
            }
//Interceptors writings
            for(int q = 0; q < HOSPERINTE; q++)
            {
                if(pair[p][q] == -1)
                {
                    break;
                }
                for(int i = 0; i < sizeof(Interceptor[pair[p][q]].trace); i++)
                {
//Interceptors trace
                    field[range(Interceptor[pair[p][q]].cordinates[i][1], fieldHeight)][range(Interceptor[pair[p][q]].cordinates[i][0], fieldWidth)] = Interceptor[pair[p][q]].trace[i];
                }
//Expected impact point
                if(Interceptor[pair[p][q]].status == 2)
                    field[(int)Interceptor[pair[p][q]].Y_targeting][(int)Interceptor[pair[p][q]].X_targeting] = '+';
                field[range(Interceptor[pair[p][q]].Y_future, fieldHeight)][range(Interceptor[pair[p][q]].X_future, fieldWidth)] = '+';
//Lock on 
                for(int i = 0; i < 5; i++)
                {
                    for(int j = 0; j < 7; j++)
                    {
                        if(Hostile[p].lock_On || Manual_Launch[0] != -1)
                        {
                            if(i < 3 && j < 5 && !(i == 1 && j == 2) && Interceptor[pair[p][q]].lock_On)
                            {
//Target point
                                if(Interceptor[pair[p][q]].status == 2){
                                    field[range(Interceptor[pair[p][q]].Y_targeting - 1 + i, fieldHeight)][range(Interceptor[pair[p][q]].X_targeting - 2 + j, fieldWidth)] = ImpactPoint[i][j];
                                    field[range(Interceptor[pair[p][q]].Y_targeting - 1, fieldHeight)][range(Interceptor[pair[p][q]].X_targeting + 1, fieldWidth)] = numbers[pair[p][q]];
                                    field[range((int)Interceptor[pair[p][q]].Y_targeting - 1, fieldHeight)][range((int)Interceptor[pair[p][q]].X_targeting - 2, fieldWidth)] = 64 + (int)Interceptor[pair[p][q]].X_targeting / 10;
                                    field[range((int)Interceptor[pair[p][q]].Y_targeting + 1, fieldHeight)][range((int)Interceptor[pair[p][q]].X_targeting - 2, fieldWidth)] = 48 + (int)Interceptor[pair[p][q]].Y_targeting / 5;
                                    field[range((int)Interceptor[pair[p][q]].Y_targeting + 1, fieldHeight)][range((int)Interceptor[pair[p][q]].X_targeting - 1, fieldWidth)] = 48 + (int)Interceptor[pair[p][q]].X_targeting % 10 / 3 + (int)Interceptor[pair[p][q]].Y_targeting % 5 / 2 * 3;
                                }
                                else{
                                    field[range(Interceptor[pair[p][q]].Y_future - 1 + i, fieldHeight)][range(Interceptor[pair[p][q]].X_future - 2 + j, fieldWidth)] = ImpactPoint[i][j];
                                    field[range(Interceptor[pair[p][q]].Y_future - 1, fieldHeight)][range(Interceptor[pair[p][q]].X_future + 1, fieldWidth)] = numbers[pair[p][q]];
                                }
                            }
                            if(!((i == 0 && j == 5) || (i == 1 && j == 6)))
                                field[range(Hostile[p].Y - 2 + i, fieldHeight) ][range(Hostile[p].X - 3 + j, fieldWidth)] = lockOn01[i][j];
                            field[range(Hostile[p].Y - 1 + q * 2, fieldHeight) ][range(Hostile[p].X + 3, fieldWidth)] = numbers[pair[p][q]];
                        }
                        else{
                            if(!((i == 0 && j == 5) || (i == 1 && j == 6)))
                                field[range(Hostile[p].Y - 2 + i, fieldHeight)][range(Hostile[p].X - 3 + j, fieldWidth)] = Laser[i][j];
                            field[range(Hostile[p].Y - 1 + q * 2, fieldHeight) ][range(Hostile[p].X + 3, fieldWidth)] = numbers[pair[p][q]];
                        }
                        field[range(Hostile[p].Y - 2, fieldHeight) ][range(Hostile[p].X + 2, fieldWidth)] = numbers[p];
                    }
                }
//Interceptors positions
                field[range(Interceptor[pair[p][q]].Y, fieldHeight)][range(Interceptor[pair[p][q]].X, fieldWidth)] = '#';

            }
//Hostile missile position
            field[range(Hostile[p].Y, fieldHeight)][range(Hostile[p].X, fieldWidth)] = '*';
        }

        field[(int)baseY][(int)baseX] = '@';
        while (time(NULL) - oldtm < 1)
        {
            Sleep(50);
            if(_kbhit())
            {
                switch(_getch())
                {
                    case '1':  break;
                    case 'g': printf("Grid type(Plain: 0 Normal: 1 Simple: 2 Advanced: 3) : "); Grid_Type = (_getch() - 48); printf("%d", Grid_Type); break;
                    case 'm': Missile_Manual(Interceptor); break;
                    case 'a': Missile_Auto(Interceptor); break;
                    case 'c': Missile_Reassign(Interceptor, Hostile, pair); break;
                    case 'l': Manual_Launch[0] = Manual_Launch[0] == -1 ? 2 : 1; break;// Missile_Manual_Launch(Interceptor, Hostile, pair, &Manual_Launch, &interval, fieldHeight, fieldWidth); break;
                    case 'f': fire = 1; printf("Fire");  break;
 }
            }
            
        }
        system("cls");
        printArray2(field, fieldHeight, fieldWidth);
        
    }
	return 0;
}

//void Missile_Manual_Launch(Missile *Interceptor, Missile *Hostile, int pair[MAXMISSILE][HOSPERINTE],  int *Manual_Lanch, int *interval, int fieldHeight, int fieldWidth)
//{
//    (*interval)++;
//    if(*Manual_Lanch == -1)
//    {
//        for(int i = 0; i < MAXMISSILE; i++)
//            if(Interceptor[i].status == 0)
//            {
//                *Manual_Lanch = i;
//                break;
//            }
//        if(*Manual_Lanch == -1){
//            printf("No Missile Available");
//            *Manual_Lanch = -1;
//            return;
//        }
//        printf("Hostile :");
//        int select = _getch();
//        if(select == 'l'){
//            *Manual_Lanch = 0;
//            printf("Canceled");
//            return;
//        }
//        while(!((48 <= select && select < MAXMISSILE + 48) || (Hostile[select].status > 0)))
//            select = _getch();
//        select -= 48;
//        printf("%d  ", select);
//        
//        
//        if(Interceptor[pair[select][0]].status == 0)
//        {
//            pair[select][0] = *Manual_Lanch;
//            Generator_Interceptor(&Interceptor[*Manual_Lanch], &Hostile[select], fieldHeight, fieldWidth);
//        }
//        else if(Interceptor[pair[select][1]].status == 0)
//        {
//            pair[select][1] = *Manual_Lanch;
//            Generator_Interceptor(&Interceptor[*Manual_Lanch], &Hostile[select], fieldHeight, fieldWidth);
//        }
//        else{
//            printf("Cannot Assign Missile");
//            *Manual_Lanch = 0;
//            return;
//        }
//    }
//    else{
//        int num;
//        char charactor;
//        printf("Target :");
//        charactor = _getch();
//        printf("%c ", charactor);
//        if(charactor == 48 + 'l'){
//            *Manual_Lanch = -1;
//            return;
//        }
//        scanf("%d", &num);
//        *interval += 13;
//        Interceptor[*Manual_Lanch].X_targeting = (charactor - 65) * 10 + 10 + num % 10 % 3 * 3;
//        Interceptor[*Manual_Lanch].Y_targeting = num / 10 * 5 + num % 10 / 3 * 2;
//        *Manual_Lanch = 0;
//    }
//}

//void Missile_Manual(Missile *Interceptor)
//{
//    printf("Missile :"); 
//    int select = _getch();
//    while(!((48 <= select && select < MAXMISSILE + 48) || (Interceptor[select].status > 0)))
//        select = _getch();
//    select -= 48;
//    printf("%d  ", select);
//    int num;
//    char charactor;
//    Interceptor[select].status = 2;
//    printf("Target :");
//    charactor = _getch();
//    printf("%c ", charactor);
//    scanf("%d", &num);
//    
//    Interceptor[select].X_targeting = (charactor - 65) * 10 + 10 + num % 10 % 3 * 3;
//    Interceptor[select].Y_targeting = num / 10 * 5 + num % 10 / 3 * 2;
//}

void Missile_Manual_Launch(Missile *Interceptor, Missile *Hostile, int *Manual_Launch, int (*pair)[HOSPERINTE], int fieldHeight, int fieldWidth, int *interval, int *fire)
{
    if(Manual_Launch[0] == 2)
    {
        for(int i = 0; i < MAXMISSILE; i++)
            if(Interceptor[i].status == 0)
            {
                Manual_Launch[1] = i;
                break;
            }
        if(Manual_Launch[1] == -1){
            printf("No Missile Available");
            return;
        }
        printf("Hostile :");
        Manual_Launch[2] = _getch();
        if(Manual_Launch[2] == 'l'){
            printf("Canceled");
            for(int i = 0; i < 3; i++)
                Manual_Launch[i] = -1;
            return;
        }
        while(!((48 <= Manual_Launch[2] && Manual_Launch[2] < MAXMISSILE + 48) || (Hostile[Manual_Launch[2]].status > 0)))
            Manual_Launch[2] = _getch();
        Manual_Launch[2] -= 48;
        printf("%d  ", Manual_Launch[2]);
        
        
        if(Interceptor[pair[Manual_Launch[2]][0]].status == 0)
        {
            pair[Manual_Launch[2]][0] = Manual_Launch[1];
            Interceptor[Manual_Launch[1]].status = 2;
            Generator_Interceptor(&Interceptor[Manual_Launch[1]], &Hostile[Manual_Launch[2]], fieldHeight, fieldWidth);
        }
        else if(Interceptor[pair[Manual_Launch[2]][1]].status == 0)
        {
            pair[Manual_Launch[2]][1] = Manual_Launch[1];
            Interceptor[Manual_Launch[1]].status = 2;
            Generator_Interceptor(&Interceptor[Manual_Launch[1]], &Hostile[Manual_Launch[2]], fieldHeight, fieldWidth);
        }
        else{
            printf("Cannot Assign Missile");
            for(int i = 0; i < 3; i++)
                Manual_Launch[i] = -1;
            Sleep(500);
            return;
        }
        Manual_Launch[0] = 1;
        if(*interval < 2)
            *interval = 2;
        return;
    }
    else if(Manual_Launch[0] == 1)
    {
        if(Interceptor[Manual_Launch[1]].status == 0)
        {
            for(int i = 0; i < 3; i++)
                Manual_Launch[i] = -1;
            return;
        }
        int num;
        char charactor;
        printf("Target :");
        charactor = _getch();
        printf("%c ", charactor);
        scanf("%d", &num);
    
        Interceptor[Manual_Launch[1]].X_targeting = (charactor - 65) * 10 + 10 + num % 10 % 3 * 3;
        Interceptor[Manual_Launch[1]].Y_targeting = num / 10 * 5 + num % 10 / 3 * 2;
        if(*interval < 2)
            *interval = 2;
        Manual_Launch[0] = 0;
        return;
    }
    else if(Manual_Launch[0] == 0)
    {
        if(*fire == 1){
            for(int i = 0; i < 3; i++)
                Manual_Launch[i] = -1;
            (*interval) += 13;
            fire = 0;
        }
    }
        return;
    
}