//Board initializeation and movement logic
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "declaraction.h"   

landProperties board[TileSize];

void initializeBoard()
{
    //land Propeties
    board[Pettah]=(landProperties){"Pettah",0,0,0,0,0,-1,0,0,0,0};
    board[Maradhana]=(landProperties){"Maradhana",0,0,0,0,0,-1,0,0,0,0};
    board[Bambalapitiya]=(landProperties){"Bambalapitiya",0,0,0,0,0,-1,0,0,0,0};
    board[Wellawatta]=(landProperties){"Wellawatta",0,0,0,0,0,-1,0,0,0,0};
    board[MountLavinia]=(landProperties){"MountLavinia",0,0,0,0,0,-1,0,0,0,0};
    board[Nugegoda]=(landProperties){"Nugegoda",0,0,0,0,0,-1,0,0,0,0};
    board[Maharagama]=(landProperties){"Maharagama",0,0,0,0,0,-1,0,0,0,0};
    board[Kottawa]=(landProperties){"Kottawa",0,0,0,0,0,-1,0,0,0,0};
    board[Negombo]=(landProperties){"Negombo",0,0,0,0,0,-1,0,0,0,0};
    board[Katunayake]=(landProperties){"Katunayake",0,0,0,0,0,-1,0,0,0,0};
    board[JaEla]=(landProperties){"Ja-Ela",0,0,0,0,0,-1,0,0,0,0};
    board[Kandy]=(landProperties){"Kandy",0,0,0,0,0,-1,0,0,0,0};
    board[Peradeniya]=(landProperties){"Peradeniya",0,0,0,0,0,-1,0,0,0,0};
    board[Katugasthota]=(landProperties){"Katugasthota",0,0,0,0,0,-1,0,0,0,0};
    board[GalleFort]=(landProperties){"Galle Fort",0,0,0,0,0,-1,0,0,0,0};
    board[Unawatuna]=(landProperties){"Unawatuna",0,0,0,0,0,-1,0,0,0,0};
    board[Hikkaduwa]=(landProperties){"Hikkaduwa",0,0,0,0,0,-1,0,0,0,0}; 
    board[Jaffna]=(landProperties){"Jaffna",0,0,0,0,0,-1,0,0,0,0};
    board[Nallur]=(landProperties){"Nallur",0,0,0,0,0,-1,0,0,0,0};
    board[Trincomalee]=(landProperties){"Trincomalee",0,0,0,0,0,-1,0,0,0,0};
    board[NuwaraEliya]=(landProperties){"NuwaraEliya",0,0,0,0,0,-1,0,0,0,0};
    board[GalleFace]=(landProperties){"Galle Face",0,0,0,0,0,-1,0,0,0,0};

    //special properties
    board[ColomboFortRailway]=(landProperties){.name="Colombo Fort Railway", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};
    board[CEB]=(landProperties){.name="Ceylon Electricity Board", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};
    board[KandyRailway]=(landProperties){.name="Kandy Railway Station", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};
    board[GalleRailway]=(landProperties){.name="Galle Railway Station", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};
    board[WaterBoard]=(landProperties){.name="National Water Board", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};
    board[JaffnaRailway]=(landProperties){.name="Jaffna Railway Station", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};

    //special tiles

    board[GO]=(landProperties){.name="Go"};    
    board[CommunityDevFund]=(landProperties){.name="Community Development Fund"};    
    board[Incometax]=(landProperties){.name="Income Tax"};      
    board[NationalEvent1]=(landProperties){.name="National Event Card"};    
    board[Jail]=(landProperties){.name="Jail"}; 
    board[SrilankaInsuarance]=(landProperties){.name="Sri Lanka Insuarance"};    
    board[FreeParking]=(landProperties){.name="Free Parking"};    
    board[NationalEvent2]=(landProperties){.name="National Event Card"};
    board[GoToJail]=(landProperties){.name="Go to Jail"};
    board[CeylincoInsuarance]=(landProperties){.name="Ceylinco Insuarance"};
    board[NationalEvent3]=(landProperties){.name="National Event Card"};
    board[BOC]=(landProperties){.name="Bank of Ceylon"}; 

}
void playerMovement(Player *players)
{
    for(int i=1;i<=5;i++)//round limit
    {
        printf("\n======================= DIES ROLL ROUND %d =======================\n",i);
        for (int j=0;j<Maxplayers;j++)
        {
            if(players[j].isBankrupt!=1)// check player bankrupt
            {
                int d1,d2;
                int diesTotal = rollDies(&d1,&d2);
                printf(BOLD_GREEN"\n Dies Roll \n"RESET);
                printf("%s rolled %d\n",players[j].name,diesTotal);    
                
                int oldPosition = players[j].currentPosition;
                players[j].currentPosition = (oldPosition+diesTotal)%TileSize;//use modulus to after passing 40th tile back to 0
                
                printf(BOLD_GREEN"\n Player Movement \n"RESET);
                printf("%s moves from Square %d to Square %d\n",players[j].name,oldPosition,players[j].currentPosition);

                if (players[j].currentPosition < oldPosition)
                {
                    printf(BOLD_GREEN"\n Passing GO \n"RESET);
                    
                    printf("\n%s is passed GO.\n",players[j].name);
                    printf("Collected LKR 2,000.\n");
                    players[j].cash+=2000.0;
                    printf("Current Balance : LKR %.2lf\n",players[j].cash);    
                }
            }
        }
    }
}