//Game controler and eimulation engine
#include <stdio.h>
#include <stdlib.h>
#include "declaraction.h"   
#include "types.h"
Player* createPlayers()
{
    //static is use to keep array in memory always
    static Player playersList[Maxplayers]={
        {1,"Aggressive Investor",30000.0,0,0,0},
        {2,"Conservative Banker",30000.0,0,0,0},
        {3,"Risk Taker",30000.0,0,0,0},
        {4,"Opportunistic Trader",30000.0,0,0,0}//turn order is save in this array
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
void tieBreaker(int *tiedPlayers,int tieCount,Player *players)
{
    while(tieCount>1)
    {
        printf("\n------TIE DETECTED------\n\n");
        //roll die of tied players
        for(int i=0;i<tieCount;i++)
        {
            int tieIndex = tiedPlayers[i];
            int d1,d2;
            players[tieIndex].dieRollValue = rollDies(&d1,&d2);
            printf("%s rolls %d\n",players[tieIndex].name,players[tieIndex].dieRollValue);  
        }
        //get highest value after reroll
        int highestRollValue = players[tiedPlayers[0]].dieRollValue;
        for(int i=1;i<tieCount;i++)
        {
            int tieIndex = tiedPlayers[i];
            if(players[tieIndex].dieRollValue>highestRollValue)
            {
                highestRollValue=players[tieIndex].dieRollValue;
            }
        }
        //update tie count
        int newTiedPlayers[Maxplayers];
        int newTieCount=0;
        for(int i=0;i<tieCount;i++)
        {
           int tieIndex=tiedPlayers[i];
           if(players[tieIndex].dieRollValue == highestRollValue)
           {
                newTiedPlayers[newTieCount]=tieIndex;
                newTieCount++;
           }            
        }
        tieCount=newTieCount;
        for(int i=0;i<tieCount;i++)
        {
            tiedPlayers[i]=newTiedPlayers[i];
        }
    }
}
void detTurnOrder(Player *players)
{
    for(int i=0;i<Maxplayers-1;i++)//bubble sort
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
        if(players[i].dieRollValue==players[i+1].dieRollValue)
        {
            int tiedPlayers[Maxplayers];
            int tieCount = 0;
            int targetValue=players[i].dieRollValue;
            
            for(int j=i;j<Maxplayers;j++)
            {
                if(players[j].dieRollValue==targetValue)
                {
                    tiedPlayers[tieCount]=j;
                    tieCount++;
                }
                else
                    break;
            }
            tieBreaker(tiedPlayers,tieCount,players);

            for(int x=0;x<tieCount-1;x++)//bubble sort
            {
                for(int y=i;y<i+tieCount-x-1;y++)
                {
                    if(players[y].dieRollValue<players[y+1].dieRollValue)
                    {
                        Player temp =players[y];
                        players[y]=players[y+1];
                        players[y+1]=temp;
                    }
                }
            }
            i=0;
        }
        else
            i++;
    }
    printf("\n%s will begin the game.\n\n",players[0].name);
    printf("Turn Order:\n");
    for(int i=0;i<Maxplayers;i++)
    {
        printf("%s\n",players[i].name);
    }
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
void gameFunctions()
{
    printf("\033[31mMONOPOLY-LK Simulation\033[0m\n\n");
    printf("\033[33mPlayer 1 : Aggressive Investor\033[0m\n");
    printf("\033[32mPlayer 2 : Conservative Banker\033[0m\n");
    printf("\033[34mPlayer 3 : Risk Taker\033[0m\n");
    printf("\033[36mPlayer 4 : Opportunistic Trader\033[0m\n\n");
    printf("Each player begins with LKR 30,000\n");

    Player *playersList = createPlayers();//get array and assign values 

    printf("\n-----DETERMINEING THE FIRST PLAYER-----\n\n");
    initializeBoard();
    playersDieRoll(playersList);

    // playersList[0].dieRollValue = 6;
    // playersList[1].dieRollValue = 6;
    // playersList[2].dieRollValue = 6;
    // playersList[3].dieRollValue = 6;

    detTurnOrder(playersList);
    playerMovement(playersList);
}