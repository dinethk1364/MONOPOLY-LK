//Game controler and eimulation engine
#include <stdio.h>
#include <stdlib.h>
#include "../headerFiles/declaraction.h"
Player* createPlayers()//return array in Player data type
{
    //static is use to keep array in memory always
    static Player playersList[Maxplayers]={
        {.id=1,.name="Aggressive Investor",.cash=30000.0,.inJail = FALSE,.isBankrupt=FALSE},
        {.id=2,.name="Conservative Banker",.cash=30000.0,.inJail = FALSE,.isBankrupt=FALSE},
        {.id=3,.name="Risk Taker",.cash=30000.0,.inJail = FALSE,.isBankrupt=FALSE},
        {.id=4,.name="Opportunistic Trader",.cash=30000.0,.inJail = FALSE,.isBankrupt=FALSE}//turn order is save in this array
    };
    return playersList;
}
int rollDies(int *die1,int *die2)
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
        playerRolls[i]=rollDies(&d1,&d2);
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
        tempRollVal[i]=rollDies(&d1,&d2);
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
void buyProperty(Player *player, landProperties *property)
{
    if(property->currentOwner==-1)
    {
        int shouldBuy = FALSE; //TRUE(1)=Buy , FALSE(0)= dont buy
        switch(player->id)
        {
            case 1:
            {
                double tempFutureRent = 250.00;////// tempary value
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
                shouldBuy = FALSE;
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
                printf(RED"Not enough cash to buy\n"RESET);
            }
        }
        else
        {
            printf(YELLOW"\n%s decided to not to buy\n"RESET,player->name);
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
                    printf("Reciver cash after: %.2f\n",playerlist[i].cash);// for testing
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