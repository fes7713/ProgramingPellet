#include "function.h"
#include "Variable.h"
#include <time.h>

int main()
{
    int weaponDamage = 627;
    char weaponType[13] = "Long Sword";
    int baseAffinity = 0;
    int custom = 0;
    int nSeriesSkill = 0;;
    int nRequired = 0;
    int SeriesSelect = 0;
    
//    strncpy(Helm, ProtectorNames[0][17], NAME);
//    strncpy(Chest, ProtectorNames[1][12], NAME);
//    strncpy(Arm, ProtectorNames[2][13], NAME);
//    strncpy(Waist, ProtectorNames[3][13], NAME);
//    strncpy(Leg, ProtectorNames[4][14], NAME);
//    strncpy(Charm, ProtectorNames[5][7], NAME);

    printf("Auto/Custom setting(0/1) : ");
    scanf("%d", &custom);    
    if(custom == 1)
    {
        printf("%16s    :%15d\n%18s  :%15d\n%14s      :%15s\n%15s     :%15d\n\n%14s      :%9s  :%3d\n%30s  :%3d\n%30s  :%3d\n\n",
        "Weapon Damage(0)", weaponDamage, "Weapon Affinity(1)", baseAffinity, "Weapon Type(2)", weaponType, "Series Skill(3)", SeriesSelect, "No of Slots(4)", "Slot1", nSlot1Original, "Slot2", nSlot2Original, "Slot3", nSlot3Original);
        printf("%13s       :%12s  %4s\n%33s  %4s\n%33s  %4s\n%33s  %4s\n%33s  %4s\n%33s  %4s\n", "Equipement(5)", &ProtectorTypes[0 * NAME], Helm, &ProtectorTypes[1 * NAME], Chest, 
        &ProtectorTypes[2 * NAME], Arm, &ProtectorTypes[3 * NAME], Waist, &ProtectorTypes[4 * NAME], Leg, &ProtectorTypes[5 * NAME], Charm);
        
        printf("Choose Custom Option");
        scanf("%d", &customSelect);
        switch(customSelect)
        {
            case 0:
                printf("Weapon Damage :");
                scanf("%d", &weaponDamage);
                break;
            case 1:
                printf("Weapon Affinity :");
                scanf("%d", &baseAffinity);
                break;
            case 2:
                puts("Enter Weapon type :");
                puts("Great Sword, Long Sword, Sword&Shield, Dual Blades, Hammer, Hunter Horn, Lance,\nGunlance, Switch Axe, Charge Blade, Insect Glaive, Light Bowgun, Heavy Bowgun, Bow");
                int i = 0;
                int c;
                getchar();
                while((i < 19) && ((c = getchar()) != '\n')){
                    weaponType[i++] = c;
                }
                weaponType[i] = '\0';
                break;
            case 3:
                printf("Series Skill (Kaisar: 0, Drachen: 1, Xeno: 2) :");
                scanf("%d", &SeriesSelect);
                break;
            case 4:
                printf("Initialize No of each Slot\n\nSlot 1 :");
                scanf("%d", &nSlot1Original);
                printf("Slot 2 :");
                scanf("%d", &nSlot2Original);
                printf("Slot 3 :");
                scanf("%d", &nSlot3Original);
//            case 5:
//                printf("Equipment\nHelmet(0), Chest(1), Arm(2), Waist(3), Leg(4), Charm(5)");
//                scanf("%d", &ProtectorSelect);
//                switch(ProtectorSelect)
//                {
//                    case 0:
//                        puts(ProtectorTypes[0]);
//                        scanf("%d", a);
//                        nLimita = a;
//                        puts(ProtectorNames[0][a]);
//                        break;
//                    case 1:
//                        puts(ProtectorTypes[1]);
//                        scanf("%d", b);
//                        nLimitb = b;
//                        puts(ProtectorNames[1][b]);
//                        break;
//                    case 2:
//                        puts(ProtectorTypes[2]);
//                        scanf("%d", c);
//                        nLimitb = c;
//                        puts(ProtectorNames[2][c]);
//                        break;
//                    case 3:
//                        puts(ProtectorTypes[3]);
//                        scanf("%d", d);
//                        nLimitd = d;
//                        puts(ProtectorNames[3][d]);
//                        break;
//                    case 4:
//                        puts(ProtectorTypes[4]);
//                        scanf("%d", e);
//                        nLimite = e;
//                        puts(ProtectorNames[4][e]);
//                        break;
//                    case 5:
//                        puts(ProtectorTypes[5]);
//                        scanf("%d", f);
//                        nLimitf = f;
//                        puts(ProtectorNames[5][f]);
//                        break;
//                    default:
//                        break;
                
        }
                
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
//    memset(SkillLevelResultHistory, -1, LEVELROWS * LEVELCOLS * sizeof(int));
//    memset(ExpectationHistory, -1, HISTORY * sizeof(float));
//    memset(RankingHistory, -1, HISTORY * (LEVELROWS + 1) * LEVELCOLS * sizeof(int));
    clock_t start,end;
    start = clock();
    puts("0%---------------------25%----------------------50%----------------------75%----------------------100%\n");
    for(int a = 0; a <= 16; a++)
    {
        
        for(int b = 0; b <= 11; b++)
        {
            if(b % 2 == 0)
            {
                printf("#");
            }
            for(int c = 0; c <= 12; c++)
            {
                for(int d = 0; d <= 12; d++)
                {
                    for(int e = 0; e <= 13; e++)
                    {
                        for(int f = 0; f <= 6; f++)
                        {
                            //ConstInitializer2Ptr(SkillLevel, 0, LEVELROWS, LEVELCOLS);
                            memset(SkillLevel, 0, LEVELROWS * LEVELCOLS * sizeof(int));
                            for(int g = 0; g < 4; g += 2)
                            {
                                SkillLevel[HelmData[a][g] > 1][HelmData[a][g] > 1 ? HelmData[a][g] - 2 : HelmData[a][g]] += HelmData[a][g] < 7 ? HelmData[a][g + 1] : 0;
                                SkillLevel[ChstData[b][g] > 1][ChstData[b][g] > 1 ? ChstData[b][g] - 2 : ChstData[b][g]] += ChstData[b][g] < 7 ? ChstData[b][g + 1] : 0;
                                SkillLevel[ArmData[c][g] > 1][ArmData[c][g] > 1 ? ArmData[c][g] - 2 : ArmData[c][g]] += ArmData[c][g] < 7 ? ArmData[c][g + 1] : 0;
                                SkillLevel[WstData[d][g] > 1][WstData[d][g] > 1 ? WstData[d][g] - 2 : WstData[d][g]] += WstData[d][g] < 7 ? WstData[d][g + 1] : 0;
                                SkillLevel[LegData[e][g] > 1][LegData[e][g] > 1 ? LegData[e][g] - 2 : LegData[e][g]] += LegData[e][g] < 7 ? LegData[e][g + 1] : 0;
                                SkillLevel[chrmData[f][g] > 1][chrmData[f][g] > 1 ? chrmData[f][g] - 2 : chrmData[f][g]] += chrmData[f][g] < 7 ? chrmData[f][g + 1] : 0;
                            }
                            
                            if(custom == 1)
                            {
                                switch(SeriesSelect)
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
                                    counter4++;
                                    continue;
                                }
                            }

                            nSlot1 = nSlot1Original;
                            nSlot2 = nSlot2Original;
                            nSlot3 = nSlot3Original;
                            
                            nSlot1 = nSlot1 + HelmData[a][6] + ChstData[b][6] + ArmData[c][6] + WstData[d][6] + LegData[e][6];
                            nSlot2 = nSlot2 + HelmData[a][5] + ChstData[b][5] + ArmData[c][5] + WstData[d][5] + LegData[e][5];
                            nSlot3 = nSlot3 + HelmData[a][4] + ChstData[b][4] + ArmData[c][4] + WstData[d][4] + LegData[e][4];
//                            if(nSlot3 < 0 || (nSlot2 < 0 || nSlot1 < 0))
//                            {
//                                counter4++;
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
                            //initializer2Ptr(SkillLevelResult, SkillLevel, LEVELROWS, LEVELCOLS);
                            memcpy(SkillLevelResult, SkillLevel, LEVELROWS * LEVELCOLS * sizeof(int));

                            AddArray(SkillLevelResult, LevelAdd, LEVELROWS, LEVELCOLS);
                                
                            nSlot1Remain = maxLimit1Ptr(SkillLevelResult[0], SkillLevelMax[0], LEVELCOLS);
                            nSlot2Remain = maxLimit2Ptr(SkillLevelResult, SkillLevelMax, LEVELROWS, LEVELCOLS);
                            
                            CriticalBoost = CriticalBoostList[SkillLevelResult[1][4]];
                            
                            if(nSlot2Remain > 0)
                            {
                                if(memcmp(SkillLevelResult, SkillLevelMax, LEVELROWS * LEVELCOLS * sizeof(int)) != 0)
                                {
                                    counter1++;
                                    //printf("Processing %d.....REJECTED\n", counter / 100 * 100);
                                    continue;
                                }
                            }
                            
                            if(nSlot1Remain > 0)
                            {
                                if(memcmp(SkillLevelResult[0], SkillLevelMax[0], LEVELCOLS * sizeof(int)) != 0)
                                {
                                    counter2++;
                                    //printf("Processing %d.....REJECTED\n", counter / 100 * 100);
                                    continue;
                                }
                            }
                            
                            if(memcmp(SkillLevelResultHistory, SkillLevelResult, LEVELROWS * LEVELCOLS * sizeof(int)) == 0)
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
                            Expectation = (baseWeaponDamage + AttackUp) * ((1 + CriticalBoost * Limit100(baseAffinity + AffinityUp) / (float)100));
                            
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
                            
                            //initializer2Ptr(&RankingHistoryInput[1][0], SkillLevelResult, LEVELROWS - 1, LEVELCOLS);
                            memcpy(&RankingHistoryInput[1][0], SkillLevelResult, (LEVELROWS - 1) * LEVELCOLS * sizeof(int));
                            RankingWithHistory13(HISTORY, LEVELROWS, LEVELCOLS, Expectation, RankingHistoryInput, ExpectationHistory, RankingHistory, temp);
                            
                            nSlot1RemainHistory = nSlot1Remain;
                            nSlot2RemainHistory = nSlot2Remain;
                            //initializer2Ptr(SkillLevelResultHistory, SkillLevelResult, LEVELROWS, LEVELCOLS);
                            memcpy(SkillLevelResultHistory, SkillLevelResult, LEVELROWS * LEVELCOLS * sizeof(int));
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
    printf("Process Completed....  Run Time :%.3fseconds \n\nPress Enter to print result",(double)(end-start)/CLOCKS_PER_SEC);
    getchar();
    getchar();
    puts("");
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
    printf("Try :%d, Excuted :%d\n,reject 0 [%d], reject 1 [%d], reject 2[%d], reject 3 [%d]\n", counter, speed,counter4, counter1, counter2, counter3);
    
    return 0;
}

