//Game controler and simulation engine
#include <stdio.h>
#include <stdlib.h>

#include "../headerFiles/declaration.h"
Player* createPlayers()//return array in Player data type
{
    //static is use to keep array in memory always
    static Player playersList[Maxplayers]={
        {.id=1,.name="Aggressive Investor",.cash=PLAYER_STARTING_CASH,.inJail = FALSE,.isBankrupt=FALSE,.hadDamage=FALSE},
        {.id=2,.name="Conservative Banker",.cash=PLAYER_STARTING_CASH,.inJail = FALSE,.isBankrupt=FALSE,.hadDamage=FALSE},
        {.id=3,.name="Risk Taker",.cash=PLAYER_STARTING_CASH,.inJail = FALSE,.isBankrupt=FALSE,.hadDamage=FALSE},
        {.id=4,.name="Opportunistic Trader",.cash=PLAYER_STARTING_CASH,.inJail = FALSE,.isBankrupt=FALSE,.hadDamage=FALSE}//turn order is save in this array
    };
    return playersList;
}
int rollDice(int *die1,int *die2)
{
    *die1 = (rand()%6)+1;
    *die2 = (rand()%6)+1;
    return (*die1) + (*die2);
}
void playersDieRoll(Player players[])
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
void tieBreaker(Player players[],int start,int end)
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
void detTurnOrder(Player players[])
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
void auctionProperty(Player playerlist[],landProperties *property,landProperties board[])
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
                case AGG_INVESTER:
                {
                    int countInGroup = propertiesCountofGroup(board,property->cGroup,playerlist[i].id);
                    if(countInGroup>0)
                    {
                        shouldBid = TRUE;
                        break;
                    }
                    shouldBid = aggInvDecisions(cuurentBidder,*property,AUCTION_MAX_BID_DECISION,proposedBid);
                    break;
                }
                case CONS_BANKER:
                {
                    shouldBid = consBanDecisions(cuurentBidder,*property,AUCTION_MAX_BID_DECISION,proposedBid);
                    break;
                }
                case RISK_TAKER:
                {
                    shouldBid = riskTakDecisions(cuurentBidder,*property,AUCTION_MAX_BID_DECISION,proposedBid);
                    break;
                }
                case OPP_TRADER:
                {
                    shouldBid = oppTraDecisions(cuurentBidder,*property,proposedBid,0,0,AUCTION_MAX_BID_DECISION);
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
        printf(GREEN"\n%s wins the auction\n"RESET,playerlist[winningPlayer].name);
        printf(GREEN"%s bought %s for LKR : %d\n"RESET,playerlist[winningPlayer].name,property->name,highestBid);
        printf(BOLD_GREEN"\n--------------------------------------------------------\n"RESET);
    }
}
void buyProperty(Player *player, landProperties *property,Player playerList[],landProperties board[])
{
    if(property->currentOwner==-1)
    {
        int shouldBuy = FALSE; //TRUE(1)=Buy , FALSE(0)= dont buy
        switch(player->id)
        {
            case AGG_INVESTER:
            {
                double futureRent = 500;

                //prioritize completing property groups
                int countInGroup = propertiesCountofGroup(board,property->cGroup,player->id);
                if(countInGroup>0) futureRent=0;

                shouldBuy=aggInvDecisions(player,*property,BUY_PROPERTY_DECISION,futureRent);
                break;
            }
            case CONS_BANKER:
            {
                shouldBuy=consBanDecisions(player,*property,BUY_PROPERTY_DECISION,0);
                break;
            }
            case RISK_TAKER:
            {
                shouldBuy=riskTakDecisions(player,*property,BUY_PROPERTY_DECISION,0);
                break;
            }
            case OPP_TRADER:
            {
                economicState *mkt = getActiveGovReg();
                //if land have dynamic marketboom appreciation rate 20%
                double appreciationRate=0.0;
                if(mkt->activeBoomGroup == property->cGroup)
                    appreciationRate=0.20;
                else appreciationRate=0.10;

                double projectAppreciation = property->propertyValue * appreciationRate;
                
                shouldBuy=oppTraDecisions(player,*property,projectAppreciation,0,0,BUY_PROPERTY_DECISION);
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
                auctionProperty(playerList,property,board);
            }
        }
        else
        {
            printf(YELLOW"\n%s decided to not to buy\n"RESET,player->name);
            
            //dicided not to but send to auction
            auctionProperty(playerList,property,board);
        }
    }
}
int hasMonopoly(landProperties board[],int playerId, int colorGroup)
{
    int landCountInCGroup=0;
    int playerOwnedLands=0;

    for (int i=0; i<TileSize; i++)
    {
        if(board[i].type==land && board[i].cGroup==colorGroup)
        {
            landCountInCGroup++;
            
            if(board[i].currentOwner==playerId)
            {
                playerOwnedLands++;
            }      
        }
    }
    if(landCountInCGroup>0 && landCountInCGroup==playerOwnedLands)
    {
        return TRUE;
    }
    return FALSE;
}

int getMinHouses(landProperties board[], int colorGroup)
{
    int minHouses = 4;
    for (int i=0;i<TileSize;i++)
    {
        if(board[i].type==land && board[i].cGroup == colorGroup)
        {
            int currentHouses = 0;
            if(board[i].noOfHotels>0)
                currentHouses = 4;// if have hotel consider as 4 houses
            else
                currentHouses = board[i].noOfHouses;
            
            if(currentHouses<minHouses)
                minHouses=currentHouses;            
        }
    }
    return minHouses;
}

void updateLandRent(landProperties *property)
{
    if(property->type!=land) return;

    if(property->currentOwner<=0)
    {
        property->currentRent=0;
        return;
    }

    int multiplier = 1;

    if(property->noOfHotels>0)
    {
        multiplier=10;
    }
    else
    {
        switch(property->noOfHouses)
        {
            case 0:
                multiplier=1;
                break;
            case 1:
                multiplier=2;
                break;
            case 2:
                multiplier=3;
                break;
            case 3:
                multiplier=5;
                break;
            case 4:
                multiplier=7;
                break;
        }
    }
    property->currentRent=property->baseRental*multiplier;
}

void buildHouses(Player *player, landProperties board[])
{
    if (player->activeCard == LABOUR_STRIKE && player->roundCount < player->eventExpiryRound)
    {
        printf(RED "Construction suspended due to active Labour Strike!\n" RESET);
        return;
    }
    int header1Print =FALSE;// print header only once
    int header2Print =FALSE;// print header only once

    for(int colorGroup =G_DARK_BLUE; colorGroup>=G_BROWN;colorGroup--)//check all color groups
    {
        if(hasMonopoly(board,player->id,colorGroup)==TRUE)
        {   
            int controlLoop =TRUE;//run loop until out of money
            while(controlLoop)
            {
                controlLoop=FALSE;
                int minHouses = getMinHouses(board,colorGroup);

                for(int i=0;i<TileSize;i++)//check all lands in color group
                {
                    if(board[i].type==land && board[i].cGroup==colorGroup && board[i].currentOwner==player->id)
                    {
                        if(board[i].noOfHotels==0 && board[i].noOfHouses<4 && board[i].noOfHouses==minHouses)
                        {
                            int buildDecision = FALSE;

                            switch (player->id)
                            {
                            case AGG_INVESTER:
                                buildDecision=aggInvDecisions(player,board[i],BUILD_HOUSE_DECISION,board[i].houseCost);
                                break;
                            case CONS_BANKER:
                                buildDecision=consBanDecisions(player,board[i],BUILD_HOUSE_DECISION,board[i].houseCost);
                                break;
                            case RISK_TAKER:
                                buildDecision=riskTakDecisions(player,board[i],BUILD_HOUSE_DECISION,board[i].houseCost);
                                break;
                            case OPP_TRADER:
                                buildDecision=oppTraDecisions(player,board[i],board[i].houseCost,0,0,BUILD_HOUSE_DECISION);
                                break;                        
                            default:
                                break;
                            }

                            if(buildDecision==TRUE)
                            {
                                player->cash-= board[i].houseCost;
                                board[i].noOfHouses++;
                                
                                updateLandRent(&board[i]);

                                if(!header1Print)
                                {
                                    printf(BOLD_GREEN"\n Building Construction \n\n"RESET);
                                    header1Print=TRUE;
                                }
                                printf(GREEN"%s is constructed one house on %s. \n"RESET,player->name,board[i].name);
                                printf(GREEN"Construction cost: LKR %'.f\n"RESET,board[i].houseCost);

                                controlLoop=TRUE;
                                break;
                                // minHouses = getMinHouses(board,colorGroup);//update minhouse after build house
                            }
                        }
                        else if(board[i].noOfHouses==4 && board[i].noOfHotels==0 && minHouses==4)
                        {
                            int buildDecision = FALSE;
                            switch (player->id)
                            {
                            case AGG_INVESTER:
                                buildDecision=aggInvDecisions(player,board[i],BUILD_HOUSE_DECISION,board[i].hotelCost);
                                break;
                            case CONS_BANKER:
                                buildDecision=consBanDecisions(player,board[i],BUILD_HOUSE_DECISION,board[i].hotelCost);
                                break;
                            case RISK_TAKER:
                                buildDecision=riskTakDecisions(player,board[i],BUILD_HOUSE_DECISION,board[i].hotelCost);
                                break;
                            case OPP_TRADER:
                                buildDecision=oppTraDecisions(player,board[i],board[i].hotelCost,0,0,BUILD_HOUSE_DECISION);
                                break;                        
                            default:
                                break;
                            }

                            if(buildDecision==TRUE)
                            {
                                player->cash-= board[i].hotelCost;
                                board[i].noOfHouses=0;
                                board[i].noOfHotels=1;

                                updateLandRent(&board[i]);

                                if(!header2Print)
                                {
                                    printf(BOLD_GREEN"\n HOTEL Construction \n\n"RESET);
                                    header2Print=TRUE;
                                }
                                printf(YELLOW"%s upgraded %s to a Hotel.\n"RESET,player->name,board[i].name);
                                printf(YELLOW"Construction cost: LKR %'.f\n"RESET,board[i].hotelCost);

                                controlLoop=TRUE;
                                break;
                                // minHouses = getMinHouses(board,colorGroup);//update minhouse after build house
                            }
                        }
                    }
                }
            }
        }
    }
    if (header1Print == TRUE || header2Print==TRUE)
    {
        printf("\nRemaining Cash: LKR %'.f\n", player->cash);
    }
}

int hasBuildings(landProperties board[], int colorGroup)
{
    for(int i=0;i<TileSize;i++)
    {
        if(board[i].type==land && board[i].cGroup==colorGroup)
        {
            if(board[i].noOfHouses>0 || board[i].noOfHotels>0)
            {
                return TRUE;// cannot mortgage if have houses of hotels
            }
        }
    }
    return FALSE;
}

int propertiesCountofGroup(landProperties board[],int colorGroup, int playerId)// get count of owned lands i color group
{
    int count =0;
    for(int i=0;i<TileSize;i++)
    {
        if(board[i].type== land && board[i].cGroup==colorGroup && board[i].currentOwner==playerId)
        {
            count++;
        }
    }
    return count;
}
void transferPlayerAssetsToBank(Player *player , landProperties board[])
{
    for(int i=0;i<TileSize;i++)
    {
        if(board[i].currentOwner==player->id)
        {
            board[i].currentOwner = -1;
            board[i].noOfHouses= 0;
            board[i].noOfHotels=0;
            board[i].buildingCondition = 100.0;
            board[i].isDamage =FALSE;
            board[i].isStucturalDamaged = FALSE;

            board[i].mortgageStatus=FALSE;
            board[i].insuaranceType=0;
            board[i].InsuranceStatus=FALSE;
            board[i].insuaranceRounds=0;

            board[i].currentRent = board[i].baseRental;

            printf(GREEN"\n%s trasferred to the bank and all developments have been removed\n"RESET,board[i].name);
        }
    }
}

void Bankrupt(Player *player,Player playerlist[],landProperties board[],double marketConsition)
{
    if(player->cash <0)
    {
        printf(YELLOW "\nLow on cash! mortgaging properties\n" RESET);

        while(player->cash<0)
        {
            int best=-1;
            int priority = 999;
            double price = 999999999.0;

            for(int i=0;i<TileSize;i++)
            {
                if(board[i].currentOwner==player->id && board[i].mortgageStatus==FALSE && board[i].isLoanLocked==FALSE)
                {
                    if(board[i].type==land && hasBuildings(board,board[i].cGroup)==TRUE)//skip constructed lands
                    {
                        continue;
                    }
                    int groupCount = propertiesCountofGroup(board,board[i].cGroup,player->id);
                    int isMonopoly = hasMonopoly(board,player->id,board[i].cGroup);

                    int currentpriority=3;
                    if(isMonopoly==FALSE && groupCount==1)//mortgage first single land in colog group
                        currentpriority=1;
                    else if(isMonopoly==FALSE&& groupCount>1)
                        currentpriority=2;

                    if(currentpriority<priority || (currentpriority==priority&& board[i].propertyValue < price))
                    {
                        priority = currentpriority;
                        price = board[i].propertyValue;
                        best = i;
                    }
                }
            }
            if(best == -1)//repeat untill not have property to morgage
            {
                break;;
            }

            mortgageProperty(player,board,&board[best],marketConsition);
            printf(RED"\n%s is mortgaged and receive LKR %'.f\n"RESET,board[best].name,board[best].mortgagePrice);
        }
    }

    if(player->cash<0)
    {
        player->isBankrupt=TRUE;
        
        printf(BOLD_GREEN"\n Bankruptcy \n"RESET);

        printf(RED"\n%s is BANKRUPT and eliminated form the game!\n"RESET,player->name);
        
        //Transferring the bankrupt players properties to the bank
        transferPlayerAssetsToBank(player,board);

        gameOver(playerlist,board);
    }
    else
    {
        printf("Remaining Balance: LKR %'.f\n",player->cash);
    }
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

        //gov regulations
        economicState *reg = getActiveGovReg();
        if (reg->activeReg == REG_RAILWAY_MODERNIZATION)
        {
            property->currentRent *= 1.25;
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
        //gov regulations
        economicState *reg = getActiveGovReg();
        if (reg->activeReg == REG_ELECTRICITY_TARIFF)
        {
            property->currentRent *= 1.20;
        }
    }
}
void payRent(Player *player,landProperties *property,Player playerlist[],landProperties board[])
{
    if(property->currentOwner>0 && property->currentOwner!=player->id)
    {
        if(property->mortgageStatus==TRUE)
        {
            printf(YELLOW "\n%s is MORTGAGED! No rent collected.\n" RESET, property->name);
            return;
        }
        if(property->isDamage==TRUE)
        {
            printf(YELLOW "\n%s is DAMAGED! No rent collected.\n" RESET, property->name);
            return;
        }

        double multiplier = rentMultiplier(property);//acording to building condition

        if(multiplier == 0.0)
        {
            printf(RED "\nBuilding on is CLOSED due to severe condition (<25%%)! No rent collected.\n" RESET);
            return;
        }

        double rentAmount = property->currentRent * multiplier; 
        printf(BOLD_GREEN"\n Paying Rent \n"RESET);

        player->cash -= rentAmount;
        for(int i=0;i<Maxplayers;i++)
        {
            if(playerlist[i].id==property->currentOwner)
            {
                //printf("Receiver cash before: %'.f\n",playerlist[i].cash);// for testing
                playerlist[i].cash += rentAmount;
                printf("Rent Paid to %s : LKR %'.f\n",playerlist[i].name,rentAmount);
                // printf("Receiver cash after: %'.f\n",playerlist[i].cash);// for testing
            }
        }
        
        if(player->cash >= 0)
        {
            printf("Remaining Balance : LKR %'.f\n",player->cash);
        }
        else
        {
            printf(RED "\n%s doesn't have enough money to pay RENT! Bankrupt Risk!\n" RESET, player->name);
            Bankrupt(player, playerlist, board,1);//martket condition is 1 temapryily
        }
    }
}
void propertyDepreciation(landProperties board[])
{
    for(int i=0;i<TileSize;i++)
    {
        if(board[i].type!=nonProperty)
        {
            board[i].age++;
            if(board[i].age>50 && board[i].age%5==0)
            {
                double minPropertyValue =board[i].purchasePrice*0.70;
                if(board[i].propertyValue>minPropertyValue)
                {
                    board[i].propertyValue *= 0.99;//depreciate by 1%
                }
            }
        }
    }
}

void renovateProperty(Player *player,landProperties *property)
{
    if(property->currentOwner == player->id && property->age>50)
    {
        double renovationCost = property->propertyValue*0.10;

        if(player->cash >= renovationCost)
        {
            player->cash-=renovationCost;
            property->age=0;
            property->propertyValue = property->purchasePrice;
            printf(BOLD_GREEN"\n PROPERTY RENOVATION\n" RESET);
            printf(YELLOW"%s renovated %s for LKR %'.f!\n"RESET, player->name, property->name, renovationCost);
        }
    }
}
void buildingCondition(landProperties board[],Player playerlist[])
{
    for(int i=0;i<TileSize;i++)
    {
        if(board[i].type==land && (board[i].noOfHouses>0 || board[i].noOfHotels>0))
        {
            if(board[i].buildingCondition>0)
            {
                board[i].buildingCondition-=2.0;
                if(board[i].buildingCondition<0) board[i].buildingCondition=0;
            }
            board[i].unmaintaindRounds++;

            //in maintainance ignored for more than 20 rounds
            if(board[i].unmaintaindRounds>20 && board[i].isStucturalDamaged==FALSE)
            {
                board[i].isStucturalDamaged=TRUE;
                board[i].propertyValue*=0.85;
                board[i].currentRent*=0.75;

                if(board[i].currentOwner>0)
                {
                    for(int k=0;k<Maxplayers;k++)
                    {
                        if(playerlist[k].id==board[i].currentOwner)
                        {
                            playerlist[k].hadDamage=TRUE;
                            break;
                        }
                    }
                }

                printf("Buildings on %s suffered structural damage due to 20 rounds of neglect!\n", board[i].name);
                printf("Property Value decreased by 15%% and Max Rent reduced by 25%%.\n");
            }
        }
    }
}

double rentMultiplier(landProperties *property)
{
    if(property->noOfHouses>0 || property->noOfHotels>0)
    {
        if(property->buildingCondition>=90.0)
            return 1.0;
        else if(property->buildingCondition>=75.0)
            return 0.90;
        else if(property->buildingCondition>=50.0)
            return 0.75;
        else if(property->buildingCondition>=25.0)
            return 0.50;
        else return 0.0;
    }
    return 1.0;
}

void buildingMaintenance(Player *player,landProperties board[])
{
    int headerprint=FALSE;
    for(int i=0;i<TileSize;i++)
    {
        if(board[i].currentOwner ==player->id && (board[i].noOfHouses>0 || board[i].noOfHotels>0))
        {
            double maintenceCost =0;

            if(board[i].isStucturalDamaged==TRUE)
            {
                double replacementValue;
                if(board[i].noOfHotels>0)
                    replacementValue=board[i].hotelCost;
                else
                    replacementValue=board[i].houseCost*board[i].noOfHouses;
                    
                maintenceCost = replacementValue*0.25;
            }
            else
            {
                if(board[i].noOfHotels>0)
                {
                    maintenceCost=board[i].hotelCost *0.08;
                }
                else
                {
                    maintenceCost = board[i].houseCost * board[i].noOfHouses*0.05;
                }
            }
            int shouldMaintenace =FALSE;
            switch (player->id)
            {
            case AGG_INVESTER:
                shouldMaintenace=aggInvDecisions(player,board[i],MAINTENANCE_DECISION,maintenceCost);
                break;
            case CONS_BANKER:
                shouldMaintenace=consBanDecisions(player,board[i],MAINTENANCE_DECISION,maintenceCost);
                break;
            case RISK_TAKER:
                shouldMaintenace=riskTakDecisions(player,board[i],MAINTENANCE_DECISION,maintenceCost);
                break;
            case OPP_TRADER:
                shouldMaintenace=oppTraDecisions(player,board[i],maintenceCost,0,0,MAINTENANCE_DECISION);
                break;                        
            default:
                break;
            }

            if(shouldMaintenace==TRUE)
            {
                if(headerprint==FALSE)
                {
                    printf(BOLD_GREEN"\n BUILDING RENOVATION\n" RESET);
                    headerprint=TRUE;
                }
                if(board[i].isStucturalDamaged==TRUE)
                {
                    if(player->cash >= maintenceCost)
                    {
                        player->cash-= maintenceCost;
                        board[i].buildingCondition = 100.0;
                        board[i].unmaintaindRounds = 0;
                        board[i].isStucturalDamaged = FALSE;
                        board[i].propertyValue /= 0.85; 
                        board[i].currentRent /= 0.75;
                        printf("%s renovated structural damage on %s for LKR %'.f!\n", player->name, board[i].name, maintenceCost);
                    }
                }
                else
                {
                    if(player->cash >= maintenceCost)
                    {
                        player->cash -= maintenceCost;
                        board[i].buildingCondition = 100.0;
                        board[i].unmaintaindRounds = 0;
                        printf("%s performed building maintenance on %s for LKR %'.f!\n", player->name, board[i].name, maintenceCost);
                    }
                }
            }
        }
    }
}

void calculateNetWorth(Player *player, landProperties board[])
{
    double total = player->cash;

    for (int i = 0; i < TileSize; i++)
    {
        if (board[i].currentOwner == player->id)
        {
            if (board[i].mortgageStatus == FALSE)
            {
                total += board[i].propertyValue;

                if (board[i].noOfHouses > 0)
                {
                    total += board[i].noOfHouses * board[i].houseCost;
                }
                if (board[i].noOfHotels > 0)
                {
                    total += board[i].hotelCost;
                }
            }
        }
    }

    //loans
    if (player->activeLoan.isActive == TRUE)
    {
        total -= player->activeLoan.currentLoanAmount;
    }

    player->netWorth = total;
}

int checkGameOver(Player playerlist[])
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
void gameOver(Player playerlist[],landProperties board[])
{
    if(checkGameOver(playerlist)==TRUE)
    {
        printf(BOLD_GREEN"\n3 Players have been bankrupt. The game has ended ! \n"RESET);

        for(int i=0;i<Maxplayers;i++)
        {
            if(playerlist[i].isBankrupt==FALSE)
            {
                displayGameOver(&playerlist[i],board);
            }
        }
        exit(0);//exit the game
    }
}
void gameRun()
{
    printGameBegins();
    Player *playersList = createPlayers();//get array and assign values 

    printf("\n-----DETERMINING THE FIRST PLAYER-----\n\n");
    landProperties *board = initializeBoard();
    playersDieRoll(playersList);

    // playersList[0].dieRollValue = 7;
    // playersList[1].dieRollValue = 7;
    // playersList[2].dieRollValue = 7;
    // playersList[3].dieRollValue = 7;

    detTurnOrder(playersList);
    playerMovement(playersList,board);

}