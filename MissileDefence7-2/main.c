#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <unistd.h>

#define MAXMISSILE 6
#define HOSPERINTE 2
#define FLEET 2
#define MILLITARY 15
#define SPE_HOS 1
#define SPE_INTE 0.5
typedef struct{
    int fleet;
    int millitary;
    int missile;
} Identity;

typedef struct{
    Identity destroyed;
    Identity destroyed_by;
    int status;
} KillFeed;

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
    Identity target;//Fleet Military
} Missile;

typedef struct{
    int type;
    int interval;
    int timer;
    int Range;
    int fire;
    int MaxAssets;
    int Full_Manual;
    int Missile_Amount;
    Missile core;
    Missile missile[MAXMISSILE];
} Millitary;

typedef struct{
    Millitary assets[MILLITARY];
    int pair[FLEET][MILLITARY][MAXMISSILE];
    int pair_base[FLEET][MILLITARY];
    int identity;
} Fleet;

char numbers[10] = {'0','1','2', '3', '4', '5', '6', '7','8','9'};
char alphabets[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

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
   
typedef void (*LaunchFunction)(Fleet *, Identity);
typedef void (*InitializeFuncion)(Millitary *, double, double, double, double);

void player(Fleet *fleet, Identity as_id, KillFeed *Record, int tableHeight, int tableWidth, int RecordHeight, double difficulty);
void Graphing(int fieldHeight, int fieldWidth, int X_Start, int Y_Start, char field[fieldHeight][fieldWidth], Fleet *fleet, Identity as_id, int *Grid_Type, int Radar);
void Control(Fleet *fleet, Identity as_id, int *Grid_Type, int Full_Control, int *Radar, int fieldHeight, int fieldWidth, int tableHeight, int tableWidth, int *X_Start, int *Y_Start, int *font, int *Grid_Update);
void printArray2(int fieldHeight, int fieldWidth, char field[fieldHeight][fieldWidth]);
int range(double num, int limit);
double to_deg360_Tri(double run, double rise);
void Missile_Stationary(Missile * missile, const double *target_X, const double *target_Y);
bool Missile_Moving(Missile *Interceptor, const Missile *Hostile);
double Missile_Angle_Ini(Missile *Interceptor, const Missile *Hostile);
void Generator_Interceptor(Missile *Interceptor, Missile *Hostile, double Launch_X, double Launch_Y);
void record_cordinates(Missile * missile);
void Grid(int fieldHeight, int fieldWidth, int X_Start, int Y_Start, char (*field)[fieldWidth], int Grid_Type);
void Grid_Rough(int fieldHeight, int fieldWidth, char (*field)[fieldWidth]);
void Grid_Normal(int fieldHeight, int fieldWidth, char (*field)[fieldWidth]);
void Grid_Simple(int fieldHeight, int fieldWidth, int X_Start, int Y_Start, char (*field)[fieldWidth]);
void Grid_Advanced(int fieldHeight, int fieldWidth, int X_Start, int Y_Start, char (*field)[fieldWidth]);
void Missile_Initialize(Missile *missile, double Pos_X, double Pos_Y, double future_X, double future_Y);
void Base_Initialize(Missile *Base, double base_X, double base_Y, double target_X, double target_Y);
void Base_Moving(Fleet *fleet, Identity as_id, int tableHeight, int tableWidth);
void Base_Grapging(Missile *Base, Identity friendly_id, Identity Base_id, const int fieldHeight, const int fieldWidth, int X_Start, int Y_Start, char (*field)[fieldWidth]);
void Lock_On_Draw(Missile *target, int Lock_On, int fieldHeight, int fieldWidth, int X_Start, int Y_Start, char field[][fieldWidth], Identity target_id, Identity Interceptor[2]);
void ImpactPoint_Draw(Missile* missile, int fieldHeight, int fieldWidth, int X_Start, int Y_Start, char field[][fieldWidth], Identity missile_id);
bool Target_Lock_On(Fleet *fleet, Identity target_id, Identity pair[2]);
int Available_Missile(Missile *missile, int Missile_Amount);
int Available_Assets(Fleet *fleet, int Assets_Amount, int type);
bool Comp_Struct(Identity id_1, Identity id_2);
Identity PosIni(int i, int j, int k);
Identity Target_Priority(Fleet* fleet, Identity identity, const double *baseX, const double *baseY, int Range);
Identity Base_Target_Priority(Fleet *fleet, Identity as_id, int Range);
Identity Base_Attack(Fleet *fleet, Identity as_id, int Range);
void Pair_Activate(Fleet *fleet, Identity activate_id);
void Pair_Deactivate(Fleet *fleet, Identity deactivate_id);
Identity Pair_Search(Fleet *fleet, Identity as_id, Identity target_id);
void Pair_Decre(Fleet *fleet, Identity activate_id);
bool Input_Conve(int *charactor, int *num, char escape);
void Missile_Manual(Fleet *fleet, Identity as_id, bool Full_Control);
void Missile_Auto(Fleet *fleet, Identity as_id, bool Full_Control);
void Missile_Reassign(Fleet *fleet, Identity as_id, bool Full_Control);
Identity far_Missile(Fleet *fleet, Identity as_id, Identity target_id);
void Agis_Launch(Fleet *fleet, Identity as_id);
void Fighter_Launch(Fleet *fleet, Identity as_id);
void AircraftCarrier_Launch(Fleet *fleet, Identity as_id);
void AirBase_Launch(Fleet *fleet, Identity as_id);
void Stealth_Fighter_Launch(Fleet *fleet, Identity as_id);
void Agis_Initialize(Millitary *Agis, double Launch_X, double Launch_Y, double target_X, double target_Y);
void Fighter_Initialize_Start(Millitary *Fighter, double Launch_X, double Launch_Y, double target_X, double target_Y);
void AircraftCarrier_Initialize_Start(Millitary *Fighter, double Launch_X, double Launch_Y, double target_X, double target_Y);
void AirBase_Initialize_Start(Millitary *AircraftBase, double Launch_X, double Launch_Y, double target_X, double target_Y);
void Stealth_Fighter_Initialize_Start(Millitary *Fighter, double Launch_X, double Launch_Y, double target_X, double target_Y);
void Fighter_Initialize(Millitary *assets, Missile *target, double Launch_X, double Launch_Y);
void Stealth_Fighter_Initialize(Millitary *assets, Missile *target, double Launch_X, double Launch_Y);
bool pair_check(Fleet *fleet);
void Radar_Range(int fieldHeight, int fieldWidth, int Height_Start, int Width_Start, char field[fieldHeight][fieldWidth], Fleet *fleet);
void Map_Import(int tableHeight, int tableWidth, char(*table)[tableWidth], char* fname);
void Map_Draw(int fieldHeight, int fieldWidth, int tableWidth, int X_Start, int Y_Start, char(*field)[fieldWidth], char(*table)[tableWidth]);
void RTB_Fighter(Fleet *fleet, Identity as_id, Identity Fighter_id, int Auto);
Identity Nearby_Base(Fleet *fleet, Identity as_id);
void Letter_Draw_Italic(int fontDataHeight, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, char* string, int letter_size);
void Letter_Draw_Normal(int fontDataHeight, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, char* string, int letter_size);
void Kill_Feed_Record(KillFeed *Record, Identity Destroyed, Identity Destroyed_By, int Status, int RecordHeight);
void Kill_Feed_Draw(KillFeed *Record, int RecordHeight, Identity as_id, int fontDataHeight, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, int letter_size);
void Grid_Draw(int fieldHeight, int fieldWidth, char(*field)[fieldWidth], char (*Grid_field)[fieldWidth], int X_Start, int Y_Start, int *Grid_Type, int *Grid_Update);
bool Error_Nan(Fleet *fleet);

LaunchFunction arrLauch[5] = {Agis_Launch, Fighter_Launch, AircraftCarrier_Launch, AirBase_Launch, Stealth_Fighter_Launch};
InitializeFuncion arrIni[5] = {Agis_Initialize, Fighter_Initialize_Start, AircraftCarrier_Initialize_Start, AirBase_Initialize_Start, Stealth_Fighter_Initialize_Start};

double Error_Record = 0;

int main(int argc, char **argv)
{
    //32:9 230:57 font 13
    //     269:70 font 10 A-Z
    //155:620 font 5
    //95:380 font 8
    //60:240 font 13
    int font = 8;
    char field[165][660] = {};
    int fieldHeight = 800 / font / 5 * 5;
    int fieldWidth = fieldHeight * 4;
    int X_Start = 0;
    int Y_Start = 0;
    char Grid_field[165][660] = {};
    char table[450][800];
    int tableHeight = 450;
    int tableWidth = 800;
    char fontData[500][50];
    int fontDataHeight = 500;
    int fontDataWidth = 50;
    int letter_size = 6;
    Map_Import(fontDataHeight, fontDataWidth, fontData, "font Ivrit.txt");
//    Letter_Draw_Normal(fontDataHeight, fontDataWidth, fontData, fieldWidth, field, 100, 30, "SXaple", 6);
//    printArray2(fieldHeight, fieldWidth, field);
    Map_Import(tableHeight, tableWidth, table, "banner (7)fixed.txt");
    int counter = 0;
    int stop = 0;
    int Grid_Type = 4;
    int Full_Control = 1;
    int Radar = 0;
    int Grid_Update = 1;
    Fleet Agis_USS[FLEET];
    KillFeed Record[5];
    int RecordHeight = 5;
    time_t oldtm;

    memset(Agis_USS, 0, sizeof(Fleet) * FLEET);
    for(int p = 0; p < FLEET; p++)
        for(int i = 0; i < FLEET; i++)
            for(int j = 0; j < MILLITARY; j++)
                for(int k  = 0; k < MAXMISSILE; k++)
                {
                    Agis_USS[p].pair[i][j][k] = -1;
                    Agis_USS[p].pair_base[i][j] = -1;
                }
    
    srand(time(NULL));
    
//    Base_Initialize(&Agis_USS[0].assets[0].core, 200, 30, 15, 20);
    arrIni[3](&Agis_USS[0].assets[0], 420, 190, 15, 20);
    Pair_Activate(Agis_USS, PosIni(0, 0, -1));
    arrIni[3](&Agis_USS[0].assets[1], 120, 195, 15, 20);
    Pair_Activate(Agis_USS, PosIni(0, 1, -1));
    Agis_USS[0].assets[2].type = 1;
    Agis_USS[0].assets[3].type = 1;
    Agis_USS[0].assets[4].type = 1;
    Agis_USS[0].assets[5].type = 1;
    Agis_USS[0].assets[6].type = 1;
    Agis_USS[0].assets[7].type = 1;
    Agis_USS[0].assets[8].type = 1;
    Agis_USS[0].assets[9].type = 1;
    Agis_USS[0].assets[10].type = 1;
    Agis_USS[0].assets[11].type = 1;
    Agis_USS[0].assets[12].type = 1;
    Agis_USS[0].assets[13].type = 4;
    Agis_USS[0].assets[14].type = 4;
    
//    arrIni[1](&Agis_USS[0].assets[1], 200, 15, 15, 20);
//    Pair_Activate(Agis_USS, PosIni(0, 1, -1));
//    arrIni[1](&Agis_USS[0].assets[2], 200, 5, 15, 20);
//    Pair_Activate(Agis_USS, PosIni(0, 2, -1));
    
    arrIni[0](&Agis_USS[1].assets[2], 40, 100, 420, 190);
    Pair_Activate(Agis_USS, PosIni(1, 0, -1));
    arrIni[0](&Agis_USS[1].assets[1], 20, 100, 420, 190);
    Pair_Activate(Agis_USS, PosIni(1, 1, -1));
    arrIni[2](&Agis_USS[1].assets[0], 20, 80, 420, 190);
    Pair_Activate(Agis_USS, PosIni(1, 2, -1));
    arrIni[0](&Agis_USS[1].assets[3], 40, 80, 420, 190);
    Pair_Activate(Agis_USS, PosIni(1, 3, -1));
    arrIni[0](&Agis_USS[1].assets[4], 30, 80, 420, 190);
    Pair_Activate(Agis_USS, PosIni(1, 4, -1));
    Agis_USS[1].assets[5].type = 1;
    Agis_USS[1].assets[6].type = 1;
//    arrIni[0](&Agis_USS[1].assets[1], 40, 15, 200, 50);
//    Pair_Activate(Agis_USS, PosIni(1, 1, -1));
    Identity friendly_id = PosIni(0, 0, -1);
    while(1)
    {
        counter ++;
        if(counter % 25 == 0)
            stop = 1;
        
        if(counter == 148)
            stop = 1;
            
        for(int i = 0; i < FLEET; i++)
            for(int j = 0; j < MILLITARY; j++)
                if(Agis_USS[i].assets[j].core.status != 0)
                    player(Agis_USS, PosIni(i, j, -1), Record, tableHeight, tableWidth, RecordHeight, 0.6);
        if(Error_Nan(Agis_USS))
            stop = 1;
         if(Agis_USS[friendly_id.fleet].assets[friendly_id.millitary].core.status == 0)
        {
            printf("Lost match");
            sleep(120);
            break;
        }
        
        memset(field, 0, fieldHeight * fieldWidth);
        Map_Draw(fieldHeight, fieldWidth, tableWidth, X_Start, Y_Start, field, table);
        Grid_Draw(fieldHeight, fieldWidth, field, Grid_field, X_Start, Y_Start, &Grid_Type, &Grid_Update);
        Graphing(fieldHeight, fieldWidth, X_Start, Y_Start, field, Agis_USS, friendly_id, &Grid_Type, Radar);
        
        Kill_Feed_Draw(Record, RecordHeight, friendly_id, fontDataHeight, fontDataWidth, fontData, fieldWidth, field, fieldWidth - 120, 5, letter_size);
        fieldHeight = 800 / font / 5 * 5;
        fieldWidth = fieldHeight * 4;
//        getchar();
        if(_kbhit())
            Control(Agis_USS, friendly_id, &Grid_Type, Full_Control, &Radar, fieldHeight, fieldWidth, tableHeight, tableWidth, &X_Start, &Y_Start, &font, &Grid_Update);
        system("cls");
        if(font == 5)
            stop = 1;
        printArray2(fieldHeight, fieldWidth, field);

    }

	return 0;
}

void player(Fleet *fleet, Identity as_id, KillFeed *Record, int tableHeight, int tableWidth, int RecordHeight, double difficulty)
{
    Millitary *as = &fleet[as_id.fleet].assets[as_id.millitary];
    Missile *missile = fleet[as_id.fleet].assets[as_id.millitary].missile;
    Missile *core = &fleet[as_id.fleet].assets[as_id.millitary].core;
    
    for(int i = 0; i < MAXMISSILE; i++)
    {
        if(missile[i].status == 0 && missile[i].X != 0 && missile[i].Y != 0)
        {
            memset(&missile[i], 0, sizeof(Missile));
            Pair_Deactivate(fleet, PosIni(as_id.fleet, as_id.millitary, i));
            continue;
        }
        
        Identity target_id = missile[i].target;
        if(missile[i].status != 0)
        {
            Missile *target;
            if(target_id.missile != -1)
                target = &fleet[target_id.fleet].assets[target_id.millitary].missile[target_id.missile];
            else
                target = &fleet[target_id.fleet].assets[target_id.millitary].core;
            if(target->status == 0)
            {
//reassign     
                if(Target_Priority(fleet, PosIni(as_id.fleet, as_id.millitary, i), &core->X, &core->Y, fleet[as_id.fleet].assets[as_id.millitary].Range).fleet == -1)
                {
                    memset(&missile[i], 0, sizeof(Missile));
                    Pair_Deactivate(fleet, PosIni(as_id.fleet, as_id.millitary, i));
                }
            }
        }
    }
    
    if(as->type == 1 && fleet[as->core.target.fleet].assets[as->core.target.millitary].core.status == 0  && as->core.status == 1)
    {
        Identity target_id;

        target_id = Base_Target_Priority(fleet, as_id, fleet[as_id.fleet].assets[as_id.millitary].Range * 2.5);
        if(target_id.fleet == -1){
            RTB_Fighter(fleet, as_id, as_id, 1);
            return;
        }
        else
            as->core.target = target_id;
    }
//Generate
    arrLauch[as->type](fleet, as_id);
    
//Moving 
    
    Base_Moving(fleet, as_id, tableHeight, tableHeight);
    for(int i = 0; i < MAXMISSILE; i++) //later chnage
    {
        if(missile[i].status == 0)
            continue;
        Identity target_id = missile[i].target;
        Missile *target;
        if(target_id.missile != -1)
            target = &fleet[target_id.fleet].assets[target_id.millitary].missile[target_id.missile];
        else
            target = &fleet[target_id.fleet].assets[target_id.millitary].core;
        
        if(missile[i].status == 2)
            Missile_Stationary(&missile[i], &missile[i].X_targeting, &missile[i].Y_targeting);
        else
            Missile_Stationary(&missile[i], &missile[i].X_future, &missile[i].Y_future);
        
        if(!(Missile_Moving(&missile[i], target)))
        {
            Pair_Decre(fleet, PosIni(as_id.fleet, as_id.millitary, i));
            Pair_Deactivate(fleet, PosIni(as_id.fleet, as_id.millitary, i));
            memset(&missile[i], 0, sizeof(Missile));
            Kill_Feed_Record(Record, PosIni(-1, -1, -1), PosIni(as_id.fleet, as_id.millitary, i), 2, RecordHeight);
        }
       
//destroyed 
        //if(fabs(target->X - missile[i].X) < SPE_INTE * missile[i].status / difficulty  && fabs(target->Y - missile[i].Y) < SPE_INTE * missile[i].status / difficulty)
        if(hypot(target->X - missile[i].X, target->Y - missile[i].Y) < SPE_INTE * missile[i].status / difficulty)
        {
            memset(&missile[i], 0, sizeof(Missile));
            target->status = 0;
            Kill_Feed_Record(Record, target_id, PosIni(as_id.fleet, as_id.millitary, i), 1, RecordHeight);
            if(target_id.missile != -1)
            {
                Pair_Decre(fleet, target_id);

                if(fleet[as_id.fleet].pair[target_id.fleet][target_id.millitary][target_id.missile] == 2)
                {
                    Identity pair_missile_id = Pair_Search(fleet, PosIni(as_id.fleet, as_id.millitary, i), target_id);
                    Missile *pair_missile_core = &fleet[pair_missile_id.fleet].assets[pair_missile_id.millitary].core;
                    Missile *pair_missile = &fleet[pair_missile_id.fleet].assets[pair_missile_id.millitary].missile[pair_missile_id.missile];
                    if(Target_Priority(fleet, pair_missile_id, &pair_missile_core->X, &pair_missile_core->Y, fleet[as_id.fleet].assets[as_id.millitary].Range).fleet == -1)
                    {
                        Pair_Deactivate(fleet, pair_missile_id);
                        memset(pair_missile, 0, sizeof(Missile));
                    }
                }
                Pair_Deactivate(fleet, PosIni(as_id.fleet, as_id.millitary, i));
            }
            else{
                for(int i = 0; i < MAXMISSILE; i++)
                {
                    if(fleet[target_id.fleet].assets[target_id.millitary].missile[i].status == 0)
                        continue;
                    Pair_Decre(fleet, PosIni(target_id.fleet, target_id.millitary, i));
                    Pair_Deactivate(fleet, PosIni(target_id.fleet, target_id.millitary, i));
                }
                memset(&fleet[target_id.fleet].assets[target_id.millitary], 0, sizeof(Millitary));
            }
        
        }
    }
}

void Graphing(int fieldHeight, int fieldWidth, int X_Start, int Y_Start, char field[fieldHeight][fieldWidth], Fleet *fleet, Identity as_id, int *Grid_Type, int Radar)
{
//    Grid(fieldHeight, fieldWidth, X_Start, Y_Start, field, *Grid_Type);
    if(Radar)
        Radar_Range(fieldHeight, fieldWidth, Y_Start, X_Start, field, &fleet[as_id.fleet]);
    for(int i = 0; i < FLEET; i++)
    {
        for(int j = 0; j < MILLITARY; j++)
        {
            if(fleet[i].assets[j].core.status == 0)
                continue;
            Base_Grapging(&fleet[i].assets[j].core, as_id, PosIni(i, j, -1),  fieldHeight, fieldWidth, X_Start, Y_Start, field);
        }
    }

    for(int i = 0; i < FLEET; i++)
    {
        for(int j = 0; j < MILLITARY; j++)
        {
            for(int k = 0; k < MAXMISSILE; k++)
            {
                if(fleet[i].assets[j].missile[k].status == 0)
                    continue;
                Missile *missile = &fleet[i].assets[j].missile[k];
                for(int p = 0; p < sizeof(missile->trace); p++)
                {
                    field[range(missile->cordinates[p][1] - Y_Start, fieldHeight)][range(missile->cordinates[p][0] - X_Start, fieldWidth)] = missile->trace[p];
                }
                if(i == as_id.fleet){
                    field[range(missile->Y - Y_Start, fieldHeight)][range(missile->X - X_Start, fieldWidth)] = '#';
                    field[range(missile->Y - 1 - Y_Start, fieldHeight)][range(missile->X + 3 - X_Start, fieldWidth)] = numbers[k];
                    field[range(missile->Y - 1 - Y_Start, fieldHeight)][range(missile->X + 2 - X_Start, fieldWidth)] = 65 + j;
                }
                else{
                    field[range(missile->Y - Y_Start, fieldHeight)][range(missile->X - X_Start, fieldWidth)] = '*';
                    field[range(missile->Y - 1 - Y_Start, fieldHeight) ][range(missile->X + 1 - X_Start, fieldWidth)] = 65 + i + 10;
                    field[range(missile->Y - 1 - Y_Start, fieldHeight) ][range(missile->X + 2 - X_Start, fieldWidth)] = 65 + j;
                    field[range(missile->Y - 1 - Y_Start, fieldHeight) ][range(missile->X + 3 - X_Start, fieldWidth)] = 48 + k;
                }
            }
        }
    }

    for(int i = MILLITARY - 1; i >= 0; i--)
    {
        for(int j = 0; j < MAXMISSILE; j++)
        {
            Missile *missile = fleet[as_id.fleet].assets[i].missile;
            if(missile[j].status == 0)
                continue;
            
            ImpactPoint_Draw(&missile[j], fieldHeight, fieldWidth, X_Start, Y_Start, field, PosIni(-1, i, j));
            
            int Lock_On;
            Identity pair[2];
            Identity target_id = missile[j].target;
            Missile *target;
            if(target_id.missile != -1)
                target = &fleet[target_id.fleet].assets[target_id.millitary].missile[target_id.missile];
            else
                target = &fleet[target_id.fleet].assets[target_id.millitary].core;
                
            if(Target_Lock_On(&fleet[as_id.fleet], target_id, pair))
                Lock_On = 1;
            else
                Lock_On = 0;
            
            Lock_On_Draw(target, Lock_On, fieldHeight, fieldWidth, X_Start, Y_Start, field, target_id, pair);
            
        }
    }
    
}

void Control(Fleet *fleet, Identity as_id, int *Grid_Type, int Full_Control, int *Radar, int fieldHeight, int fieldWidth, int tableHeight, int tableWidth, int *X_Start, int *Y_Start, int *font, int *Grid_Update)
{
    switch(_getch())
    {
        case '1':  break;
        case 'g': printf("Grid type(Plain: 0 Normal: 1 Simple: 2 Advanced: 3) : "); *Grid_Type = (_getch() - 48); printf("%d", *Grid_Type); *Grid_Update = 2; break;
        case 'm': Missile_Manual(&fleet[as_id.fleet], as_id, Full_Control); break;
        case 'z': Missile_Auto(&fleet[as_id.fleet], as_id, Full_Control); break;
        case 'c': Missile_Reassign(fleet, as_id, Full_Control); break;
        case 'b': *Radar = !(*Radar); break;
        case 'w':  *Y_Start = (int)range(*Y_Start - 10, tableHeight - 21 - fieldHeight); *Grid_Update = 2; break;
        case 'a':  *X_Start = (int)range(*X_Start - 20, tableWidth - 21 - fieldWidth); *Grid_Update = 2; break;
        case 's':  *Y_Start = (int)range(*Y_Start + 10, tableHeight - 21 - fieldHeight); *Grid_Update = 2; break;
        case 'd':  *X_Start = (int)range(*X_Start + 20, tableWidth - 21 - fieldWidth); *Grid_Update = 2; break;
        case 'v': (*font)++; *Grid_Update = 2; break;
        case 'f': (*font)--; *font = *font < 5 ? 5 : *font; *Grid_Update = 2; break;
        case 'r': RTB_Fighter(fleet, as_id, PosIni(-1,-1,-1), 0); break;
        case 'k': break;
//        case 'l': Manual_Launch[0] = Manual_Launch[0] == -1 ? 2 : 1; break;
//        case 'f': *fire = 1; printf("Fire");  break;
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

int range(double num, int limit)
{
    if(0 > num || num > limit)
        return 0;
    return (int)num;
}

Identity Target_Priority(Fleet* fleet, Identity identity, const double *baseX, const double *baseY, int Range)
{
    Identity nMinPos, nMinPos_Unmarked, base_attack;
    Missile *missile = &fleet[identity.fleet].assets[identity.millitary].missile[identity.missile];
    nMinPos = PosIni(-1, -1, -1);
    nMinPos_Unmarked = PosIni(-1, -1, -1);
    base_attack = Base_Attack(fleet, identity, Range);
    
    double distance[FLEET][MILLITARY][MAXMISSILE] = {};
    
    for(int i = 0; i < FLEET; i++)
    {
        if(i == identity.fleet)
            continue;
        for(int j = 0; j < MILLITARY; j++)
        {
            for(int k = 0; k < MAXMISSILE; k++)
            {
                if(fleet[identity.fleet].pair[i][j][k] == -1 || fleet[identity.fleet].pair[i][j][k] >= 2)
                    continue;
                distance[i][j][k] = hypot(*baseX - fleet[i].assets[j].missile[k].X, *baseY - fleet[i].assets[j].missile[k].Y);
                if(hypot(*baseX - fleet[i].assets[j].missile[k].X, (*baseY - fleet[i].assets[j].missile[k].Y) * 2) > Range)
                    continue;
                double run = fleet[i].assets[j].missile[k].X - missile->X;
                double rise = missile->Y - fleet[i].assets[j].missile[k].Y;
                double Constant = fleet[i].assets[j].missile[k].speed / missile->speed * (run * sin(fleet[i].assets[j].missile[k].direction) - rise * cos(fleet[i].assets[j].missile[k].direction));
                double Limit = pow(run, 2) + pow(rise, 2);
                if(Limit < pow(Constant, 2))
                    continue;
                if(distance[nMinPos.fleet][nMinPos.millitary][nMinPos.missile] > distance[i][j][k] || nMinPos.fleet == -1)
                {
                    nMinPos = PosIni(i, j, k);
                }
                //pair is initialized with -1
                if(fleet[identity.fleet].pair[i][j][k] == 0 && (distance[nMinPos_Unmarked.fleet][nMinPos_Unmarked.millitary][nMinPos_Unmarked.missile] > distance[i][j][k] || nMinPos_Unmarked.fleet == -1))
                {
                    nMinPos_Unmarked = PosIni(i, j, k);
                }
            }
        }
    }
    
    //Emergency situation. Hostile missile is within 60m range
    if(distance[nMinPos.fleet][nMinPos.millitary][nMinPos.missile] < (30 * SPE_INTE) && nMinPos.fleet != -1)
    {
        missile->target = nMinPos;
        fleet[identity.fleet].pair[nMinPos.fleet][nMinPos.millitary][nMinPos.missile]++;
        return nMinPos;
    }
    
    //if there are unmarked missile mMinPos_Unmarked gives pos and if there are no unmarked missiles then nMinPos_unmarked is 0 that is base attack
    if(nMinPos_Unmarked.fleet != -1)
    {
        missile->target = nMinPos_Unmarked;
        fleet[identity.fleet].pair[nMinPos_Unmarked.fleet][nMinPos_Unmarked.millitary][nMinPos_Unmarked.missile]++;
        return nMinPos_Unmarked;
    }
    //base attack unmarked 
    if(base_attack.missile == 0)
    {
        base_attack.missile = -1;
        missile->target = base_attack;
        fleet[identity.fleet].pair_base[base_attack.fleet][base_attack.millitary]++;
        return base_attack;
    }
    //second attack
    if(nMinPos.fleet != -1)
    {
        missile->target = nMinPos;
        fleet[identity.fleet].pair[nMinPos.fleet][nMinPos.millitary][nMinPos.missile]++;
        return nMinPos;
    }
    //second base attack
    if(base_attack.missile != -1)
    {
        base_attack.missile = -1;
        missile->target = base_attack;
        fleet[identity.fleet].pair_base[base_attack.fleet][base_attack.millitary]++;
        return base_attack;
    }
    else
        return PosIni(-1, -1, -1);
}

Identity Base_Attack(Fleet *fleet, Identity as_id, int Range)
{
    Identity nMinPos = {-1, -1, -1};
    Missile* core = &fleet[as_id.fleet].assets[as_id.millitary].core;
    Missile* missile = &fleet[as_id.fleet].assets[as_id.millitary].missile[as_id.missile];
    double distance[FLEET][MILLITARY];
    
    for(int i = 0; i < FLEET; i++)
    {
        for(int j = 0; j < MILLITARY; j++)
        {
            if(fleet[as_id.fleet].pair_base[i][j] == -1 || fleet[as_id.fleet].pair_base[i][j] >= 2 || fleet[i].assets[j].core.status == 0 || i == as_id.fleet)
                continue;
            double run = fleet[i].assets[j].core.X - missile->X;
            double rise = missile->Y - fleet[i].assets[j].core.Y;
            double Constant = fleet[i].assets[j].core.speed / missile->speed * (run * sin(fleet[i].assets[j].core.direction) - rise * cos(fleet[i].assets[j].core.direction));
            double Limit = pow(run, 2) + pow(rise, 2);
            if(Limit < pow(Constant, 2))
                continue;
            distance[i][j] = hypot(core->X - fleet[i].assets[j].core.X, core->Y - fleet[i].assets[j].core.Y);                                                                                      //first time 
            if(hypot(core->X - fleet[i].assets[j].core.X, (core->Y - fleet[i].assets[j].core.Y) * 2) < Range && (distance[i][j] < distance[nMinPos.fleet][nMinPos.millitary] || nMinPos.fleet == -1))
            {
                nMinPos = PosIni(i, j, 0);
            }
        } 
    }
    return nMinPos;
}

Identity Base_Target_Priority(Fleet *fleet, Identity as_id, int Range)
{
    Identity nMinPos = {-1, -1, -1};
    Missile* core = &fleet[as_id.fleet].assets[as_id.millitary].core;
    
    double distance[FLEET][MILLITARY];
    
    for(int i = 0; i < FLEET; i++)
    {
        for(int j = 0; j < MILLITARY; j++)
        {
            if(fleet[i].assets[j].core.status == 0 || i == as_id.fleet)
                continue;
            
            distance[i][j] = hypot(core->X - fleet[i].assets[j].core.X, core->Y - fleet[i].assets[j].core.Y);                                                                                      //first time 
            if(hypot(core->X - fleet[i].assets[j].core.X, (core->Y - fleet[i].assets[j].core.Y) * 2) < Range && (distance[i][j] < distance[nMinPos.fleet][nMinPos.millitary] || nMinPos.fleet == -1))
            {
                nMinPos = PosIni(i, j, -1);
            }
        } 
    }
    return nMinPos;
}

void Agis_Launch(Fleet *fleet, Identity as_id)
{
    Millitary *as = &fleet[as_id.fleet].assets[as_id.millitary];
    Missile *core = &fleet[as_id.fleet].assets[as_id.millitary].core;
    Missile *missile = fleet[as_id.fleet].assets[as_id.millitary].missile;
    if((as->interval = range(--(as->interval), 30)) == 0)
    {
        int No_Missile = Available_Missile(missile, MAXMISSILE); // later change
        
        if(No_Missile != -1)
        {
            Identity target_id;
            Missile *target;
            missile[No_Missile].speed = SPE_INTE;
            missile[No_Missile].X = core->X;
            missile[No_Missile].Y = core->Y;
            target_id = Target_Priority(fleet, PosIni(as_id.fleet, as_id.millitary, No_Missile), &core->X, &core->Y, fleet[as_id.fleet].assets[as_id.millitary].Range);
            
            if(target_id.fleet != -1){
                if(target_id.missile != -1)
                    target = &fleet[target_id.fleet].assets[target_id.millitary].missile[target_id.missile];
                else
                    target = &fleet[target_id.fleet].assets[target_id.millitary].core;
                missile[No_Missile].status = 1;
                Generator_Interceptor(&missile[No_Missile], target, core->X, core->Y);
                Pair_Activate(fleet, PosIni(as_id.fleet, as_id.millitary, No_Missile));
                missile[No_Missile].target = target_id;
                as->interval += fleet[as_id.fleet].assets[as_id.millitary].timer;
            }
            else
                memset(&missile[No_Missile], 0, sizeof(Missile));
        }
    }
}

void Fighter_Launch(Fleet *fleet, Identity as_id)
{
    Millitary *as = &fleet[as_id.fleet].assets[as_id.millitary];
    Missile *core = &fleet[as_id.fleet].assets[as_id.millitary].core;
    Missile *missile = fleet[as_id.fleet].assets[as_id.millitary].missile;
    if((as->interval = range(--(as->interval), 30)) == 0)
    {
        int No_Missile = Available_Missile(missile, 2); // later change
        
        if(No_Missile != -1)
        {
            Identity target_id;
            Missile *target;
            missile[No_Missile].speed = SPE_INTE * 2;
            missile[No_Missile].X = core->X;
            missile[No_Missile].Y = core->Y;
            target_id = Target_Priority(fleet, PosIni(as_id.fleet, as_id.millitary, No_Missile), &core->X, &core->Y, fleet[as_id.fleet].assets[as_id.millitary].Range);
            
            if(target_id.fleet != -1){
                if(target_id.missile != -1)
                    target = &fleet[target_id.fleet].assets[target_id.millitary].missile[target_id.missile];
                else
                    target = &fleet[target_id.fleet].assets[target_id.millitary].core;
                missile[No_Missile].status = 1;
                Generator_Interceptor(&missile[No_Missile], target, core->X, core->Y);
                missile[No_Missile].speed = SPE_INTE * 2;
                Pair_Activate(fleet, PosIni(as_id.fleet, as_id.millitary, No_Missile));
                missile[No_Missile].target = target_id;
                as->interval += fleet[as_id.fleet].assets[as_id.millitary].timer;
            }
            else
                memset(&missile[No_Missile], 0, sizeof(Missile));
        }
    }
}

void AircraftCarrier_Launch(Fleet *fleet, Identity as_id)
{
    Millitary *as = &fleet[as_id.fleet].assets[as_id.millitary];
    Missile *core = &fleet[as_id.fleet].assets[as_id.millitary].core;
    Missile *missile = fleet[as_id.fleet].assets[as_id.millitary].missile;
    if((as->interval = range(--(as->interval), 200)) == 0)
    {
        int No_Missile = Available_Missile(missile, 2); // later change
        
        if(No_Missile != -1)
        {
            Identity target_id;
            Missile *target;
            missile[No_Missile].speed = SPE_INTE;
            missile[No_Missile].X = core->X;
            missile[No_Missile].Y = core->Y;
            target_id = Target_Priority(fleet, PosIni(as_id.fleet, as_id.millitary, No_Missile), &core->X, &core->Y, fleet[as_id.fleet].assets[as_id.millitary].Range / 3);
            
            if(target_id.fleet != -1){
                if(target_id.missile != -1)
                    target = &fleet[target_id.fleet].assets[target_id.millitary].missile[target_id.missile];
                else
                    target = &fleet[target_id.fleet].assets[target_id.millitary].core;
                missile[No_Missile].status = 1;
                Generator_Interceptor(&missile[No_Missile], target, core->X, core->Y);
                Pair_Activate(fleet, PosIni(as_id.fleet, as_id.millitary, No_Missile));
                missile[No_Missile].target = target_id;
                as->interval += fleet[as_id.fleet].assets[as_id.millitary].timer / 2;
            }
            else
                memset(&missile[No_Missile], 0, sizeof(Missile));
        }
    }
    
//    if((as->interval = range(--(as->interval), 30)) % 2 == 0) && as->MaxAssets > 0)
    if((as->interval = range(--(as->interval), 200)) == 0)
    {
        int No_Fighter = Available_Assets(&fleet[as_id.fleet], MILLITARY, 1); // later change
        Millitary *fighter = &fleet[as_id.fleet].assets[No_Fighter];
        if(No_Fighter != -1)
        {
            Identity target_id;
            Missile *target;
            
            target_id = Base_Target_Priority(fleet, as_id, fleet[as_id.fleet].assets[as_id.millitary].Range);
            if(target_id.fleet != -1)
            {
                target = &fleet[target_id.fleet].assets[target_id.millitary].core;
                
                Fighter_Initialize(fighter, target, core->X, core->Y);
                Pair_Activate(fleet, PosIni(as_id.fleet, No_Fighter, -1));
                fighter->core.target = target_id;
                as->interval += fleet[as_id.fleet].assets[as_id.millitary].timer;
            }
//            as->MaxAssets--;
        }
    }
}

void AirBase_Launch(Fleet *fleet, Identity as_id)
{
    Millitary *as = &fleet[as_id.fleet].assets[as_id.millitary];
    Missile *core = &fleet[as_id.fleet].assets[as_id.millitary].core;
    Missile *missile = fleet[as_id.fleet].assets[as_id.millitary].missile;
    
    if((as->interval = range(--(as->interval), 200)) == 0)
    {
        int No_Missile = Available_Missile(missile, 2); // later change
        
        if(No_Missile != -1)
        {
            Identity target_id;
            Missile *target;
            missile[No_Missile].speed = SPE_INTE;
            missile[No_Missile].X = core->X;
            missile[No_Missile].Y = core->Y;
            target_id = Target_Priority(fleet, PosIni(as_id.fleet, as_id.millitary, No_Missile), &core->X, &core->Y, fleet[as_id.fleet].assets[as_id.millitary].Range / 2);
            
            if(target_id.fleet != -1){
                if(target_id.missile != -1)
                    target = &fleet[target_id.fleet].assets[target_id.millitary].missile[target_id.missile];
                else
                    target = &fleet[target_id.fleet].assets[target_id.millitary].core;
                missile[No_Missile].status = 1;
                Generator_Interceptor(&missile[No_Missile], target, core->X, core->Y);
                Pair_Activate(fleet, PosIni(as_id.fleet, as_id.millitary, No_Missile));
                missile[No_Missile].target = target_id;
                as->interval += fleet[as_id.fleet].assets[as_id.millitary].timer / 2;
            }
            else
                memset(&missile[No_Missile], 0, sizeof(Missile));
        }
    }
    
    if((as->interval = range(--(as->interval), 200)) == 0) //&& as->MaxAssets > 0)
    {
        int No_Fighter = Available_Assets(&fleet[as_id.fleet], MILLITARY, 1); // later change
        Millitary *fighter = &fleet[as_id.fleet].assets[No_Fighter];
        if(No_Fighter != -1)
        {
            Identity target_id;
            Missile *target;
            
            target_id = Base_Target_Priority(fleet, as_id, fleet[as_id.fleet].assets[as_id.millitary].Range / 1.5);
            if(target_id.fleet != -1)
            {
                target = &fleet[target_id.fleet].assets[target_id.millitary].core;
                
                Fighter_Initialize(fighter, target, core->X, core->Y);
                Pair_Activate(fleet, PosIni(as_id.fleet, No_Fighter, -1));
                fighter->core.target = target_id;
                as->interval += fleet[as_id.fleet].assets[as_id.millitary].timer;
            }
//            as->MaxAssets--;
        }
    }
    
    if((as->interval = range(--(as->interval), 200)) == 0) //&& as->MaxAssets > 0)
    {
        int No_Fighter = Available_Assets(&fleet[as_id.fleet], MILLITARY, 4); // later change
        Millitary *fighter = &fleet[as_id.fleet].assets[No_Fighter];
        if(No_Fighter != -1)
        {
            Identity target_id;
            Missile *target;
            
            target_id = Base_Target_Priority(fleet, as_id, fleet[as_id.fleet].assets[as_id.millitary].Range);
            if(target_id.fleet != -1)
            {
                target = &fleet[target_id.fleet].assets[target_id.millitary].core;
                
                Stealth_Fighter_Initialize(fighter, target, core->X, core->Y);
                Pair_Activate(fleet, PosIni(as_id.fleet, No_Fighter, -1));
                fighter->core.target = target_id;
                as->interval += fleet[as_id.fleet].assets[as_id.millitary].timer * 1.5;
            }
//            as->MaxAssets--;
        }
    }
}

void Stealth_Fighter_Launch(Fleet *fleet, Identity as_id)
{
    Millitary *as = &fleet[as_id.fleet].assets[as_id.millitary];
    Missile *core = &fleet[as_id.fleet].assets[as_id.millitary].core;
    Missile *missile = fleet[as_id.fleet].assets[as_id.millitary].missile;
    if((as->interval = range(--(as->interval), 200)) == 0)
    {
        int No_Missile = Available_Missile(missile, 2); // later change
        
        if(No_Missile != -1)
        {
            Identity target_id;
            Missile *target;
            missile[No_Missile].speed = SPE_INTE * 3;
            missile[No_Missile].X = core->X;
            missile[No_Missile].Y = core->Y;
            target_id = Target_Priority(fleet, PosIni(as_id.fleet, as_id.millitary, No_Missile), &core->X, &core->Y, fleet[as_id.fleet].assets[as_id.millitary].Range);
            
            if(target_id.fleet != -1){
                if(target_id.missile != -1)
                    target = &fleet[target_id.fleet].assets[target_id.millitary].missile[target_id.missile];
                else
                    target = &fleet[target_id.fleet].assets[target_id.millitary].core;
                missile[No_Missile].status = 1;
                Generator_Interceptor(&missile[No_Missile], target, core->X, core->Y);
                missile[No_Missile].speed = SPE_INTE * 3;
                Pair_Activate(fleet, PosIni(as_id.fleet, as_id.millitary, No_Missile));
                missile[No_Missile].target = target_id;
                as->interval += fleet[as_id.fleet].assets[as_id.millitary].timer;
            }
            else
                memset(&missile[No_Missile], 0, sizeof(Missile));
        }
    }
}

void Base_Moving(Fleet *fleet, Identity as_id, int tableHeight, int tableWidth)
{
    Missile *Base = &fleet[as_id.fleet].assets[as_id.millitary].core;
    if(Base->status == 1)
    {
        Missile *target = &fleet[Base->target.fleet].assets[Base->target.millitary].core; //expect only base targets
        Missile_Moving(Base, target);
        Base->X_targeting = Base->X_future;
        Base->Y_targeting = Base->Y_future;
    }
    Missile_Stationary(Base, &Base->X_targeting, &Base->Y_targeting);
    if(fabs(Base->X_targeting - Base->X) < Base->speed * 5 && fabs(Base->Y_targeting - Base->Y) < Base->speed * 5)
    {
        Base->X_targeting = rand() % tableWidth;
        Base->Y_targeting = rand() % tableHeight;
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

bool Missile_Moving(Missile *Interceptor, const Missile *Hostile)
{
    double run = Hostile->X - Interceptor->X;
    double rise = Interceptor->Y - Hostile->Y;
    
    double Constant = Hostile->speed / Interceptor->speed * (run * sin(Hostile->direction) - (rise * cos(Hostile->direction)));
    double Square_root = pow(rise, 2) * pow(Constant, 2) - ((pow(run, 2) + pow(rise, 2)) * (pow(Constant, 2) - pow(run, 2)));
    
    Error_Record = Square_root;
    if(Square_root < 0)
        return false;
    if(M_PI / 3 < fabs(Interceptor->direction - to_deg360_Tri(run, -1 * rise)) && fabs(Interceptor->direction - to_deg360_Tri(run, -1 *rise)) < M_PI / 3 * 5 && fabs(run) < 10  && fabs(rise) < 10)
        return false;
    double angle_plus =  acos((sqrt(Square_root) - (rise * Constant)) / (pow(run, 2) + pow(rise, 2)));
    double angle_minus = acos(-1 * (sqrt(Square_root) + (rise * Constant)) / (pow(run, 2) + pow(rise, 2)));
    double time_travel_plus = run / (Interceptor->speed * cos(angle_plus) - Hostile->speed * cos(Hostile->direction));
    double time_travel_minus = run / (Interceptor->speed * cos(angle_minus) - Hostile->speed * cos(Hostile->direction));
    
    if((time_travel_plus < time_travel_minus && time_travel_plus > 0) || (time_travel_minus < 0))
        Interceptor->time_impact = time_travel_plus;
    else
        Interceptor->time_impact = time_travel_minus;

    Interceptor->X_future = Hostile->X + Hostile->speed * Interceptor->time_impact * cos(Hostile->direction);
    Interceptor->Y_future = Hostile->Y - Hostile->speed * Interceptor->time_impact * sin(Hostile->direction);
    return true;
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

void Generator_Interceptor(Missile *Interceptor, Missile *Hostile, double Launch_X, double Launch_Y)
{
    srand(time(NULL));
    Interceptor->X = Launch_X;
    Interceptor->Y = Launch_Y;
    Interceptor->direction = Missile_Angle_Ini(Interceptor, Hostile);
    record_cordinates(Interceptor);
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

void Base_Initialize(Missile *Base, double base_X, double base_Y, double target_X, double target_Y)
{
    Base->speed = SPE_INTE / (double)4;
    Base->X = base_X;
    Base->Y = base_Y;
    Base->X_targeting = target_X;
    Base->Y_targeting = target_Y;
    Base->direction = to_deg360_Tri(target_X - base_X, target_Y - base_Y);
    Base->status = 2;
}

void Agis_Initialize(Millitary *Agis, double Launch_X, double Launch_Y, double target_X, double target_Y)
{
    Agis->type = 0;
    Agis->Range = 125;
    Agis->timer = 20;
    Agis->core.status = 2;
    Agis->core.speed = SPE_INTE / (double)4;
    Agis->core.X = Launch_X;
    Agis->core.Y = Launch_Y;
    Agis->core.X_targeting = target_X;
    Agis->core.Y_targeting = target_Y;
    Agis->core.direction = to_deg360_Tri(target_X - Launch_X, target_Y - Launch_Y);
}

void Fighter_Initialize_Start(Millitary *Fighter, double Launch_X, double Launch_Y, double target_X, double target_Y)
{
    Fighter->type = 1;
    Fighter->Range = 50;
    Fighter->timer = 25;
    Fighter->core.status = 2;
    Fighter->core.speed = SPE_INTE;
    Fighter->core.X = Launch_X;
    Fighter->core.Y = Launch_Y;
    Fighter->core.X_targeting = target_X;
    Fighter->core.Y_targeting = target_Y;
    Fighter->core.direction = to_deg360_Tri(target_X - Launch_X, target_Y - Launch_Y);
}

void AircraftCarrier_Initialize_Start(Millitary *AircraftCarrier, double Launch_X, double Launch_Y, double target_X, double target_Y)
{
    AircraftCarrier->type = 2;
    AircraftCarrier->Range = 125;
    AircraftCarrier->timer = 100;
    AircraftCarrier->MaxAssets = 2;
    AircraftCarrier->core.status = 2;
    AircraftCarrier->core.speed = SPE_INTE / (double)4;
    AircraftCarrier->core.X = Launch_X;
    AircraftCarrier->core.Y = Launch_Y;
    AircraftCarrier->core.X_targeting = target_X;
    AircraftCarrier->core.Y_targeting = target_Y;
    AircraftCarrier->core.direction = to_deg360_Tri(target_X - Launch_X, target_Y - Launch_Y);
}

void AirBase_Initialize_Start(Millitary *AircraftBase, double Launch_X, double Launch_Y, double target_X, double target_Y)
{
    AircraftBase->type = 3;
    AircraftBase->Range = 250;
    AircraftBase->timer = 50;
    AircraftBase->MaxAssets = 12;
    AircraftBase->core.status = 2;
    AircraftBase->core.speed = 0;
    AircraftBase->core.X = Launch_X;
    AircraftBase->core.Y = Launch_Y;
}

void Stealth_Fighter_Initialize_Start(Millitary *Fighter, double Launch_X, double Launch_Y, double target_X, double target_Y)
{
    Fighter->type = 4;
    Fighter->Range = 200;
    Fighter->timer = 50;
    Fighter->core.status = 2;
    Fighter->core.speed = SPE_INTE * 1.5;
    Fighter->core.X = Launch_X;
    Fighter->core.Y = Launch_Y;
    Fighter->core.X_targeting = target_X;
    Fighter->core.Y_targeting = target_Y;
    Fighter->core.direction = to_deg360_Tri(target_X - Launch_X, target_Y - Launch_Y);
}

void Fighter_Initialize(Millitary *assets, Missile *target, double Launch_X, double Launch_Y)
{
    assets->timer = 25;
    assets->Range = 50;
    assets->core.status = 1;
    assets->core.speed = SPE_INTE;
    assets->core.X = Launch_X;
    assets->core.Y = Launch_Y;
    assets->core.direction = Missile_Angle_Ini(&assets->core, target);
    record_cordinates(&assets->core);
}

void Stealth_Fighter_Initialize(Millitary *assets, Missile *target, double Launch_X, double Launch_Y)
{
    assets->timer = 50;
    assets->Range = 200;
    assets->core.status = 1;
    assets->core.speed = SPE_INTE * 1.5;
    assets->core.X = Launch_X;
    assets->core.Y = Launch_Y;
    assets->core.direction = Missile_Angle_Ini(&assets->core, target);
    record_cordinates(&assets->core);
}

void Missile_Initialize(Missile *missile, double Pos_X, double Pos_Y, double future_X, double future_Y)
{
    missile->speed = SPE_INTE / (double)4;
    missile->X = Pos_X;
    missile->Y = Pos_Y;
    missile->X_future = future_X;
    missile->Y_future = future_Y;
    missile->direction = to_deg360_Tri(future_X - Pos_X, future_Y - Pos_Y);
    missile->status = 1;
}

void Base_Grapging(Missile *Base, Identity friendly_id, Identity Base_id, const int fieldHeight, const int fieldWidth, int X_Start, int Y_Start, char (*field)[fieldWidth])
{
    for(int i = 0; i < sizeof(Base->trace); i++)
    {
        field[range(Base->cordinates[i][1] - Y_Start, fieldHeight)][range(Base->cordinates[i][0] - X_Start, fieldWidth)] = Base->trace[i];
    }
    
   // if(Comp_Struct(friendly_id, Base_id)){
    if(friendly_id.fleet == Base_id.fleet){
        for(int i = 0; i < 5; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                if(i < 3 && j < 5 && !(i == 1 && j == 2)){
                    field[range((int)Base->Y_targeting - Y_Start, fieldHeight)][range((int)Base[0].X_targeting - X_Start, fieldWidth)] = '+';
                    field[range(Base->Y_targeting - 1 + i - Y_Start, fieldHeight)][range(Base->X_targeting - 2 + j - X_Start, fieldWidth)] = ImpactPoint[i][j];
                    field[range(Base->Y_targeting - 1 - Y_Start, fieldHeight)][range(Base->X_targeting + 1 - X_Start, fieldWidth)] = Base_id.millitary + 65;
                    field[range((int)Base->Y_targeting - 1 - Y_Start, fieldHeight)][range((int)Base->X_targeting - 1 - X_Start, fieldWidth)] = alphabets[(int)(Base->X_targeting / 10 - 1) % 26];
                                                                                                                                                    
                    field[range((int)Base->Y_targeting - 1 - Y_Start, fieldHeight)][range((int)Base->X_targeting - 2 - X_Start, fieldWidth)] = (int)(Base->X_targeting / 260) == 0 ? 32 : alphabets[(int)(Base->X_targeting / 260) % 26 - 1];
                    field[range((int)Base->Y_targeting + 1 - Y_Start, fieldHeight)][range((int)Base->X_targeting - 3 - X_Start, fieldWidth)] = numbers[(int)Base->Y_targeting / 50 % 10];
                    field[range((int)Base->Y_targeting + 1 - Y_Start, fieldHeight)][range((int)Base->X_targeting - 2 - X_Start, fieldWidth)] = 48 + (int)Base->Y_targeting / 5 % 10;
                    field[range((int)Base->Y_targeting + 1 - Y_Start, fieldHeight)][range((int)Base->X_targeting - 1 - X_Start, fieldWidth)] = 48 + (int)Base->X_targeting % 10 / 3 + (int)Base->Y_targeting % 5 / 2 * 3;
                }
            }
        }
    }
    
    if(friendly_id.fleet == Base_id.fleet){
        field[range(Base->Y - Y_Start, fieldHeight)][range(Base->X - X_Start, fieldWidth)] = '@';
        field[range(Base->Y - 1 - Y_Start, fieldHeight)][range(Base->X + 1 - X_Start, fieldWidth)] = 65 + Base_id.millitary;
    }
    else{
        field[range(Base->Y - Y_Start, fieldHeight)][range(Base->X - X_Start, fieldWidth)] = '*';
        field[range(Base->Y - 1 - Y_Start, fieldHeight)][range(Base->X + 1 - X_Start, fieldWidth)] = 65 + Base_id.fleet + 10;
        field[range(Base->Y - 1 - Y_Start, fieldHeight)][range(Base->X + 2 - X_Start, fieldWidth)] = 65 + Base_id.millitary;
    }
}

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
            if(i % 150 == 2 && j % 10 == 0){
                field[i][j] = alphabets[((j + X_Start) / 10 - 1) % 26];
                field[i][j - 1] = alphabets[((j + X_Start - 10) / 260 - 1) % 26];
            }
            if(i % 5 == 0 && j % 600 == 10){
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

Identity PosIni(int i, int j, int k)
{
    Identity Pos;
    
    Pos.fleet = i;
    Pos.millitary = j;
    Pos.missile = k;
    
    return Pos;
}

void Lock_On_Draw(Missile *target, int Lock_On, int fieldHeight, int fieldWidth, int X_Start, int Y_Start, char field[][fieldWidth], Identity target_id, Identity Interceptor[2])
{
    if(Interceptor[0].fleet != -1)
    {
        for(int i = 0; i < 5; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                if(Lock_On)
                    field[range(target->Y - 2 + i - Y_Start, fieldHeight) ][range(target->X - 3 + j - X_Start, fieldWidth)] = lockOn01[i][j];
                else
                    field[range(target->Y - 2 + i - Y_Start, fieldHeight)][range(target->X - 3 + j - X_Start, fieldWidth)] = Laser[i][j];


                field[range(target->Y - 1 - Y_Start, fieldHeight) ][range(target->X + 4 - X_Start, fieldWidth)] = numbers[Interceptor[0].missile];
                field[range(target->Y - 1 - Y_Start, fieldHeight) ][range(target->X + 3 - X_Start, fieldWidth)] = 65 + Interceptor[0].millitary;
                if(Interceptor[1].fleet != -1){
                    field[range(target->Y + 1 - Y_Start, fieldHeight) ][range(target->X + 4 - X_Start, fieldWidth)] = numbers[Interceptor[1].missile];
                    field[range(target->Y + 1 - Y_Start, fieldHeight) ][range(target->X + 3 - X_Start, fieldWidth)] = 65 + Interceptor[1].millitary;
                }
//                else
//                    field[range(target->Y + 1, fieldHeight) ][range(target->X + 4, fieldWidth)] = ' ';
//                    field[range(target->Y + 1, fieldHeight) ][range(target->X + 3, fieldWidth)] = ' ';

            }
        }
    }
    field[range(target->Y - Y_Start, fieldHeight)][range(target->X - X_Start, fieldWidth)] = '*';
    field[range(target->Y - 2 - Y_Start, fieldHeight) ][range(target->X + 1 - X_Start, fieldWidth)] = 65 + target_id.fleet + 10;
    field[range(target->Y - 2 - Y_Start, fieldHeight) ][range(target->X + 2 - X_Start, fieldWidth)] = 65 + target_id.millitary;
    field[range(target->Y - 2 - Y_Start, fieldHeight) ][range(target->X + 3 - X_Start, fieldWidth)] = 48 + target_id.missile;
//    field[range(Hostile[p].Y - 1 + q * 2, fieldHeight) ][range(Hostile[p].X + 3, fieldWidth)] = numbers[pair[p][q]];
}

void ImpactPoint_Draw(Missile* missile, int fieldHeight, int fieldWidth, int X_Start, int Y_Start, char field[][fieldWidth], Identity missile_id)
{
    if(missile->lock_On)
    {
        for(int i = 0; i < 5; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                if(i < 3 && j < 5 && !(i == 1 && j == 2)){
                    if(missile->status == 1){
                        field[range(missile->Y_future - 1 + i - Y_Start, fieldHeight)][range(missile->X_future - 2 + j - X_Start, fieldWidth)] = ImpactPoint[i][j];
                        field[range(missile->Y_future - 1 - Y_Start, fieldHeight)][range(missile->X_future + 2 - X_Start, fieldWidth)] = numbers[missile_id.missile];
                        field[range(missile->Y_future - 1 - Y_Start, fieldHeight)][range(missile->X_future + 1 - X_Start, fieldWidth)] = 65 + missile_id.millitary;
                    }
                    if(missile->status == 2){
                        field[range(missile->Y_targeting - Y_Start, fieldHeight)][range(missile->X_targeting - X_Start, fieldWidth)] = '+';
                        field[range(missile->Y_targeting - 1 + i - Y_Start, fieldHeight)][range(missile->X_targeting - 2 + j - X_Start, fieldWidth)] = ImpactPoint[i][j];
                        field[range(missile->Y_targeting - 1 - Y_Start, fieldHeight)][range(missile->X_targeting + 2 - X_Start, fieldWidth)] = numbers[missile_id.missile];
                        field[range(missile->Y_targeting - 1 - Y_Start, fieldHeight)][range(missile->X_targeting + 1 - X_Start, fieldWidth)] = 65 + missile_id.millitary;
                        field[range((int)missile->Y_targeting - 1 - Y_Start, fieldHeight)][range((int)missile->X_targeting - 1 - X_Start, fieldWidth)] = alphabets[(int)(missile->X_targeting / 10 - 1) % 26];
                        field[range((int)missile->Y_targeting - 1 - Y_Start, fieldHeight)][range((int)missile->X_targeting - 2 - X_Start, fieldWidth)] = (int)(missile->X_targeting / 260) == 0 ? 32 : alphabets[(int)(missile->X_targeting / 260) % 26 - 1];
                        field[range((int)missile->Y_targeting - 1 - Y_Start, fieldHeight)][range((int)missile->X_targeting - 3 - X_Start, fieldWidth)] = numbers[(int)missile->Y_targeting / 50 % 10];
                        field[range((int)missile->Y_targeting + 1 - Y_Start, fieldHeight)][range((int)missile->X_targeting - 2 - X_Start, fieldWidth)] = 48 + (int)missile->Y_targeting / 5;
                        field[range((int)missile->Y_targeting + 1 - Y_Start, fieldHeight)][range((int)missile->X_targeting - 1 - X_Start, fieldWidth)] = 48 + (int)missile->X_targeting % 10 / 3 + (int)missile->Y_targeting % 5 / 2 * 3;
                    }
                }
            }
        }
    }
    field[range(missile->Y_future - Y_Start, fieldHeight)][range(missile->X_future - X_Start, fieldWidth)] = '+';
    
}

bool Target_Lock_On(Fleet *fleet, Identity target_id, Identity pair[2])//does not get fleet id so return fleet id as -2
{
    pair[0] = PosIni(-1,-1,-1); pair[1] = PosIni(-1,-1,-1);
    int Lock_On = 0;
    
    for(int i = 0; i < MILLITARY; i++)
    {
        for(int j = 0; j < MAXMISSILE; j++)
        {
            if(fleet->assets[i].missile[j].status == 0)
                continue;
            if(Comp_Struct(fleet->assets[i].missile[j].target, target_id))
            {
                if(pair[0].missile == -1)
                    pair[0] = PosIni(-2, i, j);
                else
                    pair[1] = PosIni(-2, i, j);
                if(fleet->assets[i].missile[j].lock_On)
                    Lock_On = 1;
            }
        }
    }
    if(Lock_On)
        return true;
    return false;
}

bool Comp_Struct(Identity id_1, Identity id_2)
{
    if(id_1.fleet == id_2.fleet && id_1.millitary == id_2.millitary && id_1.missile == id_2.missile)
        return true;
    return false;
}

int Available_Missile(Missile *missile, int Missile_Amount)
{
    for(int i = 0; i < Missile_Amount; i++)
    {
        if(missile[i].status == false)
        {
            return i;
        }
    }
    return -1;
}

int Available_Assets(Fleet *fleet, int Assets_Amount, int type)
{
    for(int i = 0; i < Assets_Amount; i++)
    {
        if(fleet->assets[i].core.status == false && fleet->assets[i].type == type)
        {
            return i;
        }
    }
    return -1;
}

void Pair_Activate(Fleet *fleet, Identity activate_id)
{
    for(int i = 0; i < FLEET; i++)
    {
        if(activate_id.fleet == i)
            continue;
        if(activate_id.missile != -1)
            fleet[i].pair[activate_id.fleet][activate_id.millitary][activate_id.missile] = 0;
        else
            fleet[i].pair_base[activate_id.fleet][activate_id.millitary] = 0;
    }
}

Identity Pair_Search(Fleet *fleet, Identity as_id, Identity target_id)
{
    for(int i = 0; i < MILLITARY; i++)
    {
        for(int j = 0; j < MAXMISSILE; j++)
        {
            if(Comp_Struct(PosIni(as_id.fleet, i, j), as_id))
                continue;
            if(Comp_Struct(fleet[as_id.fleet].assets[i].missile[j].target, target_id))
                return PosIni(as_id.fleet, i, j);

        }
    }
    return PosIni(-1,-1,-1);
}

void Pair_Deactivate(Fleet *fleet, Identity deactivate_id)
{
    for(int p = 0; p < FLEET; p++)
    {
        if(deactivate_id.missile == -1)
            fleet[p].pair_base[deactivate_id.fleet][deactivate_id.millitary] = -1;
        else
            fleet[p].pair[deactivate_id.fleet][deactivate_id.millitary][deactivate_id.missile] = -1;
    }
}

void Pair_Decre(Fleet *fleet, Identity activate_id)
{
    if(activate_id.missile == -1)
        return;
    
    Identity target_id = fleet[activate_id.fleet].assets[activate_id.millitary].missile[activate_id.missile].target;

    if(target_id.missile != -1)
        fleet[activate_id.fleet].pair[target_id.fleet][target_id.millitary][target_id.missile]--;
    else
        fleet[activate_id.fleet].pair_base[target_id.fleet][target_id.millitary]--;
    
}

void Missile_Manual(Fleet *fleet, Identity as_id, bool Full_Control)
{
    Identity missile_id;
    printf("Missile :"); 
    
    int asset = 0;
    int missile_no = 0;
    if(!(Input_Conve(&asset, &missile_no, 'm'))){
        printf("Canceled");
        Sleep(300);
        return;
    }
    
    if(missile_no == -1)//base move sequesnce
    {
        missile_id = PosIni(as_id.fleet, asset % 26, -1);
        if(fleet->assets[missile_id.millitary].core.status == 0)
        {
            printf("Base %*c is not active", 65 + missile_id.millitary);
            Sleep(300);
            return;
        }
        if(fleet->assets[missile_id.millitary].core.status == 1)
            fleet->assets[missile_id.millitary].core.status = 2;
    }
    else{
        if(Full_Control)
            missile_id = PosIni(as_id.fleet, asset % 26, missile_no % 10);
        else
            missile_id = PosIni(as_id.fleet, as_id.millitary, missile_no % 10);
    }
    
    if(fleet->assets[missile_id.millitary].missile[missile_id.missile].status == 0)
    {
        printf("Missile %d is not active", missile_id.missile);
        Sleep(300);
        return;
    }
    
    Missile *missile;
    if(missile_id.missile != -1)
        missile = &fleet->assets[missile_id.millitary].missile[missile_id.missile];
    else
        missile = &fleet->assets[missile_id.millitary].core;
    missile->status = 2;
    
    int num;
    char charactor;
    
    printf("Target :");
    Input_Conve(&charactor, &num, 'm');
    
    missile->X_targeting = charactor * 10 + 10 + num % 10 % 3 * 3;
    missile->Y_targeting = num / 10 * 5 + num % 10 / 3 * 2;
}

void Missile_Auto(Fleet *fleet, Identity as_id, bool Full_Control)
{
    Identity missile_id;
    printf("Missile :"); 
    
    int asset = 0;
    int missile_no = 0;
    if(!(Input_Conve(&asset, &missile_no, 'a'))){
        printf("Canceled");
        Sleep(300);
        return;
    }
    
    if(missile_no == -1)//base move sequesnce
    {
        missile_id = PosIni(as_id.fleet, asset % 26, -1);
        if(fleet->assets[missile_id.millitary].core.status == 0)
        {
            printf("Asset %*c is not active", 65 + missile_id.millitary);
            Sleep(300);
            return;
        }
        Identity target_id;
            
        target_id = Base_Target_Priority(fleet, as_id, fleet[missile_id.fleet].assets[missile_id.millitary].Range * 2.5);
        if(target_id.fleet == -1)
        {
            fleet[missile_id.fleet].assets[missile_id.millitary].core.status = 2;
            printf("No target");
            Sleep(300);
            return;
        }
        else{
            fleet[missile_id.fleet].assets[missile_id.millitary].core.status = 1;
            fleet[missile_id.fleet].assets[missile_id.millitary].core.target = target_id;
        }
        
    }
    else{
        if(Full_Control)
            missile_id = PosIni(as_id.fleet, asset % 26, missile_no % 10);
        else
            missile_id = PosIni(as_id.fleet, as_id.millitary, missile_no % 10);
    }
    
    if(fleet->assets[missile_id.millitary].missile[missile_id.missile].status == 0)
    {
        printf("Missile %d is not active", missile_id.missile);
        Sleep(300);
        return;
    }
    
    Missile *missile = &fleet->assets[missile_id.millitary].missile[missile_id.missile];
    if(missile->status == 2)
        missile->status = 1;
}

void Missile_Reassign(Fleet *fleet, Identity as_id, bool Full_Control)
{
    Identity missile_id;
    Missile *missile; 
    printf("Missile :"); 
    
    int asset = 0;
    int missile_no = 0;
    if(!(Input_Conve(&asset, &missile_no, 'c'))){
        printf("Canceled");
        Sleep(300);
        return;
    }
    if(Full_Control)
        missile_id = PosIni(as_id.fleet, asset % 26, missile_no % 10);
    else
        missile_id = PosIni(as_id.fleet, as_id.millitary, missile_no % 10);
    
    missile = &fleet[missile_id.fleet].assets[missile_id.millitary].missile[missile_id.missile];
    if(missile->status == 0)
    {
        printf("Missile %d is not active", missile_id.missile);
        Sleep(300);
        return;
    }
    
    Identity target_id;
    printf("Hostile: "); 
    
    int asset_tar = 0;
    int missile_no_tar = 0;
    if(!(Input_Conve(&asset_tar, &missile_no_tar, 'c'))){
        printf("Canceled");
        Sleep(300);
        return;
    }
    
    if(missile_no_tar == -1)
    {
        target_id = PosIni((asset_tar - 10) / 26 % 10, asset_tar % 26, -1);
        if(fleet[target_id.fleet].assets[target_id.millitary].core.status == 0 || target_id.fleet == as_id.fleet)
        {
            printf("Base %*c is not active", 65 + target_id.millitary);
            Sleep(300);
            return;
        }
    }
    else{
        target_id = PosIni((asset_tar - 10) / 26 % 10, asset_tar % 26, missile_no_tar % 10);
        if(fleet[target_id.fleet].assets[target_id.millitary].missile[target_id.missile].status == 0)
        {
            printf("Target %d is not active", target_id.missile);
            Sleep(300);
            return;
        }
    }
    if(target_id.fleet == as_id.fleet)
    {
        printf("Targeting own fleet");
        Sleep(300);
        return;
    }
    
    Identity Missile_far;
    if(target_id.missile == -1)
    {
        if(fleet[as_id.fleet].pair_base[target_id.fleet][target_id.millitary] == 2)
        {
            Missile_far =  far_Missile(fleet, as_id, target_id);
            fleet[Missile_far.fleet].assets[Missile_far.millitary].missile[Missile_far.missile].target = missile->target;
        }
        else
        {
            if(missile->target.missile == -1)
                fleet[as_id.fleet].pair_base[missile->target.fleet][missile->target.millitary]--;
            else
                fleet[as_id.fleet].pair[missile->target.fleet][missile->target.millitary][missile->target.missile]--;
            fleet[as_id.fleet].pair_base[target_id.fleet][target_id.millitary]++;
        }
    }
    else{
        if(fleet[as_id.fleet].pair[target_id.fleet][target_id.millitary][target_id.missile] == 2)
        {
            Missile_far =  far_Missile(fleet, as_id, target_id);
            fleet[Missile_far.fleet].assets[Missile_far.millitary].missile[Missile_far.missile].target = missile->target;
        }
        else{
            if(missile->target.missile == -1)
                fleet[as_id.fleet].pair_base[missile->target.fleet][missile->target.millitary]--;
            else
                fleet[as_id.fleet].pair[missile->target.fleet][missile->target.millitary][missile->target.missile]--;
            fleet[as_id.fleet].pair[target_id.fleet][target_id.millitary][target_id.missile]++;
        }
    }
    missile->target = target_id;
    
}

Identity far_Missile(Fleet *fleet, Identity as_id, Identity target_id)
{
    Identity pair = PosIni(-1,-1,-1);
    Missile *target;
    if(target_id.missile == -1)
        target = &fleet[target_id.fleet].assets[target_id.millitary].core;
    else
        target = &fleet[target_id.fleet].assets[target_id.millitary].missile[target_id.missile];
    for(int i = 0; i < MILLITARY; i++)
    {
        for(int j = 0; j < MAXMISSILE; j++)
        {
            if(fleet[as_id.fleet].assets[i].missile[j].status == 0)
                continue;
            if(Comp_Struct(fleet[as_id.fleet].assets[i].missile[j].target, target_id))
            {
                if(pair.millitary == -1)
                {
                    pair = PosIni(as_id.fleet, i, j);
                }
                else{
                    if(hypot(target->X - fleet[as_id.fleet].assets[i].missile[j].X, target->Y - fleet[as_id.fleet].assets[i].missile[j].Y) > hypot(target->X - fleet[pair.fleet].assets[pair.millitary].missile[pair.missile].X, target->Y - fleet[as_id.fleet].assets[pair.millitary].missile[pair.missile].Y))
                        return PosIni(as_id.fleet, i, j);
                    else
                        return pair;
                }
            }
        }
    }
}

bool Input_Conve(int *charactor, int *num, char escape)
{
    char string[6] = {};

    scanf("%s", string);
    
    if(string[0] == escape)
        return false;
    if(string[0] < 65)
        *num = string[0] - 48;
    else if(string[1] < 65)
    {
        *charactor = string[0] - 65;
        if(string[1] == 0)
            *num = -1;
        else if(string[2] == 0)
            *num = string[1] - 48;
        else if(string[3] == 0)
            *num = (string[1] - 48) * 10 + string[2] - 48;
        else
            *num = (string[1] - 48) * 100 + (string[2] - 48) * 10 + string[3] - 48;
    }
    else
    {
        *charactor = 26 * (string[0] - 65 + 1) + string[1] - 65;
        if(string[2] == 0)
            *num = -1;
        else if(string[3] == 0)
            *num = string[2] - 48;
        else if(string[4] == 0)
            *num = (string[2] - 48) * 10 + string[3] - 48;
        else
            *num = (string[2] - 48) * 100 + (string[3] - 48) * 10 + string[4] - 48;

    }
    return true;
}

bool pair_check(Fleet *fleet)
{
    for(int p = 0; p < FLEET; p++)
    {
        for(int i = 0; i < FLEET; i++)
        {
            for(int j = 0; j < MILLITARY; j++)
            {
                for(int k = 0; k < MAXMISSILE; k++)
                {
                    int pair_num = fleet[p].pair[i][j][k];
                    if(pair_num == -1)
                        continue;
                    if(pair_num < -1)
                        return false;
                    for(int q = 0; q < MILLITARY; q++)
                    {
                        for(int s = 0; s < MAXMISSILE; s++)
                        {
                            if(fleet[p].assets[q].missile[s].status == 0)
                                continue;
                            if(Comp_Struct(PosIni(i, j, k), fleet[p].assets[q].missile[s].target))
                                pair_num--;
                        }
                    }
                    if(pair_num != 0)
                        return false;
                }
            }
        }
    }
    return true;
}

void Radar_Range(int fieldHeight, int fieldWidth, int Height_Start, int Width_Start, char field[fieldHeight][fieldWidth], Fleet *fleet)
{
    for(int p = 0; p < MILLITARY; p++)
    {
        Missile *core;
        core = &fleet->assets[p].core;
        if(core->status == 0)
            continue;
        for(int i = 0; i < fieldHeight; i++)
        {
            for(int j = 0; j < fieldWidth; j++)
            {
                int X_cor = j + Width_Start;
                int Y_cor = i + Height_Start;

                if((int)hypot(X_cor - core->X, (Y_cor - core->Y) * 2) == fleet->assets[p].Range)
                    field[(int)range(i, fieldHeight)][(int)range(j, fieldWidth)] = '\'';
            }
        }
    }
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
        while(fgets(table[p], 800, cfPtr) != NULL) {
            p++;
        }
        fclose(cfPtr);
    }
}

void Map_Draw(int fieldHeight, int fieldWidth, int tableWidth, int X_Start, int Y_Start, char(*field)[fieldWidth], char(*table)[tableWidth])
{
    for(int i = 0; i < fieldHeight; i++)
    {
        for(int j = 0; j < fieldWidth; j++)
        {
            field[i][j] = table[Y_Start + i][X_Start + j];
        }
    }
}

void RTB_Fighter(Fleet *fleet, Identity as_id, Identity Fighter_id, int Auto)
{
    Identity fighter_id;
    Fleet *fleet_as = &fleet[as_id.fleet];
    printf("Fighter :"); 
    int missile_no = 0;
    if(Fighter_id.fleet == -1)
    {
        int asset = 0;
        if(!(Input_Conve(&asset, &missile_no, 'r'))){
            printf("Canceled");
            Sleep(300);
            return;
        }
        
        fighter_id = PosIni(as_id.fleet, asset % 26, -1);
        if(!(fleet_as->assets[fighter_id.millitary].type == 1 || fleet_as->assets[fighter_id.millitary].type == 4))
        {
            printf("Asset %d is not fighter", fighter_id.millitary);
            Sleep(300);
            return;
        }
        
        if(fleet_as->assets[fighter_id.millitary].core.status == 0)
        {
            printf("Fighter %*c is not active", 65 + fighter_id.millitary);
            Sleep(300);
            return;
        }
    }
    else{
        fighter_id = Fighter_id;
        printf("%*c\n", fighter_id.millitary + 65);
    }

    Identity base_id;
    printf("Return to :"); 
    
    if(Auto == 1)
    {
        base_id = Nearby_Base(fleet_as, as_id);
        if(base_id.fleet == -1)
        {
            printf("No Avalable Base");
            Sleep(300);
            return;
        }
    }
    else{
    int asset_to = 0;
        if(!(Input_Conve(&asset_to, &missile_no, 'r'))){
            printf("Canceled");
            Sleep(300);
            return;
        }
        
        base_id = PosIni(as_id.fleet, asset_to % 26, -1);
        if(!(fleet_as->assets[base_id.millitary].type == 2 || fleet_as->assets[base_id.millitary].type == 3))
        {
            printf("Asset %d is not base", base_id.millitary);
            Sleep(300);
            return;
        }
        
        if(fleet_as->assets[base_id.millitary].core.status == 0)
        {
            printf("Base %*c is not active", 65 + base_id.millitary);
            Sleep(300);
            return;
        }
    }

    Millitary *Fighter = &fleet_as->assets[fighter_id.millitary];
    Millitary *Base = &fleet_as->assets[base_id.millitary];
    printf("Processing");
    int type = Fighter->type;
    memset(Fighter, 0, sizeof(Millitary));
    Pair_Deactivate(fleet, Fighter_id);
    Fighter->type = type;
    Base->MaxAssets++;
    return;
}

void Kill_Feed_Record(KillFeed *Record, Identity Destroyed, Identity Destroyed_By, int Status, int RecordHeight)
{
    for(int i = 0; i < RecordHeight - 1; i++)
    {
        Record[i] = Record[i + 1];
    }
    Record[RecordHeight - 1].destroyed = Destroyed;
    Record[RecordHeight - 1].destroyed_by = Destroyed_By;
    Record[RecordHeight - 1].status = Status;
}

void Letter_Draw_Italic(int fontDataHeight, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, char* string, int letter_size)
{
    //expect font data with all numbers and alphabets with letter size of 5 and data order according to ASCII table
    for(int i = 0; i < fontDataHeight; i++)
        for(int j = 0; j < fontDataWidth; j++)
            if(fontData[i][j] == 10)
                fontData[i][j] = 0;
    
    char string_field[150];
    for(int i = 0; i < letter_size; i++) // 5 is letter hight
    {
        memset(string_field, 0, 150);
        for(int p = 0; p < letter_size - i - 1; p++)
            string_field[p] = ' ';
        for(int j = 0; string[j] != 0; j++)
            strcat(string_field, fontData[(string[j] == 32 ? 75 : (string[j] - 48)) * letter_size + i]);
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
    
    char string_field[120];
    for(int i = 0; i < letter_size; i++) // 5 is letter hight
    {
        memset(string_field, 0, 120);
        
        for(int j = 0; string[j] != 0; j++)
            strcat(string_field, fontData[(string[j] == 32 ? 75 : (string[j] - 48)) * letter_size + i]);
        strcpy(&field[DrawFromY + i][DrawFromX], string_field);
    }
}

void Kill_Feed_Draw(KillFeed *Record, int RecordHeight, Identity as_id, int fontDataHeight, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, int letter_size)
{
    char list_killfeed[3][15] = {" destroyed ", "  missed   ", "    RTB    "};
    char print_field[80];
    for(int i = 0; i < RecordHeight; i++)
    {
        if(Record[i].status == 0)
            continue;
        memset(print_field, 0, 80);
        
        print_field[0] = Record[i].destroyed_by.fleet == as_id.fleet ? ' ' : Record[i].destroyed_by.fleet + 65 + 10;
        print_field[1] = Record[i].destroyed_by.millitary + 65;
        print_field[2] = Record[i].destroyed_by.missile == -1 ? ' ' : Record[i].destroyed_by.missile + 48;
        
        strcat(print_field, list_killfeed[Record[i].status - 1]);
        
        char temp[3] = {};
        if(Record[i].status == 1)
        {
            sprintf(&print_field[14], "%c%c%c", Record[i].destroyed.fleet == as_id.fleet ? ' ' : Record[i].destroyed.fleet + 65 + 10, 
                                                Record[i].destroyed.millitary + 65,
                                                Record[i].destroyed.missile == -1 ? ' ' : Record[i].destroyed.missile + 48);
        }
        
        Letter_Draw_Normal(fontDataHeight, fontDataWidth, fontData, fieldWidth, field, DrawFromX, DrawFromY + letter_size * (RecordHeight - i - 1), print_field, letter_size);
    }
}

Identity Nearby_Base(Fleet *fleet, Identity as_id)
{
    Identity nMinPos = {-1, -1, -1};
    Missile* core = &fleet->assets[as_id.millitary].core;
    
    double distance[MILLITARY];
    
    for(int i = 0; i < MILLITARY; i++)
    {
        if(fleet->assets[i].core.status == 0 || !(fleet->assets[i].type == 2 || fleet->assets[i].type == 3) || as_id.millitary == i)
            continue;
        distance[i] = hypot(core->X - fleet->assets[i].core.X, core->Y - fleet->assets[i].core.Y);                                                                                      //first time 
        if(distance[i] < distance[nMinPos.millitary] || nMinPos.fleet == -1)
        {
            nMinPos = PosIni(as_id.fleet, i, -1);
        }
    } 

    return nMinPos;
}

void Grid_Draw(int fieldHeight, int fieldWidth, char(*field)[fieldWidth], char (*Grid_field)[fieldWidth], int X_Start, int Y_Start, int *Grid_Type, int *Grid_Update)
{
    if(*Grid_Update > 0)
    {
        memset(Grid_field, 0, fieldHeight * fieldWidth);
        Grid(fieldHeight, fieldWidth, X_Start, Y_Start, Grid_field, *Grid_Type);
        (*Grid_Update)--;
    }
    for(int i = 0; i < fieldHeight; i++)
//        sprintf(field[i], "%s", Grid_field[i]);
        for(int j = 0; j < fieldWidth; j++)
            if(field[i][j] == 0 || field[i][j] == 32)
                field[i][j] = Grid_field[i][j];
}

bool Error_Nan(Fleet *fleet)
{
    for(int i = 0; i < FLEET; i++)
        for(int j = 0; j < MILLITARY; j++){
            for(int k = 0; k < MAXMISSILE; k++)
                if(isnan(fleet[i].assets[j].missile[k].X))
                    return true;
            if(isnan(fleet[i].assets[j].core.X))
                return true;
        }
    return false;
}