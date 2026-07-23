//Game controler and eimulation engine
#include <stdio.h>
#include <stdlib.h>
#include "declaraction.h"   
#include "types.h"
Player* createPlayers()
{
    //static is use to keep array in memory always
    static Player playersList[Maxplayers]={
        {1,"Aggressive Investor",30000.0,0,0},
        {2,"Conservative Banker",30000.0,0,0},
        {3,"Risk Taker",30000.0,0,0},
        {4,"Opportunistic Trader",30000.0,0,0}
    };
    return playersList;
}
int rollDies(int *die1,int *die2)
{
    *die1 = (rand()%6)+1;
    *die2 = (rand()%6)+1;
    return (*die1) + (*die2);
}
int playersDieRoll(Player *players)
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
void detFirstPlayer(Player *players)
{
    int highestRollValue=players[0].dieRollValue;
    int firstPlayerIndex=0;
    for(int i=1;i<Maxplayers;i++)
    {
        if(highestRollValue<players[i].dieRollValue)
        {
            highestRollValue=players[i].dieRollValue;
            firstPlayerIndex=i;
        }
    }
    int tieCount=0;
    int tiedPlayers[Maxplayers];
    for(int i=0;i<Maxplayers;i++)
    {
        if(players[i].dieRollValue==highestRollValue)
        {
            tiedPlayers[tieCount]=i;
            tieCount++;
        }
    }
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
        highestRollValue = players[tiedPlayers[0]].dieRollValue;
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

    firstPlayerIndex = tiedPlayers[0];
    printf("\n%s will begin the game\n\n",players[firstPlayerIndex].name);
}
void gameFunctions()
{
    gameBegins();
    int d1,d2;
    rollDies(&d1,&d2);

    Player *playersList = createPlayers();//get array and assign values 

    printf("\n-----DETERMINEING THE FIRST PLAYER-----\n\n");
    
    playersDieRoll(playersList);

    detFirstPlayer(playersList);
}