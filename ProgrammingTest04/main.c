#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <unistd.h>
#define MAXMISSILE 3
#define HOSPERINTE 2
#define SPE_HOS 1
#define SPE_INTE 2
#define MILLITARY 3
#define FLEET 2
#define HAND 7
#define SUIT 4
#define FACE 13
#define TBLHD 7
#define PLAYER 3
typedef struct {		// 複素数型の定義
	double re;
	double im;
} Complex;

Complex  z;

typedef struct{
    int fleet;
    int millitary;
    int missile;
} Identity;

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
    Identity self;
    Identity target;//Fleet Military
} Missile;

typedef struct{
    int type;
    int pair[MAXMISSILE][HOSPERINTE];
    int Manual_Launch[3];
    int interval;
    int timer;
    int fire;
    Missile core;
    Missile missile[MAXMISSILE];
} Millitary;

typedef struct{
    Millitary assets[MILLITARY];
    int pair_base[FLEET][MILLITARY];
    int pair[FLEET][MILLITARY][MAXMISSILE];
} Fleet;

typedef struct{
    char * face;
    char * suit;
    int num;
} Card;

typedef struct{
    int hand;
    int ref_1;
    int ref_2;
    int ref_3;
} Strenght;

typedef struct{
    Strenght Hand_id;
    Card Hands[HAND];
    Card Tb_Hd_Hands [TBLHD];
    int coin;
    int bet;
    int Error;
    int status;
    int Total_bet;
    char name[20];
} Player;

int Available_Missile(Missile *missile);
Complex ComplexInit(double re, double im);
Identity PosIni(int i, int j, int k);
Identity PassingStruct(Identity Id);
bool Target_Lock_On(Missile *missile, Identity target_id);
bool Comp_Struct(Identity id_1, Identity id_2);
Identity Base_Attack(int (*pair_base)[MILLITARY]);
Identity Target_Priority(Fleet* fleet, Identity identity, const double *baseX, const double *baseY);
void Base_Initialize(Missile *Base, double base_X, double base_Y, double target_X, double target_Y);
void Missile_Initialize(Missile *missile, double Pos_X, double Pos_Y, double future_X, double future_Y);
double to_deg360_Tri(double run, double rise);
bool Input_Conve(int *charactor, int *num, char escape);
Identity far_Missile(Fleet *fleet, Identity as_id, Identity target_id);
int Ext_Array(int *From_arr, int ref_1, int ref_2, int ref_3);
Strenght Hnds_Idntfy(Card *Hands, int size);
Strenght HandIni(int Hand_id, int ref_1, int ref_2, int ref_3);
void fillDeck(Card * wDeck, char * wFace[], char * wSuit[], int *Hand_set, int size);
void deal(Card * wDeck, int size);
int test_in_function(int a, int b);
int a = 2;
bool Status_Same(int *status, int size);
int Hand_Cmp(Player * players, int size, int h_size);

int main(int argc, char **argv)
{


    Fleet fleet[2];
    Identity enemy, enemy01;
    memset(fleet, 0, sizeof(Fleet) * 2);
    

    
    	Complex z1, z2;

//	z1 = {1.0, 2.0};		// NG...
	z1 = ComplexInit(1.0, 2.0);		// z1 = 1 + 2i
    z2 = ComplexInit(2.0, 8.0);
    enemy = PosIni(1, 2, 3);
    enemy01 = PassingStruct(enemy);

	printf("z1 = %f + %f i\n", z1.re, z1.im);
    printf("z1 = %f + %f i\n", z2.re, z2.im);
    printf("fleet: %d, millitary: %d, missile: %d\n", enemy.fleet, enemy.millitary, enemy.missile);
    printf("fleet: %d, millitary: %d, missile: %d\n", enemy01.fleet, enemy01.millitary, enemy01.missile);
    
    Missile missile[6];
    memset(missile, 0, sizeof(Missile) * 6);
    missile[0].status = 1;
    missile[0].target = PosIni(1, 1, 1);
    missile[0].lock_On = 1;
    missile[1].status = 1;
    missile[1].target = PosIni(1, 1, 2);
    missile[1].lock_On = 0;
    
    printf("Lock_On: %d\n", Target_Lock_On(missile, PosIni(1, 1, 1)));
    
    int pair_base[1][3] = {{2, 1, 0}};
    Identity base = Base_Attack(pair_base);
    
    for(int i = 0; i < FLEET; i++)
    {
        for(int j = 0; j < MILLITARY; j++)
        {
            for(int k  = 0; k < MAXMISSILE; k++)
            {
                fleet[0].pair[i][j][k] = -1;
                fleet[1].pair[i][j][k] = -1;
                fleet[0].pair_base[i][j] = -1;
                fleet[1].pair_base[i][j] = -1;
            }
        }
    }
    
    int BaseX = 0;
    int BaseY = 0;
    Base_Initialize(&fleet[0].assets[0].core, 0, 0, 50, 50);
    Missile_Initialize(&fleet[0].assets[0].missile[0], 20, 20, 30, 30);
    Missile_Initialize(&fleet[0].assets[0].missile[1], 25, 25, 35, 35);
    Missile_Initialize(&fleet[0].assets[0].missile[2], 30, 30, 40, 40);
    Missile_Initialize(&fleet[1].assets[0].missile[0], 70, 20, 30, 30);
    Missile_Initialize(&fleet[1].assets[0].missile[1], 65, 25, 35, 35);
    Missile_Initialize(&fleet[1].assets[0].missile[2], 60, 30, 40, 40);
    Missile_Initialize(&fleet[1].assets[1].missile[0], 20, 20, 30, 30);
    Missile_Initialize(&fleet[1].assets[1].missile[1], 25, 25, 35, 35);
    Missile_Initialize(&fleet[1].assets[1].missile[2], 30, 30, 40, 40);
    Missile_Initialize(&fleet[1].assets[2].missile[0], 35, 20, 30, 30);
    Missile_Initialize(&fleet[1].assets[2].missile[1], 40, 25, 35, 35);
    Missile_Initialize(&fleet[1].assets[2].missile[2], 45, 30, 40, 40);

    fleet[0].pair[1][0][0] = 2;
    fleet[0].pair[1][0][1] = 1;
    fleet[0].pair[1][0][2] = 2;
    fleet[0].pair[1][1][0] = 1;
    fleet[0].pair[1][1][1] = 2;
    fleet[0].pair[1][1][2] = 1;
    fleet[0].pair[1][2][0] = 2;
    fleet[0].pair[1][2][1] = 1;
    fleet[0].pair[1][2][2] = 1;
    fleet[0].pair_base[1][0] = 0;
    fleet[0].pair_base[1][1] = 0;
    fleet[0].pair_base[1][2] = 0;
    
    fleet[0].assets[0].missile[1].target = PosIni(1, 0, 2);
    fleet[0].assets[0].missile[2].target = PosIni(1, 0, 2);
    
    Identity far_target = far_Missile(fleet, PosIni(0, 0, -1), PosIni(1, 0, 2));
    Identity target = Target_Priority(fleet, PosIni(0, 0, 2), &BaseX, &BaseY);
    printf("%c\n", 65);
    
//    for(double i = 0; i < 2 * M_PI; i += (M_PI / 12))
//        for(double j = 0; j < 2 * M_PI; j += (M_PI / 12))
//        {
//            printf("target %.3lf, actual %.3lf, result ", i, j);
//            if(M_PI / 3 < fabs(i -j) && fabs(i - j) < M_PI / 3 * 5)
//                printf("false\n");
//            else
//                printf("true\n");
//        }
    
    
        

//    int num = 0;
//
//    int cordinateY = 0;
//    int cordinateX = 0;
//    
//    while(1){
//        Input_Conve(&cordinateY, &cordinateX, 'm');
//        
//        printf("CordinateY %c%c CordinateX %c%c%c\n", cordinateY / 26 == 0 ? 32 : cordinateY / 26 + 65 - 1 , cordinateY % 26 + 65, cordinateX / 100 + 48, cordinateX / 10 % 10 + 48, cordinateX % 10 + 48);
//        printf("CordinateY %d CordinateX %d\n", cordinateY, cordinateX);
////        printf("Fleet %d, Millitary %d, Missile %d\n", (cordinateY - 10)/ 26 % 10, cordinateY % 26, cordinateX);
//    }

    Missile OnePush1;
    OnePush1.target = PosIni(1, 2, 2);
    OnePush1.self = PosIni(2, 4, 3);
    Missile OnePush2;
    OnePush2 = OnePush1;
    printf("\\|_-\n");

    const char Hands_Rank_Ext[10][25] = {"Royal Flush", 
                            "Straight Flush", 
                            "Four of a Kind", 
                            "Full House", 
                            "Flush", 
                            "Straight", 
                            "Three of a Kind", 
                            "Two Pair", 
                            "One Pair", 
                            "No Pair"};
    int odds[10] = {0, 1000, 250, 75, 50, 25, 5, 2, 1, 0};
    float probability[10] = {0, 0.000015, 0.00024, 0.0014, 0.002, 0.0039, 0.021, 0.0475, 0.4225, 0.5};
    
    double sumPro = 0;
    for(int i = 0; i < 9; i++)
        sumPro += odds[i] * probability[i];
    for(int i = 0; i < 9; i++){
        printf("%-20s", Hands_Rank_Ext[i]);
        for(int j = 0; odds[i] * probability[i] > j * 0.01; j++)
            printf("*");
        printf("\n");
    }
    printf("%lf\n", sumPro);
    
    int From_arr[13] = {9, -1, 2, 1, 0};
    
    printf("Ext number is :%d\n", Ext_Array(From_arr, -2, -2, -1));
    const char * wFace[FACE] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
    const char * wSuit[SUIT] = {"Spade", "Heart", "Clover", "Diamond"};
    
    int size = 7;
    int Hands_num[7] = {1, 31, 29, 10, 17, 6, 46};
    
    Card Hands[HAND];
    fillDeck(Hands, wFace, wSuit, Hands_num, size);
    deal(Hands, size);
    
    
    printf("%s\n", Hands_Rank_Ext[Hnds_Idntfy(Hands, size).hand]);
    printf("%d\n", test_in_function(4, 5));
    char field_string_1[50] = "apple";
    char field_string_2[50] = " orange";
    sprintf(field_string_1, "%s, %s", field_string_2, field_string_1);
    printf("%s\n", field_string_1);
    int status[5] = {1, 2, 1, 1, 1};
    printf("%d\n", Status_Same(status, 5));
    
    Player players[PLAYER];
    int Hands_num_1[7] = {5, 33, 43, 39, 12, 17, 30};
    int Hands_num_2[7] = {21, 25, 43, 39, 12, 17, 30};
    int Hands_num_3[7] = {7, 20, 43, 39, 12, 17, 30};
//    int Hands_num_4[7] = {1, 1, 2, 2, 3, 4, 6};
    players[0].Hand_id.hand = 6;
    players[1].Hand_id.hand = 3;
    players[2].Hand_id.hand = 3;
//    players[3].Hand_id.hand = 9;
    players[0].Hand_id.ref_1 = 4;
    players[1].Hand_id.ref_1 = 12;
    players[2].Hand_id.ref_1 = 7;
//    players[3].Hand_id.ref_1 = 8;
    players[0].Hand_id.ref_2 = 4;
    players[1].Hand_id.ref_2 = 12;
    players[2].Hand_id.ref_2 = 8;
//    players[3].Hand_id.ref_2 = 6;
    players[0].Hand_id.ref_3 = 4;
    players[1].Hand_id.ref_3 = 7;
    players[2].Hand_id.ref_3 = 12;
//    players[3].Hand_id.ref_3 = 6;
    
    fillDeck(players[0].Hands, wFace, wSuit, Hands_num_1, size);
    deal(players[0].Hands, size);
    printf("\n");
    fillDeck(players[1].Hands, wFace, wSuit, Hands_num_2, size);
    deal(players[1].Hands, size);
    printf("\n");
    fillDeck(players[2].Hands, wFace, wSuit, Hands_num_3, size);
    deal(players[2].Hands, size);
    printf("\n");
//    fillDeck(players[3].Hands, wFace, wSuit, Hands_num_4, size);
//    deal(players[3].Hands, size);
    printf("%d\n", Hand_Cmp(players, PLAYER, size));
    
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    return;
}

int Available_Missile(Missile *missile)
{
    for(int i = 0; i < MAXMISSILE; i++)
    {
        if(missile[i].status == false)
        {
            return i;
        }
    }
    return -1;
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

Complex ComplexInit(double re, double im)
{
	Complex z;

	z.re = re;
	z.im = im;

	return z;
}

Identity PosIni(int i, int j, int k)
{
    Identity Pos;
    
    Pos.fleet = i;
    Pos.millitary = j;
    Pos.missile = k;
    
    return Pos;
}

Identity PassingStruct(Identity Id)
{
    Identity result = {-1, -1, -1};
    
    result.fleet = Id.fleet;
    
    return result;
}

bool Target_Lock_On(Missile *missile, Identity target_id)
{

    for(int i = 0; i < MAXMISSILE; i++)
    {
        if(missile[i].status == 0)
            continue;
        if(Comp_Struct(missile[i].target, target_id) && missile[i].lock_On)
            return true;
    }
}

bool Comp_Struct(Identity id_1, Identity id_2)
{
    if(id_1.fleet == id_2.fleet && id_1.millitary == id_2.millitary && id_1.missile == id_2.missile)
        return true;
    return false;
}

Identity Target_Priority(Fleet* fleet, Identity identity, const double *baseX, const double *baseY)
{
    Identity nMinPos, nMinPos_Unmarked, base_attack;
    Missile *missile = &fleet[identity.fleet].assets[identity.millitary].missile[identity.missile];
    nMinPos = PosIni(-1, -1, -1);
    nMinPos_Unmarked = PosIni(-1, -1, -1);
    base_attack = Base_Attack(fleet[identity.fleet].pair_base);
    
    double distance[FLEET][MILLITARY][MAXMISSILE] = {};
    
    
    for(int i = 0; i < FLEET; i++)
    {
        for(int j = 0; j < MILLITARY; j++)
        {
            for(int k = 0; k < MAXMISSILE; k++)
            {
                distance[i][j][k] = 999;

            }
        }
    }
    
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
    if(distance[nMinPos.fleet][nMinPos.millitary][nMinPos.missile] < (15))
    {
        missile->target = nMinPos;
        fleet[identity.fleet].pair[nMinPos.fleet][nMinPos.millitary][nMinPos.missile]++;
        return nMinPos;
    }
    
    //if there are unmarked missile mMinPos_Unmarked gives pos and if there are no unmarked missiles then nMinPos_unmarked is 0 that is base attack
    if(nMinPos_Unmarked.fleet !=  -1)
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

Identity Base_Attack(int (*pair_base)[MILLITARY])
{
    Identity nMinPos = {-1, -1, -1};
    
    for(int i = 0; i < FLEET; i++)
    {
        for(int j = 0; j < MILLITARY; j++)
        {
            if(pair_base[i][j] == -1)
                continue;
                                                                                                    //first time 
            if(pair_base[i][j] < 2 && pair_base[nMinPos.fleet][nMinPos.millitary] > pair_base[i][j] || nMinPos.fleet == -1)
            {
                nMinPos = PosIni(i, j, 0);
            }
        }
                
    }
    return nMinPos;
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

bool Input_Conve(int *charactor, int *num, char escape)
{
    char string[6] = {};

    scanf("%s", &string);
    
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
                    if(hypot(target->X - fleet[as_id.fleet].assets[i].missile[j].X, target->Y - fleet[as_id.fleet].assets[i].missile[j].Y) > hypot(target->X - fleet[pair.fleet].assets[pair.millitary].missile[j].X, target->Y - fleet[as_id.fleet].assets[pair.millitary].missile[pair.missile].Y))
                        return PosIni(as_id.fleet, i, j);
                    else
                        return pair;
                }
            }
        }
    }
}

int Ext_Array(int *From_arr, int ref_1, int ref_2, int ref_3)
{
    ///if ref_1 is -1, need to find ref_1 first and if ref_1 is -2 that is one skip,
    //if ref_2 is -2, that is double skip,
    //if ref_2 and ref_3 are -2, that is triple skip.
    int size = HAND;
    
    if(ref_1 == -1)
    {
        for(int i = 0; i < size; i++){
            if(From_arr[i] == -1)
                continue;
            if(ref_2 == -1 && ref_3 == -1)
                return From_arr[i];
            ref_1 =  From_arr[i];
            break;
        }
    }
    if(ref_1 == -2)
    {
        for(int i = 0; i < size; i++){
            if(From_arr[i] == -1)
                continue;
            ref_1 =  From_arr[i];
            break;
        }
    }
    if(ref_2 != -1 && ref_3 != -1 && ref_2 != -2 && ref_3 != -2){
        for(int i = 0; i < size; i++){
            if(From_arr[i] == -1)
                continue;
            if(!(From_arr[i] == ref_1 || From_arr[i] == ref_2 || From_arr[i] == ref_3))
                return From_arr[i];
        }
    }
    else if(ref_2 != -1 && ref_2 != -2 && ref_3 != -2){
        for(int i = 0; i < size; i++){
            if(From_arr[i] == -1)
                continue;
            if(!(From_arr[i] == ref_1 || From_arr[i] == ref_2))
                return From_arr[i];
        }
    }
    else if(ref_2 == -2 && ref_3 == -2){
        for(int i = 0; i < size; i++){
            if(From_arr[i] == -1)
                continue;
            if(!(From_arr[i] == ref_1 || From_arr[i] == Ext_Array(From_arr, ref_1, -1, -1) || From_arr[i] == Ext_Array(From_arr, ref_1, -2, -1)))
                return From_arr[i];
        }
    }
    else if(ref_2 == -2){
        for(int i = 0; i < size; i++){
            if(From_arr[i] == -1)
                continue;
            if(!(From_arr[i] == ref_1 || From_arr[i] == Ext_Array(From_arr, ref_1, -1, -1)))
                return From_arr[i];
        }
    }
    else{
        for(int i = 0; i < size; i++){
            if(From_arr[i] == -1)
                continue;
            if(From_arr[i] != ref_1)
                return From_arr[i];
                
        }
    }
}

Strenght Hnds_Idntfy(Card *Hands, int size)
{
    int Card_Strenght[HAND] = {};
    int suit[4];
    int face[13];
    memset(suit, 0, 4 * sizeof(int));
    memset(face, 0, 13 * sizeof(int));
    for(int i = 0; i < size; i++)
    {
        suit[Hands[i].num / 13] ++;
        face[Hands[i].num % 13] ++;
    }

    for(int i = 12, j = 0; i >= 0; i--)
        if(face[i] > 0)
            Card_Strenght[j++] = i;
            
    //flash
    int flash = -1;
    int straight = -1;
    int three = -1;
    int two = -1;
    Strenght two_pair = HandIni(-1, -1, -1, -1);
    
    for(int i = 0; i < 13; i++) // 13 numbers of faces
    {    
        if(face[i] == 0)
            continue;
            
        if(straight == -1 && face[i] != 0)
        {
            for(int j = 4; j >= 1; j--)
            {
                if(face[i + j] == 0)
                    break;
                if(j == 1)
                    straight = i+4;
            }
        }
        
        if(two != -1 && face[i] == 2)
            two_pair = HandIni(7,  two > face[i] ? two : face[i], two < face[i] ? two : face[i], Ext_Array(Card_Strenght, two, face[i], -1));
        if(face[i] == 4)
            return HandIni(2, i, Card_Strenght[0] == i ? Card_Strenght[1] : Card_Strenght[0], -1);
        if(face[i] == 3)
            three = i;
        if(face[i] == 2)
            two = i;
        if((two != -1 && face[i] == 3)|| (three != -1 && face[i] == 2))
            return HandIni(3, three != -1 ? three : i, three != -1 ?  i : three, -1);
    }

    for(int i = 0; i < 4; i++)
    {
        if(suit[i] == 5)
        {
//Royal Flush
            if(straight != -1)
                return HandIni(1, 12, -1, -1);
//Flush
            return HandIni(4, Card_Strenght[0], Card_Strenght[1], Card_Strenght[2]);
        }
    }
//Straight
    if(straight != -1)
        return HandIni(5, straight, -1, -1);
//Three of a Kind
    if(three != -1)
        return HandIni(6, three, Ext_Array(Card_Strenght, three, -1, -1), Ext_Array(Card_Strenght, three, -2, -1));
//Two Pair
    if(two_pair.hand != -1)
        return two_pair;
//One Pair
    if(two != -1)
        return HandIni(8, two,  Ext_Array(Card_Strenght, two, -1, -1), Ext_Array(Card_Strenght, two, -2, -1));

        
    return HandIni(9, Card_Strenght[0], Card_Strenght[1], Card_Strenght[2]);
}

Strenght HandIni(int Hand_id, int ref_1, int ref_2, int ref_3)
{
    Strenght Hand;
    
    Hand.hand = Hand_id;
    Hand.ref_1 = ref_1;
    Hand.ref_2 = ref_2;
    Hand.ref_3 = ref_3;
    
    return Hand;
}

void fillDeck(Card * wDeck, char * wFace[], char * wSuit[], int *Hand_set, int size)
{
    for(int i = 0; i < size; i++)
    {
        wDeck[i].face = wFace[Hand_set[i] % FACE];
        wDeck[i].suit = wSuit[Hand_set[i] / FACE];
        wDeck[i].num = Hand_set[i];
    }
}
void deal(Card * wDeck, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%5s of %-8s (%d)%s", wDeck[i].face, wDeck[i].suit, wDeck[i].num, (i + 1) % 4 ? " " : "\n");
    }
}

int test_in_function(int a, int b)
{
//    a = 3;
    return a;
}

bool Status_Same(int *status, int size)
{
    for(int i = 0; i < size - 1; i++)
    {
        if(status[i] == status[i + 1])
            continue;
        return false;
    }
    return true;
}

int Hand_Cmp(Player * players, int size, int h_size)
{
    int Hand_rank[PLAYER] = {};
    for(int i = 0; i < PLAYER; i++)
        if(players[i].Error == 5)
            Hand_rank[i] = -1;
    int counter = 0;
    int nMax_Pos = 0;
    for(int i = 1; i < size; i++){
        if(Hand_rank[i] == -1)
            continue;
        if(players[nMax_Pos].Hand_id.hand >= players[i].Hand_id.hand || Hand_rank[nMax_Pos] == -1){
            if(players[nMax_Pos].Hand_id.hand == players[i].Hand_id.hand){
                nMax_Pos = i;
                counter++;
            }
            else{
                nMax_Pos = i;
                counter = 0;
            }
        }
        else{
            Hand_rank[i] = -1;
        }
    }
    if(counter == 0)
        return nMax_Pos;
    counter = 0;
    nMax_Pos = 0;
    for(int i = 1; i < size; i++){
        if(Hand_rank[i] == -1)
            continue;
        if(players[nMax_Pos].Hand_id.ref_1 <= players[i].Hand_id.ref_1 || Hand_rank[nMax_Pos] == -1){
            if(players[nMax_Pos].Hand_id.ref_1 == players[i].Hand_id.ref_1){
                nMax_Pos = i;
                counter++;
            }
            else{
                nMax_Pos = i;
                counter = 0;
            }
        }
        else{
            Hand_rank[i] = -1;
        }
    }
    if(counter == 0)
        return nMax_Pos;
    counter = 0;
    nMax_Pos = 0;
    for(int i = 1; i < size; i++){
        if(Hand_rank[i] == -1)
            continue;
        if(players[nMax_Pos].Hand_id.ref_2 <= players[i].Hand_id.ref_2 || Hand_rank[nMax_Pos] == -1){
            if(players[nMax_Pos].Hand_id.ref_2 == players[i].Hand_id.ref_2){
                nMax_Pos = i;
                counter++;
            }
            else{
                nMax_Pos = i;
                counter = 0;
            }
        }
        else{
            Hand_rank[i] = -1;
        }
    }
    if(counter == 0)
        return nMax_Pos;
    counter = 0;
    nMax_Pos = 0;
    for(int i = 1; i < size; i++){
        if(Hand_rank[i] == -1)
            continue;
        if(players[nMax_Pos].Hand_id.ref_3 <= players[i].Hand_id.ref_3 || Hand_rank[nMax_Pos] == -1){
            if(players[nMax_Pos].Hand_id.ref_3 == players[i].Hand_id.ref_3){
                nMax_Pos = i;
                counter++;
            }
            else{
                nMax_Pos = i;
                counter = 0;
            }
        }
        else{
            Hand_rank[i] = -1;
        }
    }
    if(counter == 0)
        return nMax_Pos;
    counter = 0;
    nMax_Pos = 0;
    
    int face[PLAYER][FACE] = {};

    for(int i = 0; i < PLAYER; i++){
        if(Hand_rank[i] == -1)
            continue;
        for(int j = 0; j < h_size; j++)
            face[i][players[i].Hands[j].num % FACE]++;
    }
    
    int nMax = -1;
    
    for(int i = FACE - 1; i >= 0; i--){
        int on = 0;
        for(int j = 0; j < PLAYER; j++){
            if(Hand_rank[j] == -1)
                continue;
            if((face[j][i] != 0 && on == 0) || face[j][i] > on)
                on = face[j][i];
        }
        if(on == 0)
            continue;
        for(int j = 0; j < PLAYER; j++){
            if(Hand_rank[j] == -1)
                continue;
            if(face[j][i] == on){
                counter++;
                nMax = j;
            }
            else
                Hand_rank[j] = -1;
        }
        if(counter == 1)
            return nMax;
        nMax = -1;
        counter = 0;
        on = 0;
    }
    
    return -1;
    
}
//
//int Hand_Cmp(Player * players, int size, int h_size)
//{
//    int Hand_rank[PLAYER] = {};
//    for(int i = 0; i < PLAYER; i++)
//        if(players[i].Error == 5)
//            Hand_rank[i] = -1;
//    int counter = 0;
//    int nMax_Pos = 0;
//    for(int i = 1; i < size; i++){
//        if(Hand_rank[i] == -1)
//            continue;
//        if(players[nMax_Pos].Hand_id.hand >= players[i].Hand_id.hand){
//            if(players[nMax_Pos].Hand_id.hand == players[i].Hand_id.hand){
//                nMax_Pos = i;
//                counter++;
//            }
//            else{
//                nMax_Pos = i;
//                counter = 0;
//            }
//        }
//        else{
//            Hand_rank[i] = -1;
//        }
//    }
//    if(counter == 0)
//        return nMax_Pos;
//    counter = 0;
//    nMax_Pos = 0;
//    for(int i = 1; i < size; i++){
//        if(Hand_rank[i] == -1)
//            continue;
//        if(players[nMax_Pos].Hand_id.ref_1 <= players[i].Hand_id.ref_1){
//            if(players[nMax_Pos].Hand_id.ref_1 == players[i].Hand_id.ref_1){
//                nMax_Pos = i;
//                counter++;
//            }
//            else{
//                nMax_Pos = i;
//                counter = 0;
//            }
//        }
//        else{
//            Hand_rank[i] = -1;
//        }
//    }
//    if(counter == 0)
//        return nMax_Pos;
//    counter = 0;
//    nMax_Pos = 0;
//    for(int i = 1; i < size; i++){
//        if(Hand_rank[i] == -1)
//            continue;
//        if(players[nMax_Pos].Hand_id.ref_2 <= players[i].Hand_id.ref_2){
//            if(players[nMax_Pos].Hand_id.ref_2 == players[i].Hand_id.ref_2){
//                nMax_Pos = i;
//                counter++;
//            }
//            else{
//                nMax_Pos = i;
//                counter = 0;
//            }
//        }
//        else{
//            Hand_rank[i] = -1;
//        }
//    }
//    if(counter == 0)
//        return nMax_Pos;
//    counter = 0;
//    nMax_Pos = 0;
//    for(int i = 1; i < size; i++){
//        if(Hand_rank[i] == -1)
//            continue;
//        if(players[nMax_Pos].Hand_id.ref_3 <= players[i].Hand_id.ref_3){
//            if(players[nMax_Pos].Hand_id.ref_3 == players[i].Hand_id.ref_3){
//                nMax_Pos = i;
//                counter++;
//            }
//            else{
//                nMax_Pos = i;
//                counter = 0;
//            }
//        }
//        else{
//            Hand_rank[i] = -1;
//        }
//    }
//    if(counter == 0)
//        return nMax_Pos;
//    counter = 0;
//    nMax_Pos = 0;
//    
//    int face[PLAYER][FACE] = {};
//
//    for(int i = 0; i < PLAYER; i++){
//        if(Hand_rank[i] == -1)
//            continue;
//        for(int j = 0; j < h_size; j++)
//            face[i][players[i].Hands[j].num % FACE]++;
//    }
//            
//    int nMax = -1;
//    
//    for(int i = FACE - 1; i >= 0; i--){
//        int on = 0;
//        for(int j = 0; j < PLAYER; j++){
//            if(Hand_rank[j] == -1)
//                continue;
//            if((face[j][i] != 0 && on == 0) || face[j][i] > on)
//                on = face[j][i];
//        }
//        if(on == 0)
//            continue;
//        for(int j = 0; j < PLAYER; j++){
//            if(Hand_rank[j] == -1)
//                continue;
//            if(face[j][i] == on){
//                counter++;
//                nMax = j;
//            }
//            else
//                Hand_rank[j] = -1;
//        }
//        if(counter == 1)
//            return nMax;
//        nMax = -1;
//        counter = 0;
//        on = 0;
//    }
//    
//    return -1;
//    
//}

//void fill_Card_Fr_Ch(Card *Table, Card (*Hands)[PLAYER_3], char (*cards)[2], int size)
//{
//    
//}