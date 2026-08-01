#ifndef DECLARATION
#define DECLARATION
#include "types.h"

void printGameBegins();
void gameRun();
int rollDies(int *, int*);
void initializeBoard();
void playerMovement(Player *players,landProperties *propery);
void displayLandDetails(landProperties *property);
void buyProperty(Player *player, landProperties *property);
//player decisions
int aggInvDecisions(Player *players, landProperties property, int actionType, double futureRent);
int consBanDecisions(Player *players, landProperties property, int actionType);
int riskTakDecisions(Player *players, landProperties property, int actionType);
int oppTraDecisions(Player *players, landProperties property,double projectedAppreciation, int currentInflation, int currentSubsidies, int actionType);

#endif // !DECLARATION