// Definitions of structures, enumarations, constance adn data types
#ifndef TYPES_H
#define TYPES_H

#define Maxplayers 4


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
    int ID;
    char name[50];
    double purchasePrice;
    double mortgagePrice;
    double baseRental;
    double houseCost;
    double hotelCost;
    int currentOwner;
    int mortgageStatus;
    int InsuaranceStatus;
    int noOfBuilds;
}landProperties;

typedef struct{
    int id;
    char name[50];
    double chash;
    int currentPosition;
    int dieRollValue;
}Player;

#endif // !TYPES_H