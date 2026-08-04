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
        printf(BOLD_RED"\n===========================================================\n"RESET);
        printf(BOLD_RED"                           GAME OVER !                     "RESET);
        printf(BOLD_RED"\n===========================================================\n"RESET);
        printf(GREEN"\n3 Players have been bankrupt. The game has ended ! \n"RESET);

        for(int i=0;i<Maxplayers;i++)
        {
            if(playerlist[i].isBankrupt==FALSE)
            {
                printf(BOLD_GREEN"\nWinner of the Game: %s\n"RESET,playerlist[i].name);
                printf(BOLD_GREEN"Remaining Cash: LKR %.2f\n"RESET,playerlist[i].cash);
            }
        }
        printf(BOLD_RED"\n===========================================================\n"RESET);
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