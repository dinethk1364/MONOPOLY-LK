// Definitions of structures, enumarations, constance adn data types
#ifndef TYPES_H
#define TYPES_H

#define Maxplayers 4
#define TileSize 40
#define RoundCount 500
#define GO_MONEY 2000.0f
#define PLAYER_STARTING_CASH 30000.0f
#define MAX_ROWS 22

#define BOLD_GREEN "\033[1;32m"
#define GREEN "\033[0;32m"
#define BOLD_RED "\033[1;31m"
#define RED "\033[0;31m"
#define BOLD_BLUE "\033[1;34m"
#define BLUE "\033[0;34m"
#define BOLD_YELLOW "\033[1;33m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

// #define BOLD_GREEN ""
// #define GREEN ""
// #define BOLD_RED ""
// #define RED ""
// #define BOLD_BLUE ""
// #define BLUE ""
// #define BOLD_YELLOW ""
// #define YELLOW ""
// #define RESET ""

#define mktCond 1 //tempory

typedef enum{
    FALSE,TRUE
}boolValue;

typedef enum{
    G_BROWN = 1,
    G_LIGHT_BLUE,
    G_PINK,
    G_ORANGE,
    G_RED,
    G_YELLOW,
    G_GREEN,
    G_DARK_BLUE
}colorGroup;

typedef enum{
    AGG_INVESTER=1,CONS_BANKER,RISK_TAKER,OPP_TRADER
}playerNames;

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
    SrilankaInsurance, //17
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
    CeylincoInsurance, //33
    Trincomalee,        //34
    JaffnaRailway,      //35
    NationalEvent3,     //36
    NuwaraEliya,        //37
    BOC,                //38
    GalleFace           //39
}boardTiles;

typedef enum{
    land=1,
    utility,
    railway,
    nonProperty
}tileTypes;

typedef enum {
    INS_BASIC=1,
    INS_COMPREHENSIVE,
    INS_BUISINESS_INTERUPTION
} InsuaranceType;

typedef struct {
    int isActive;
    double currentLoanAmount;//current outstandint loan
    double originalLoanAmount;
    double intRate;
    int remainingRounds;
    int collateralProperties[TileSize];
    int collateralCount;
} LoanInfo;

typedef struct{
    char name[50];
    double purchasePrice;
    double mortgagePrice;
    double baseRental;
    double houseCost;
    double hotelCost;
    int type;// 1: land 2: utility  3: railway   4: nonproperty
    int currentOwner;//-1:no owner  //0:cannot be own //1,2,3,4: belongs to player ID
    double currentRent;
    boolValue mortgageStatus;// 1 is true 0 is false
    int noOfHouses;
    int noOfHotels;
    colorGroup cGroup;
    double propertyValue;
    int age;
    double buildingCondition;
    int unmaintaindRounds;
    boolValue isStucturalDamaged;//building depreciation
    boolValue isDamage;//for disaster

    boolValue InsuranceStatus;// 1 is true 0 is false
    InsuaranceType insuaranceType;
    int insuaranceRounds;

    boolValue isLoanLocked;

}landProperties;

typedef struct{
    int id;
    char name[50];
    double cash;
    double netWorth;
    int currentPosition;
    int dieRollValue;
    int roundCount;
    boolValue isBankrupt; //1 if bankrupt, 0 otherwise
    boolValue inJail; //1 if in jail, 0 otherwise
    int jailTurns;// turns of player who in jail

    //events
    int eventExpiryRound;
    double eventValueMultiplier;
    int activeCard;

    LoanInfo activeLoan;
}Player;

typedef enum {
    BUY_PROPERTY_DECISION,
    AUCTION_MAX_BID_DECISION,
    BUILD_HOUSE_DECISION,
    UNMORTGAGE,
    MAINTENANCE_DECISION,
    BUY_INSURANCE_DECISION,
    TAKE_LOAN_DECISION,
    REPAY_LOAN_DECISION,
    EXTEND_LOAN_DECISION
}decisionType;

typedef struct {
    int cardId;
    char name[50];
    char description[100];
}nationalEventCards;

typedef enum {
    TOURISM_HYPE,         
    FUEL_SHORTAGE,            
    HEAVY_FLOODS,             
    POLITICAL_RALLY,          
    STOCK_MARKET_RISE,        
    ECONOMIC_DOWNTURN,        
    HOUSING_SUBSIDY,          
    INTEREST_RATE_CUT,        
    INTEREST_RATE_INCREASE,   
    TAX_AMNESTY,              
    POWER_FAILURE,            
    FOREIGN_FUNDING,          
    PORT_EXPANSION,           
    FESTIVAL_SEASON,          
    LABOUR_STRIKE,            
    INSURANCE_DISCOUNT,       
    PROPERTY_REVALUATION,     
    CURRENCY_DEPRECIATION,    
    GOVERNMENT_GRANT,         
    NATIONAL_DISASTER         
}NationalEventCardID;

typedef enum {
    TOURISM_BOOM,
    FUEL_CRISIS,
    HEAVY_MONSOON,
    ECONOMIC_RECESSION,
    STOCK_MARKET_BOOM,
    GOVT_HOUSING_PROGRAMME,
    FOREIGN_INVESTMENT,
    POLITICAL_UNREST,
    NO_EVENT
}EconomicEvent;

typedef struct {
    EconomicEvent currentEvent;
    double propertyValueMult;
    double rentMultiplier;
    double houseCostMult;
    double hotelRentMult;
    double railwayRentMult;
}GlobalEconomy;

typedef enum{
    DISASTER_FIRE,
    DISASTER_FLOOD,
    DISASTER_RIOT,
    DISASTER_BUILDING_COLLAPSE,
    DISASTER_ELECTRICAL_FAILURE
}RandomDisaster;
typedef enum {
    REG_INCREASE_PROPERTY_TAX,      
    REG_REDUCE_LOAN_INTEREST,       
    REG_HOUSING_SUBSIDY,            
    REG_LUXURY_PROPERTY_TAX,         
    REG_RAILWAY_MODERNIZATION,      
    REG_ELECTRICITY_TARIFF,         
    REG_INSURANCE_REGULATION,       
    REG_ANTI_SPECULATION,           
    NO_REGULATION = -1
} GovRegulation;

typedef struct {
    //gov regulations
    GovRegulation activeReg;
    int activeRound;

    //dynamic prop market
    colorGroup activeBoomGroup;
    colorGroup activeDeclineGroup;
    int boomRoundsRemaining;
    int declineRoundsRemaining;
    int lastAffectedRound[9]; 

    //inflation & interest
    double currentInflationRate;
    double currentBaseInterest;
} economicState;


#endif 