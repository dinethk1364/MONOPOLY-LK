//Board initializeation and movement logic
#include <stdio.h>
#include <string.h>
#include "types.h"

landProperties board[TileSize];

void initializeBoard()
{
    //land Propeties
    board[Pettah]=(landProperties){"Pettah",0,0,0,0,0,-1,-1,-1,0,0};
    board[Maradhana]=(landProperties){"Maradhana",0,0,0,0,0,-1,-1,-1,0,0};
    board[Bambalapitiya]=(landProperties){"Bambalapitiya",0,0,0,0,0,-1,-1,-1,0,0};
    board[Wellawatta]=(landProperties){"Wellawatta",0,0,0,0,0,-1,-1,-1,0,0};
    board[MountLavinia]=(landProperties){"MountLavinia",0,0,0,0,0,-1,-1,-1,0,0};
    board[Nugegoda]=(landProperties){"Nugegoda",0,0,0,0,0,-1,-1,-1,0,0};
    board[Maharagama]=(landProperties){"Maharagama",0,0,0,0,0,-1,-1,-1,0,0};
    board[Kottawa]=(landProperties){"Kottawa",0,0,0,0,0,-1,-1,-1,0,0};
    board[Negombo]=(landProperties){"Negombo",0,0,0,0,0,-1,-1,-1,0,0};
    board[Katunayake]=(landProperties){"Katunayake",0,0,0,0,0,-1,-1,-1,0,0};
    board[JaEla]=(landProperties){"Ja-Ela",0,0,0,0,0,-1,-1,-1,0,0};
    board[Kandy]=(landProperties){"Kandy",0,0,0,0,0,-1,-1,-1,0,0};
    board[Peradeniya]=(landProperties){"Peradeniya",0,0,0,0,0,-1,-1,-1,0,0};
    board[Katugasthota]=(landProperties){"Katugasthota",0,0,0,0,0,-1,-1,-1,0,0};
    board[GalleFort]=(landProperties){"Galle Fort",0,0,0,0,0,-1,-1,-1,0,0};
    board[Unawatuna]=(landProperties){"Unawatuna",0,0,0,0,0,-1,-1,-1,0,0};
    board[Hikkaduwa]=(landProperties){"Hikkaduwa",0,0,0,0,0,-1,-1,-1,0,0}; 
    board[Jaffna]=(landProperties){"Jaffna",0,0,0,0,0,-1,-1,-1,0,0};
    board[Nallur]=(landProperties){"Nallur",0,0,0,0,0,-1,-1,-1,0,0};
    board[Trincomalee]=(landProperties){"Trincomalee",0,0,0,0,0,-1,-1,-1,0,0};
    board[NuwaraEliya]=(landProperties){"NuwaraEliya",0,0,0,0,0,-1,-1,-1,0,0};
    board[GalleFace]=(landProperties){"Galle Face",0,0,0,0,0,-1,-1,-1,0,0};

    //special properties
    board[ColomboFortRailway]=(landProperties){.name="Colombo Fort Railway", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};
    board[CEB]=(landProperties){.name="Ceylon Electricity Board", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};
    board[KandyRailway]=(landProperties){.name="Kandy Railway Station", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};
    board[GalleRailway]=(landProperties){.name="Galle Railway Station", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};
    board[WaterBoard]=(landProperties){.name="National Water Board", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};
    board[JaffnaRailway]=(landProperties){.name="Jaffna Railway Station", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};

    //special tiles

    board[GO]=(landProperties){"Go"};    
    board[CommunityDevFund]=(landProperties){"Community Development Fund"};    
    board[Incometax]=(landProperties){"Income Tax"};      
    board[NationalEvent1]=(landProperties){"National Event Card"};    
    board[Jail]=(landProperties){"Jail"}; 
    board[SrilankaInsuarance]=(landProperties){"Sri Lanka Insuarance"};    
    board[FreeParking]=(landProperties){"Free Parking"};    
    board[NationalEvent2]=(landProperties){"National Event Card"};
    board[GoToJail]=(landProperties){"Go to Jail"};
    board[CeylincoInsuarance]=(landProperties){"Ceylinco Insuarance"};
    board[NationalEvent3]=(landProperties){"National Event Card"};
    board[BOC]=(landProperties){"Bank of Ceylon"}; 

}