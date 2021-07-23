#include "function.h"
#include "Variable.h"
#include <time.h>
#define CBSLOT 0
#define HISTORY 30
#define NAME 20

int main()
{
    int weaponDamage = 627;
    char weaponType[13] = "Long Sword";
    int baseAffinity = 0;
    int custom = 0;
    int nSeriesSkill = 0;;
    int nRequired = 0;
    int SeriesSelect = 0;
    int customSelect = 0;
    int nSlot1Original = 0;
    int nSlot2Original = 0;
    int nSlot3Original = 0;
    int temp[200];
    int GunnerOption = 0;
    int nGunner;
    
    strncpy(Helm, ProtectorNames[0][17], NAME);
    strncpy(Chest, ProtectorNames[1][12], NAME);
    strncpy(Arm, ProtectorNames[2][13], NAME);
    strncpy(Waist, ProtectorNames[3][13], NAME);
    strncpy(Leg, ProtectorNames[4][14], NAME);
    strncpy(Charm, ProtectorNames[5][8], NAME);
    
    printf("Auto/Custom setting(0/1) : ");
    scanf("%d", &custom);    
    if(custom == 1)
    {
        printf("\n----------------------\nCunstom Setting Menue\n----------------------\n\n");
        printf("%16s    :%15d\n%18s  :%15d\n%14s      :%15s\n%15s     :%15d\n%16s    :%15d\n\n%14s      :%9s  :%3d\n%30s  :%3d\n%30s  :%3d\n\n",
        "Weapon Damage(0)", weaponDamage, "Weapon Affinity(1)", baseAffinity, "Weapon Type(2)", weaponType, "Series Skill(3)", SeriesSelect, "Gunner Option(4)", GunnerOption, "No of Slots(5)", "Slot1", nSlot1Original, "Slot2", nSlot2Original, "Slot3", nSlot3Original);
        printf("%13s       :%12s  %4s\n%33s  %4s\n%33s  %4s\n%33s  %4s\n%33s  %4s\n%33s  %4s\n%15s%10s\n\n", "Equipement(6)", ProtectorTypes[0], Helm, ProtectorTypes[1], Chest, 
        ProtectorTypes[2], Arm, ProtectorTypes[3], Waist, ProtectorTypes[4], Leg, ProtectorTypes[5], Charm, "Setting Menu(7)", "Proceed(8)");
        while(customSelect != 8)
        {
            printf("\nChoose Custom Option : ");
            scanf("%d", &customSelect);
            switch(customSelect)
            {
                case 0:
                    printf("Weapon Damage : ");
                    scanf("%d", &weaponDamage);
                    break;
                case 1:
                    printf("Weapon Affinity : ");
                    scanf("%d", &baseAffinity);
                    break;
                case 2:
                    puts("Enter Weapon type : ");
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
                    printf("Series Skill (Kaisar: 1, Drachen: 2, Xeno: 3, Nergigante: 4, Off: 0) : ");
                    scanf("%d", &SeriesSelect);
                    break;
                case 4:
                    printf("GunnerOption (On/Off: 1/0) : ");
                    scanf("%d", &GunnerOption);
                    break;
                case 5:
                    printf("Initialize No of each Slot\n\nSlot 1 : ");
                    scanf("%d", &nSlot1Original);
                    printf("Slot 2 : ");
                    scanf("%d", &nSlot2Original);
                    printf("Slot 3 : ");
                    scanf("%d", &nSlot3Original);
                    break;
                case 6:
                    printf("Equipment :\nHelmet(0), Chest(1), Arm(2), Waist(3), Leg(4), Charm(5) : ");
                    scanf("%d", &ProtectorSelect);
                    switch(ProtectorSelect)
                    {
                        case 0:
                            printf("%s", ProtectorTypes[0]);
                            scanf("%d", &nA);
                            nLimitA = nA;
                            strncpy(Helm, ProtectorNames[0][nA], NAME);
                            puts(ProtectorNames[0][nA]);
                            break;
                        case 1:
                            printf("%s", ProtectorTypes[1]);
                            scanf("%d", &nB);
                            nLimitB = nB;
                            strncpy(Chest, ProtectorNames[1][nB], NAME);
                            puts(ProtectorNames[1][nB]);
                            break;
                        case 2:
                            printf("%s", ProtectorTypes[2]);
                            scanf("%d", &nC);
                            nLimitC = nC;
                            strncpy(Arm, ProtectorNames[2][nC], NAME);
                            puts(ProtectorNames[2][nC]);
                            break;
                        case 3:
                            printf("%s", ProtectorTypes[3]);
                            scanf("%d", &nD);
                            nLimitD = nD;
                            strncpy(Waist, ProtectorNames[3][nD], NAME);
                            puts(ProtectorNames[3][nD]);
                            break;
                        case 4:
                            printf("%s", ProtectorTypes[4]);
                            scanf("%d", &nE);
                            nLimitE = nE;
                            strncpy(Leg, ProtectorNames[4][nE], NAME);
                            printf("%s", ProtectorNames[4][nE]);
                            break;
                        case 5:
                            printf("%s", ProtectorTypes[5]);
                            scanf("%d", &nF);
                            nLimitF = nF;
                            strncpy(Charm, ProtectorNames[5][nF], NAME);
                            puts(ProtectorNames[5][nF]);
                            break;
                        default:
                            break;
                    }
                    break;
                case 7:
                    printf("\n----------------------\nCunstom Setting Menue\n----------------------\n\n");
                    printf("%16s    :%15d\n%18s  :%15d\n%14s      :%15s\n%15s     :%15d\n%16s    :%15d\n\n%14s      :%9s  :%3d\n%30s  :%3d\n%30s  :%3d\n\n",
                    "Weapon Damage(0)", weaponDamage, "Weapon Affinity(1)", baseAffinity, "Weapon Type(2)", weaponType, "Series Skill(3)", SeriesSelect, "Gunner Option(4)", GunnerOption, "No of Slots(5)", "Slot1", nSlot1Original, "Slot2", nSlot2Original, "Slot3", nSlot3Original);
                    printf("%13s       :%12s  %4s\n%33s  %4s\n%33s  %4s\n%33s  %4s\n%33s  %4s\n%33s  %4s\n%15s%10s\n\n", "Equipement(6)", ProtectorTypes[0], Helm, ProtectorTypes[1], Chest, 
                    ProtectorTypes[2], Arm, ProtectorTypes[3], Waist, ProtectorTypes[4], Leg, ProtectorTypes[5], Charm, "Setting Menu(7)", "Proceed(8)");
                    break;
                    
                puts("");
            }
        }
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
    puts("0%---------------------25%----------------------50%----------------------75%----------------------100%\n");
    for(int a = nA; a <= nLimitA; a++)
    {
        for(int b = nB; b <= nLimitB; b++)
        {
            if(b % 2 == 0)
            {
                printf("#");
            }
            for(int c = nC; c <= nLimitC; c++)
            {
                for(int d = nD; d <= nLimitD; d++)
                {
                    for(int e = nE; e <= nLimitE; e++)
                    {
                        for(int f = nF; f <= nLimitF; f++)
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
                            
                            if(SeriesSelect > 0)
                            {
                                switch(SeriesSelect)
                                {
                                    case 1:
                                        nSeriesSkill = findNumArray(MastersTouchKaiser[0], a, 3) + findNumArray(MastersTouchKaiser[1], b, 3) + findNumArray(MastersTouchKaiser[2], c, 3) + findNumArray(MastersTouchKaiser[3], d, 3) + findNumArray(MastersTouchKaiser[4], e, 3);
                                        nRequired = 3;
                                        break;
                                    case 2:
                                        nSeriesSkill = ifSame(0, a) + ifSame(0, b) + ifSame(0, c) + ifSame(0, d) + ifSame(0, e);
                                        nRequired = 4;
                                        break;
                                    case 3:
                                        nSeriesSkill = findNumArray(RazorSharpSpareShot[0], a, 2) + findNumArray(RazorSharpSpareShot[1], b, 2) + findNumArray(RazorSharpSpareShot[2], c, 2) + findNumArray(RazorSharpSpareShot[3], d, 2) + findNumArray(RazorSharpSpareShot[4], e, 2);
                                        nRequired = 3;
                                        break;
                                    case 4:
                                        nSeriesSkill = findNumArray(HastenRecovery[0], a, 2) + findNumArray(HastenRecovery[1], b, 2) + findNumArray(HastenRecovery[2], c, 2) + findNumArray(HastenRecovery[3], d, 2) + findNumArray(HastenRecovery[4], e, 2);
                                        nRequired = 3;
                                        break;
                                    default:
                                        break;
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
                            
                            if(GunnerOption)
                            {
                                nGunner = 0;
                                for(int g = 0; g < 4; g += 2)
                                {
                                    nGunner += HelmData[a][g] == 10 ? HelmData[a][g + 1] : 0;
                                    nGunner += ChstData[b][g] == 10 ? ChstData[b][g + 1] : 0;
                                    nGunner += ArmData[c][g] == 10 ? ArmData[c][g + 1] : 0;
                                    nGunner += WstData[d][g] == 10 ? WstData[d][g + 1] : 0;
                                    nGunner += LegData[e][g] == 10 ? LegData[e][g + 1] : 0;
                                    nGunner += chrmData[f][g] == 10 ? chrmData[f][g + 1] : 0;
                                }
                                if(nGunner + nSlot3 < 3)
                                {
                                    continue;
                                }
                                if(nGunner < 3)
                                {
                                    nSlot3 -= 3 - nGunner;
                                    nGunner = 3;
                                }
                                RankingHistoryInput[0][4] = nGunner;
                            }
                            if(nSlot3 < 0)
                            {
                                continue;
                            }
                            nSlot2 += nSlot3;
                            int cbtemp = nSlot2;

    for(int cb = 0; cb <= 3; cb++)
    {
        nSlot2 = cbtemp;
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
                            maxLimit2Ptr(SkillLevelResult, SkillLevelMax, LEVELROWS, LEVELCOLS);
                            
                            int LevelAdd[LEVELROWS][LEVELCOLS] = {{j, nSizeLoopIterration - j}, {i, k, p, q, cb}};
                            memcpy(SkillLevelResult, SkillLevel, LEVELROWS * LEVELCOLS * sizeof(int));

                            AddArray(SkillLevelResult, LevelAdd, LEVELROWS, LEVELCOLS);
                                
                            nSlot1Remain = maxLimit1Ptr(SkillLevelResult[0], SkillLevelMax[0], LEVELCOLS);
                            nSlot2Remain = maxLimit2Ptr(SkillLevelResult, SkillLevelMax, LEVELROWS, LEVELCOLS);
                            
                            if(nSlot2Remain > 0)
                            {
                                if(memcmp(SkillLevelResult, SkillLevelMax, LEVELROWS * LEVELCOLS * sizeof(int)) != 0)
                                {
                                    counter1++;
                                    continue;
                                }
                            }
                            
                            if(nSlot1Remain > 0)
                            {
                                if(memcmp(SkillLevelResult[0], SkillLevelMax[0], LEVELCOLS * sizeof(int)) != 0)
                                {
                                    counter2++;
                                    continue;
                                }
                            }
                            if(memcmp(SkillLevelResultHistory, SkillLevelResult, LEVELROWS * LEVELCOLS * sizeof(int)) == 0)
                            {
                                if(nSlot1Remain == nSlot1RemainHistory && nSlot2Remain == nSlot2RemainHistory)
                                {
                                    counter3++;
                                    continue;
                                }
                            }
                            
                            CriticalBoost = CriticalBoostList[SkillLevelResult[1][4]];
                            AttackUp = sumDataDictionary24(LEVELROWS, LEVELCOLS, SkillLevelResult, 2, LEVELSIZE, DataList01, 0);
                            AffinityUp = sumDataDictionary24(LEVELROWS, LEVELCOLS, SkillLevelResult, 2, LEVELSIZE, DataList01, 1);
//                            Expectation = (baseWeaponDamage + AttackUp) * (1 + CriticalBoost * (Limit100(baseAffinity + AffinityUp) / (float)100));
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
                            
                            memcpy(&RankingHistoryInput[1][0], SkillLevelResult, (LEVELROWS - 1) * LEVELCOLS * sizeof(int));
                            RankingWithHistory13(HISTORY, LEVELROWS, LEVELCOLS, Expectation, RankingHistoryInput, ExpectationHistory, RankingHistory, temp);
                            
                            nSlot1RemainHistory = nSlot1Remain;
                            nSlot2RemainHistory = nSlot2Remain;
                            memset(SkillLevelResultHistory, SkillLevelResult, LEVELROWS * LEVELCOLS * sizeof(int));
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
        set2DictionaryPrintFormat(&RankingHistory[i][3][0], ProtectorNames, ProtectorTypes, 6, 18, NAME);
        if(GunnerOption)
        {
            printf("Gunnneroption : %d\n", RankingHistory[i][0][4]);
        }
        puts("");
    }
    printf("Try :%d, Excuted :%d\n, reject 1 [%d], reject 2[%d], reject 3 [%d]\n", counter, speed, counter1, counter2, counter3);
    
    return 0;
}

