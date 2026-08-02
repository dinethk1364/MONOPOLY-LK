// Definitions of structures, enumarations, constance adn data types
#ifndef TYPES_H
#define TYPES_H

#define Maxplayers 4
#define TileSize 40
#define RoundCount 2

#define BOLD_GREEN "\033[1;32m"
#define GREEN "\033[0;32m"
#define BOLD_RED "\033[1;31m"
#define RED "\033[0;31m"
#define BOLD_BLUE "\033[1;34m"
#define BLUE "\033[0;34m"
#define BOLD_YELLOW "\033[1;33m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

typedef enum{
    TRUE,FALSE
}boolValue;

typedef enum{
    GO,                 //0
    Pettah,             //1
    CommunityDevFund,   //2
    Maradhana,          //3
    Incometax,          //4
    ColomboFortRailway, //5
    Bambalapitiya,      //6
    NationalEvent1,     //7
    Wellawatta,         //8
    MountLavinia,       //9
    Jail,               //10
    Nugegoda,           //11
    CEB,                //12
    Maharagama,         //13
    Kottawa,            //14
    KandyRailway,       //15
    Negombo,            //16
    SrilankaInsuarance, //17
    Katunayake,         //18
    JaEla,              //19
    FreeParking,        //20
    Kandy,              //21
    NationalEvent2,     //22
    Peradeniya,         //23
    Katugasthota,       //24
    GalleRailway,       //25
    GalleFort,          //26
    Unawatuna,          //27
    WaterBoard,         //28
    Hikkaduwa,          //29
    GoToJail,           //30
    Jaffna,             //31
    Nallur,             //32
    CeylincoInsuarance, //33
    Trincomalee,        //34
    JaffnaRailway,      //35
    NationalEvent3,     //36
    NuwaraEliya,        //37
    BOC,                //38
    GalleFace           //39
}boardTiles;

typedef struct{
    char name[50];
    double purchasePrice;
    double mortgagePrice;
    double baseRental;
    double houseCost;
    double hotelCost;
    int currentOwner;//-1:no owner  //0:cannot be own //1,2,3,4: belongs to player ID
    double currentRent;
    boolValue mortgageStatus;// 1 is true 0 is false
    boolValue InsuaranceStatus;// 1 is true 0 is false
    int noOfHouses;
    int noOfHotels;
}landProperties;

extern landProperties board[TileSize];//declare global array(Global Extern Declarations)


typedef struct{
    int id;
    char name[50];
    double cash;
    int currentPosition;
    int currentRound;
    int dieRollValue;
    boolValue isBankrupt; //1 if bankrupt, 0 otherwise
    boolValue hasPassedGo; // 1 if passed Go, 0 otherwise
    boolValue inJail; //1 if in jail, 0 otherwise
    int jailTurns;// turns of player who in jail
}Player;

typedef enum {
    BUY_PROPERTY_DECISION,
    AUCTION_MAX_BID_DECISION,
    BUILD_HOUSE_DECISION,
    TAKE_LOAN_DECISION,
    BUY_INSURANCE_DECISION
} DecisionType;

#endif // !TYPES_H