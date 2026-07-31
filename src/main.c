//program entry point
#include <stdlib.h>
#include <time.h>
#include "../headerFiles/declaraction.h"
void gameRun();
int main()
{
    srand(time(NULL));
    gameRun();
    return 0;
}