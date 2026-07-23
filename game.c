//Game controler and eimulation engine
#include <stdio.h>
#include <stdlib.h>
#include "declaraction.h"   

int rollSingleDie()
{
    int dieRoll;
    dieRoll = (rand()%6)+1;

    return dieRoll;
}
int rollDies()
{
    puts("Game Started");
    int isRollDoubles = 0;
    int dieRoll1 = rollSingleDie();
    int dieRoll2 = rollSingleDie();

    printf("Roll 1 : %d \t Roll 2 : %d\n",dieRoll1,dieRoll2);
    if(dieRoll1==dieRoll2)
    {
        isRollDoubles = 1;
        puts("Rolling Double");
    }
}
void gameFunctions()
{
    gameBegins();
    rollDies();
}