#ifndef DECLARATION
#define DECLARATION
#include "types.h"

void printGameBegins();
void gameRun();
int rollDice(int *, int*);
landProperties *initializeBoard();
void playerMovement(Player players[],landProperties board[]);
void displayLandDetails(Player *player,landProperties *property,landProperties board[]);
void buyProperty(Player *player, landProperties *property,Player playerlist[],landProperties board[]);
void Bankrupt(Player *player,Player playerlist[],landProperties board[],double marketConsition);
void payRent(Player *player,landProperties *property,Player playerlist[],landProperties board[]);
int checkGameOver(Player playerlist[]);
void gameOver(Player playerlist[],landProperties board[]);
int landData(double purchasePrice[],double baseRents[]);
void updateRailwayRent(landProperties *property, landProperties board[]);
void updateUtilityRent(landProperties *property,landProperties board[],int diceRoll);
void endOfTheRounds(Player* players, int roundCount,landProperties board[]);
void displayGameOver(Player *player,landProperties board[]);
int hasMonopoly(landProperties board[],int playerId, int colorGroup);
void buildHouses(Player *player, landProperties board[]);

void calPropertyValue(landProperties *property);
void calMortgageValue(landProperties *property);
int hasBuildings(landProperties board[], int colorGroup);
void updateLandRent(landProperties *property);
void mortgageProperty(Player *player,landProperties board[],landProperties *property,double marketcondition);
void unmortgageProperty(Player *player, landProperties board[]);
void incomeTax(Player *player, double marketCondition);
void communityDevFund(Player *player,Player playerlist[],landProperties board[],double marketCondition);

void executeNationalEvents(Player playerlist[],Player *player,landProperties board[],int cardId);
void nationalEventCardProcess(Player playerlist[], Player *player, landProperties board[]);
void checkEventExpiry(Player *player,landProperties board[]);
void clearPlayerEvent(Player *player, landProperties board[]);
void economicEventProcess(int currentRound, landProperties board[]);
void executeEconomicEvents(landProperties board[], EconomicEvent eventId, int currentRound);
void clearEconEvents(landProperties board[]);
void randomDisaster(landProperties board[],Player playerlist[],int currentRound);
void processDisaster(landProperties *property,Player playerlist[]);

void propertyDepreciation(landProperties board[]);
void renovateProperty(Player *player,landProperties *property);
void buildingCondition(landProperties board[],Player players[]);
double rentMultiplier(landProperties *property);
void buildingMaintenance(Player *player,landProperties board[]);
int hasMonopoly(landProperties board[],int playerId, int colorGroup);

void handleInsuarace(Player *player, landProperties board[],double marketCondition);
void checkInsuaranceExpiry(landProperties board[]);

void updateLoanInterest(Player playerlist[],landProperties board[]);
double takeLoan(Player *player, landProperties board[],double requestedAmount,double currentIntRate);
void handleBanking(Player *player,landProperties board[],double currentIntRate);
void repayLoan(Player *player,landProperties board[],double amount);
void extendLoan(Player *player);

int needsLoanForMonopolyDevelopment(Player *player, landProperties board[]);
int propertiesCountofGroup(landProperties board[],int colorGroup, int playerId);

GlobalEconomy *initGlobalEco();
economicState *getActiveGovReg();
void clearPreviousRegulation(landProperties board[]);
void processGovernmentRegulations(int currentRound, landProperties board[], Player playerlist[]);
double calculateCurrentInterestRate();
void processInflation(int currentRound, landProperties board[]);

void processDynamicMarket(int currentRound, landProperties board[]);
void displayMarketConditions(double currentLoanInterest, double currentInflation);
const char *getColorGroupName(colorGroup group);
double calculateCurrentInterestRate();

void calculateNetWorth(Player *player, landProperties board[]);

//player decisions
int aggInvDecisions(Player *players, landProperties property, int actionType, double value);
int consBanDecisions(Player *players, landProperties property, int actionType, int value);
int riskTakDecisions(Player *players, landProperties property, int actionType, int value);
int oppTraDecisions(Player *players, landProperties property,double projectedAppreciation, int currentInflation, int currentSubsidies, int actionType);

#endif 