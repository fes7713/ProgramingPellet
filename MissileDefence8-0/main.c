///////////////////////////////////////////
///////////////////////////////////////////
///need font, map and unit icon files//////
///in same folder//////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////

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
    int Point;
    Missile core;
    Missile missile[MAXMISSILE];
} Millitary;

typedef struct{
    Millitary assets[MILLITARY];
    int pair[FLEET][MILLITARY][MAXMISSILE];
    int pair_base[FLEET][MILLITARY];
    int identity;
    int score;
    bool Attack;
} Fleet;

char numbers[10] = {'0','1','2', '3', '4', '5', '6', '7','8','9'};
char alphabets[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char list_killfeed[3][15] = {" destroyed ", "  missed   ", "    RTB    "};
int Assets_Price[8] = {0, 150, 300, 300, 600, 750, 1000, 1500};
int Radar_Sites[26][2] = {{170, 1196}, {155, 1166}, {165, 1090}, {132, 1106}, {190, 1120}, {182, 1036}, {204, 1063}, {220, 1023}, {230, 1083}, {255, 920}, 
{267, 1036}, {249, 976}, {305, 1000}, {305, 933}, {292, 890}, {317, 866}, {274, 803}, {295, 696}, {274, 690}, {305, 646}, 
{327, 666}, {332, 710}, {404, 570}, {427, 506}, {450, 393}, {444, 276}};
int JSDF_AirForce[11][2] = {{300, 936}, {175, 1090}, {209, 1070}, {250, 1056}, {325, 720}, {270, 910}, {285, 1020}, {295, 723}, {427, 513}, {292, 976}, {297, 706}};
int JSDF_Navy[4][2] = {{300, 1000}, {300, 680}, {277, 866}, {294, 776}};
int Assets_Pos[3][26][2] = {{{170, 1196}, {155, 1166}, {165, 1090}, {132, 1106}, {190, 1120}, {182, 1036}, {204, 1063}, {220, 1023}, {230, 1083}, {255, 920}, 
{267, 1036}, {249, 976}, {305, 1000}, {305, 933}, {292, 890}, {317, 866}, {274, 803}, {295, 696}, {274, 690}, {305, 646}, 
{327, 666}, {332, 710}, {404, 570}, {427, 506}, {450, 393}, {444, 276}}, 
{{300, 1000}, {300, 680}, {277, 866}, {294, 776}},
{{300, 936}, {175, 1090}, {209, 1070}, {250, 1056}, {325, 720}, {270, 910}, {285, 1020}, {295, 723}, {427, 513}, {292, 976}, {297, 706}}};

int Attack_Spawn[26][2] = {{44, 89}, {44, 356}, {44, 533}, {44, 711}, {44, 889}, {44, 1067}, {44, 1244}, {44, 1511},
{178, 1511}, {266, 1511}, {355, 1511}, {444, 1511}, {533, 1511}, {666, 1511}, 
{666, 1244}, {666, 1067}, {666, 889}, {666, 711}, {666, 533}, {666, 356}, {666, 89},
{533, 89}, {444, 89}, {355, 89}, {266, 89}, {178, 89}};
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
   
typedef void (*LaunchFunction)(Fleet *, Identity, bool);
typedef void (*InitializeFuncion)(Millitary *, double, double, double, double);
typedef void (*AutoInitialize)(Millitary* , Missile* , double , double);

void player(Fleet *fleet, Identity as_id, KillFeed *Record, int tableHeight, int tableWidth, int RecordHeight, double difficulty, bool Auto);
void Graphing(int fieldHeight, int fieldWidth, int X_Start, int Y_Start, char field[fieldHeight][fieldWidth], Fleet *fleet, Identity as_id, int *Grid_Type, int Radar);
void Control(Fleet *fleet, Identity as_id, int *Grid_Type, int Full_Control, int *Radar, int fieldHeight, int fieldWidth, int tableHeight, int tableWidth, int *X_Start, int *Y_Start, int *font, int *Grid_Update, int *Select_Asset, int *Spawn_Type);
void printArray2(int fieldHeight, int fieldWidth, char field[fieldHeight][fieldWidth]);
void printArray3(int fieldHeight, int fieldWidth, char field[fieldHeight][fieldWidth]);
int range(double num, int limit);
double to_deg360_Tri(double run, double rise);
void Missile_Stationary(Missile * missile, const double *target_X, const double *target_Y);
bool Missile_Moving(Missile *Interceptor, const Missile *Hostile);
double Missile_Angle_Ini(Missile *Interceptor, const Missile *Hostile);
void Generator_Interceptor(Missile *Interceptor, Missile *Hostile, double Launch_X, double Launch_Y);
void record_cordinates(Missile * missile);
void Grid(int fieldHeight, int fieldWidth, int X_Start, int Y_Start, char (*field)[fieldWidth], int Grid_Type);
void Grid_Rough(int fieldHeight, int fieldWidth, char (*field)[fieldWidth]);
void Grid_Simple(int fieldHeight, int fieldWidth, int X_Start, int Y_Start, char (*field)[fieldWidth]);
void Grid_Advanced(int fieldHeight, int fieldWidth, int X_Start, int Y_Start, char (*field)[fieldWidth]);
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
void Missile_Launch(Fleet *fleet, Identity as_id, bool Auto, int missile_no_di, float speedx, int timer_di);
void Asset_Launch(AutoInitialize AutoLaunch, Fleet *fleet, Identity as_id, int Launch_Type, bool Auto, float speedx);
void Fighter_Launch(Fleet *fleet, Identity as_id, bool Auto);
void Agis_Launch(Fleet *fleet, Identity as_id, bool Auto);
void Stealth_Fighter_Launch(Fleet *fleet, Identity as_id, bool Auto);
void AircraftCarrier_Launch(Fleet *fleet, Identity as_id, bool Auto);
void MissileBase_Launch(Fleet *fleet, Identity as_id, bool Auto);
void NavalBase_Launch(Fleet *fleet, Identity as_id, bool Auto);
void AirBase_Launch(Fleet *fleet, Identity as_id, bool Auto);
void Fighter_Initialize_Start(Millitary *Fighter, double Launch_X, double Launch_Y, double target_X, double target_Y);
void Agis_Initialize_Start(Millitary *Agis, double Launch_X, double Launch_Y, double target_X, double target_Y);
void Stealth_Fighter_Initialize_Start(Millitary *Fighter, double Launch_X, double Launch_Y, double target_X, double target_Y);
void AircraftCarrier_Initialize_Start(Millitary *Fighter, double Launch_X, double Launch_Y, double target_X, double target_Y);
void MissileBase_Initialize_Start(Millitary *MissileBase, double Launch_X, double Launch_Y, double target_X, double target_Y);
void NavalBase_Initialize_Start(Millitary *MissileBase, double Launch_X, double Launch_Y, double target_X, double target_Y);
void AirBase_Initialize_Start(Millitary *AircraftBase, double Launch_X, double Launch_Y, double target_X, double target_Y);
void Agis_Initialize(Millitary *assets, Missile *target, double Launch_X, double Launch_Y);
void Fighter_Initialize(Millitary *assets, Missile *target, double Launch_X, double Launch_Y);
void AircraftCarrier_Initialize(Millitary *assets, Missile *target, double Launch_X, double Launch_Y);
void Stealth_Fighter_Initialize(Millitary *assets, Missile *target, double Launch_X, double Launch_Y);
bool pair_check(Fleet *fleet);
void Radar_Range(int fieldHeight, int fieldWidth, int Height_Start, int Width_Start, char field[fieldHeight][fieldWidth], Fleet *fleet);
void Map_Import(int tableHeight, int tableWidth, char(*table)[tableWidth], char* fname);
void Map_Draw(int fieldHeight, int fieldWidth, int tableWidth, int X_Start, int Y_Start, char(*field)[fieldWidth], char(*table)[tableWidth]);
void RTB_Fighter(Fleet *fleet, Identity as_id, Identity Fighter_id, int Auto);
Identity Nearby_Base(Fleet *fleet, Identity as_id);
void Letter_Draw_Italic(int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, char* string, int letter_size);
void Letter_Draw_Normal(int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, char* string, int letter_size);
void Kill_Feed_Record(KillFeed *Record, Identity Destroyed, Identity Destroyed_By, int Status, int RecordHeight);
void Kill_Feed_Draw(KillFeed *Record, int RecordHeight, Identity as_id, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, int letter_size);
void Grid_Draw(int fieldHeight, int fieldWidth, char(*field)[fieldWidth], char (*Grid_field)[fieldWidth], int X_Start, int Y_Start, int *Grid_Type, int *Grid_Update);
bool Error_Nan(Fleet *fleet);
void Assets_Detail_Draw(Fleet *fleet, int fontDataHeight, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldHeight, int fieldWidth, char (*field)[fieldWidth], int X_Start, int Y_Start, int letter_size, int Select_Asset);
void Score_Display(Fleet *fleet, int fontDataHeight, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, int letter_size);
void Asset_Icon_Draw(Fleet *fleet, int Select, int IconDataWidth, const char (*IconData)[IconDataWidth], int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, int Icon_Height, int letter_size);
void Base_Detail_Draw(int size, int (*pos)[2], int fontDataHeight, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldHeight, int fieldWidth, char (*field)[fieldWidth], int X_Start, int Y_Start, int letter_size);
void Base_Detail(int Spawn_Type, int fontDataHeight, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldHeight, int fieldWidth, char (*field)[fieldWidth], int X_Start, int Y_Start, int letter_size);
void Assets_Spawn(Fleet *fleet, Identity as_id, bool Auto, bool Attack, int *Spawn_Type);

LaunchFunction arrLauch[8] = {0, Fighter_Launch, Agis_Launch, Stealth_Fighter_Launch, AircraftCarrier_Launch, MissileBase_Launch, NavalBase_Launch, AirBase_Launch};
InitializeFuncion arrIni[8] = {0, Fighter_Initialize_Start, Agis_Initialize_Start, Stealth_Fighter_Initialize_Start, AircraftCarrier_Initialize_Start, MissileBase_Initialize_Start, NavalBase_Initialize_Start, AirBase_Initialize_Start};
AutoInitialize arrAutoLaunch[8] = {0, Fighter_Initialize, Agis_Initialize, Stealth_Fighter_Initialize, AircraftCarrier_Initialize};

double Error_Record = 0;

int main(int argc, char **argv)
{
    //32:9 230:57 font 13
    //     269:70 font 10 A-Z
    //155:620 font 5
    //95:380 font 8
    //60:240 font 13
    int font = 8;
    static char field[165][660] = {};
    int fieldHeight = 800 / font / 5 * 5;
    int fieldWidth = fieldHeight * 4;
    int X_Start = 0;
    int Y_Start = 0;
    char Grid_field[165][660] = {};
    
    static char table[710][1600];
    int tableHeight = 710;
    int tableWidth = 1600;
    
    static char fontData[500][50];
    int fontDataHeight = 500;
    int fontDataWidth = 50;
    int letter_size = 6;
    
    static char IconData[210][100] = {};
    int IconDataHeight = 210;
    int IconDataWidth = 100;
    int Icon_Height = 30;
    Map_Import(fontDataHeight, fontDataWidth, fontData, "font Ivrit.txt");
    Map_Import(tableHeight, tableWidth, table, "Full Map1.txt");
    Map_Import(IconDataHeight, IconDataWidth, IconData, "Assets Logo Selected.txt");
    int counter = 0;
    int stop = 0;
    int Grid_Type = 3;
    int Full_Control = 1;
    int Radar = 0;
    int Grid_Update = 1;
    int Select_Asset = 15;
    int Spawn_Type = 0;
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
    Agis_USS[0].Attack = false;
    Agis_USS[1].Attack = true;
    arrIni[7](&Agis_USS[0].assets[0], 976,292,  15, 20);
    Pair_Activate(Agis_USS, PosIni(0, 0, -1));

    Agis_USS[0].score = 2000;
    Agis_USS[1].score = 2000;
    Identity friendly_id = PosIni(0, 0, -1);
    while(1)
    {
        for(int i = 0; i < FLEET; i++)
            for(int j = 0; j < MILLITARY; j++)
                if(Agis_USS[i].assets[j].core.status != 0)
                    player(Agis_USS, PosIni(i, j, -1), Record, tableHeight, tableWidth, RecordHeight, 0.6, friendly_id.fleet != i);//friendly_id.fleet != i
        if(Error_Nan(Agis_USS))
            stop = 1;
        for(int i = 0; i < FLEET; i++)
            Agis_USS[i].score += 1;
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
        
        Kill_Feed_Draw(Record, RecordHeight, friendly_id, fontDataWidth, fontData, fieldWidth, field, fieldWidth - letter_size * 22, letter_size * 3, letter_size);
        Assets_Detail_Draw(&Agis_USS[friendly_id.fleet], fontDataHeight, fontDataWidth, fontData, fieldHeight,fieldWidth, field, X_Start, Y_Start, letter_size, Select_Asset);
        Score_Display(&Agis_USS[friendly_id.fleet], fontDataHeight, fontDataWidth, fontData, fieldWidth, field, fieldWidth - letter_size * 15, letter_size, letter_size);
        Asset_Icon_Draw(&Agis_USS[friendly_id.fleet], Select_Asset, IconDataWidth, IconData, fontDataWidth, fontData, fieldWidth, field, fieldWidth - 100, fieldHeight - Icon_Height * 1.2, Icon_Height, letter_size);
        for(int i = 0; i < FLEET; i++)
            Assets_Spawn(Agis_USS, PosIni(i, -1, -1), friendly_id.fleet != i, Agis_USS[i].Attack, &Spawn_Type);
        fieldHeight = 800 / font / 5 * 5;
        fieldWidth = fieldHeight * 4;
        
//        getchar();
//        while(counter++ < 2)
//        {
//            Sleep(100);
            if(_kbhit()){
                Control(Agis_USS, friendly_id, &Grid_Type, Full_Control, &Radar, fieldHeight, fieldWidth, tableHeight, tableWidth, &X_Start, &Y_Start, &font, &Grid_Update, &Select_Asset, &Spawn_Type);
//                break;
            }
//        }
        counter = 0;
        Base_Detail(Spawn_Type, fontDataHeight, fontDataWidth, fontData, fieldHeight, fieldWidth, field, X_Start, Y_Start, letter_size);
        system("cls");
        printArray3(fieldHeight, fieldWidth, field);
        
    }
	return 0;
}

void player(Fleet *fleet, Identity as_id, KillFeed *Record, int tableHeight, int tableWidth, int RecordHeight, double difficulty, bool Auto)
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
    
    if(fleet[as->core.target.fleet].assets[as->core.target.millitary].core.status == 0  && as->core.status == 1)
    {
        Identity target_id;

        target_id = Base_Target_Priority(fleet, as_id, fleet[as_id.fleet].assets[as_id.millitary].Range * 3);
        if(target_id.fleet == -1){
//            RTB_Fighter(fleet, as_id, as_id, 1);
            memset(as, 0, sizeof(Millitary));
            Pair_Deactivate(fleet, as_id);
            return;
        }
        else
            as->core.target = target_id;
    }
//Generate
    arrLauch[as->type](fleet, as_id, Auto);
    
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
                
                fleet[as_id.fleet].score += 50;            // missile destroy score point 50
                
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
                fleet[as_id.fleet].score += fleet[target_id.fleet].assets[target_id.millitary].Point / 4 * 3;
                for(int i = 0; i < MAXMISSILE; i++)
                {
                    if(fleet[target_id.fleet].assets[target_id.millitary].missile[i].status == 0)
                        continue;
                    Pair_Decre(fleet, PosIni(target_id.fleet, target_id.millitary, i));
                    Pair_Deactivate(fleet, PosIni(target_id.fleet, target_id.millitary, i));
                }
                memset(&fleet[target_id.fleet].assets[target_id.millitary], 0, sizeof(Millitary));
                Pair_Deactivate(fleet, target_id);
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

void Control(Fleet *fleet, Identity as_id, int *Grid_Type, int Full_Control, int *Radar, int fieldHeight, int fieldWidth, int tableHeight, int tableWidth, int *X_Start, int *Y_Start, int *font, int *Grid_Update, int *Select_Asset, int *Spawn_Type)
{
    switch(_getch())
    {
        case '1': if(!(fleet[as_id.fleet].assets[*Select_Asset].type == 4 || fleet[as_id.fleet].assets[*Select_Asset].type == 7) || fleet[as_id.fleet].score - Assets_Price[1] < 0)
                        break;
                  Stand_By_Assets(&fleet[as_id.fleet], PosIni(as_id.fleet, *Select_Asset, -1), 1); break;
        case '2': if(fleet[as_id.fleet].score - Assets_Price[2] < 0 || !(fleet[as_id.fleet].assets[*Select_Asset].type == 6 || fleet[as_id.fleet].Attack == true))
                        break;
                  if(fleet[as_id.fleet].Attack == true)
                        *Spawn_Type = 2;
                  else
                    Stand_By_Assets(&fleet[as_id.fleet], PosIni(as_id.fleet, *Select_Asset, -1), 2); break;
        case '3': if(!(fleet[as_id.fleet].assets[*Select_Asset].type == 4 || fleet[as_id.fleet].assets[*Select_Asset].type == 7) || fleet[as_id.fleet].score - Assets_Price[3] < 0)
                        break;
                  Stand_By_Assets(&fleet[as_id.fleet], PosIni(as_id.fleet, *Select_Asset, -1), 3); break;
        case '4': if(fleet[as_id.fleet].score - Assets_Price[4] < 0 || !(fleet[as_id.fleet].assets[*Select_Asset].type == 6 || fleet[as_id.fleet].Attack == true))
                        break;
                  if(fleet[as_id.fleet].Attack == true)
                        *Spawn_Type = 4;
                  else
                    Stand_By_Assets(&fleet[as_id.fleet], PosIni(as_id.fleet, *Select_Asset, -1), 4); break;
                  
        case '5': if(fleet[as_id.fleet].Attack == false && fleet[as_id.fleet].score >= Assets_Price[5])
                        *Spawn_Type = 5; break;
        
        case '6': if(fleet[as_id.fleet].Attack == false && fleet[as_id.fleet].score >= Assets_Price[6])
                        *Spawn_Type = 6; break;
        
        case '7': if(fleet[as_id.fleet].Attack == false && fleet[as_id.fleet].score >= Assets_Price[7])
                        *Spawn_Type = 7; break;
        
        case 'q': *Select_Asset = range(*Select_Asset - 1, MILLITARY); break;
        case 'e': *Select_Asset = range(*Select_Asset + 1, MILLITARY); break;
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

void printArray3(int fieldHeight, int fieldWidth, char field[fieldHeight][fieldWidth])
{
//    for(int i = 0; i < fieldHeight; i++)
//        field[i][fieldWidth - 1] = '\0';
    for(int i = 0; i < fieldHeight; i++)
        for(int j = 0; j < fieldWidth; j++){
            if(field[i][j] == 0 || field[i][j] == '\n')
                field[i][j] = ' ';
            if(j == fieldWidth - 1)
                field[i][j] = 10;
        }
    field[fieldHeight - 1][fieldWidth - 1] = 0;
    printf("%s\n", field);
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
            double run = fleet[i].assets[j].core.X - core->X;
            double rise = core->Y - fleet[i].assets[j].core.Y;
            double Constant = fleet[i].assets[j].core.speed / core->speed * (run * sin(fleet[i].assets[j].core.direction) - rise * cos(fleet[i].assets[j].core.direction));
            double Limit = pow(run, 2) + pow(rise, 2);
            if(Limit < pow(Constant, 2))
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

void Base_Moving(Fleet *fleet, Identity as_id, int tableHeight, int tableWidth)
{
    Missile *Base = &fleet[as_id.fleet].assets[as_id.millitary].core;
    if(Base->status == 1)
    {
        Missile *target = &fleet[Base->target.fleet].assets[Base->target.millitary].core; //expect only base targets
        if(Missile_Moving(Base, target) == true){
            Base->X_targeting = Base->X_future;
            Base->Y_targeting = Base->Y_future;
        }
        else{
            Identity target_id = Base_Target_Priority(fleet, as_id, fleet[as_id.fleet].assets[as_id.millitary].Range * 3);
            if(target_id.fleet == -1)
            {
                memset(&fleet[as_id.fleet].assets[as_id.millitary], 0, sizeof(Millitary));
                Pair_Deactivate(fleet, as_id);
            }
            Missile_Moving(Base, target);
            Base->X_targeting = Base->X_future;
            Base->Y_targeting = Base->Y_future;
        }
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

void Fighter_Launch(Fleet *fleet, Identity as_id, bool Auto)
{
    Missile_Launch(fleet, as_id, Auto, 3, 2, 1);
}

void Agis_Launch(Fleet *fleet, Identity as_id, bool Auto)
{
    Missile_Launch(fleet, as_id, Auto, 1, 1, 1);
}

void Stealth_Fighter_Launch(Fleet *fleet, Identity as_id, bool Auto)
{
    Missile_Launch(fleet, as_id, Auto, 2, 3, 1);
}

void AircraftCarrier_Launch(Fleet *fleet, Identity as_id, bool Auto)
{
    Asset_Launch(arrAutoLaunch[1], fleet, as_id, 1, Auto, 1);
    Asset_Launch(arrAutoLaunch[3], fleet, as_id, 3, Auto, 1.5);
    
    Missile_Launch(fleet, as_id, Auto, 3, 1, 2);

}

void MissileBase_Launch(Fleet *fleet, Identity as_id, bool Auto)
{
    Missile_Launch(fleet, as_id, Auto, 1, 1, 1);
}

void NavalBase_Launch(Fleet *fleet, Identity as_id, bool Auto)
{
    Asset_Launch(arrAutoLaunch[2], fleet, as_id, 2, Auto, 0.25);
    Asset_Launch(arrAutoLaunch[4], fleet, as_id, 4, Auto, 0.25);
}

void AirBase_Launch(Fleet *fleet, Identity as_id, bool Auto)
{
    Asset_Launch(arrAutoLaunch[1], fleet, as_id, 1, Auto, 1);
    Asset_Launch(arrAutoLaunch[3], fleet, as_id, 3, Auto, 1.5);
    
    Missile_Launch(fleet, as_id, Auto, 2, 1, 2);
    
}

void Missile_Launch(Fleet *fleet, Identity as_id, bool Auto, int missile_no_di, float speedx, int timer_di)
{
    Millitary *as = &fleet[as_id.fleet].assets[as_id.millitary];
    Missile *core = &fleet[as_id.fleet].assets[as_id.millitary].core;
    Missile *missile = fleet[as_id.fleet].assets[as_id.millitary].missile;
    
    if((as->interval = range(--(as->interval), 300)) == 0)
    {
        int No_Missile = Available_Missile(missile, MAXMISSILE / missile_no_di); // later change
        
        if(No_Missile != -1)
        {
            Identity target_id;
            Missile *target;
            missile[No_Missile].speed = SPE_INTE * speedx;
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
                missile[No_Missile].speed = SPE_INTE * speedx;
                Pair_Activate(fleet, PosIni(as_id.fleet, as_id.millitary, No_Missile));
                missile[No_Missile].target = target_id;
                as->interval += fleet[as_id.fleet].assets[as_id.millitary].timer / timer_di;
            }
            else
                memset(&missile[No_Missile], 0, sizeof(Missile));
        }
    }
}

void Asset_Launch(AutoInitialize AutoLaunch, Fleet *fleet, Identity as_id, int Launch_Type, bool Auto, float speedx)
{
    Millitary *as = &fleet[as_id.fleet].assets[as_id.millitary];
    Missile *core = &fleet[as_id.fleet].assets[as_id.millitary].core;
    
    if((as->interval = range(--(as->interval), 200)) == 0 && (as->MaxAssets > 0 || (Auto == true && fleet[as_id.fleet].score - Assets_Price[Launch_Type] > 0)))
    {
        int No_Asset;
        if(Auto == true && as->MaxAssets == 0)
            No_Asset = Stand_By_Assets(&fleet[as_id.fleet], as_id, Launch_Type);
        else
            No_Asset = Available_Assets(&fleet[as_id.fleet], MILLITARY, Launch_Type); // later change
            
        Millitary *Asset = &fleet[as_id.fleet].assets[No_Asset];
        if(No_Asset != -1)
        {
            Identity target_id;
            Missile *target;
            fleet[as_id.fleet].assets[No_Asset].core.speed = SPE_INTE * speedx;
            fleet[as_id.fleet].assets[No_Asset].core.X = core->X;
            fleet[as_id.fleet].assets[No_Asset].core.Y = core->Y;
            target_id = Base_Target_Priority(fleet, PosIni(as_id.fleet, No_Asset, -1), fleet[as_id.fleet].assets[as_id.millitary].Range);
            if(target_id.fleet != -1)
            {
                target = &fleet[target_id.fleet].assets[target_id.millitary].core;
                
                AutoLaunch(Asset, target, core->X, core->Y);
                Pair_Activate(fleet, PosIni(as_id.fleet, No_Asset, -1));
                Asset->core.target = target_id;
                as->interval += fleet[as_id.fleet].assets[as_id.millitary].timer;
                as->MaxAssets--;
            }
            else{
                memset(&fleet[as_id.fleet].assets[No_Asset], 0, sizeof(Millitary));
                fleet[as_id.fleet].assets[No_Asset].type = Launch_Type;
            }
        }
    }
}

void Fighter_Initialize_Start(Millitary *Fighter, double Launch_X, double Launch_Y, double target_X, double target_Y)
{
    Fighter->type = 1;
    Fighter->Range = 50;
    Fighter->timer = 20;
    Fighter->Point = Assets_Price[1];
    Fighter->core.status = 2;
    Fighter->core.speed = SPE_INTE;
    Fighter->core.X = Launch_X;
    Fighter->core.Y = Launch_Y;
    Fighter->core.X_targeting = target_X;
    Fighter->core.Y_targeting = target_Y;
    Fighter->core.direction = to_deg360_Tri(target_X - Launch_X, target_Y - Launch_Y);
}

void Agis_Initialize_Start(Millitary *Agis, double Launch_X, double Launch_Y, double target_X, double target_Y)
{
    Agis->type = 2;
    Agis->Range = 125;
    Agis->timer = 25;
    Agis->Point = Assets_Price[2];
    Agis->core.status = 2;
    Agis->core.speed = SPE_INTE / (double)4;
    Agis->core.X = Launch_X;
    Agis->core.Y = Launch_Y;
    Agis->core.X_targeting = target_X;
    Agis->core.Y_targeting = target_Y;
    Agis->core.direction = to_deg360_Tri(target_X - Launch_X, target_Y - Launch_Y);
}

void Stealth_Fighter_Initialize_Start(Millitary *Fighter, double Launch_X, double Launch_Y, double target_X, double target_Y)
{
    Fighter->type = 3;
    Fighter->Range = 200;
    Fighter->timer = 15;
    Fighter->Point = Assets_Price[3];
    Fighter->core.status = 2;
    Fighter->core.speed = SPE_INTE * 1.5;
    Fighter->core.X = Launch_X;
    Fighter->core.Y = Launch_Y;
    Fighter->core.X_targeting = target_X;
    Fighter->core.Y_targeting = target_Y;
    Fighter->core.direction = to_deg360_Tri(target_X - Launch_X, target_Y - Launch_Y);
}

void AircraftCarrier_Initialize_Start(Millitary *AircraftCarrier, double Launch_X, double Launch_Y, double target_X, double target_Y)
{
    AircraftCarrier->type = 4;
    AircraftCarrier->Range = 175;
    AircraftCarrier->timer = 200;
    AircraftCarrier->Point = Assets_Price[4];
    AircraftCarrier->MaxAssets = 0;
    AircraftCarrier->core.status = 2;
    AircraftCarrier->core.speed = SPE_INTE / (double)4;
    AircraftCarrier->core.X = Launch_X;
    AircraftCarrier->core.Y = Launch_Y;
    AircraftCarrier->core.X_targeting = target_X;
    AircraftCarrier->core.Y_targeting = target_Y;
    AircraftCarrier->core.direction = to_deg360_Tri(target_X - Launch_X, target_Y - Launch_Y);
}

void MissileBase_Initialize_Start(Millitary *MissileBase, double Launch_X, double Launch_Y, double target_X, double target_Y)
{
    MissileBase->type = 5;
    MissileBase->Range = 125;
    MissileBase->timer = 10;
    MissileBase->Point = Assets_Price[5];
    MissileBase->MaxAssets = 12;
    MissileBase->core.status = 2;
    MissileBase->core.speed = 0;
    MissileBase->core.X = Launch_X;
    MissileBase->core.Y = Launch_Y;
}

void NavalBase_Initialize_Start(Millitary *NavalBase, double Launch_X, double Launch_Y, double target_X, double target_Y)
{
    NavalBase->type = 6;
    NavalBase->Range = 200;
    NavalBase->timer = 200;
    NavalBase->Point = Assets_Price[6];
    NavalBase->MaxAssets = 0;
    NavalBase->core.status = 2;
    NavalBase->core.speed = 0;
    NavalBase->core.X = Launch_X;
    NavalBase->core.Y = Launch_Y;
    NavalBase->core.X_targeting = target_X;
    NavalBase->core.Y_targeting = target_Y;
    NavalBase->core.direction = to_deg360_Tri(target_X - Launch_X, target_Y - Launch_Y);
}

void AirBase_Initialize_Start(Millitary *AircraftBase, double Launch_X, double Launch_Y, double target_X, double target_Y)
{
    AircraftBase->type = 7;
    AircraftBase->Range = 250;
    AircraftBase->timer = 90;
    AircraftBase->Point = Assets_Price[7];
    AircraftBase->MaxAssets = 0;
    AircraftBase->core.status = 2;
    AircraftBase->core.speed = 0;
    AircraftBase->core.X = Launch_X;
    AircraftBase->core.Y = Launch_Y;
}

void Fighter_Initialize(Millitary *assets, Missile *target, double Launch_X, double Launch_Y)
{
    assets->timer = 20;
    assets->Range = 50;
    assets->Point = Assets_Price[1];
    assets->core.status = 1;
    assets->core.speed = SPE_INTE;
    assets->core.X = Launch_X;
    assets->core.Y = Launch_Y;
    assets->core.direction = Missile_Angle_Ini(&assets->core, target);
    record_cordinates(&assets->core);
}

void Agis_Initialize(Millitary *assets, Missile *target, double Launch_X, double Launch_Y)
{
    assets->timer = 25;
    assets->Range = 125;
    assets->Point = Assets_Price[2];
    assets->core.status = 1;
    assets->core.speed = SPE_INTE / (double)4;
    assets->core.X = Launch_X;
    assets->core.Y = Launch_Y;
    assets->core.direction = Missile_Angle_Ini(&assets->core, target);
    record_cordinates(&assets->core);
}

void Stealth_Fighter_Initialize(Millitary *assets, Missile *target, double Launch_X, double Launch_Y)
{
    assets->timer = 15;
    assets->Range = 200;
    assets->Point = Assets_Price[3];
    assets->core.status = 1;
    assets->core.speed = SPE_INTE * 1.5;
    assets->core.X = Launch_X;
    assets->core.Y = Launch_Y;
    assets->core.direction = Missile_Angle_Ini(&assets->core, target);
    record_cordinates(&assets->core);
}

void AircraftCarrier_Initialize(Millitary *assets, Missile *target, double Launch_X, double Launch_Y)
{
    assets->timer = 200;
    assets->Range = 175;
    assets->Point = Assets_Price[4];
    assets->core.status = 1;
    assets->core.speed = SPE_INTE / (double)4;
    assets->core.X = Launch_X;
    assets->core.Y = Launch_Y;
    assets->core.direction = Missile_Angle_Ini(&assets->core, target);
    record_cordinates(&assets->core);
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
                field[i][j - 1] = numbers[(i + Y_Start) / 5 / 10 % 10];
                field[i][j - 1] = numbers[(i + Y_Start) / 5 / 100 % 10];
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
                field[i][j - 2] = numbers[(i + Y_Start) / 5 / 100 % 10];
            }
        }
    }
}

void Grid(int fieldHeight, int fieldWidth, int X_Start, int Y_Start, char (*field)[fieldWidth], int Grid_Type)
{
    switch(Grid_Type){
        case 0: return;
        case 1: Grid_Rough(fieldHeight, fieldWidth, field); return;
        case 2: Grid_Simple(fieldHeight, fieldWidth, X_Start, Y_Start, field); return;
        case 3: Grid_Advanced(fieldHeight, fieldWidth, X_Start, Y_Start, field); return;
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
        if(!(fleet_as->assets[fighter_id.millitary].type == 1 || fleet_as->assets[fighter_id.millitary].type == 3))
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
        if(!(fleet_as->assets[base_id.millitary].type == 4 || fleet_as->assets[base_id.millitary].type == 7))
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

void Letter_Draw_Italic(int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, char* string, int letter_size)
{
    char string_field[150];
    for(int i = 0; i < letter_size; i++) // 5 is letter hight
    {
        memset(string_field, 0, 150);
        for(int p = 0; p < letter_size - i - 1; p++)
            string_field[p] = ' ';
        for(int j = 0; string[j] != 0; j++)
            strcat(string_field, fontData[(string[j] == 32 ? 75 : (string[j] - 48)) * letter_size + i]);
//        strcpy(&field[DrawFromY + i][DrawFromX], string_field);
        memcpy(&field[DrawFromY + i][DrawFromX], string_field, strlen(string_field));
    }
}

void Letter_Draw_Normal(int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, char* string, int letter_size)
{
    char string_field[120];
    for(int i = 0; i < letter_size; i++) // 5 is letter hight
    {
        memset(string_field, 0, 120);
        
        for(int j = 0; string[j] != 0; j++)
            strcat(string_field, fontData[(string[j] == 32 ? 75 : (string[j] - 48)) * letter_size + i]);
//        strcpy(&field[DrawFromY + i][DrawFromX], string_field);
        memcpy(&field[DrawFromY + i][DrawFromX], string_field, strlen(string_field));
    }
}

void Kill_Feed_Draw(KillFeed *Record, int RecordHeight, Identity as_id, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, int letter_size)
{
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

        if(Record[i].status == 1)
        {
            sprintf(&print_field[14], "%c%c%c", Record[i].destroyed.fleet == as_id.fleet ? ' ' : Record[i].destroyed.fleet + 65 + 10, 
                                                Record[i].destroyed.millitary + 65,
                                                Record[i].destroyed.missile == -1 ? ' ' : Record[i].destroyed.missile + 48);
        }
        
        Letter_Draw_Normal(fontDataWidth, fontData, fieldWidth, field, DrawFromX, DrawFromY + letter_size * (RecordHeight - i - 1), print_field, letter_size);
//        Letter_Draw_Italic(fontDataHeight, fontDataWidth, fontData, fieldWidth, field, DrawFromX, DrawFromY + letter_size * (RecordHeight - i - 1), print_field, letter_size);
    }
}

Identity Nearby_Base(Fleet *fleet, Identity as_id)
{
    Identity nMinPos = {-1, -1, -1};
    Missile* core = &fleet->assets[as_id.millitary].core;
    
    double distance[MILLITARY];
    
    for(int i = 0; i < MILLITARY; i++)
    {
        if(fleet->assets[i].core.status == 0 || !(fleet->assets[i].type == 4 || fleet->assets[i].type == 7) || as_id.millitary == i)
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

int Stand_By_Assets(Fleet *fleet, Identity as_id, int type)
{
    for(int i = 0; i < MILLITARY; i++)
    {
        if(fleet->assets[i].core.status == false && fleet->assets[i].type == 0)
        {
            fleet->assets[i].type = type;
            fleet->score -= Assets_Price[type];
            if(as_id.fleet != -1)
                fleet->assets[as_id.millitary].MaxAssets++;
            return i;
        }
    }
    return -1;
}

void Assets_Detail_Draw(Fleet *fleet, int fontDataHeight, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldHeight, int fieldWidth, char (*field)[fieldWidth], int X_Start, int Y_Start, int letter_size, int Select_Asset)
{
    char list_Assets_type[8][80] = {"", "Fighter", "Warship", "Advanced Fighter", "Aircraft Carrier", "Missile Base", "Naval Base", "Air Base"};
    char print_field[80];
    Missile *core;

    if(fleet->assets[Select_Asset].core.status <= 0)
        return;
    core = &fleet->assets[Select_Asset].core;
    if(core->X < X_Start || X_Start + fieldWidth < core->X || core->Y < Y_Start || Y_Start + fieldHeight < core->Y)
        return;
    memset(print_field, 0, 80);
    sprintf(print_field, "%s %c", list_Assets_type[fleet->assets[Select_Asset].type], (char)(Select_Asset + 65));
    Letter_Draw_Normal(fontDataWidth, fontData, fieldWidth, field, core->X + 5 - X_Start, core->Y - letter_size - Y_Start, print_field, letter_size);
//       Letter_Draw_Italic(fontDataHeight, fontDataWidth, fontData, fieldWidth, field, core->X + 5 - X_Start, core->Y - letter_size - Y_Start, print_field, letter_size);
    if(fleet->assets[Select_Asset].type == 4 || fleet->assets[Select_Asset].type == 6 || fleet->assets[Select_Asset].type == 7)
    {
        memset(print_field, 0, 80); 
        sprintf(print_field, "%d %s ready", fleet->assets[Select_Asset].MaxAssets, list_Assets_type[fleet->assets[Select_Asset].type == 6 ? 2 : 1]);
        Letter_Draw_Normal(fontDataWidth, fontData, fieldWidth, field, core->X + 5 - X_Start, core->Y - Y_Start, print_field, letter_size);
//            Letter_Draw_Italic(fontDataHeight, fontDataWidth, fontData, fieldWidth, field, core->X + 5 - X_Start, core->Y - Y_Start, print_field, letter_size);
    }
    
}

void Score_Display(Fleet *fleet, int fontDataHeight, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, int letter_size)
{
    char print_field[80];
    memset(print_field, 0, 80);
    sprintf(print_field, "Score %d", fleet->score);
    Letter_Draw_Normal(fontDataWidth, fontData, fieldWidth, field, DrawFromX, DrawFromY, print_field, letter_size);
//        Letter_Draw_Italic(fontDataHeight, fontDataWidth, fontData, fieldWidth, field, DrawFromX, DrawFromY, print_field, letter_size);
}

void Asset_Icon_Draw(Fleet *fleet, int Select, int IconDataWidth, const char (*IconData)[IconDataWidth], int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, int Icon_Height, int letter_size)
{
    char list_Assets_Name[8][80] = {"Not Active", "Fighter", "Warship", "Fighter", "Carrier", "Missile Base", "Naval Base", "Air Base"};
    char print_field[80] = {};
    sprintf(print_field, "%s %c",  list_Assets_Name[fleet->assets[Select].type], Select + 65);
    if(fleet->assets[Select].type == 3)
        Letter_Draw_Normal(fontDataWidth, fontData, fieldWidth, field, DrawFromX, DrawFromY - letter_size, "Advanced", letter_size);
    if(fleet->assets[Select].type == 4)
        Letter_Draw_Normal(fontDataWidth, fontData, fieldWidth, field, DrawFromX, DrawFromY - letter_size, "Aircraft", letter_size);
    Letter_Draw_Normal(fontDataWidth, fontData, fieldWidth, field, DrawFromX, DrawFromY, print_field, letter_size);
    for(int i = 0; i < Icon_Height; i++) 
//        memcpy(&field[DrawFromY + letter_size + i][DrawFromX], IconData[(fleet->assets[Select].type - 1) * Icon_Height + i], strlen(IconData[(fleet->assets[Select].type - 1)* Icon_Height + i]));
        strcpy(&field[DrawFromY + letter_size + i][DrawFromX], IconData[(fleet->assets[Select].type - 1) * Icon_Height + i]);
}

void Base_Detail_Draw(int size, int (*pos)[2], int fontDataHeight, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldHeight, int fieldWidth, char (*field)[fieldWidth], int X_Start, int Y_Start, int letter_size)
{
    char print_field[5];

    for(int i = 0; i < size; i++)
    {
        if(pos[i][0] == 0)
            continue;
        if(pos[i][1] < X_Start || X_Start + fieldWidth < pos[i][1] || pos[i][0] < Y_Start || Y_Start + fieldHeight < pos[i][0])
            continue;
        sprintf(print_field, "%c", i + 65);
        Letter_Draw_Normal(fontDataWidth, fontData, fieldWidth, field, pos[i][1] + 5 - X_Start, pos[i][0] - letter_size - Y_Start, print_field, letter_size);
    //       Letter_Draw_Italic(fontDataHeight, fontDataWidth, fontData, fieldWidth, field, core->X + 5 - X_Start, core->Y - letter_size - Y_Start, print_field, letter_size);
        
    }
}

void Base_Detail(int Spawn_Type, int fontDataHeight, int fontDataWidth, char (*fontData)[fontDataWidth], int fieldHeight, int fieldWidth, char (*field)[fieldWidth], int X_Start, int Y_Start, int letter_size)
{
    if(Spawn_Type == 0)
        return;
    switch(Spawn_Type){
        case 2:
        case 4: Base_Detail_Draw(26, Attack_Spawn, fontDataHeight, fontDataWidth, fontData, fieldHeight, fieldWidth, field, X_Start, Y_Start, letter_size); break;
        case 5: Base_Detail_Draw(26, Radar_Sites, fontDataHeight, fontDataWidth, fontData, fieldHeight, fieldWidth, field, X_Start, Y_Start, letter_size); break;
        case 6: Base_Detail_Draw(4, JSDF_Navy, fontDataHeight, fontDataWidth, fontData, fieldHeight, fieldWidth, field, X_Start, Y_Start, letter_size); break;
        case 7: Base_Detail_Draw(11, JSDF_AirForce, fontDataHeight, fontDataWidth, fontData, fieldHeight, fieldWidth, field, X_Start, Y_Start, letter_size); break;
    }
}

void Assets_Spawn(Fleet *fleet, Identity as_id, bool Auto, bool Attack, int *Spawn_Type)//if score condition is needed
{
    if(Auto == true)
    {
        if(fleet[as_id.fleet].Attack == false && fleet[as_id.fleet].score >= Assets_Price[7])
        {
            int pos = rand() % 41; // 26 + 11 + 4
            int type;
            if(pos < 26)
                type = 5;
            else if(pos < 30)
                type = 6;
            else
                type = 7;
            int No_Asset = Stand_By_Assets(&fleet[as_id.fleet], PosIni(-1, -1, -1), type);
            if(No_Asset == -1)
                return;
            
            arrIni[type](&fleet[as_id.fleet].assets[No_Asset], Assets_Pos[type - 5][pos - (type == 5 ? 0 : type == 6 ? 26 : 30)][1], Assets_Pos[type - 5][pos - (type == 5 ? 0 : type == 6 ? 26 : 30)][0], 0, 0);
            Pair_Activate(fleet, PosIni(as_id.fleet, No_Asset, -1));
        }
        else if(fleet[as_id.fleet].Attack == true && fleet[as_id.fleet].score >= Assets_Price[4])
        {
            int pos = rand() % 26;
//            int pos = 21;
            int type = rand() % 4 + 1;
            
            int No_Asset;
            No_Asset = Stand_By_Assets(&fleet[as_id.fleet], as_id, type);
                
            Millitary *Asset = &fleet[as_id.fleet].assets[No_Asset];
            if(No_Asset != -1)
            {
                Identity target_id;
                Missile *target;
                fleet[as_id.fleet].assets[No_Asset].core.speed = SPE_INTE * (type == 0 ? 1 : type == 3 ? 1.5 : 0.25);
                fleet[as_id.fleet].assets[No_Asset].core.X = Attack_Spawn[pos][1];
                fleet[as_id.fleet].assets[No_Asset].core.Y = Attack_Spawn[pos][0];
                target_id = Base_Target_Priority(fleet, PosIni(as_id.fleet, No_Asset, -1), 2000);
                if(target_id.fleet != -1)
                {
                    target = &fleet[target_id.fleet].assets[target_id.millitary].core;
                        
                    arrAutoLaunch[type](Asset, target, Attack_Spawn[pos][1], Attack_Spawn[pos][0]);
                    Pair_Activate(fleet, PosIni(as_id.fleet, No_Asset, -1));
                    Asset->core.target = target_id;
                }
                else{
                    memset(&fleet[as_id.fleet].assets[No_Asset], 0, sizeof(Millitary));
                    fleet[as_id.fleet].score += Assets_Price[type];
                }
            }
        }
    }
    else{
        if(*Spawn_Type != 0)
        {
            if(fleet[as_id.fleet].Attack == false && fleet[as_id.fleet].score >= Assets_Price[*Spawn_Type]){
                char pos;
                scanf(" %c", &pos);
                int No_Asset = Stand_By_Assets(&fleet[as_id.fleet], PosIni(-1, -1, -1), *Spawn_Type);
                if(No_Asset == -1){
                    *Spawn_Type = 0;
                    return;
                }
                arrIni[*Spawn_Type](&fleet[as_id.fleet].assets[No_Asset], Assets_Pos[*Spawn_Type - 5][pos - 65][1], Assets_Pos[*Spawn_Type - 5][pos - 65][0], 0, 0);
                Pair_Activate(fleet, PosIni(as_id.fleet, No_Asset, -1));
            }
            else if(fleet[as_id.fleet].Attack == true && fleet[as_id.fleet].score >= Assets_Price[*Spawn_Type])
            {
                char pos;
                scanf(" %c", &pos);
                int No_Asset;
                No_Asset = Stand_By_Assets(&fleet[as_id.fleet], as_id, *Spawn_Type);
                
                Millitary *Asset = &fleet[as_id.fleet].assets[No_Asset];
                if(No_Asset != -1)
                {
                    Identity target_id;
                    Missile *target;
                    fleet[as_id.fleet].assets[No_Asset].core.speed = SPE_INTE * (*Spawn_Type == 0 ? 1 : *Spawn_Type == 3 ? 1.5 : 0.25);
                    fleet[as_id.fleet].assets[No_Asset].core.X = Attack_Spawn[pos - 65][1];
                    fleet[as_id.fleet].assets[No_Asset].core.Y = Attack_Spawn[pos - 65][0];
                    target_id = Base_Target_Priority(fleet, PosIni(as_id.fleet, No_Asset, -1), 2000);
                    if(target_id.fleet != -1)
                    {
                        target = &fleet[target_id.fleet].assets[target_id.millitary].core;
                        arrAutoLaunch[*Spawn_Type](Asset, target, Attack_Spawn[pos - 65][1], Attack_Spawn[pos - 65][0]);
                        Pair_Activate(fleet, PosIni(as_id.fleet, No_Asset, -1));
                        Asset->core.target = target_id;
                    }
                    else{
                        memset(&fleet[as_id.fleet].assets[No_Asset], 0, sizeof(Millitary));
                        fleet[as_id.fleet].score += Assets_Price[*Spawn_Type];
                    }
                }
            }
            *Spawn_Type = 0;
        }
    }  
}
