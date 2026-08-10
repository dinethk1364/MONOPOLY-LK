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

void mortgageProperty(Player *player,landProperties board[],landProperties *property,double marketcondition)
{
    if(property->currentOwner == player->id && property->mortgageStatus==FALSE)
    {
        if(property->type == land && hasBuildings(board,property->cGroup)==TRUE)
        {
            printf(RED"Cannot mortgage %s! property has buildings.\n"RESET,property->name);
        }
        else
        {
            calMortgageValue(property,marketcondition);//update property value
            property->mortgageStatus=TRUE;
            property->currentRent=0;//mortgage properties cannot collect rent
            player->cash+=property->mortgagePrice;

            printf(BOLD_GREEN "\n Property Mortgaged \n" RESET);
            printf(GREEN "%s mortgaged %s for LKR %'.f\n" RESET, player->name, property->name, property->mortgagePrice);
            printf("Updated Cash Balance: LKR %'.f\n", player->cash);
        }
    }
}

void unmortgageProperty(Player *player, landProperties board[])
{   
    for(int i=0;i<TileSize;i++)
    {        
        if(board[i].currentOwner==player->id && board[i].mortgageStatus==TRUE)
        {
            int shouldUnmortgage = FALSE;

            switch(player->id)
            {
                case AGG_INVESTER:
                    shouldUnmortgage = aggInvDecisions(player, board[i],UNMORTGAGE,2000);
                    break;
                case CONS_BANKER:
                    shouldUnmortgage = aggInvDecisions(player, board[i],UNMORTGAGE,2000);
                    break;
                case RISK_TAKER:
                    shouldUnmortgage = aggInvDecisions(player, board[i],UNMORTGAGE,2000);
                    break;
                case OPP_TRADER:
                    shouldUnmortgage = aggInvDecisions(player, board[i],UNMORTGAGE,2000);
                    break;
                default:
                    shouldUnmortgage = FALSE;
                    break;
            }

            if(shouldUnmortgage==TRUE)
            {
                double unmortgageCost = board[i].mortgagePrice*1.10;//10% interest
                player->cash -= unmortgageCost;
                board[i].mortgageStatus = FALSE;
                updateLandRent(&board[i]);

                printf(BOLD_GREEN"\n Property is Unmortgaged\n"RESET);
                printf(YELLOW"%s unmortgaged %s for LKR %.f\n"RESET, player->name, board[i].name, unmortgageCost);
                printf("Remaining Balance : LKR %.f\n", player->cash);
            }
        }
    }
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
