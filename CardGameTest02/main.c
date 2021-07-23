#include <stdio.h>
#include <math.h>
#define CARD 52
#define FACE 13
#define SUIT 4
#define HAND 2
#define TBL 5
#define TBLHD 7
#define PLAYER 6

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
    int Ready_bet;
    char name[20];
    float prob_win;
} Player;

typedef struct{
    Player players[PLAYER];
    Card TB_Hands[TBL];
    int status[PLAYER];
    int call;
    int raise;
    int stage;
    int nCall;
    int pot;
    int min_bet;
    int lead;
    int nPlayer_Pos;
    int area;
    int info;
    int range_Ai;
    int shift_Ai;
    int AiIQ;
    int Click_Overlay;
    int Total_Call;
    int Round;
    int Round_Speed;
} Game;

int Ai_Actions_Expec(Game *game, float prob_win, int nPlayer)
{

    int call = game->call;
    int pot = game->pot;
    int min_bet = game->min_bet;
    int bet = floor(pot * prob_win / (1 - prob_win) / min_bet) * min_bet;
    if(bet < call){
        return 'f';
    }
    if(bet < call * 2){
        return 'c';
    }
    
    return bet * 10;
}

int main(int argc, char **argv)
{
    Game game;
    game.pot = 1000;
    game.call = 100;
    game.min_bet = 100;
    float prob_win = 0.95;
    int bet = Ai_Actions_Expec(&game, prob_win, PLAYER);
    if(bet == 'c')
        bet = game.call;
    if(bet == 'f')
        bet = -1;
    
    printf("%d\n", bet);
    printf("%f\n", (game.pot + game.call) / game.call * prob_win);
}
