#include <stdio.h>
#include "../headerFiles/types.h"
#include <locale.h>

void printGameBegins()
{
    setlocale(LC_NUMERIC,"");
    printf("\033[31mMONOPOLY-LK Simulation\033[0m\n\n");
    printf("\033[33mPlayer 1 : Aggressive Investor\033[0m\n");
    printf("\033[32mPlayer 2 : Conservative Banker\033[0m\n");
    printf("\033[34mPlayer 3 : Risk Taker\033[0m\n");
    printf("\033[36mPlayer 4 : Opportunistic Trader\033[0m\n\n");
    printf("Each player begins with LKR %.2f\n",PLAYER_STARTING_CASH);
}

void displayLandDetails(Player *player,landProperties *property)
{
    printf("\n================ PROPERTY DETAILS ================\n");
    if(property->currentOwner==-1)
    {
        printf("Status          : Unowned (Available to Buy)\n");
        printf("Purcase Price   : LKR %.2f\n",property->purchasePrice);
    }
    else if (property->currentOwner==0)
    {
        printf("Status          : Non-purchasable Property (Cannot be bought)\n");
    }
    else
    {
        if(player->id==property->currentOwner)
        {
            printf("This property is belongs to you\n");
        }
        else
        { 
            //get owner name
            int ownerID = property->currentOwner;
            const char *ownerName = "Unknown";
            switch(ownerID)
            {
                case 1:
                    ownerName = "Aggressive Investor";
                    break;
                case 2:
                    ownerName = "Conservative Banker";
                    break;
                case 3:
                    ownerName = "Risk Taker";
                    break;
                case 4:
                    ownerName = "Opportunistic Trader";
                    break;
                default:
                    ownerName = "Unknown Player";
                    break;
            }
            printf("Status          : Owned by %s\n",ownerName);
            printf("Current Rent    : LKR %.2f\n",property->currentRent);
            
        }
    }
}
