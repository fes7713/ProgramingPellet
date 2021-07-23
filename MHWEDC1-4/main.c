#include "function.h"
#include "Variable.h"
#include <time.h>
#define CBSLOT 0
#define HISTORY 30

int main()
{
    int weaponDamage = 627 * 1.05;
    char weaponType[13];
    int baseAffinity = 0;
    int custom = 0;
    int nSeriesSkill = 0;;
    int nRequired = 0;
    int nSeries = 0;
    int nSlot1Original;
    int nSlot2Original;
    int nSlot3Original;
    

    printf("Auto/Custom setting(0/1/2) : ");
    scanf("%d", &custom);    
    if(custom == 1 || custom == 2)
    {
        printf("Weapon Damage, Weapon Affinity :");
        scanf("%d%d", &weaponDamage, &baseAffinity);
        printf("Series Skill (Kaisar: 0, Drachen: 1, Xeno: 2) :");
        scanf("%d", &nSeries);
        if(custom == 2)
        {
            printf("\nInitialize No of each Slot\n\nSlot 1 :");
            scanf("%d", &nSlot1Original);
            printf("Slot 2 :");
            scanf("%d", &nSlot2Original);
            printf("Slot 3 :");
            scanf("%d", &nSlot3Original);
        }
        puts("Enter Weapon type :");
        puts("Great Sword, Long Sword, Sword&Shield, Dual Blades, Hammer, Hunter Horn, Lance,\nGunlance, Switch Axe, Charge Blade, Insect Glaive, Light Bowgun, Heavy Bowgun, Bow");
        int i = 0;
        int c;
        getchar();
        while((i < 19) && ((c = getchar()) != '\n')){
            weaponType[i++] = c;
        }
        weaponType[i] = '\0';
        puts("");
    }
    printf("Processing.....");
    puts("...");
    puts("");
    
    int nSlot1 = nSlot1Original;
    int nSlot2 = nSlot2Original;
    int nSlot3 = nSlot3Original;
    char * typeInput = &weaponType;
    float weaponDamageMultiplier = Dictionary(typeInput, &weaponTypeData, damageMultiplier, 14, 13);
    float baseWeaponDamage = weaponDamage / weaponDamageMultiplier;
    float CriticalBoost = 0.25;
    
    int SkillLevel[LEVELROWS][LEVELCOLS] = {{2, 5}, {2, 0, 3, 1, 1}};
    int SkillLevelMax[LEVELROWS][LEVELCOLS] = {{7, 7}, {3, 5, 3, 3, 3}};

    ConstInitializer2Ptr(SkillLevelResultHistory, -1, LEVELROWS, LEVELCOLS);
    ConstInitializer1Ptr(ExpectationHistory, -1, HISTORY);
    ConstInitializer3Ptr(RankingHistory, -1, HISTORY, LEVELROWS + 1, LEVELCOLS);
    clock_t start,end;
    start = clock();
    puts("0%-------------25%-------------50%-------------75%-------------100%\n");
    for(int a = 0; a <= 16; a++)
    {
        printf("####");
        for(int b = 0; b <= 11; b++)
        {
            for(int c = 0; c <= 12; c++)
            {
                for(int d = 0; d <= 12; d++)
                {
                    for(int e = 0; e <= 13; e++)
                    {
                        for(int f = 0; f <= 6; f++)
                        {
                            ConstInitializer2Ptr(SkillLevel, 0, LEVELROWS, LEVELCOLS);
                            for(int g = 0; g < 4; g += 2)
                            {
                                SkillLevel[HelmData[a][g] > 1][HelmData[a][g] > 1 ? HelmData[a][g] - 2 : HelmData[a][g]] += HelmData[a][g] < 7 ? HelmData[a][g + 1] : 0;
                                SkillLevel[ChstData[b][g] > 1][ChstData[b][g] > 1 ? ChstData[b][g] - 2 : ChstData[b][g]] += ChstData[b][g] < 7 ? ChstData[b][g + 1] : 0;
                                SkillLevel[ArmData[c][g] > 1][ArmData[c][g] > 1 ? ArmData[c][g] - 2 : ArmData[c][g]] += ArmData[c][g] < 7 ? ArmData[c][g + 1] : 0;
                                SkillLevel[WstData[d][g] > 1][WstData[d][g] > 1 ? WstData[d][g] - 2 : WstData[d][g]] += WstData[d][g] < 7 ? WstData[d][g + 1] : 0;
                                SkillLevel[LegData[e][g] > 1][LegData[e][g] > 1 ? LegData[e][g] - 2 : LegData[e][g]] += LegData[e][g] < 7 ? LegData[e][g + 1] : 0;
                                SkillLevel[chrmData[f][g] > 1][chrmData[f][g] > 1 ? chrmData[f][g] - 2 : chrmData[f][g]] += chrmData[f][g] < 7 ? chrmData[f][g + 1] : 0;
                            }
                            
                            if(custom == 2)
                            {
                                switch(nSeries)
                                {
                                    case 0:
                                        nSeriesSkill = findNumArray(MastersTouchKaiser[0], a, 3) + findNumArray(MastersTouchKaiser[1], b, 3) + findNumArray(MastersTouchKaiser[2], c, 3) + findNumArray(MastersTouchKaiser[3], d, 3) + findNumArray(MastersTouchKaiser[4], e, 3);
                                        nRequired = 3;
                                        break;
                                    case 1:
                                        nSeriesSkill = ifSame(0, a) + ifSame(0, b) + ifSame(0, c) + ifSame(0, d) + ifSame(0, e);
                                        nRequired = 4;
                                        break;
                                    case 2:
                                        nSeriesSkill = findNumArray(RazorSharpSpareShot[0], a, 2) + findNumArray(RazorSharpSpareShot[1], b, 2) + findNumArray(RazorSharpSpareShot[2], c, 2) + findNumArray(RazorSharpSpareShot[3], d, 2) + findNumArray(RazorSharpSpareShot[4], e, 2);
                                        nRequired = 3;
                                        break;
                                    default:
                                        printf("Error");
                                        continue;
                                }
                                if(nSeriesSkill < nRequired)
                                {
                                    continue;
                                }
                            }

                            nSlot1 = nSlot1Original;
                            nSlot2 = nSlot2Original;
                            nSlot3 = nSlot3Original;
                            
                            nSlot1 = nSlot1 + HelmData[a][6] + ChstData[b][6] + ArmData[c][6] + WstData[d][6] + LegData[e][6];
                            nSlot2 = nSlot2 + HelmData[a][5] + ChstData[b][5] + ArmData[c][5] + WstData[d][5] + LegData[e][5];
                            nSlot3 = nSlot3 + HelmData[a][4] + ChstData[b][4] + ArmData[c][4] + WstData[d][4] + LegData[e][4];
//                            if(nSlot3 < 0)
//                            {
//                                continue;
//                            }
                            nSlot2 += nSlot3;

    for(int cb = 0; cb <= 3; cb++)
    {
        //initializer2Ptr(SkillLevelResult, SkillLevel, LEVELROWS, LEVELCOLS);
        nSlot2 -= cb;
        for(int i = 0; i <= nSlot2; i++)
        {
        
            for(int k = 0; k <= Positive(nSlot2 - i); k++)
            {
                for(int p = 0; p <= Positive(nSlot2 - i - k); p++)
                {
                    for(int q = 0; q <= Positive(nSlot2 - i - k - p); q++)
                    {
                        int nSizeLoopIterration = nSlot1 + nSlot2 - i - k - p - q;
                        for(int j = 0; j < nSizeLoopIterration; j++)
                        {
                            counter++;
                            
                            int LevelAdd[LEVELROWS][LEVELCOLS] = {{j, nSizeLoopIterration - j}, {i, k, p, q, cb}};
                            initializer2Ptr(SkillLevelResult, SkillLevel, LEVELROWS, LEVELCOLS);

                            AddArray(SkillLevelResult, LevelAdd, LEVELROWS, LEVELCOLS);
                                
                            nSlot1Remain = maxLimit1Ptr(SkillLevelResult[0], SkillLevelMax[0], LEVELCOLS);
                            nSlot2Remain = maxLimit2Ptr(SkillLevelResult, SkillLevelMax, LEVELROWS, LEVELCOLS);
                            
                            CriticalBoost = CriticalBoostList[SkillLevelResult[1][4]];
                            
                            if(nSlot2Remain > 0)
                            {
                                if(!(CompareArray2(SkillLevelResult, SkillLevelMax, LEVELROWS, LEVELCOLS)))
                                {
                                    counter1++;
                                    //printf("Processing %d.....REJECTED\n", counter / 100 * 100);
                                    continue;
                                }
                            }
                            
                            if(nSlot1Remain > 0)
                            {
                                if(!(CompareArray(SkillLevelResult[0], SkillLevelMax[0], LEVELCOLS)))
                                {
                                    counter2++;
                                    //printf("Processing %d.....REJECTED\n", counter / 100 * 100);
                                    continue;
                                }
                            }
                            
                            if(CompareArray2(SkillLevelResultHistory, SkillLevelResult, LEVELROWS, LEVELCOLS))
                            {
                                if(nSlot1Remain == nSlot1RemainHistory && nSlot2Remain == nSlot2RemainHistory)
                                {
                                    counter3++;
                                    //printf("Processing %d.....REJECTED\n", counter / 100 * 100);
                                    continue;
                                }
                            }
                            
                            
                            AttackUp = sumDataDictionary24(LEVELROWS, LEVELCOLS, SkillLevelResult, 2, LEVELSIZE, DataList01, 0);
                            AffinityUp = sumDataDictionary24(LEVELROWS, LEVELCOLS, SkillLevelResult, 2, LEVELSIZE, DataList01, 1);
                            Expectation = (baseWeaponDamage + AttackUp) * ((1 + CriticalBoost * (baseAffinity + Limit100(AffinityUp)) / (float)100));
                            
                            RankingHistoryInput[0][0] = AttackUp;
                            RankingHistoryInput[0][1] = AffinityUp;
                            RankingHistoryInput[0][2] = nSlot2Remain;
                            RankingHistoryInput[0][3] = nSlot1Remain;
                            
                            RankingHistoryInput[3][0] = a;
                            RankingHistoryInput[3][1] = b;
                            RankingHistoryInput[3][2] = c;
                            RankingHistoryInput[3][3] = d;
                            RankingHistoryInput[3][4] = e;
                            RankingHistoryInput[3][5] = f;
                            
                            initializer2Ptr(&RankingHistoryInput[1][0], SkillLevelResult, LEVELROWS - 1, LEVELCOLS);
                            RankingWithHistory13(HISTORY, LEVELROWS, LEVELCOLS, Expectation, RankingHistoryInput, ExpectationHistory, RankingHistory);
                            
                            nSlot1RemainHistory = nSlot1Remain;
                            nSlot2RemainHistory = nSlot2Remain;
                            initializer2Ptr(SkillLevelResultHistory, SkillLevelResult, LEVELROWS, LEVELCOLS);
                            speed++;
                        }
                    }
                }
            }
        }
    }
                        }
                    }
                }
            }
        }
    }
    puts("\n");
    end = clock();
    printf("Process Completed....  Run Time :%.2fseconds \n\nPress Enter to print result",(double)(end-start)/CLOCKS_PER_SEC);
    getchar();
    for(int i = HISTORY - 1; i >= 0; i--)
    {
        if(ExpectationHistory[i] == -1)
        {
            break;
        }
        printf("Ranking No.%d\nExpectation is %.2f, AttackUp is %d, AffinityUp is %d, Remain nSlot2 is %d, nSlot1 is %d\n", HISTORY - i, ExpectationHistory[i] * weaponDamageMultiplier, RankingHistory[i][0][0], RankingHistory[i][0][1], RankingHistory[i][0][2], RankingHistory[i][0][3]);
        printArray2(&RankingHistory[i][1][0], LEVELROWS - 1, LEVELCOLS);
        set2DictionaryPrintFormat(&RankingHistory[i][3][0], ProtectorNames, ProtectorTypes, 6, 17, 20);
        puts("");
    }
    printf("Try :%d, Excuted :%d\n, reject 1 [%d], reject 2[%d], reject 3 [%d]\n", counter, speed, counter1, counter2, counter3);
    
    return 0;
}

