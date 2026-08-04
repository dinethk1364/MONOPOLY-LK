#include<stdio.h>
#include"../headerFiles/declaraction.h"

void auctionProperty(Player *playerlist,landProperties *property)
{
    printf(BOLD_YELLOW"\n================== Property Auction ==================\n"RESET);
    printf("Base Purchase Price: LKR %.2f\n",property->purchasePrice*0.5);

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
        printf(BLUE"\n%f #######cash of the winner before auction\n"RESET,playerlist[winningPlayer].cash);

        playerlist[winningPlayer].cash -= highestBid;
        property->currentOwner = playerlist[winningPlayer].id;
        property->currentRent = property->baseRental;

        printf(BOLD_GREEN"\n--------------------------------------------------------\n"RESET);
        printf(GREEN"\n\n%s wins the auction\n"RESET,playerlist[winningPlayer].name);
        printf(GREEN"%s bought %s for LKR : %d\n"RESET,playerlist[winningPlayer].name,property->name,highestBid);
        printf(BLUE"\n%f #######remain cash of the winner \n"RESET,playerlist[winningPlayer].cash);
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
                printf(GREEN"\n%s purchased %s for LKR %.2f\n"RESET,player->name,property->name,property->purchasePrice);
                printf("Remaining Balance : LKR %.2f\n",player->cash);
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
    printf(RED"\n%s doesn't have enough money to pay! Bankrupt Risk!\n"RESET,player->name);
    //sell properties or mortgage
    player->isBankrupt=TRUE;
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
                    //printf("Reciver cash before: %.2f\n",playerlist[i].cash);// for testing
                    playerlist[i].cash += rentAmount;
                    printf("Rent Paid to %s : LKR %.2f\n",playerlist[i].name,property->currentRent);
                    // printf("Reciver cash after: %.2f\n",playerlist[i].cash);// for testing
                }
            }
            printf("Remaining Balance : LKR %.2f\n",player->cash);
        }
        else
        {
            Bankrupt(player,playerlist,properties);
        }
    }
}
