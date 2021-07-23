#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#define CARD 52
#define FACE 13
#define SUIT 4
#define HAND 5
#define TBL 5
#define TBLHD 7
#define PLAY 1

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
    int money;
    int bet;
    int Error;
    int status;
} Player;

typedef struct{
    Player player[PLAY];
    int call;
    int raise;
    int stage;
    int nCall;
    int pot;
    int min_bet;
} Game;

const char Hands_Rank[10][25] = {"Royal        Flush", 
                            "Straight      Flush", 
                            "Four   of   a   Kind", 
                            "Full      House", 
                            "Flush", 
                            "Straight", 
                            "Three   of   a   Kind", 
                            "Two      Pair", 
                            "One      Pair", 
                            "No      Pair"};

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

void fillDeck(Card * wDeck, char * wFace[], char * wSuit[]);
void shuffleDeck(Card * wDeck);
void deal(Card * wDeck);
int range(int num);
void Map_Import(int tableHeight, int tableWidth, char(*table)[tableWidth], char* fname);
void nTable_Draw(int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, Card *Hand, int size, int letter_size);
void Letter_Draw_Italic(int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, char* string, int letter_size);
void Letter_Draw_Normal(int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, char* string, int letter_size);
void printArray2(int fieldHeight, int fieldWidth, char field[fieldHeight][fieldWidth]);
void printArray3(int fieldHeight, int fieldWidth, char field[fieldHeight][fieldWidth]);
void Chng_Crds(Card * wDeck, Card *Hand, int *Draw_Start, bool *Chng_Pos, int size);
void Cpy_Hnds(Card *wDeck, Card *Hands, int *pos, int size);
Strenght Hnds_Idntfy(Card *Hands, int size);
void S_C_Draw(int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], bool *Chng_Pos, int size, int DrawFromX, int DrawFromY, int letter_size, int Card_DesignWidth);
int Control(bool *Chng_Pos, int size);
int Betting(int *bet, int *money, int min_bet);
void Odds_Prob_Draw(int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int bet, int DrawFromX, int DrawFromY, int letter_size);
void Pay_Bet(int *money, int bet);
void Get_Award(int *money, int bet, int Hand_id);
void Mny_Bt_Draw(int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int money, int bet, int earned, int *Error, int DrawFromX, int DrawFromY, int letter_size);
Strenght HandIni(int Hand_id, int ref_1, int ref_2, int ref_3);
int Ext_Array(int *From_arr, int ref_1, int ref_2, int ref_3);

int main(int argc, char **argv)
{
    Card deck[CARD];
    Card Hands[HAND];
    const char * wFace[FACE] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
    const char * wSuit[SUIT] = {"Spade", "Heart", "Clover", "Diamond"};
    
    char Card_Design[3485][101] = {};
    int Card_DesignHeight = 3485;
    int Card_DesignWidth = 101;
    int Card_Height = 67;
    char field[160][800] = {};
    int fieldHeight = 160;
    int fieldWidth = 800;
    static char fontData[500][50];
    int fontDataHeight = 500;
    int fontDataWidth = 50;
    static char fontData_Ext[500][50];
    int fontDataHeight_Ext = 500;
    int fontDataWidth_Ext = 50;
    int font_size = 6;
    char print_field[50] = {};
    
    Strenght Hand_id = HandIni(-1, -1, -1, -1);
    int money = 1000;
    int bet = 0;
    int min_bet = 100;
    int Error = 0;
    int pot = 0;
    int counter = 0;
    int hit_counter = 0;
    
    srand(time(NULL));
    Map_Import(Card_DesignHeight, Card_DesignWidth, Card_Design, "Cards Full Fixed.txt");
    Map_Import(fontDataHeight, fontDataWidth, fontData, "font Ivrit Space1.txt");
    Map_Import(fontDataHeight_Ext, fontDataWidth_Ext, fontData_Ext, "font Ivrit.txt");
    fillDeck(deck, wFace, wSuit);
    shuffleDeck(deck);
    deal(deck);
    
    int Draw_Start = 0;
    ///////////
    ///////////
    //Chenge here when u change HAND value
//    int posHand[HAND] = {Draw_Start + 0 , Draw_Start + 1, Draw_Start + 2, Draw_Start + 3, Draw_Start + 4};
//    int posHand[HAND] = {Draw_Start + 0 , Draw_Start + 1, Draw_Start + 2, Draw_Start + 3, Draw_Start + 4, Draw_Start + 5};
    int posHand[HAND] = {Draw_Start + 0 , Draw_Start + 1, Draw_Start + 2, Draw_Start + 3, Draw_Start + 4, Draw_Start + 5, Draw_Start + 6};
//    int posHand[HAND] = {48 , 28, 29, 36, 30};
    Draw_Start += HAND;
    bool Chng_Pos[HAND] = {false, false, false, false, false};
    
    Cpy_Hnds(deck, Hands, posHand, HAND);
    while(1){
        bet = 0;
//Betting time
        while(1){
            memset(field, 0, fieldWidth * fieldHeight);
            Odds_Prob_Draw(fontDataWidth_Ext, fontData_Ext, fieldWidth, field, bet, 0, Card_Height + font_size*3 + 2, font_size);
            Mny_Bt_Draw(fontDataWidth_Ext, fontData_Ext, fieldWidth, field, money, bet, -1, &Error, 0, Card_Height + font_size*2 + 2, font_size);
            system("cls");
//            deal(deck);
            printArray3(fieldHeight, fieldWidth, field);
            if((Error = Betting(&bet, &money, min_bet)) == true)
                break;
        }
        for(int i = 0; i < HAND; i++)
            Chng_Pos[i] = false;
        while(1){
            Hand_id = Hnds_Idntfy(Hands, HAND);
            memset(field, 0, fieldWidth * fieldHeight);
//Hand Card Drawing
            nTable_Draw(Card_DesignWidth, Card_Design, fieldWidth, field, 0, 0, Hands, HAND, Card_Height);
//Stay or Change
            S_C_Draw(fontDataWidth, fontData, fieldWidth, field, Chng_Pos, HAND, 0, Card_Height + 1, font_size, Card_DesignWidth);
//Hands Rank
            Letter_Draw_Normal(fontDataWidth, fontData, fieldWidth, field, 0, Card_Height + font_size + 2, Hands_Rank[Hand_id.hand], font_size);
//Odds Reference
//            Odds_Prob_Draw(fontDataWidth_Ext, fontData_Ext, fieldWidth, field, bet, Card_DesignWidth * HAND, 0, font_size);
            Odds_Prob_Draw(fontDataWidth_Ext, fontData_Ext, fieldWidth, field, bet, 0, Card_Height + font_size*3 + 2, font_size);
//Money and bet
            Mny_Bt_Draw(fontDataWidth_Ext, fontData_Ext, fieldWidth, field, money, bet, -1, &Error, 0, Card_Height + font_size*2 + 2, font_size);
            system("cls");
//            deal(deck);
            printArray3(fieldHeight, fieldWidth, field);
            if(Control(Chng_Pos, HAND) == true)
                break;
        }
        
        Chng_Crds(deck, Hands, &Draw_Start, Chng_Pos, HAND);
        Hand_id = Hnds_Idntfy(Hands, HAND);
        
        
//        if(Hand_id.hand == 4){
            memset(field, 0, fieldWidth * fieldHeight);
            nTable_Draw(Card_DesignWidth, Card_Design, fieldWidth, field, 0, 0, Hands, HAND, Card_Height);
            Letter_Draw_Normal(fontDataWidth, fontData, fieldWidth, field, 0, Card_Height + font_size + 2, Hands_Rank[Hand_id.hand], font_size);
            
            
//counter display
//            memset(print_field, 0, 50);
//            sprintf(print_field, "Counter %d", counter);
//            Letter_Draw_Normal(fontDataWidth_Ext, fontData_Ext, fieldWidth, field, Card_DesignWidth * 1.5, Card_Height + font_size*4 + 2, print_field, font_size);
////Prob Display
//            memset(print_field, 0, 50);
//            sprintf(print_field, "Prob %.3f", hit_counter / (float)counter);
//
//            Letter_Draw_Normal(fontDataWidth_Ext, fontData_Ext, fieldWidth, field, Card_DesignWidth * 1.5, Card_Height + font_size*5 + 2, print_field, font_size);
            
//Reference info Draw
            memset(print_field, 0, 50);
            sprintf(print_field, "Ref1 %d", Hand_id.ref_1 + 1);
            Letter_Draw_Normal(fontDataWidth_Ext, fontData_Ext, fieldWidth, field, Card_DesignWidth * 4, Card_Height + font_size + 2, print_field, font_size);
            memset(print_field, 0, 50);
            sprintf(print_field, "Ref2 %d", Hand_id.ref_2 + 1);
            Letter_Draw_Normal(fontDataWidth_Ext, fontData_Ext, fieldWidth, field, Card_DesignWidth * 4, Card_Height + font_size*2 + 2, print_field, font_size);
            memset(print_field, 0, 50);
            sprintf(print_field, "Ref3 %d", Hand_id.ref_3 + 1);
            Letter_Draw_Normal(fontDataWidth_Ext, fontData_Ext, fieldWidth, field, Card_DesignWidth * 4, Card_Height + font_size*3 + 2, print_field, font_size);
            
//Info Display
//            Odds_Prob_Draw(fontDataWidth_Ext, fontData_Ext, fieldWidth, field, bet, Card_DesignWidth * HAND, 0, font_size);
            Odds_Prob_Draw(fontDataWidth_Ext, fontData_Ext, fieldWidth, field, bet, 0, Card_Height + font_size*3 + 2, font_size);
            Mny_Bt_Draw(fontDataWidth_Ext, fontData_Ext, fieldWidth, field, money, bet, bet * odds[Hand_id.hand], &Error, 0, Card_Height + font_size*2 + 2, font_size);
            system("cls");
//            deal(deck);
            printArray3(fieldHeight, fieldWidth, field);
//        if(Hand_id != 0 && Hand_id == 2){
        
//            int k = 0;
//            _getch();
//            hit_counter++;
//        }
        counter++;
        _getch();
        printf("*");
        Get_Award(&money, bet, Hand_id.hand);
        shuffleDeck(deck);
        Draw_Start = 0;
        Draw_Start += HAND;
        Cpy_Hnds(deck, Hands, posHand, HAND);
        getchar();
    }
    
	return 0;
}

void fillDeck(Card * wDeck, char * wFace[], char * wSuit[])
{
    for(int i = 0; i < CARD; i++)
    {
        wDeck[i].face = wFace[i % FACE];
        wDeck[i].suit = wSuit[i / FACE];
        wDeck[i].num = i;
    }
}

void shuffleDeck(Card * wDeck)
{
    for(int i = 0; i < CARD; i++)
    {
        size_t j = rand() % CARD;
        Card temp = wDeck[i];
        wDeck[i] = wDeck[j];
        wDeck[j] = temp;
    }
}

void deal(Card * wDeck)
{
    for(int i = 0; i < CARD; i++)
    {
        printf("%5s of %-8s (%d)%s", wDeck[i].face, wDeck[i].suit, wDeck[i].num, (i + 1) % 4 ? " " : "\n");
    }
}

int range(int num)
{
    if(0 > num)
        return 0;
    return num;
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

void nTable_Draw(int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int DrawFromX, int DrawFromY, Card *Hand, int size, int letter_size)
{

    char string_field[1600];
    for(int i = 0; i < letter_size; i++) // 5 is letter hight
    {
        memset(string_field, 0, 1600);
        
        for(int j = 0; j < size; j++)
            strcat(string_field, fontData[Hand[j].num * letter_size + i]);
        strcpy(&field[DrawFromY + i][DrawFromX], string_field);
    }
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
    char string_field[500];
    for(int i = 0; string[i] != 0; i++)
        if(string[i] < 48 && string[i] != 32)
            string[i] = 32;

    for(int i = 0; i < letter_size; i++) // 5 is letter hight
    {
        memset(string_field, 0, 500);
        
        for(int j = 0; string[j] != 0; j++)
            strcat(string_field, fontData[(string[j] == 32 ? 75 : (string[j] - 48)) * letter_size + i]);
//        strcpy(&field[DrawFromY + i][DrawFromX], string_field);
        memcpy(&field[DrawFromY + i][DrawFromX], string_field, strlen(string_field));
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
                field[i][j] = '\n';
        }
    field[fieldHeight - 1][fieldWidth - 1] = 0;
    printf("%s", field);
}

void Chng_Crds(Card * wDeck, Card *Hand, int *Draw_Start, bool *Chng_Pos, int size)
{
    for(int i = 0; i < size; i++)
    {
        if(Chng_Pos[i] == false)
            continue;
        Hand[i] = wDeck[*Draw_Start];
        (*Draw_Start)++;
    }
}

void Cpy_Hnds(Card *wDeck, Card *Hands, int *pos, int size)
{
    for(int i = 0; i < size; i++)
    {
        Hands[i] = wDeck[pos[i]];
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
            two_pair = HandIni(7,  two > i ? two : i, two < i ? two : i, Ext_Array(Card_Strenght, two, i, -1));
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
            for(int j = 0; j < size; j++){
                if(Hands[j].num / 13 != i && face[Hands[j].num % 13] == 1)
                    for(int k = 0; k < size; k++)
                        if(Card_Strenght[k] == Hands[j].num % 13){
                            Card_Strenght[k] = -1;
                            break;
                        }
                if(Hands[j].num / 13 != i && face[Hands[j].num % 13] > 1)
                    face[Hands[j].num % 13]--;
            }
                        
            return HandIni(4, Ext_Array(Card_Strenght, -1, -1, -1), Ext_Array(Card_Strenght, -2, -1, -1), Ext_Array(Card_Strenght, -2, -2, -1));
            //                                         finding biggest    finding second biggest by using single skip       finding third biggest using double skip
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

        
    return HandIni(9, Ext_Array(Card_Strenght, -1, -1, -1), Ext_Array(Card_Strenght, -2, -1, -1), Ext_Array(Card_Strenght, -2, -2, -1));
}

int Control(bool *Chng_Pos, int size)
{
    switch(_getch())
    {
        case '1': Chng_Pos[0] = !(Chng_Pos[0]); return 0;
        case '2': Chng_Pos[1] = !(Chng_Pos[1]); return 0;
        case '3': Chng_Pos[2] = !(Chng_Pos[2]); return 0;
        case '4': Chng_Pos[3] = !(Chng_Pos[3]); return 0;
        case '5': Chng_Pos[4] = !(Chng_Pos[4]); return 0;
        case 10: return 1;
        default : return 1;
    }
}

int Betting(int *bet, int *money, int min_bet)
{
    switch(_getch())
    {
        case 'w': (*bet) = (*bet) + 100; return 0;
        case 's': (*bet) = range((*bet) - 100); return 0;
        case '\n': if((*bet) < min_bet || (*bet) > *money)
                    {
                        if((*bet) < min_bet)
                            return -1;
                        return -2;
                    }
                    Pay_Bet(money, *bet);
                    return 1;
        default : if((*bet) < min_bet || (*bet) > *money)
                    {
                        if((*bet) < min_bet)
                            return -1;
                        return -2;
                    }
                    Pay_Bet(money, *bet);
                    return 1;
    }
}

void S_C_Draw(int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], bool *Chng_Pos, int size, int DrawFromX, int DrawFromY, int letter_size, int Card_DesignWidth)
{
    char print_string[300];
    memset(print_string, 0, 300);
    
    for(int i = 0; i < size; i++)
    {
        if(Chng_Pos[i] == true)
        {
            for(int j = 0; j < (Card_DesignWidth - 47) / 4; j++)
                strcat(print_string, " ");
            strcat(print_string, "Change"); // 47 ~53~
            for(int j = 0; j < (Card_DesignWidth - 47) / 4; j++)
                strcat(print_string, " ");
        }
        else{
            for(int j = 0; j < (Card_DesignWidth - 30) / 4; j++)
                strcat(print_string, " ");
            strcat(print_string, "Stay"); // 30 42 ~58~
            for(int j = 0; j < (Card_DesignWidth - 30) / 4; j++)
                strcat(print_string, " ");
        }
    }
    Letter_Draw_Normal(fontDataWidth, fontData, fieldWidth, field, DrawFromX, DrawFromY, print_string, letter_size);
}

void Odds_Prob_Draw(int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int bet, int DrawFromX, int DrawFromY, int letter_size)
{
    char print_field[300];

    for(int i = 1; i < 10; i++)
    {
        memset(print_field, 0, 300);
        sprintf(print_field, "%-18s%d", Hands_Rank_Ext[i], odds[i] * bet);
        Letter_Draw_Normal(fontDataWidth, fontData, fieldWidth, field, DrawFromX, DrawFromY + letter_size * i, print_field, letter_size);
    }
}

void Pay_Bet(int *money, int bet)
{
    *money = bet < *money ? *money - bet : -1; 
}

void Get_Award(int *money, int bet, int Hand_id)
{
    *money = *money + bet * odds[Hand_id];
}

void Mny_Bt_Draw(int fontDataWidth, char (*fontData)[fontDataWidth], int fieldWidth, char (*field)[fieldWidth], int money, int bet, int earned, int *Error, int DrawFromX, int DrawFromY, int letter_size)
{
    char print_field[300];
    memset(print_field, 0, 300);
    if(earned == -1)
        sprintf(print_field, "Money  %-10d Bet  %-10d", money, bet);
    else
        sprintf(print_field, "Money  %-10d Bet  %-10d Award %-10d", money, bet, earned);
    if(*Error == -1)
        strcat(print_field, "Minimum bet error");
    if(*Error == -2)
        strcat(print_field, "Over Badget");
    Letter_Draw_Normal(fontDataWidth, fontData, fieldWidth, field, DrawFromX, DrawFromY, print_field, letter_size);
    *Error = 0;
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

//int Ext_Array(int *From_arr, int ref_1, int ref_2)
//{
//    int size = 3;
//    
//    if(ref_2 != -1)
//        for(int i = 0; i < size; i++)
//            if(!(From_arr[i] == ref_1 || From_arr[i] == ref_2))
//                return i;
//    else
//        for(int i = 0; i < size; i++)
//            if(From_arr[i] != ref_1)
//                return i;
//}

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