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

void printArray2(char *arr, int rows, int cols);
int range(double num, int limit);
double to_deg360_Tri(double run, double rise);
int Target_Priority(const Missile *target, const double *base_X, const double *base_Y, int pair[MAXMISSILE][HOSPERINTE], const int *j);
void Missile_Stationary(Missile * missile, const double *target_X, const double *target_Y);
//double Missile_Moving(Missile *Interceptor, Missile *Hostile);
void Missile_Moving(Missile *Interceptor, const Missile *Hostile);
double Missile_Angle_Ini(Missile *Interceptor, const Missile *Hostile);
void Hostile_Missile_Lock(const Missile *Interceptor, Missile * Hostile, int pair[MAXMISSILE][HOSPERINTE], int *p);
void record_cordinates(Missile * missile);
void Generator_Hostile(Missile *Hostile, int fieldHeight, int fieldWidth);
void Generator_Interceptor(Missile *Interceptor, Missile *Hostile, int fieldHeight, int fieldWidth);
void Grid(char *field, int fieldHeight, int fieldWidth, int Grid_Type);
void Grid_Normal(char *field, int fieldHeight, int fieldWidth);
void Grid_Simple(char *field, int fieldHeight, int fieldWidth);
void Grid_Advanced(char *field, int fieldHeight, int fieldWidth);
void Missile_Manual(Missile *Interceptor);
void Missile_Auto(Missile *Interceptor);
void Missile_Reassign(Missile *Interceptor, Missile *Hostile, int pair[MAXMISSILE][HOSPERINTE]);
int far_Missile(Missile *missile, int pair[MAXMISSILE][HOSPERINTE], int num_tag);
void Missile_Manual_Launch(Missile *Interceptor, Missile *Hostile, int *Manual_Launch, int (*pair)[HOSPERINTE], int fieldHeight, int fieldWidth, int *interval, int *fire);

extern char numbers[6];
extern char lockOn[5][7];
extern char lockOn01[5][7];
extern char Laser[5][7];
extern char ImpactPoint[3][5];