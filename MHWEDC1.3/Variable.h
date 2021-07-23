#define LEVELROWS 3 //slot
#define LEVELCOLS 6 //number of skill  
#define LEVELSIZE 7
#define HISTORY 30
extern char weaponTypeData[][13];
extern float damageMultiplier[];
extern float CriticalBoostList[4];
extern float weaponDamageMultiplier;
extern float baseWeaponDamage;
extern float Expectation;
extern int SkillLevelResult[LEVELROWS][LEVELCOLS];
extern int AttackUp;
extern int AffinityUp;
extern int nSlot1Remain;
extern int nSlot2Remain;
extern int nSlot1RemainHistory;
extern int nSlot2RemainHistory;
extern int SkillLevelResultHistory[LEVELROWS][LEVELCOLS];
extern float ExpectationHistory[HISTORY];
extern int RankingHistory[HISTORY][LEVELROWS + 1][LEVELCOLS];
extern int RankingHistoryInput[LEVELROWS + 1][LEVELCOLS];
extern int DataList01[LEVELROWS][LEVELCOLS][2][LEVELSIZE];
extern int counter;
extern int speed;  
extern int counter1;
extern int counter2;
extern int counter3;
extern int HelmData[][7];
extern int HelmOptionData[][7];
extern int ChstData[][7];
extern int ChstOptionData[][7];
extern int ArmData[][7];
extern int ArmOptionData[][7];
extern int WstData[][7];
extern int WstOptionData[][7];
extern int LegData[][7];
extern int LegOptionData[][7];
extern int chrmData[][7];
extern int MastersTouchKaiser[5][3];
extern int MastersTouchDrachen[5][1];