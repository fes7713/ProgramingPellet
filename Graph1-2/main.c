#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define ROWS 47
#define COLS 180
//font 16, window size height 49, width 189

int main(int argc, char** argv)
{
    char field[ROWS][COLS];
    memset(field, 0, ROWS * COLS);
    float nX;
    float nY;
    float EnY;
    float nPrevY = 0;
    float nYStart = 5;
    float nXStart = -10;
    float nXPrecision = 10;
    float nYPrecision = 1;
    int nXFractionLevel = 0;
    int nYFractionLevel = 0;
    float nGridDensData[] = { 0.125, 0.25, 0.5, 1, 2, 3, 4, 5, 10, 20, 50, 100, 200, 500, 1000 };
    int nGridDensLevel = 7;
    float nXGridDens = nGridDensData[nGridDensLevel];
    float nYGridDens = nGridDensData[nGridDensLevel];
    //    float nXGridDens = 0.5;
    //    float nYGridDens = 0.5;
    int temp = 0;
    float nThickness = 8;
    int counter = 0;
    float nXLevel = 1;
    float nYLevel = 1;
    int a = 1;
    int b = 0;
    int c = -20;
    int d = -12;
    

    nGridDensData[0] = floor(nGridDensData[0] * 1000) / 1000;
    nGridDensData[1] = floor(nGridDensData[1] * 1000) / 1000;
    while (1) {
        memset(field, 0, ROWS * COLS);
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++) {
                if (fmodf(i, nYPrecision * nYGridDens) == 0)
                    field[i][j] = '_';
                if (fmodf(j, (nXPrecision * nXGridDens)) == 0)
                    field[i][j] = '|';
            }

        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++) {
                nX = nXStart + j / nXPrecision;
                //nY = (1.0 * nX - 12.0) / (1.0 * nX * nX - 3.0 * nX - 12.0);
                //nY = 1.0 * nX * nX * nX + 0 * nX * nX + 5 * nX -13.0;
                //nY = a * nX * nX * nX + b * nX * nX + c * nX + d;
                //nY = 1.0 * nX * nX * nX * nX - 4 * nX -12.0;
                //nY = 10.0 /(nX);
                //nY = exp(nX);
                //nY = acos(nX);
                //nY = cos(nX);
                //nY = (-nX) * nX * nX * nX *nX + 2.5 * nX * nX * nX * nX + 40 / 3 * nX * nX * nX + 5;
                //nY = 3 * nX * nX -16 * nX + 22;
                //nY = nX * nX * nX -8 * nX * nX + 22 * nX;
                //nY = 8 / nX;
                //nY = 8 - 9 * nX;
                //nY = pow(nX, 3.0 / 4.0) - 3 * pow(nX, 1.0 / 4.0);
                //nY = 2 * pow(nX , 3) - 3 * pow(nX, 2) - 72 * nX + 7;
                nY =  nX - pow(nX , 1.0 / 3.0); 
                EnY = nYStart - i / nYPrecision;
                if ((EnY - nY <= 1.0 / nYPrecision * nThickness && EnY - nY >= 1.0 / -nYPrecision * nThickness || EnY - nY == 0) || (nY < EnY && EnY < nPrevY || nPrevY < EnY && EnY < nY))
                {
                    if (j != 0)
                        field[i][j] = '/';
                }
                nPrevY = nY;
            }

        printf("      ");
        for (int j = 0; j < COLS; j++) {
            if (fmodf(j, (nXPrecision * nXGridDens)) == 0) {
                printf("|%-6.1f", nXStart + j / nXPrecision);
                counter = 6;
            }
            else {
                if (counter > 0) {
                    printf("");
                    counter--;
                }
                else
                    putchar(' ');
            }
        }
        puts("");

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (j == 0) {
                    if (fmodf(i, nYPrecision * nYGridDens) == 0)
                        printf("%6.1f", nYStart - i / nYPrecision);
                    else
                        printf("      ");
                }
                if (field[i][j] != 0)
                    putchar(field[i][j]);
                else
                    putchar(' ');
            }
            putchar('\n');
        }

        int p = _getch();
        switch (p) {
        case 'w': nYStart += nYLevel * 2; break;
        case 's': nYStart -= nYLevel * 2; break;
        case 'a': nXStart -= nXLevel; break;
        case 'd': nXStart += nXLevel; break;
        case 'q': nXPrecision *= 2; nXLevel /= 2; break;
        case 'e': nXPrecision /= 2; nXLevel *= 2; break;
        case 'z': nYPrecision *= 2; nYLevel /= 2; break;
        case 'x': nYPrecision /= 2; nYLevel *= 2; break;
        case 't': nThickness *= 2; break;
        case 'r': nThickness /= 2; break;
        case 'g': nGridDensLevel++; break;
        case 'f': nGridDensLevel--; break;
        case '1': nXLevel *= 2; nYLevel *= 2; break;
        case '2': nXLevel /= 2; nYLevel /= 2; break;
        case '0': nYStart = 0; nXStart = 0; break;
        case 'i': printf("Type a, b, c, d"); scanf("%d%d%d%d", &a, &b, &c, &d); break;
        }
        if (nGridDensLevel > 14)
            nGridDensLevel = 14;

        if (nGridDensLevel < 0)
            nGridDensLevel = 0;

        if (nXLevel < 0.1)
            nXLevel = 0.1;
        if (nXLevel > 1000)
            nXLevel = 1000;
        if (nYLevel < 0.1)
            nYLevel = 0.1;
        if (nYLevel > 1000)
            nYLevel = 1000;

        nXGridDens = nGridDensData[nGridDensLevel];
        nYGridDens = nGridDensData[nGridDensLevel];
        system("cls");
    }
    return 0;
}