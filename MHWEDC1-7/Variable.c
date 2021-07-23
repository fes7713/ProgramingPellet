#include <stdio.h>
#define LEVELROWS 3 //slot
#define LEVELCOLS 6 //number of skill  
#define LEVELSIZE 7
#define HISTORY 30
char weaponTypeData[][13] = {"Great Sword", "Long Sword","Sword&Shield", "Dual Blades", "Hammer", "Hunter Horn", "Lance", "Gunlance", 
                                "Switch Axe", "Charge Blade", "Insect Glaive", "Light Bowgun", "Heavy Bowgun", "Bow"};
                    
float damageMultiplier[] = {4.8, 3.3, 1.4, 1.4, 5.2, 4.2, 2.3, 2.3, 3.5, 3.6, 3.1, 1.3, 1.5, 1.2};

float CriticalBoostList[4] = {0.25, 0.30, 0.35, 0.40};


float Expectation;
int SkillLevelResult[LEVELROWS][LEVELCOLS];
int AttackUp;
int AffinityUp;
int nSlot1Remain;
int nSlot2Remain;
int nSlot1RemainHistory = -1;
int nSlot2RemainHistory = -1;
int SkillLevelResultHistory[LEVELROWS][LEVELCOLS];
float ExpectationHistory[HISTORY];
int RankingHistory[HISTORY][LEVELROWS + 1][LEVELCOLS];
int RankingHistoryInput[LEVELROWS + 1][LEVELCOLS];

int counter = 0;
int speed = 0;  
int counter1 = 0;
int counter2 = 0;
int counter3 = 0;
    
int DataList01[LEVELROWS][LEVELCOLS][2][LEVELSIZE] = {{{{3, 6, 9, 12, 15, 18, 21},{0, 0, 0, 5, 5, 5, 5}},
                                                        {{0},{5, 10, 15, 20, 25, 30, 40}}}, 
                                                        
                                                        {{{5, 10, 20}},
                                                        {{4, 8, 12, 16, 20},{5, 5, 7, 7, 10}}, 
                                                        {{0},{10, 20, 30}},
                                                        {{0},{15, 30, 50}}}};
                                                        
//                                                        {{{{AttackBoost}},
//                                                        {{CriticalEye}}},
//                                                        
//                                                        {{{PeakPerformance}}, 
//                                                        {{Agitator}},
//                                                        {{MaximumMight}},
//                                                        {{WeaknessExploit}}}}



char ProtectorNames[][17][20] = {{"0  Drachen a", "1  Dante a", "2  AzureSTarloard a", "3  Empress y", "4  Xeno y", "5  Zoara y", "6  Nergigante y", "7  Kaiser y", "8  GalaSuit a", "9  Empress b", 
"10 Taroth b", "11 Vengis b", "12 Doragonking a", "13 Guild b", "14 Kaiser b", "15 Nergigante b", "16 Taroth y"}, 
{"0  Drachen a", "1  Dante a", "2  Taroth y", "3  Xeno y", "4  Nergigante y", "5  Kaiser y", "6  Kirin y", "7  Hazaky y", "8  Empress b", "9  Taroth b", 
"10 Uragaan a", "11 Rathalos b"},
{"0  Drachen a", "1  Empress y", "2  Xeno y", "3  Nergigante y", "4  Kaiser y", "5  Kirin y", "6  GalaSuit a","7  Taroth b", "8  Vangis b", "9  Xeno a", 
"10 Kaiser b", "11 Kaiser a", "12 Nergigante b"},
{"0  Drachen a", "1  Dante a", "2  Taroth y", "3  Empress y", "4  Xeno y", "5  Zoara y", "6  Nergigante y", "7  Kaiser y", "8  Taroth b", "9  Vangis b", 
"10 Hazak b", "11 Nergigante b", "12 Uragaan b"},
{"0  Drachen a", "1  Dante a", "2  AzureSTarloard a", "3  Taroth y", "4  Empress y", "5  Xeno y", "6  Zoara y", "7  Nergigante y", "8  Kaiser y", "9  Hazaky y", 
"10 Taroth b", "11 Kirin b", "12 Kaiser b", "13 Nergigante a"},
{"0  Attack", "1  Critical Eyes", "2  Peak Performance", "3  Agitator", "4  Maximum Might", "5  Weakness Exploit", "6  Critical Boost"}};

char ProtectorTypes[][20] = {"Hemet  :", "Chest  :", "Arm    :", "Waist  :", "Leg    :", "Charm  :"};

//0 Drachen a,  1 Dante a, 2 AzureSTarloard a, 3 Empress y, 4 Xeno y, 
//5 Zoara y, 6 Nergigante y, 7 Kaiser y, 8 GalaSuit a, 9 Empress b, 
//10 Taroth b, 11 Vengis b, 12 Doragonking a, 13 Guild b, 14 Kaiser b, 
//15 Nergigante b, , 16 Taroth y, 
int HelmData[][7] = {{6, 1, 0, 0, 1, 0, 1}, {5, 1, 1, 1, 0, 0, 1}, {3, 1, 0, 0, 1, 0, 0}, {2, 1, 23, 2, 0, 0, 3}, {0, 0, 0, 0, 0, 1, 2}, 
{1, 2, 22, 2, 0, 1, 0}, {3, 1, 17, 1, 0, 2, 0}, {1, 2, 0, 0, 0, 2, 0}, {6, 1, 0, 0, 1, 2}, {19, 2, 0, 0, 1, 1, 0}, 
{10, 1, 3, 1, 0, 1, 1}, {8, 1, 0, 0, 1, 0, 1},{5, 2, 0, 0, 1, 0, 0}, {11, 2, 0, 0, 0, 0, 3}, {9, 1, 0, 0, 0, 1, 0},
{4, 2, 0, 0, 0, 0, 2}, {10, 0, 0, 0, 1, 0, 2}};



//0 Kushala y, 1 Kirin y, 2 Hazak y, 3 Hazak a, 4 Kushala b, 
//5 Bazel b, 6 Diablos a, 
int HelmOptionData[][7] = {{29, 2, 0, 0, 0, 1, 0}, {32, 3, 0, 0, 0, 1, 0}, {34, 1, 0, 0, 1, 0, 0}, {34, 2, 2 ,1, 0, 0, 0, 0}, {33, 2, 0, 0, 0, 0, 3},
{21, 2, 0, 0, 1, 0, 1}, {15, 2, 0, 0, 0, 0, 1}};

//0 Drachen a, 1 Dante a, 2 Taroth y, 3 Xeno y, 4 Nergigante y, 
//5 Kaiser y, 6 Kirin y, 7 Hazaky y, 8 Empress b, 9 Taroth b, 
//10 Uragaan a, 11 Rathalos b.
int ChstData[][7] = {{1, 2, 6, 1, 1, 0, 0}, {18, 1, 1, 1, 1, 0, 0}, {29, 2, 3, 1, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 2}, {4, 1, 0, 0, 1, 1, 1}, 
{9, 2, 5, 1, 0, 1, 0}, {10, 2, 0, 0, 0, 0, 2}, {2, 1, 0, 0, 1, 0, 0}, {2, 2, 0, 0, 0, 0, 3}, {42, 2, 6, 1, 1, 0, 1}, 
{8, 2, 0, 0, 0, 0, 1}, {5, 2, 0, 0, 0, 0, 1}};

//0 Empress y, 1 Zoara y, 2 Kushala y, 8 GalaSuit a, 3  Vangis a, 4 Vangis b, 
//5 Kushala b, 6 Kaiser b, 7 Nergigante b, 8 Damascus b, 9 Basel b,
int ChstOptionData[][7] = {{21, 2, 24, 1, 1, 0, 0}, {20, 2, 0, 0, 0, 0, 3}, {33, 3, 19, 1, 0, 1, 0}, {12, 1, 0, 0, 0, 1, 2}, {25, 1, 29, 1, 0, 1, 0}, {25, 1, 0, 0, 1, 0, 0},
{29, 2, 0, 0, 1, 0}, {28, 2, 0, 0, 0, 0, 2}, {17, 2, 0, 0, 0, 1, 1}, {15, 2, 0, 0, 0, 0, 3}, {43, 2, 0, 0, 0, 0, 2}};

//0 Drachen a, 1 Empress y, 2 Xeno y, 3 Nergigante y, 4 Kaiser y, 
//5 Kirin y, 6 GalaSuit a,7 Taroth b, 8 Vangis b, 9 Xeno a, 
//10 Kaiser b, 11 Kaiser a, 12 Nergigante b
int ArmData[][7] = {{1, 2, 0, 1, 0, 2, 0}, {3, 2, 19, 1, 1, 0, 1}, {28, 1, 0, 0, 0, 2, 1}, {8, 1, 0, 1, 0, 1, 2}, {1, 3, 0, 0, 1, 0, 0},
 {10, 1, 0, 0, 0, 2, 0}, {4, 1, 0, 0, 0, 1, 2}, {10, 1, 0, 0, 1, 0, 1}, {9, 2, 0, 0, 0, 1, 0}, {6, 1, 0, 0, 0, 0, 1}, 
 {5, 1, 0, 0, 1, 0, 0}, {5, 2, 0, 0, 0, 0, 1}, {3, 2, 0, 0, 0, 0, 1}};

//0 Dante a, 1 Taroth y, 2 Zoara y, 3 Kushala y, 4 Hazaky y, 
//5 Empress b, 6 Kirin b, 7 Hazak b, 8 Kushala b, 9 Bazel b
int ArmOptionData[][7] = {{28, 1, 18, 1, 1, 0, 0}, {29, 2, 16, 1, 0, 0, 1}, {21, 2, 0, 0, 1, 0, 1}, {15, 2, 0, 0, 0, 0, 3}, {34, 3, 0, 0, 1, 1, 0}, 
{23, 2, 0, 0, 1, 1, 0}, {32, 2, 0, 0, 0, 0, 2}, {2, 1, 0, 0, 0, 0, 3}, {18, 2, 0, 0, 1, 0, 0}, {12, 2, 0, 0, 1, 0, 0}};

//0 Drachen a, 1 Dante a, 2 Taroth y, 3 Empress y, 4 Xeno y, 
//5 Zoara y, 6 Nergigante y, 7 Kaiser y, 8 Taroth b, 9 Vangis b, 
//10 Hazak b, 11 Nergigante b, 12 Uragaan b.
int WstData[][7] = {{1, 2, 0, 0, 1, 0, 0}, {18, 1, 9, 1, 1, 0, 0}, {6, 1, 5, 1, 1, 0, 0}, {18, 2, 7, 2, 1, 0, 0}, {6, 1, 0, 0, 1, 0, 1},
{1, 1, 27, 2, 1, 1, 0}, {3, 1, 4, 1, 1, 0, 1}, {9, 3, 0, 0, 0, 0, 2}, {10, 1, 29, 1, 1, 0, 1}, {9, 1, 0, 0, 1, 0, 1}, 
{2, 1, 0, 0, 0, 0, 2}, {0, 2, 0, 0, 0, 1, 0}, {8, 1, 0, 0, 0, 1, 1}};

//0 Kushala y, 1 Hazaky y, 2 Empress b, 3 Kushala a, 4 Kushala b, 
//5 Kaiser b, 6 Empress a, 7 DeathStence b, 8 Damascus b, 9 Bazel b, 
int WstOptionData[][7] = {{29, 2, 0, 0, 0, 0, 2}, {34, 1, 0, 0, 0, 1, 2}, {24, 2, 0, 0, 0, 2, 0}, {33, 2, 19, 1, 0, 0, 0}, {33, 2, 0, 0, 0, 0, 2}, 
{35, 2, 0, 0, 0, 1, 0}, {24, 2, 35, 1, 0, 1, 1}, {34, 2, 0, 0, 0, 0, 2}, {15, 1, 0, 0, 0, 0, 3}, {21, 2, 0, 0, 1, 0, 0}};

//0 Drachen a, 1 Dante a, 2 AzureSTarloard a, 3 Taroth y, 4 Empress y, 
//5 Xeno y, 6 Zoara y, 7 Nergigante y, 8 Kaiser y, 9 Hazaky y, 
//10 Taroth b, 11 Kirin b, 12 Kaiser b, 13 Nergigante a,
int LegData[][7] = {{0, 2, 6, 1, 0, 1, 0}, {5, 2, 0, 0, 0, 0, 2}, {6, 1, 0, 0, 1, 0, 0}, {3, 2, 41, 1, 1, 0, 1}, {21, 2, 3, 1, 1, 0, 0},
{6, 1, 0, 0, 0, 1, 2}, {1, 1, 35, 2, 1, 1, 0}, {0, 3, 0, 0, 0, 2, 0}, {1, 2, 0, 0, 1, 0, 1}, {2, 1, 0, 0, 1, 0, 1}, 
{2, 1, 23, 2, 0, 1, 1}, {10, 2, 0, 0, 0, 0, 2}, {9, 2, 0, 0, 0, 0, 1}, {4, 1, 3, 1, 0, 0, 1}};

//0 Kushala y, 1 Kirin y, 2 GalaSuit a, 3 Empress b, 4 Empress a, 
//5 Vangis b, 6 Kushala b, 7 Bazel a
int LegOptionData[][7] = {{18, 2, 0, 0, 1, 0, 0}, {32, 2, 0, 0, 1, 0, 0}, {11, 1, 0, 0, 1, 0, 2}, {7, 2, 0, 0, 0, 2, 0}, {7, 2, 23, 2, 0, 1, 1}, 
{25, 2, 0, 0, 0, 0, 2}, {19, 2, 0, 0, 1, 0, 0}, {27, 2, 12, 1, 0, 0, 1}};

int chrmData[][7] = {{0, 3, 0, 0, 0, 0, 0}, {1, 3, 0, 0, 0, 0, 0}, {2, 2, 0, 0, 0, 0, 0}, {3, 2, 0, 0, 0, 0, 0}, {4, 2, 0, 0, 0, 0, 0}, 
{5, 2, 0, 0, 0, 0, 0}, {6, 1, 0, 0, 0, 0, 0}};

int chrmOptionData[][7] = {{7, 3, 0, 0, 0, 0, 0}, {8, 2, 0, 0, 0, 0, 0}, {9, 2, 0, 0, 0, 0, 0},
{10, 2, 0, 0, 0, 0, 0}, {11, 3, 0, 0, 0, 0, 0}, {12, 2, 0, 0, 0, 0, 0}, {13, 0}, {14, 0}, 
{15, 2, 0, 0, 0, 0, 0}, {16, 3, 0, 0, 0, 0, 0}, {17, 2, 0, 0, 0, 0, 0}, {18, 3, 0, 0, 0, 0, 0}, {19, 2, 0, 0, 0, 0, 0}, 
{20, 2, 0, 0, 0, 0, 0}, {21, 3, 0, 0, 0, 0, 0}, {22, 3, 0, 0, 0, 0, 0}, {23, 3, 0, 0, 0, 0, 0}, {24, 3, 0, 0, 0, 0, 0}, 
{25, 3, 0, 0, 0, 0, 0}, {26, 2, 0, 0, 0, 0, 0}, {27, 3, 0, 0, 0, 0, 0}, {28, 2, 0, 0, 0, 0, 0}, {29, 3, 0, 0, 0, 0, 0}};

int MastersTouchKaiser[5][3] = {{7, 14, -1}, {5, -1, -1}, {4, 10, 11}, {7, -1, -1}, {8, 12, -1}};
int MastersTouchDrachen[5][1] = {{0},{0}, {0}, {0}, {0}};
int RazorSharpSpareShot[5][2] = {{4, -1}, {3, -1}, {2, 9}, {4, -1}, {5, -1}};