//Game controler and eimulation engine
#include <stdio.h>
#include <stdlib.h>

#include "../headerFiles/declaraction.h"
Player* createPlayers()//return array in Player data type
{
    //static is use to keep array in memory always
    static Player playersList[Maxplayers]={
        {.id=1,.name="Aggressive Investor",.cash=PLAYER_STARTING_CASH,.inJail = FALSE,.isBankrupt=FALSE},
        {.id=2,.name="Conservative Banker",.cash=PLAYER_STARTING_CASH,.inJail = FALSE,.isBankrupt=FALSE},
        {.id=3,.name="Risk Taker",.cash=PLAYER_STARTING_CASH,.inJail = FALSE,.isBankrupt=FALSE},
        {.id=4,.name="Opportunistic Trader",.cash=PLAYER_STARTING_CASH,.inJail = FALSE,.isBankrupt=FALSE}//turn order is save in this array
    };
    return playersList;
}
int rollDice(int *die1,int *die2)
{
    *die1 = (rand()%6)+1;
    *die2 = (rand()%6)+1;
    return (*die1) + (*die2);
}
void playersDieRoll(Player *players)
{
    int playerRolls[Maxplayers];
    
    for(int i=0;i<Maxplayers;i++)
    {
        int d1,d2;
        playerRolls[i]=rollDice(&d1,&d2);
        printf("%s rolls %d\n",players[i].name,playerRolls[i]);
        players[i].dieRollValue=playerRolls[i];
    }
}
void tieBreaker(Player *players,int start,int end)
{
    if(start>=end)//base case(if exit only 1 player break the recursion)
    {
        return;
    }
    printf("\n------ TIE DETECTED ------\n");

    int tempRollVal[Maxplayers];

    for(int i=start;i<=end;i++)// reroll tie players
    {
        int d1,d2;
        tempRollVal[i]=rollDice(&d1,&d2);
        printf("%s rerolls %d\n",players[i].name,tempRollVal[i]);
    }
    // sorting reroll value array
    for(int i=start;i<end;i++)
    {
        for(int j=start;j<end;j++)
        {
            if(tempRollVal[j]<tempRollVal[j+1])
            {
                //swap temp roll values
                int temp = tempRollVal[j];
                tempRollVal[j]=tempRollVal[j+1];
                tempRollVal[j+1]=temp;
                //swap players(if dont swap players names are not changing)
                Player tempP = players[j];
                players[j]=players[j+1];
                players[j+1]=tempP;
            }
        }
    }
    //check ties after reroll
    int nStart = start;
    while(nStart<end)
    {
        int nEnd=nStart;
        while(nEnd+1<=end)
        {
            if(tempRollVal[nEnd+1]==tempRollVal[nStart])
            {
                nEnd++;
            }else
                break;
        }
        if(nEnd>nStart)//check if there is a tie
        {
            tieBreaker(players,nStart,nEnd);//recursion call
        }
        nStart = nEnd+1;
    }
}
void detTurnOrder(Player *players)
{
    for(int i=0;i<Maxplayers-1;i++)//bubble sort(sort max roll value to min)
    {
        for(int j=0;j<Maxplayers-i-1;j++)
        {
            if(players[j].dieRollValue<players[j+1].dieRollValue)
            {
                Player temp =players[j];
                players[j]=players[j+1];
                players[j+1]=temp;
            }
        }
    }
    int i=0;
    while(i<Maxplayers-1)
    {
        int j=i;
        while(j+1<Maxplayers)
        {
            if(players[j+1].dieRollValue==players[i].dieRollValue)
            {
                j++;
            }
            else
                break;
        }
        if(j>i)
        {
            tieBreaker(players,i,j);
            i=j+1;
        }
        else
        {
            i++;
        }
    }
    printf("\n%s will begin the game.\n\n",players[0].name);
    printf("Turn Order:\n");
    for(int i=0;i<Maxplayers;i++)
    {
        printf("%s\n",players[i].name);
    }
}
void auctionProperty(Player *playerlist,landProperties *property)
{
    printf(BOLD_YELLOW"\n================== Property Auction ==================\n"RESET);
    printf("Base Purchase Price: LKR %'.f\n",property->purchasePrice*0.5);

    int highestBid=0;
    int winningPlayer = -1;
    int activeBidders = 0;

    int droppedFromAuction[Maxplayers];// to track the remain players in auction
    for(int i=0;i<Maxplayers;i++)
    {
        if(playerlist[i].isBankrupt==FALSE)
        {
            droppedFromAuction[i]=FALSE;
            activeBidders++;
        }
        else droppedFromAuction[i] = TRUE;
    }

    while(activeBidders>1)//bid until remain only one player
    {
        int placedBids=0;
        for(int i=0;i<Maxplayers;i++)
        {
            if(droppedFromAuction[i]==TRUE || playerlist[i].isBankrupt == TRUE)
                continue;

            Player *cuurentBidder = &playerlist[i];
            int shouldBid = FALSE;
            int proposedBid = 0;

            if(highestBid==0)
                proposedBid = property->purchasePrice*0.5;
            else    
                proposedBid = highestBid+250;

            switch(cuurentBidder->id)
            {
                case 1:
                {
                    shouldBid = aggInvDecisions(cuurentBidder,*property,AUCTION_MAX_BID_DECISION,proposedBid);
                    break;
                }
                case 2:
                {
                    shouldBid = aggInvDecisions(cuurentBidder,*property,AUCTION_MAX_BID_DECISION,proposedBid);
                    break;
                }
                case 3:
                {
                    shouldBid = aggInvDecisions(cuurentBidder,*property,AUCTION_MAX_BID_DECISION,proposedBid);
                    break;
                }
                case 4:
                {
                    shouldBid = aggInvDecisions(cuurentBidder,*property,AUCTION_MAX_BID_DECISION,proposedBid);
                    break;
                }
            }

            if(shouldBid==FALSE || cuurentBidder->cash <proposedBid)
            {
                printf(RED"%s is dropped out of the auction!\n"RESET,cuurentBidder->name);
                droppedFromAuction[i]=TRUE;
                activeBidders--;
            }
            else{
                highestBid = proposedBid;
                winningPlayer = i;
                placedBids++;
                printf(GREEN"%s bids LKR %d\n"RESET,cuurentBidder->name,highestBid);
            }
            if(activeBidders<=1) break;
        }
        
        if(activeBidders<=1) break;// for safty

        if(placedBids ==0)
        {
            printf(YELLOW"No Players are willing to bid, Auction ended.\n"RESET);
            break;
        }
    }

    //select winner
    if(winningPlayer!= -1 && highestBid >0)
    {
        playerlist[winningPlayer].cash -= highestBid;
        property->currentOwner = playerlist[winningPlayer].id;
        property->currentRent = property->baseRental;

        printf(BOLD_GREEN"\n--------------------------------------------------------\n"RESET);
        printf(GREEN"\n\n%s wins the auction\n"RESET,playerlist[winningPlayer].name);
        printf(GREEN"%s bought %s for LKR : %d\n"RESET,playerlist[winningPlayer].name,property->name,highestBid);
        printf(BOLD_GREEN"\n--------------------------------------------------------\n"RESET);
    }
}
void buyProperty(Player *player, landProperties *property,Player *playerList)
{
    if(property->currentOwner==-1)
    {
        int shouldBuy = FALSE; //TRUE(1)=Buy , FALSE(0)= dont buy
        switch(player->id)
        {
            case 1:
            {
                double tempFutureRent = 50.00;////// tempary value
                shouldBuy=aggInvDecisions(player,*property,BUY_PROPERTY_DECISION,tempFutureRent);
                break;
            }
            case 2:
            {
                shouldBuy=consBanDecisions(player,*property,BUY_PROPERTY_DECISION);
                break;
            }
            case 3:
            {
                shouldBuy=riskTakDecisions(player,*property,BUY_PROPERTY_DECISION);
                break;
            }
            case 4:
            {
                //uses agginv stratagies temraraly
                double tempFutureRent = 250.00;////// tempary value
                shouldBuy=aggInvDecisions(player,*property,BUY_PROPERTY_DECISION,tempFutureRent);
                break;
            }
        }
        if(shouldBuy==TRUE)
        {
            if(player->cash>=property->purchasePrice)
            {
                property->currentOwner=player->id;
                player->cash -= property->purchasePrice;
                property->currentRent=property->baseRental;//update current rent
                printf(BOLD_GREEN"\n Purchasing Property \n"RESET);
                printf(GREEN"\n%s purchased %s for LKR %'.f\n"RESET,player->name,property->name,property->purchasePrice);
                printf("Remaining Balance : LKR %'.f\n",player->cash);
            }
            else
            {
                printf(RED"Not enough cash to buy, Sending to auction!\n"RESET);
                
                //not enough cash send to auction
                auctionProperty(playerList,property);
            }
        }
        else
        {
            printf(YELLOW"\n%s decided to not to buy\n"RESET,player->name);
            
            //dicided not to but send to auction
            auctionProperty(playerList,property);
        }
    }
}
void Bankrupt(Player *player,Player *playerlist,landProperties *properties)
{
    //sell properties or mortgage
    player->isBankrupt=TRUE;
    
    printf(BOLD_GREEN"\n Bankruptcy \n"RESET);

    printf(RED"\n%s is BANKRUPT and eliminated form the game!\n"RESET,player->name);
    //Transferring the bankrupt players properties to the bank
    for(int i=0;i<TileSize;i++)
    {
        if(properties[i].currentOwner==player->id)
        {
            properties[i].currentOwner = -1;
            properties[i].noOfHouses= 0;
            properties[i].noOfHotels=0;
            printf(GREEN"\n%s trasferred to the bank and all buildings have been removed\n"RESET,properties[i].name);
        }
    }
    gameOver(playerlist);
}
int countOwnedRailway(int ownerId, landProperties board[])
{
    int count = 0;
    for(int i=0;i<TileSize;i++)
    {
        if(board[i].type==railway && board[i].currentOwner==ownerId)
        {
            count++;
        }
    }
    return count;
}
int countOwnedUtility(int ownerId, landProperties board[])
{
    int count =0;
    for(int i=0;i<TileSize;i++)
    {
        if(board[i].type==utility && board[i].currentOwner==ownerId)
        {
            count++;
        }
    }
    return count;
}
void updateRailwayRent(landProperties *property, landProperties board[])
{
    if(property->type==railway && property->currentOwner >0)
        {
        int ownerId = property->currentOwner;
        int ownedRailway = countOwnedRailway(ownerId,board);

        switch(ownedRailway)
        {
            case 1:
                property->currentRent = 250.0;
                break;
            case 2:
                property->currentRent = 500.0;
                break;
            case 3:
                property->currentRent = 1000.0;
                break;
            case 4:
                property->currentRent = 2000.0;
                break;
        }
    }
}
void updateUtilityRent(landProperties *property,landProperties board[],int diceRoll)
{
    if(property->type==utility && property->currentOwner>0)
    {
        int ownerId = property->currentOwner;
        int ownedUtilities = countOwnedUtility(ownerId,board);

        switch (ownedUtilities)
        {
        case 1:
            property->currentRent = 4*diceRoll;
            break;
        
        case 2:
            property->currentRent = 10*diceRoll;
            break;
        }
    }
}
void payRent(Player *player,landProperties *property,Player *playerlist,landProperties *properties)
{
    if(property->currentOwner>0 && property->currentOwner!=player->id)
    {
        double rentAmount = property->currentRent; 
        printf(BOLD_GREEN"\n Paying Rent \n"RESET);
        if(player->cash >= rentAmount)
        {
            player->cash -= rentAmount;
            for(int i=0;i<Maxplayers;i++)
            {
                if(playerlist[i].id==property->currentOwner)
                {
                    //printf("Reciver cash before: %'.f\n",playerlist[i].cash);// for testing
                    playerlist[i].cash += rentAmount;
                    printf("Rent Paid to %s : LKR %'.f\n",playerlist[i].name,property->currentRent);
                    // printf("Reciver cash after: %'.f\n",playerlist[i].cash);// for testing
                }
            }
            printf("Remaining Balance : LKR %'.f\n",player->cash);
        }
        else
        {
            printf(RED"\n%s doesn't have enough money to pay! Bankrupt Risk!\n"RESET,player->name);
            Bankrupt(player,playerlist,properties);
        }
    }
}

int checkGameOver(Player *playerlist)
{
    int bankruptCount = 0;
    for(int i=0;i<Maxplayers;i++)
    {
        if(playerlist[i].isBankrupt==TRUE)
        {
            bankruptCount++;
        }
    }
    if(bankruptCount==3)
    {
        return TRUE;
    }
    return FALSE;
}
void gameOver(Player *playerlist)
{
    if(checkGameOver(playerlist)==TRUE)
    {
        printf(BOLD_GREEN"\n3 Players have been bankrupt. The game has ended ! \n"RESET);

        for(int i=0;i<Maxplayers;i++)
        {
            if(playerlist[i].isBankrupt==FALSE)
            {
                displayGameOver(&playerlist[i]);
            }
        }
        exit(0);//exit the game
    }
}
void gameRun()
{
    printGameBegins();
    Player *playersList = createPlayers();//get array and assign values 

    printf("\n-----DETERMINEING THE FIRST PLAYER-----\n\n");
    landProperties *board = initializeBoard();
    playersDieRoll(playersList);

    // playersList[0].dieRollValue = 7;
    // playersList[1].dieRollValue = 7;
    // playersList[2].dieRollValue = 7;
    // playersList[3].dieRollValue = 7;

    detTurnOrder(playersList);
    playerMovement(playersList,board);

}