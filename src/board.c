//Board initializeation and movement logic
#include <stdio.h>
#include <string.h>
#include "../headerFiles/declaraction.h"   

landProperties board[TileSize];

void initializeBoard()
{
    //land Propeties
    board[Pettah]=(landProperties){.name="Pettah",.purchasePrice=1500.0,.baseRental=100.0,.currentOwner=-1};
    board[Maradhana]=(landProperties){.name="Maradhana",.purchasePrice=1800.0,.baseRental=120.0,.currentOwner=-1};
    board[Bambalapitiya]=(landProperties){.name="Bambalapitiya",.purchasePrice=2500.0,.baseRental=180.0,.currentOwner=-1};
    board[Wellawatta]=(landProperties){.name="Wellawatta",.purchasePrice=2700.0,.baseRental=200.0,.currentOwner=-1};
    board[MountLavinia]=(landProperties){.name="MountLavinia",.purchasePrice=3000.0,.baseRental=220.0,.currentOwner=-1};
    board[Nugegoda]=(landProperties){.name="Nugegoda",.purchasePrice=3500.0,.baseRental=260.0,.currentOwner=-1};
    board[Maharagama]=(landProperties){.name="Maharagama",.purchasePrice=3800.0,.baseRental=280.0,.currentOwner=-1};
    board[Kottawa]=(landProperties){.name="Kottawa",.purchasePrice=4000.0,.baseRental=300.0,.currentOwner=-1};
    board[Negombo]=(landProperties){.name="Negombo",.purchasePrice=4500.0,.baseRental=350.0,.currentOwner=-1};
    board[Katunayake]=(landProperties){.name="Katunayake",.purchasePrice=4700.0,.baseRental=370.0,.currentOwner=-1};
    board[JaEla]=(landProperties){.name="Ja-Ela",.purchasePrice=5000.0,.baseRental=400.0,.currentOwner=-1};
    board[Kandy]=(landProperties){.name="Kandy",.purchasePrice=5500.0,.baseRental=450.0,.currentOwner=-1};
    board[Peradeniya]=(landProperties){.name="Peradeniya",.purchasePrice=5800.0,.baseRental=480.0,.currentOwner=-1};
    board[Katugasthota]=(landProperties){.name="Katugasthota",.purchasePrice=6000.0,.baseRental=500.0,.currentOwner=-1};
    board[GalleFort]=(landProperties){.name="Galle Fort",.purchasePrice=6500.0,.baseRental=600.0,.currentOwner=-1};
    board[Unawatuna]=(landProperties){.name="Unawatuna",.purchasePrice=6800.0,.baseRental=620.0,.currentOwner=-1};
    board[Hikkaduwa]=(landProperties){.name="Hikkaduwa",.purchasePrice=7000.0,.baseRental=650.0,.currentOwner=-1}; 
    board[Jaffna]=(landProperties){.name="Jaffna",.purchasePrice=8000.0,.baseRental=750.0,.currentOwner=-1};
    board[Nallur]=(landProperties){.name="Nallur",.purchasePrice=8300.0,.baseRental=780.0,.currentOwner=-1};
    board[Trincomalee]=(landProperties){.name="Trincomalee",.purchasePrice=8500.0,.baseRental=800.0,.currentOwner=-1};
    board[NuwaraEliya]=(landProperties){.name="NuwaraEliya",.purchasePrice=10000.0,.baseRental=1000.0,.currentOwner=-1};
    board[GalleFace]=(landProperties){.name="Galle Face",.purchasePrice=12000.0,.baseRental=1200.0,.currentOwner=-1};

    //special properties
    board[ColomboFortRailway]=(landProperties){.name="Colombo Fort Railway", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};
    board[CEB]=(landProperties){.name="Ceylon Electricity Board", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};
    board[KandyRailway]=(landProperties){.name="Kandy Railway Station", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};
    board[GalleRailway]=(landProperties){.name="Galle Railway Station", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};
    board[WaterBoard]=(landProperties){.name="National Water Board", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};
    board[JaffnaRailway]=(landProperties){.name="Jaffna Railway Station", .purchasePrice=0,.mortgagePrice=0,.baseRental=0,.currentOwner=-1};

    //special tiles

    board[GO]=(landProperties){.name="Go",.currentOwner=0};    
    board[CommunityDevFund]=(landProperties){.name="Community Development Fund",.currentOwner=0};    
    board[Incometax]=(landProperties){.name="Income Tax",.currentOwner=0};      
    board[NationalEvent1]=(landProperties){.name="National Event Card",.currentOwner=0};    
    board[Jail]=(landProperties){.name="Jail",.currentOwner=0}; 
    board[SrilankaInsuarance]=(landProperties){.name="Sri Lanka Insuarance",.currentOwner=0};    
    board[FreeParking]=(landProperties){.name="Free Parking",.currentOwner=0};    
    board[NationalEvent2]=(landProperties){.name="National Event Card",.currentOwner=0};
    board[GoToJail]=(landProperties){.name="Go to Jail",.currentOwner=0};
    board[CeylincoInsuarance]=(landProperties){.name="Ceylinco Insuarance",.currentOwner=0};
    board[NationalEvent3]=(landProperties){.name="National Event Card",.currentOwner=0};
    board[BOC]=(landProperties){.name="Bank of Ceylon",.currentOwner=0}; 
}
void handleLandLanding(Player *player, landProperties *property, Player *playerlist)
{
    displayLandDetails(player,property);
    buyProperty(player,property);
    payRent(player,property,playerlist);
}
void playerMovement(Player *players,landProperties *propery)
{
    int currentRound = 1;
    int diesRollRound = 1;
    printf(BOLD_BLUE"\n========================== ROUND %d ==========================\n"RESET,currentRound);

    while(currentRound<=RoundCount)//round limit
    {
        printf(BOLD_YELLOW"\n\t\tDIES ROLL ROUND %d\n"RESET,diesRollRound);

        for (int j=0;j<Maxplayers;j++)
        {
            if(players[j].isBankrupt!=1)// check player bankrupt
            {
                int d1,d2;
                int diesTotal = rollDies(&d1,&d2);
                
                if(players[j].inJail!=1)//move player if not in jail
                {
                    printf(BOLD_GREEN"\n Dies Roll \n"RESET);
                    printf("%s rolled %d\n",players[j].name,diesTotal);    
                
                    int oldPosition = players[j].currentPosition;
                    players[j].currentPosition = (oldPosition+diesTotal)%TileSize;//use modulus to after passing 40th tile back to 0
                    printf(BOLD_GREEN"\n Player Movement \n"RESET);

                    if(players[j].currentPosition==GoToJail)//send to jail
                    {
                        printf("%s moves from Square %d to Square %d\n",players[j].name,oldPosition,players[j].currentPosition);

                        printf(RED"Busted! %s was caught and sent straight to Jail!\n"RESET,players[j].name);
                        players[j].currentPosition = Jail;
                        players[j].inJail = 1;
                        players[j].hasPassedGo=1;
                        players[j].jailTurns=0;
                        continue;
                    }

                    printf("%s moves from Square %d to Square %d\n",players[j].name,oldPosition,players[j].currentPosition);
                    printf("%s lands on %s\n",players[j].name,board[players[j].currentPosition].name);
                    if(players[j].currentPosition==10)
                    {
                        printf("(Just visiting Jail)\n");
                    }
                    handleLandLanding(&players[j],&board[players[j].currentPosition],players);

                    if (players[j].currentPosition < oldPosition)
                    {
                        printf(BOLD_GREEN"\n Passing GO \n"RESET);
                        printf("\n%s is passed GO.\n",players[j].name);
                        printf("Collected LKR 2,000.00\n");
                        players[j].cash+=2000.0;
                        players[j].hasPassedGo = 1;//mark that player passed Go
                        printf("Current Balance : LKR %.2lf\n",players[j].cash);    
                    }                
                }
                else // (if inJail==1)free from jail
                {
                    players[j].jailTurns++;
                    if(players[j].jailTurns==4)
                    {
                        printf(BOLD_YELLOW"\n Free From Jail \n"RESET);
                        printf("%s rolled %d and %d\n",players[j].name,d1,d2);
                    }
                    if(d1==d2 && players[j].jailTurns<=3)//if rolling doubles
                    {
                        printf(BOLD_RED"\n Jail turn %d\n"RESET,players[j].jailTurns);
                        printf("%s rolled %d and %d\n",players[j].name,d1,d2);

                        printf(YELLOW"%s rolled DOUBLES and free from JAIL!\n"RESET,players[j].name);
                        players[j].inJail = 0;
                        players[j].jailTurns =0;
                        //move player after roll doubles
                        int oldPosition = players[j].currentPosition;
                        players[j].currentPosition=(oldPosition+diesTotal)%TileSize;
                        printf(BOLD_GREEN"\n Player Movement \n"RESET);
                        printf("%s moves from Square %d to Square %d\n", players[j].name, oldPosition, players[j].currentPosition);
                        printf("%s lands on %s\n", players[j].name, board[players[j].currentPosition].name);
                        
                        handleLandLanding(&players[j],&board[players[j].currentPosition],players);

                        players[j].hasPassedGo = 1;//for round complete
                    }
                    else if(players[j].jailTurns>3)//if remain imprisoned for 3 turns
                    {
                        printf(YELLOW"%s completed 3 turns in Jail and has beed released from Jail\n"RESET,players[j].name);
                        players[j].inJail = 0 ;
                        players[j].jailTurns = 0; 
                        //move player
                        int oldPosition = players[j].currentPosition;
                        players[j].currentPosition=(oldPosition+diesTotal)%TileSize;
                        printf(BOLD_GREEN"\n Player Movement \n"RESET);
                        printf("%s moves from Square %d to Square %d\n", players[j].name, oldPosition, players[j].currentPosition);
                        printf("%s lands on %s\n", players[j].name, board[players[j].currentPosition].name);
    
                        handleLandLanding(&players[j],&board[players[j].currentPosition],players);

                        players[j].hasPassedGo = 1;//for round complete
                    }
                    else
                    {
                        printf(BOLD_RED"\n Jail turn %d\n"RESET,players[j].jailTurns);
                        printf("%s rolled %d and %d\n",players[j].name,d1,d2);

                        printf(RED"%s failed to roll doubles and remains in Jail.\n"RESET,players[j].name);
                        players[j].hasPassedGo = 1; //not to stuck round
                    }

                }
            }
        }
        diesRollRound++;

        int playersPassedGo = 0;
        int activePlayersCount = 0;
        for(int k =0;k<Maxplayers;k++)
        {
            if(players[k].isBankrupt != 1)
            {
                activePlayersCount++;//get active player count
                if(players[k].hasPassedGo == 1 || players[k].inJail==1)
                {
                    playersPassedGo++;
                }
            }
        }

        if(playersPassedGo==activePlayersCount && activePlayersCount>0)
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