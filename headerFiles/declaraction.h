#ifndef DECLARATION
#define DECLARATION
#include "types.h"

void printGameBegins();
void gameRun();
int rollDice(int *, int*);
landProperties *initializeBoard();
void playerMovement(Player *players,landProperties *propery);
void displayLandDetails(Player *player,landProperties *property);
void buyProperty(Player *player, landProperties *property,Player *playerlist);
void payRent(Player *player,landProperties *property,Player *playerlist,landProperties *properties);
int checkGameOver(Player *playerlist);
void gameOver(Player *playerlist);
int landData(double purchasePrice[],double baseRents[]);
void updateRailwayRent(landProperties *property, landProperties board[]);

//player decisions
int aggInvDecisions(Player *players, landProperties property, int actionType, double futureRent);
int consBanDecisions(Player *players, landProperties property, int actionType);
int riskTakDecisions(Player *players, landProperties property, int actionType);
int oppTraDecisions(Player *players, landProperties property,double projectedAppreciation, int currentInflation, int currentSubsidies, int actionType);

#endif // !DECLARATION