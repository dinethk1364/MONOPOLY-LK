//Board initializeation and movement logic
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "declaraction.h"   

landProperties board[TileSize];

void initializeBoard()
{
    //land Propeties
    board[Pettah]=(landProperties){.name="Pettah",.currentOwner=-1};
    board[Maradhana]=(landProperties){.name="Maradhana",.currentOwner=-1};
    board[Bambalapitiya]=(landProperties){.name="Bambalapitiya",.currentOwner=-1};
    board[Wellawatta]=(landProperties){.name="Wellawatta",.currentOwner=-1};
    board[MountLavinia]=(landProperties){.name="MountLavinia",.currentOwner=-1};
    board[Nugegoda]=(landProperties){.name="Nugegoda",.currentOwner=-1};
    board[Maharagama]=(landProperties){.name="Maharagama",.currentOwner=-1};
    board[Kottawa]=(landProperties){.name="Kottawa",.currentOwner=-1};
    board[Negombo]=(landProperties){.name="Negombo",.currentOwner=-1};
    board[Katunayake]=(landProperties){.name="Katunayake",.currentOwner=-1};
    board[JaEla]=(landProperties){.name="Ja-Ela",.currentOwner=-1};
    board[Kandy]=(landProperties){.name="Kandy",.currentOwner=-1};
    board[Peradeniya]=(landProperties){.name="Peradeniya",.currentOwner=-1};
    board[Katugasthota]=(landProperties){.name="Katugasthota",.currentOwner=-1};
    board[GalleFort]=(landProperties){.name="Galle Fort",.currentOwner=-1};
    board[Unawatuna]=(landProperties){.name="Unawatuna",.currentOwner=-1};
    board[Hikkaduwa]=(landProperties){.name="Hikkaduwa",.currentOwner=-1}; 
    board[Jaffna]=(landProperties){.name="Jaffna",.currentOwner=-1};
    board[Nallur]=(landProperties){.name="Nallur",.currentOwner=-1};
    board[Trincomalee]=(landProperties){.name="Trincomalee",.currentOwner=-1};
    board[NuwaraEliya]=(landProperties){.name="NuwaraEliya",.currentOwner=-1};
    board[GalleFace]=(landProperties){.name="Galle Face",.currentOwner=-1};

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
    int currentRound = 1;
    int diesRollRound = 1;
    printf(BOLD_BLUE"\n========================== ROUND %d ==========================\n"RESET,currentRound);

    while(currentRound<=RoundCount)//round limit
    {
        printf(BOLD_RED"\n\t\tDIES ROLL ROUND %d\n"RESET,diesRollRound);

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
                    players[j].hasPassedGo = 1;//mark that player passed Go
                    printf("Current Balance : LKR %.2lf\n",players[j].cash);    
                }
            }
        }
        diesRollRound++;

        int playerWhoPassedGo = 0;
        int activePlayersCount = 0;
        for(int k =0;k<Maxplayers;k++)
        {
            if(players[k].isBankrupt != 1 && players[k].inJail !=1)
            {
                activePlayersCount++;//get active player count
                if(players[k].hasPassedGo == 1)
                {
                    playerWhoPassedGo++;
                }
            }
        }

        if(playerWhoPassedGo==activePlayersCount && activePlayersCount>0)
        {
            currentRound++;
            for(int k=0;k<Maxplayers;k++)
            {
                players[k].hasPassedGo=0;
            }
            if(currentRound<=RoundCount)
            {
                printf(BOLD_BLUE"\n========================== ROUND %d ==========================\n"RESET,currentRound);                
            }
        }        
    }
    printf(BOLD_BLUE"\n====================== GAME END ======================\n"RESET);

}