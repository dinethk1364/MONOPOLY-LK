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
    for(int i=0;i<Maxplayers-1;i++)
    {
        if(players[i].dieRollValue==players[i+1].dieRollValue)
        {
            int tiedPlayers[2]={i,i+1};

            tieBreaker(tiedPlayers,2,players);

            if(players[i].dieRollValue<players[i+1].dieRollValue)
            {
                Player temp=players[i];
                players[i]=players[i+1];
                players[i+1]=temp;
            }
        }
    }
    printf("\n%s will begin the game.\n\n",players[0].name);
    printf("Turn Order:\n");
    for(int i=0;i<Maxplayers;i++)
    {
        printf("%s\n",players[i].name);
    }
}
void gameFunctions()
{
    gameBegins();

    Player *playersList = createPlayers();//get array and assign values 

    printf("\n-----DETERMINEING THE FIRST PLAYER-----\n\n");
    
    playersDieRoll(playersList);

    detTurnOrder(playersList);
}