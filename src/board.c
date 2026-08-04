//Board initializeation and movement logic
#include <stdio.h>
#include <string.h>
#include "../headerFiles/declaraction.h"   

landProperties *initializeBoard()
{
    double purchasePrice[MAX_ROWS];
    double baseRents[MAX_ROWS];

    int totalRows = landData(purchasePrice,baseRents);
    /*
    printf("\n---- Successfully Stored and Returned Data ----\n");
    
    for (int i = 0; i < totalRows; i++) {
        printf("%d. Purchase Price: %lf | Base Rent: %lf\n", i, purchasePrice[i], baseRents[i]);
    }
    */

    static landProperties board[TileSize];
    //land Propeties
                        //brown
    board[Pettah]=(landProperties){.name="Pettah",.purchasePrice=purchasePrice[0],.baseRental=baseRents[0],.currentOwner=-1,.cGroup=G_BROWN};
    board[Maradhana]=(landProperties){.name="Maradhana",.purchasePrice=purchasePrice[1],.baseRental=baseRents[1],.currentOwner=-1,.cGroup=G_BROWN};
                        //light blue
    board[Bambalapitiya]=(landProperties){.name="Bambalapitiya",.purchasePrice=purchasePrice[2],.baseRental=baseRents[2],.currentOwner=-1,.cGroup=G_LIGHT_BLUE};
    board[Wellawatta]=(landProperties){.name="Wellawatta",.purchasePrice=purchasePrice[3],.baseRental=baseRents[3],.currentOwner=-1,.cGroup=G_LIGHT_BLUE};
    board[MountLavinia]=(landProperties){.name="MountLavinia",.purchasePrice=purchasePrice[4],.baseRental=baseRents[4],.currentOwner=-1,.cGroup=G_LIGHT_BLUE};
                        //pink
    board[Nugegoda]=(landProperties){.name="Nugegoda",.purchasePrice=purchasePrice[5],.baseRental=baseRents[5],.currentOwner=-1,.cGroup=G_PINK};
    board[Maharagama]=(landProperties){.name="Maharagama",.purchasePrice=purchasePrice[6],.baseRental=baseRents[6],.currentOwner=-1,.cGroup=G_PINK};
    board[Kottawa]=(landProperties){.name="Kottawa",.purchasePrice=purchasePrice[7],.baseRental=baseRents[7],.currentOwner=-1,.cGroup=G_PINK};
                        //orange
    board[Negombo]=(landProperties){.name="Negombo",.purchasePrice=purchasePrice[8],.baseRental=baseRents[8],.currentOwner=-1,.cGroup=G_ORANGE};
    board[Katunayake]=(landProperties){.name="Katunayake",.purchasePrice=purchasePrice[9],.baseRental=baseRents[9],.currentOwner=-1,.cGroup=G_ORANGE};
    board[JaEla]=(landProperties){.name="Ja-Ela",.purchasePrice=purchasePrice[10],.baseRental=baseRents[10],.currentOwner=-1,.cGroup=G_ORANGE};
                        //red
    board[Kandy]=(landProperties){.name="Kandy",.purchasePrice=purchasePrice[11],.baseRental=baseRents[11],.currentOwner=-1,.cGroup=G_RED};
    board[Peradeniya]=(landProperties){.name="Peradeniya",.purchasePrice=purchasePrice[12],.baseRental=baseRents[12],.currentOwner=-1,.cGroup=G_RED};
    board[Katugasthota]=(landProperties){.name="Katugasthota",.purchasePrice=purchasePrice[13],.baseRental=baseRents[13],.currentOwner=-1,.cGroup=G_RED};
                        //yellow
    board[GalleFort]=(landProperties){.name="Galle Fort",.purchasePrice=purchasePrice[14],.baseRental=baseRents[14],.currentOwner=-1,.cGroup=G_YELLOW};
    board[Unawatuna]=(landProperties){.name="Unawatuna",.purchasePrice=purchasePrice[15],.baseRental=baseRents[15],.currentOwner=-1,.cGroup=G_YELLOW};
    board[Hikkaduwa]=(landProperties){.name="Hikkaduwa",.purchasePrice=purchasePrice[16],.baseRental=baseRents[16],.currentOwner=-1,.cGroup=G_YELLOW}; 
                        //green
    board[Jaffna]=(landProperties){.name="Jaffna",.purchasePrice=purchasePrice[17],.baseRental=baseRents[17],.currentOwner=-1,.cGroup=G_GREEN};
    board[Nallur]=(landProperties){.name="Nallur",.purchasePrice=purchasePrice[18],.baseRental=baseRents[18],.currentOwner=-1,.cGroup=G_GREEN};
    board[Trincomalee]=(landProperties){.name="Trincomalee",.purchasePrice=purchasePrice[19],.baseRental=baseRents[19],.currentOwner=-1,.cGroup=G_GREEN};
                        //darkblue
    board[NuwaraEliya]=(landProperties){.name="NuwaraEliya",.purchasePrice=purchasePrice[20],.baseRental=baseRents[20],.currentOwner=-1,.cGroup=G_DARK_BLUE};
    board[GalleFace]=(landProperties){.name="Galle Face",.purchasePrice=purchasePrice[21],.baseRental=baseRents[21],.currentOwner=-1,.cGroup=G_DARK_BLUE};

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
/*
    for (int i = 0; i < TileSize; i++) {
        printf("%d. Purchase Price: %lf | Base Rent: %lf\n", i, board[i].purchasePrice, board[i].baseRental);
    }*/

    return board;
}
void gameCountCounter(Player *players,int *currentRound,int *activePlayersList,int *activePlayersCount)
{
    int minRound = players[activePlayersList[0]].roundCount;
    for(int i=1;i<*activePlayersCount;i++)
    {
        if(players[activePlayersList[i]].roundCount<minRound)
        {
            minRound=players[activePlayersList[i]].roundCount;
        }
    }
    if(minRound>*currentRound)
    {
        *currentRound=minRound;
        printf(BOLD_BLUE"\n====================== ROUND %d END ======================\n"RESET,*currentRound);
    }
}
void handleLandLanding(Player *player, landProperties *property, Player *playerlist,landProperties *board)
{
    displayLandDetails(player,property);
    if(property->currentOwner>0)
    {
        payRent(player,property,playerlist,board);
    }
    else
    {
        buyProperty(player,property,playerlist);
    }
    printf(BLUE"#############balance %f\n"RESET,player->cash);
}
void playerMovement(Player *players,landProperties *board)
{
    int currentRound = 0;
    int diesRollRound = 1;
    for(int i=0;i<Maxplayers;i++)
    {
        players[i].roundCount=0;
    }
    
    printf(BOLD_BLUE"\n\n========================== GAME BEGINS ==========================\n"RESET);

    while(currentRound<RoundCount)//round limit
    {
        printf(BOLD_YELLOW"\n\t\tDIES ROLL ROUND %d\n"RESET,diesRollRound);

        for (int j=0;j<Maxplayers;j++)
        {
            if(players[j].isBankrupt==FALSE)// check player bankrupt
            {
                int d1,d2;
                int diesTotal = rollDies(&d1,&d2);
                
                if(players[j].inJail==FALSE)//move player if not in jail
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
                        players[j].inJail = TRUE;
                        players[j].jailTurns=0;
                        continue;
                    }

                    printf("%s moves from Square %d to Square %d\n",players[j].name,oldPosition,players[j].currentPosition);
                    printf("%s lands on %s\n",players[j].name,board[players[j].currentPosition].name);
                    if(players[j].currentPosition==10)
                    {
                        printf("(Just visiting Jail)\n");
                    }
                    handleLandLanding(&players[j],&board[players[j].currentPosition],players,board);

                    if (players[j].currentPosition < oldPosition)
                    {
                        printf(BOLD_GREEN"\n Passing GO \n"RESET);
                        printf("\n%s is passed GO.\n",players[j].name);
                        printf("Collected LKR %.2f\n",GO_MONEY);
                        players[j].cash+=GO_MONEY;
                        players[j].roundCount++;
                        printf("Current Balance : LKR %.2lf\n",players[j].cash);   
                        printf(BOLD_RED"##########player round %d\n"RESET,players[j].roundCount); 
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
                        players[j].inJail = FALSE;
                        players[j].jailTurns =0;
                        //move player after roll doubles
                        int oldPosition = players[j].currentPosition;
                        players[j].currentPosition=(oldPosition+diesTotal)%TileSize;
                        printf(BOLD_GREEN"\n Player Movement \n"RESET);
                        printf("%s moves from Square %d to Square %d\n", players[j].name, oldPosition, players[j].currentPosition);
                        printf("%s lands on %s\n", players[j].name, board[players[j].currentPosition].name);
                        
                        handleLandLanding(&players[j],&board[players[j].currentPosition],players,board);
                        if(players[j].roundCount<currentRound)
                        {
                            players[j].roundCount=currentRound;
                        }
                    }
                    else if(players[j].jailTurns>3)//if remain imprisoned for 3 turns
                    {
                        printf(YELLOW"%s completed 3 turns in Jail and has beed released from Jail\n"RESET,players[j].name);
                        players[j].inJail = FALSE ;
                        players[j].jailTurns = 0; 
                        //move player
                        int oldPosition = players[j].currentPosition;
                        players[j].currentPosition=(oldPosition+diesTotal)%TileSize;
                        printf(BOLD_GREEN"\n Player Movement \n"RESET);
                        printf("%s moves from Square %d to Square %d\n", players[j].name, oldPosition, players[j].currentPosition);
                        printf("%s lands on %s\n", players[j].name, board[players[j].currentPosition].name);
    
                        handleLandLanding(&players[j],&board[players[j].currentPosition],players,board);
                        if(players[j].roundCount<currentRound)
                        {
                            players[j].roundCount=currentRound;
                        }
                    }
                    else
                    {
                        printf(BOLD_RED"\n Jail turn %d\n"RESET,players[j].jailTurns);
                        printf("%s rolled %d and %d\n",players[j].name,d1,d2);

                        printf(RED"%s failed to roll doubles and remains in Jail.\n"RESET,players[j].name);
                    }
                }
            }
            int activePlayersCount = 0;
            int activePlayerList[Maxplayers];

            for(int k =0;k<Maxplayers;k++)
            {
                if(players[k].isBankrupt ==FALSE && players[k].inJail==FALSE)
                {
                    activePlayerList[activePlayersCount]=k;
                    activePlayersCount++;//get active player count
                }
            }
            if(activePlayersCount>0)
            {
                gameCountCounter(players,&currentRound,activePlayerList,&activePlayersCount);
                if(currentRound>=RoundCount)
                {
                    break;
                }
            }
        }
        diesRollRound++;      
    }
}

