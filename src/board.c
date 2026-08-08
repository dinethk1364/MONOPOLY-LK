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
    board[Pettah]=(landProperties){.name="Pettah",.type=land,.purchasePrice=purchasePrice[0],.baseRental=baseRents[0],.currentOwner=-1,.cGroup=G_BROWN,.houseCost=500.0,.hotelCost=2000.0};
    board[Maradhana]=(landProperties){.name="Maradhana",.type=land,.purchasePrice=purchasePrice[1],.baseRental=baseRents[1],.currentOwner=-1,.cGroup=G_BROWN,.houseCost=500.0,.hotelCost=2000.0};
                        //light blue
    board[Bambalapitiya]=(landProperties){.name="Bambalapitiya",.type=land,.purchasePrice=purchasePrice[2],.baseRental=baseRents[2],.currentOwner=-1,.cGroup=G_LIGHT_BLUE,.houseCost=750.0,.hotelCost=3000.0};
    board[Wellawatta]=(landProperties){.name="Wellawatta",.type=land,.purchasePrice=purchasePrice[3],.baseRental=baseRents[3],.currentOwner=-1,.cGroup=G_LIGHT_BLUE,.houseCost=750.0,.hotelCost=3000.0};
    board[MountLavinia]=(landProperties){.name="MountLavinia",.type=land,.purchasePrice=purchasePrice[4],.baseRental=baseRents[4],.currentOwner=-1,.cGroup=G_LIGHT_BLUE,.houseCost=750.0,.hotelCost=3000.0};
                        //pink
    board[Nugegoda]=(landProperties){.name="Nugegoda",.type=land,.purchasePrice=purchasePrice[5],.baseRental=baseRents[5],.currentOwner=-1,.cGroup=G_PINK,.houseCost=1000.0,.hotelCost=4000.0};
    board[Maharagama]=(landProperties){.name="Maharagama",.type=land,.purchasePrice=purchasePrice[6],.baseRental=baseRents[6],.currentOwner=-1,.cGroup=G_PINK,.houseCost=1000.0,.hotelCost=4000.0};
    board[Kottawa]=(landProperties){.name="Kottawa",.type=land,.purchasePrice=purchasePrice[7],.baseRental=baseRents[7],.currentOwner=-1,.cGroup=G_PINK,.houseCost=1000.0,.hotelCost=4000.0};
                        //orange
    board[Negombo]=(landProperties){.name="Negombo",.type=land,.purchasePrice=purchasePrice[8],.baseRental=baseRents[8],.currentOwner=-1,.cGroup=G_ORANGE,.houseCost=1250.0,.hotelCost=5000.0};
    board[Katunayake]=(landProperties){.name="Katunayake",.type=land,.purchasePrice=purchasePrice[9],.baseRental=baseRents[9],.currentOwner=-1,.cGroup=G_ORANGE,.houseCost=1250.0,.hotelCost=5000.0};
    board[JaEla]=(landProperties){.name="Ja-Ela",.type=land,.purchasePrice=purchasePrice[10],.baseRental=baseRents[10],.currentOwner=-1,.cGroup=G_ORANGE,.houseCost=1250.0,.hotelCost=5000.0};
                        //red
    board[Kandy]=(landProperties){.name="Kandy",.type=land,.purchasePrice=purchasePrice[11],.baseRental=baseRents[11],.currentOwner=-1,.cGroup=G_RED,.houseCost=1500.0,.hotelCost=6000.0};
    board[Peradeniya]=(landProperties){.name="Peradeniya",.type=land,.purchasePrice=purchasePrice[12],.baseRental=baseRents[12],.currentOwner=-1,.cGroup=G_RED,.houseCost=1500.0,.hotelCost=6000.0};
    board[Katugasthota]=(landProperties){.name="Katugasthota",.type=land,.purchasePrice=purchasePrice[13],.baseRental=baseRents[13],.currentOwner=-1,.cGroup=G_RED,.houseCost=1500.0,.hotelCost=6000.0};
                        //yellow
    board[GalleFort]=(landProperties){.name="Galle Fort",.type=land,.purchasePrice=purchasePrice[14],.baseRental=baseRents[14],.currentOwner=-1,.cGroup=G_YELLOW,.houseCost=2000.0,.hotelCost=8000.0};
    board[Unawatuna]=(landProperties){.name="Unawatuna",.type=land,.purchasePrice=purchasePrice[15],.baseRental=baseRents[15],.currentOwner=-1,.cGroup=G_YELLOW,.houseCost=2000.0,.hotelCost=8000.0};
    board[Hikkaduwa]=(landProperties){.name="Hikkaduwa",.type=land,.purchasePrice=purchasePrice[16],.baseRental=baseRents[16],.currentOwner=-1,.cGroup=G_YELLOW,.houseCost=2000.0,.hotelCost=8000.0}; 
                        //green
    board[Jaffna]=(landProperties){.name="Jaffna",.type=land,.purchasePrice=purchasePrice[17],.baseRental=baseRents[17],.currentOwner=-1,.cGroup=G_GREEN,.houseCost=2500.0,.hotelCost=10000.0};
    board[Nallur]=(landProperties){.name="Nallur",.type=land,.purchasePrice=purchasePrice[18],.baseRental=baseRents[18],.currentOwner=-1,.cGroup=G_GREEN,.houseCost=2500.0,.hotelCost=10000.0};
    board[Trincomalee]=(landProperties){.name="Trincomalee",.type=land,.purchasePrice=purchasePrice[19],.baseRental=baseRents[19],.currentOwner=-1,.cGroup=G_GREEN,.houseCost=2500.0,.hotelCost=10000.0};
                        //darkblue
    board[NuwaraEliya]=(landProperties){.name="NuwaraEliya",.type=land,.purchasePrice=purchasePrice[20],.baseRental=baseRents[20],.currentOwner=-1,.cGroup=G_DARK_BLUE,.houseCost=3000.0,.hotelCost=12000.0};
    board[GalleFace]=(landProperties){.name="Galle Face",.type=land,.purchasePrice=purchasePrice[21],.baseRental=baseRents[21],.currentOwner=-1,.cGroup=G_DARK_BLUE,.houseCost=3000.0,.hotelCost=12000.0};

    //special properties
    board[ColomboFortRailway]=(landProperties){.name="Colombo Fort Railway",.type=railway ,.purchasePrice=2000.0,.mortgagePrice=1000.0,.baseRental=0,.currentOwner=-1};
    board[CEB]=(landProperties){.name="Ceylon Electricity Board",.type=utility ,.purchasePrice=1500.0,.mortgagePrice=750.0,.baseRental=0,.currentOwner=-1};
    board[KandyRailway]=(landProperties){.name="Kandy Railway Station",.type=railway ,.purchasePrice=2000.0,.mortgagePrice=1000.0,.baseRental=0,.currentOwner=-1};
    board[GalleRailway]=(landProperties){.name="Galle Railway Station",.type=railway ,.purchasePrice=2000.0,.mortgagePrice=1000.0,.baseRental=0,.currentOwner=-1};
    board[WaterBoard]=(landProperties){.name="National Water Board",.type=utility ,.purchasePrice=1500.0,.mortgagePrice=750.0,.baseRental=0,.currentOwner=-1};
    board[JaffnaRailway]=(landProperties){.name="Jaffna Railway Station",.type=railway ,.purchasePrice=2000.0,.mortgagePrice=1000.0,.baseRental=0,.currentOwner=-1};

    //special tiles

    board[GO]=(landProperties){.name="Go",.type=nonProperty ,.currentOwner=0};    
    board[CommunityDevFund]=(landProperties){.name="Community Development Fund",.type=nonProperty ,.currentOwner=0};    
    board[Incometax]=(landProperties){.name="Income Tax",.type=nonProperty ,.currentOwner=0};      
    board[NationalEvent1]=(landProperties){.name="National Event Card",.type=nonProperty ,.currentOwner=0};    
    board[Jail]=(landProperties){.name="Jail",.type=nonProperty ,.currentOwner=0}; 
    board[SrilankaInsurance]=(landProperties){.name="Sri Lanka Insurance",.type=nonProperty ,.currentOwner=0};    
    board[FreeParking]=(landProperties){.name="Free Parking",.type=nonProperty ,.currentOwner=0};    
    board[NationalEvent2]=(landProperties){.name="National Event Card",.type=nonProperty ,.currentOwner=0};
    board[GoToJail]=(landProperties){.name="Go to Jail",.type=nonProperty ,.currentOwner=0};
    board[CeylincoInsurance]=(landProperties){.name="Ceylinco Insurance",.type=nonProperty ,.currentOwner=0};
    board[NationalEvent3]=(landProperties){.name="National Event Card",.type=nonProperty ,.currentOwner=0};
    board[BOC]=(landProperties){.name="Bank of Ceylon",.type=nonProperty ,.currentOwner=0}; 
/*
    for (int i = 0; i < TileSize; i++) {
        printf("%d. Purchase Price: %lf | Base Rent: %lf\n", i, board[i].purchasePrice, board[i].baseRental);
    }*/

    return board;
}
void gameCountCounter(Player players[],int *currentRound,int *activePlayersList,int *activePlayersCount)
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
        endOfTheRounds(players,*currentRound);
    }
}
void handleLandLanding(Player *player, landProperties *property, Player playerlist[],landProperties board[])
{
    updateRailwayRent(property,board);
    updateUtilityRent(property,board,player->dieRollValue);
    displayLandDetails(player,property,board);
    printf(YELLOW"###############dice roll : %d\n"RESET,player->dieRollValue);
    if(property->currentOwner>0)
    {
        payRent(player,property,playerlist,board);
    }
    else if(property->currentOwner == -1)
    {
        buyProperty(player,property,playerlist);
    }
    else
    {
        //special tiles
        if(player->currentPosition==Incometax)
        {
            incomeTax(player,1);
        }
        else if(player->currentPosition==CommunityDevFund)
        {
            communityDevFund(player,playerlist,board,1);
        }
    }
    buildHouses(player,board);
}
void playerMovement(Player players[],landProperties board[])
{
    int currentRound = 0;
    int diceRollRound = 1;
    for(int i=0;i<Maxplayers;i++)
    {
        players[i].roundCount=0;
    }
    
    printf(BOLD_BLUE"\n\n========================== GAME BEGINS ==========================\n"RESET);

    while(currentRound<RoundCount)//round limit
    {
        printf(BOLD_YELLOW"\n\t\tDICE ROLL ROUND %d\n"RESET,diceRollRound);

        for (int j=0;j<Maxplayers;j++)
        {
            if(players[j].isBankrupt==FALSE)// check player bankrupt
            {
                int d1,d2;
                int diceTotal = rollDice(&d1,&d2);
                players[j].dieRollValue = diceTotal;//for utility
                
                if(players[j].inJail==FALSE)//move player if not in jail
                {
                    printf(BOLD_GREEN"\n Dice Roll \n"RESET);
                    printf("%s rolled %d\n",players[j].name,diceTotal);    
                
                    int oldPosition = players[j].currentPosition;
                    players[j].currentPosition = (oldPosition+diceTotal)%TileSize;//use modulus to after passing 40th tile back to 0
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

                    if (players[j].currentPosition < oldPosition)
                    {
                        printf(BOLD_GREEN"\n Passing GO \n"RESET);
                        printf("\n%s is passed GO.\n",players[j].name);
                        printf("Collected LKR %'.f\n",GO_MONEY);
                        players[j].cash+=GO_MONEY;
                        players[j].roundCount++;
                        printf("Current Balance : LKR %'.f\n",players[j].cash);   
                        printf(BOLD_RED"##########player round %d\n"RESET,players[j].roundCount); 
                    }   
                    handleLandLanding(&players[j],&board[players[j].currentPosition],players,board);
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
                        players[j].currentPosition=(oldPosition+diceTotal)%TileSize;
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
                        printf(YELLOW"%s completed 3 turns in Jail and has been released from Jail\n"RESET,players[j].name);
                        players[j].inJail = FALSE ;
                        players[j].jailTurns = 0; 
                        //move player
                        int oldPosition = players[j].currentPosition;
                        players[j].currentPosition=(oldPosition+diceTotal)%TileSize;
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
        diceRollRound++;      
    }
}

