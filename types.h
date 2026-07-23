// Definitions of structures, enumarations, constance adn data types
#ifndef TYPES_H
#define TYPES_H

typedef enum{
    GO,
    Pettah,
    CommunityDevFund,
    Maradhana,
    Incometax,
    ColomboFortRailway,
    Bambalapitiya,
    NationalEvent1,
    Wellawatta,
    MountLavinia,
    Jail,
    Nugegoda,
    CEB,
    Maharagama,
    Kottawa,
    KandyRailway,
    Negombo,
    SrilankaInsuarance,
    Katunayake,
    JaEla,
    FreeParking,
    Kandy,
    NationalEvent2,
    Peradeniya,
    Katugasthota,
    GalleRailway,
    GalleFort,
    Unawatuna,
    WaterBoard,
    Hikkaduwa,
    GoToJail,
    Jaffna,
    Nallur,
    CeylincoInsuarance,
    Trincomalee,
    JaffnaRailway,
    NationalEvent3,
    NuwaraEliya,
    BOC,
    GalleFace
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

#endif // !TYPES_H