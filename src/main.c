//program entry point
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void gameRun();
int main()
{
    setlocale(LC_NUMERIC, "");
    srand(time(NULL));
    gameRun();
    return 0;
}