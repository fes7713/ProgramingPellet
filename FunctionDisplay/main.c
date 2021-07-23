#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
    int nXscale = 0;
    int nYscale = 0;
    float nXPrecision = 0;
    float nYPrecision = 0;
    float nXGridDens = 0;
    float nYGridDens = 0;
    int nThickness = 2;
    printf("Type X scale");
    scanf("%d", &nXscale);
    nXPrecision = 94 /nXscale ;
//    printf("Type XPrecision");
//    scanf("%f", &nXPrecision);
    printf("Type Grid density of X-aix (Number per lines)");
    scanf("%f", &nXGridDens);
    printf("Type Y scale");
    scanf("%d", &nYscale);
    printf("Type YPrecision");
    scanf("%f", &nYPrecision);
    printf("Type Grid density of Y-aix (Number per lines)");
    scanf("%f", &nYGridDens);
    printf("Type thickness of brush");
    scanf("%d", &nThickness);
    
    
    float nX;
    float nY;
    float EnY;
    float nPrevY;
    int counter = 0;
    
    for(int i = nYscale; i > -nYscale; i--)
    {
        for(int j = 0; j > -nYPrecision; j--)
        {
            EnY = i + (1.0 / nYPrecision) * j;
            if(i % (int)(1.0 / nYGridDens) == 0 && j == 0)
            {
                printf("\n%5.0f", EnY);
            }
            else{
                printf("\n     ");
            }
            
            for(int k = -nXscale; k < nXscale; k++)
            {
                for(int p = 0; p < nXPrecision; p++)
                {
                    nX = k + (1.0 / nXPrecision) * p;
            
                    //nY = (1.0 * nX - 12.0) / (1.0 * nX * nX - 3.0 * nX - 12.0);
                    nY = 1.0 * nX * nX * nX - 20 * nX -12.0;
                    //nY = 1.0 * nX * nX * nX * nX - 4 * nX -12.0;
                    //nY = 10.0 /(nX);
                    //nY = exp(nX);
                    //nY = acos(nX);
                    
                    
                    //if(absolute(EnY - nY) <= 1.0 / nYPrecision)
                    //if(EnY - nY <= 1.0 / nYPrecision * nThickness && EnY - nY >= 1.0 / -nYPrecision * nThickness || EnY - nY == 0)
                    //if(EnY / nY <= 1.0 / nYPrecision  && EnY / nY >= 1.0 / -nYPrecision || EnY - nY == 0)
                    //if(nY < EnY && EnY < nPrevY || nPrevY < EnY && EnY < nY)
                    //if(nY * 2 < EnY && EnY < nPrevY * 2|| nPrevY * 2 < EnY && EnY < nY * 2)
                    if((EnY - nY <= 1.0 / nYPrecision * nThickness && EnY - nY >= 1.0 / -nYPrecision * nThickness || EnY - nY == 0) || (nY < EnY && EnY < nPrevY || nPrevY < EnY && EnY < nY))
                    {
                        if(!(k == -nXscale && p == 0))
                        {
//                            if(fmodf(nX, nXGridDens) == 0)
//                            {
//                                if(i == -1 && j == 0)
//                                {
//                                    printf("%4.1f", nX);
//                                    counter = 4;
//                                }
//                            }
//                            else{
                            printf("/");
//                            }
                        }
                        else{
                            printf("|");
                        }
                    }
                    else{
                    
                        if(fmodf(nX, nXGridDens) == 0)
                        {
                            printf("|");
                            if(i == -1 && j == 0)
                            {
                                printf("%4.1f", nX);
                                counter = 4;
                            }
                        }
                        else if(fmodf(i, nYGridDens) == 0 && j == 0){
                            printf("_");
                        }
                        else{
                            if(counter > 0)
                            {
                                printf("");
                                counter--;
                            }
                            else{
                                printf(" ");
                            }
                        }
                    }
                    nPrevY = nY;
                }
            }
        }
    }
	return 0;
}