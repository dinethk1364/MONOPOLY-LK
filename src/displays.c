#include <stdio.h>
#include "../headerFiles/declaraction.h"

void printGameBegins()
{
    printf("\033[31mMONOPOLY-LK Simulation\033[0m\n\n");
    printf("\033[33mPlayer 1 : Aggressive Investor\033[0m\n");
    printf("\033[32mPlayer 2 : Conservative Banker\033[0m\n");
    printf("\033[34mPlayer 3 : Risk Taker\033[0m\n");
    printf("\033[36mPlayer 4 : Opportunistic Trader\033[0m\n\n");
    printf("Each player begins with LKR %'.f\n",PLAYER_STARTING_CASH);
}

void displayLandDetails(Player *player,landProperties *property,landProperties board[])
{
    printf("\n===================== PROPERTY DETAILS =====================\n\n");

    if(property->currentOwner==-1)
    {
        printf("Status          : Unowned (Available to Buy)\n");
        printf("Purcase Price   : LKR %'.f\n",property->purchasePrice);
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
            printf("Current Rent    : LKR %'.f\n",property->currentRent);
            
        }
    }
    printf("\n\n------------------------------------------------------------\n");
}

void endOfTheRounds(Player* players, int roundCount,landProperties board[])
{
    printf(BOLD_YELLOW"\n===========================================================\n"RESET);
    printf(BOLD_YELLOW"                       Round %d Summary"RESET,roundCount);
    printf(BOLD_YELLOW"\n===========================================================\n"RESET);

    for (int i = 0; i < Maxplayers; i++)
    {
        if(players[i].isBankrupt==TRUE)
        {
            printf("\n%s\n",players[i].name);
            printf(RED"\nBankrupt\n"RESET);
            printf(BOLD_YELLOW"\n-----------------------------------------------------------\n"RESET);        
        }
        else
        {
            int propCount = 0;
            int hotelCount = 0;
            int houseCount = 0;

            for (int j = 0; j < TileSize; j++)
            {
                if (board[j].currentOwner == players[i].id)
                {
                    propCount++;
                    if (board[j].noOfHotels > 0)
                    {
                        hotelCount += board[j].noOfHotels;
                    }
                    if (board[j].noOfHouses > 0)
                    {
                        houseCount += board[j].noOfHouses;
                    }
                }
            }
            
            double loanValue=0.0;
            if(players[i].activeLoan.isActive == TRUE)
                loanValue=players[i].activeLoan.currentLoanAmount;
           
            printf("\n%s\n",players[i].name);
            printf("\nCash : LKR %'.f\n",players[i].cash);

            calculateNetWorth(&players[i],board);
            printf("\nNet Worth : LKR %'.f\n",players[i].netWorth);
            printf("\nProperties : %d\n",propCount);
            printf("\nHotels : %d\n",hotelCount);
            printf("\nHouses : %d\n",houseCount);
            printf("\nOutstanding Loan : LKR %'.f\n",loanValue);
            printf(BOLD_YELLOW"\n-----------------------------------------------------------\n"RESET);
        }        
    } 
}
const char *getColorGroupName(colorGroup group)
{
    switch (group)
    {
        case G_BROWN: return "Brown (Pettah, Maradana)";
        case G_LIGHT_BLUE: return "Light Blue (Bambalapitiya, Wellawatta, Mount Lavinia)";
        case G_PINK: return "Pink (Maharagama, Nugegoda, Kottawa)";
        case G_ORANGE: return "Orange (Negombo, Katunayake, Ja-Ela)";
        case G_RED: return "Red (Kandy City, Peradeniya, Katugastota)";
        case G_YELLOW: return "Yellow (Galle Fort, Unawatuna, Hikkaduwa)";
        case G_GREEN: return "Green (Jaffna Town, Nallur, Trincomalee)";
        case G_DARK_BLUE: return "Dark Blue (Nuwara Eliya, Galle Face)";
        default: return "None";
    }
}

void displayMarketConditions(double currentLoanInterest, double currentInflation)
{
    economicState *mkt = getActiveGovReg();

    printf(BOLD_GREEN "\n===========================================================\n" RESET);
    printf(BOLD_GREEN "                Current Market Conditions        \n" RESET);
    printf(BOLD_GREEN "===========================================================\n\n" RESET);

    printf("Market Boom\n-------------\n");
    if (mkt->activeBoomGroup > 0 && mkt->boomRoundsRemaining > 0)
    {
        printf("%s (+20%%)\n", getColorGroupName(mkt->activeBoomGroup));
        printf("Rounds Remaining : %d\n", mkt->boomRoundsRemaining);
    }
    else
    {
        printf("None\n");
    }

    printf("\nMarket Decline\n----------------\n");
    if (mkt->activeDeclineGroup > 0 && mkt->declineRoundsRemaining > 0)
    {
        printf("%s (-15%%)\n", getColorGroupName(mkt->activeDeclineGroup));
        printf("Rounds Remaining : %d\n", mkt->declineRoundsRemaining);
    }
    else
    {
        printf("None\n");
    }

    printf("\nInflation\n------------\n");
    printf("%+.0f%%\n", currentInflation * 100.0);

    printf("\nCurrent Loan Interest\n-----------------------\n");
    printf("%.0f%%\n", currentLoanInterest * 100.0);
    printf(BOLD_GREEN "===========================================================\n\n" RESET);
}

void displayGameOver(Player *player,landProperties board[])
{
    double totalPropertyValue = 0.0;
    for(int i=0;i<TileSize;i++)
    {
        if(board[i].currentOwner==player->id)
        {
            totalPropertyValue+=board[i].propertyValue;
            if(board[i].noOfHouses>0)
                totalPropertyValue += board[i].noOfHouses * board[i].houseCost;
            if (board[i].noOfHotels > 0)
                totalPropertyValue += board[i].hotelCost;
        }
    }
    double outstandingLoan = 0.0;
    if (player->activeLoan.isActive == TRUE)
    {
        outstandingLoan = player->activeLoan.currentLoanAmount;
    }
    int propCount = 0;
    int hotelCount = 0;
    int houseCount = 0;
    for (int j = 0; j < TileSize; j++)
    {
        if (board[j].currentOwner == player->id)
        {
            propCount++;
            if (board[j].noOfHotels > 0)
            {
                hotelCount += board[j].noOfHotels;
            }
            if (board[j].noOfHouses > 0)
            {
                houseCount += board[j].noOfHouses;
            }
        }
    }

    printf(BOLD_RED"\n===========================================================\n"RESET);
    printf(BOLD_RED"                         End of Game!                     "RESET);
    printf(BOLD_RED"\n===========================================================\n"RESET);

    printf("\nGAME OVER\n");
    printf("\nWinner                : %s\n",player->name);
    printf("\nTotal Cash            : LKR %'.f\n",player->cash);
    printf("\nTotal Property Value  : LKR %'.f\n",totalPropertyValue);
    printf("\nProperties            : %d\n",propCount);
    printf("\nHotels                : %d\n",hotelCount);
    printf("\nHouses                : %d\n",houseCount);
    printf("\nOutstanding Loans     : LKR %'.f\n",outstandingLoan);
    printf("\nNet Worth             : LKR %'.f\n",player->netWorth);

    printf(BOLD_RED"\n===========================================================\n"RESET);

}
