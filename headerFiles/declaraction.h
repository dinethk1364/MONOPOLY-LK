#ifndef DECLARATION
#define DECLARATION
#include "types.h"

void printGameBegins();
void gameRun();
int rollDice(int *, int*);
landProperties *initializeBoard();
void playerMovement(Player *players,landProperties *propery);
void displayLandDetails(Player *player,landProperties *property,landProperties board[]);
void buyProperty(Player *player, landProperties *property,Player playerlist[]);
void Bankrupt(Player *player,Player playerlist[],landProperties board[]);
void payRent(Player *player,landProperties *property,Player playerlist[],landProperties board[]);
int checkGameOver(Player playerlist[]);
void gameOver(Player playerlist[]);
int landData(double purchasePrice[],double baseRents[]);
void updateRailwayRent(landProperties *property, landProperties board[]);
void updateUtilityRent(landProperties *property,landProperties board[],int diceRoll);
void endOfTheRounds(Player* players, int roundCount);
void displayGameOver(Player *player);
int hasMonopoly(landProperties board[],int playerId, int colorGroup);
void buildHouses(Player *player, landProperties board[]);

void incomeTax(Player *player, double marketCondition);
void communityDevFund(Player *player,Player playerlist[],landProperties board[],double marketCondition);

//player decisions
int aggInvDecisions(Player *players, landProperties property, int actionType, double value);
int consBanDecisions(Player *players, landProperties property, int actionType);
int riskTakDecisions(Player *players, landProperties property, int actionType);
int oppTraDecisions(Player *players, landProperties property,double projectedAppreciation, int currentInflation, int currentSubsidies, int actionType);

#endif // !DECLARATION