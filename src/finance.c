#include<stdio.h>
#include"../headerFiles/declaraction.h"

void calPropertyValue(landProperties *property,double marketCondition)
{
    if(property->type!=nonProperty)
    {
        property->propertyValue=property->purchasePrice*marketCondition;
    }
    else{
        property->propertyValue=0;
    }
}
void calMortgageValue(landProperties *property,double marketcondition)
{
    calPropertyValue(property,marketcondition);
    property->mortgagePrice = property->propertyValue*0.5;
}

void incomeTax(Player *player, double marketCondition)
{
    double taxRate = 0.15*marketCondition;
    double taxAmount = player->cash*taxRate;

    player->cash -= taxAmount;
    printf(BOLD_GREEN"\n Tax Payment\n"RESET);
    printf(RED"%s paid Income Tax: LKR %'.f (Rate: %.1f%%)\n"RESET,player->name,taxAmount,taxRate*100);
    printf("Remaining Balance: LKR %'.f\n", player->cash);
}

void communityDevFund(Player *player,Player playerlist[],landProperties board[],double marketCondition)
{
    double totalAssets = player->cash;
    for(int i=0;i<TileSize;i++)
    {
        if(board[i].currentOwner==player->id && board[i].type != nonProperty)
        {
            calPropertyValue(&board[i],marketCondition);
            totalAssets+=board[i].propertyValue;
        }
    }
    double taxRate = 0.10*marketCondition;
    double taxAmount = totalAssets * taxRate;

    player->cash -= taxAmount;
    printf(BOLD_GREEN"\n Tax Payment\n"RESET);
    printf(RED"%s paid Community Development Fund Tax: LKR %'.f (Rate: %.1f%%)\n"RESET,player->name,taxAmount,taxRate*100);
    printf("Total Assets: LKR %'.f\n",totalAssets);

    //check bankrupt
    if(player->cash >= 0)
    {
        printf("Remaining Balance: LKR %'.f\n", player->cash);
    }
    else
    {
        printf(RED"\n%s doesn't have enough money to pay TAX! Bankrupt Risk!\n"RESET,player->name);
        Bankrupt(player,playerlist,board,marketCondition);
    }
}
