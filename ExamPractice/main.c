#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

int * returnPointer();

void stringAllocation(char ** p);

int main(int argc, char **argv)
{
//	int a = 5;
//    printf("Value of a : %d\n", a);
//    printf("Address of a : %d\n\n", &a);
//    
//    int ptrA = &a;
//    printf("Value of ptrA : %d\n", ptrA);
//    printf("Dereferencing ptrA : %d\n\n", ptrA);
//    
//    int * p;
//    //malloc needs stdlib
//    
//    p = (int*)malloc(sizeof(int));
//    
//    *p = 5;
//    printf("The value pointed by p is %d\n", *p);
//
//    //never forget free!!!!!!!!!!!!!!!!!!!!!!!!
//    free(p);
//    
//    
//    int *q;
//    q = (int *)malloc(sizeof(int) * SIZE);
//    
//    p[0] = 5;
//    
//    for(int i = 0; i < SIZE; i++)
//    {
//        ///////
//    }
//    
//    free(q);
//    
//    int * arr;
//    
//    arr = returnPointer();
//    
//    /////......
//    
//    free(arr);
//    
//    s = (char *)malloc(20);
////no need to used size of char

    
    char * s;
    stringAllocation(&s);
    
    strcpy(s, "Testing new string");
    puts(s);
    
    
	return 0;
}


//never return pointer of local variable.
//So instead use dynamic allocation
int * returnPointer()
{
    int * p = (int *)malloc(sizeof(int) * SIZE);
    
    return  p;
}

void stringAllocation(char ** p)
{
    *p = (char *)malloc(strlen(p));
}

char * stringAllocation2()
{
    char * c = (char *)malloc(80);
    return c;
}