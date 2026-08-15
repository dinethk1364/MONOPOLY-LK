#include <stdio.h>
#include <stdlib.h>
#include "../headerFiles/declaraction.h"

ActiveGovRegulation *getActiveGovReg()
{
    static ActiveGovRegulation currentReg = {NO_REGULATION, 0};
    return &currentReg;
}

void clearPreviousRegulation(landProperties board[])
{
    ActiveGovRegulation *reg = getActiveGovReg();
    if (reg->activeReg == NO_REGULATION) return;

    switch (reg->activeReg)
    {
        case REG_HOUSING_SUBSIDY:
            for (int i = 0; i < TileSize; i++)
            {
                if (board[i].type == land) board[i].houseCost /= 0.70;
            }
            break;

        case REG_RAILWAY_MODERNIZATION:
            for (int i = 0; i < TileSize; i++)
            {
                if (board[i].type == railway) board[i].currentRent /= 1.25;
            }
            break;

        case REG_ELECTRICITY_TARIFF:
            for (int i = 0; i < TileSize; i++)
            {
                if (board[i].type == utility) board[i].currentRent /= 1.20;
            }
            break;

        default:
            break;
    }

    reg->activeReg = NO_REGULATION;
}

void processGovernmentRegulations(int currentRound, landProperties board[], Player playerlist[])
{
    if (currentRound > 0 && currentRound % 20 == 0)
    {
        clearPreviousRegulation(board); //clear previous regulation

        ActiveGovRegulation *reg = getActiveGovReg();
        GovRegulation selectedReg = (GovRegulation)(rand() % 8);
        reg->activeReg = selectedReg;
        reg->activeRound = currentRound;

        printf(BOLD_GREEN "\n Government Regulations" RESET);

        switch (selectedReg)
        {
            case REG_INCREASE_PROPERTY_TAX:
                printf(YELLOW "Increase Property Tax.\n" RESET);
                printf("-Income Tax increased by 50%%.\n");
                break;

            case REG_REDUCE_LOAN_INTEREST:
                printf(YELLOW "Reduce Loan Interest.\n" RESET);
                printf("-Loan interest reduced by 2%%.\n");
                break;

            case REG_HOUSING_SUBSIDY:
                for (int i = 0; i < TileSize; i++)
                {
                    if (board[i].type == land) board[i].houseCost *= 0.70;
                }
                printf(YELLOW "Housing Subsidy.\n" RESET);
                printf("-Construction costs reduced by 30%%.\n");
                break;

            case REG_LUXURY_PROPERTY_TAX:
                printf(YELLOW "Luxury Property Tax.\n" RESET);
                printf("-Hotels incur a 25%% tax of property value.\n");
                
                for (int i = 0; i < TileSize; i++)
                {
                    if (board[i].type == land && board[i].noOfHotels > 0 && board[i].currentOwner > 0)
                    {
                        double tax = board[i].propertyValue * 0.25;
                        for (int j = 0; j < Maxplayers; j++)
                        {
                            if (playerlist[j].id == board[i].currentOwner && playerlist[j].isBankrupt == FALSE)
                            {
                                if(playerlist[j].cash>=tax)
                                {
                                    playerlist[j].cash -= tax;
                                    printf("%s paid LKR %'.f Luxury Tax for Hotel on %s.\n", playerlist[j].name, tax, board[i].name);
                                }
                                else
                                {
                                    Bankrupt(&playerlist[j],playerlist,board,mktCond);
                                }
                            }
                        }
                    }
                }
                break;

            case REG_RAILWAY_MODERNIZATION:
                for (int i = 0; i < TileSize; i++)
                {
                    if (board[i].type == railway) board[i].currentRent *= 1.25;
                }
                printf(YELLOW "Railway Modernization.\n" RESET);
                printf("-Railway rents increased by 25%%.\n");
                break;

            case REG_ELECTRICITY_TARIFF:
                for (int i = 0; i < TileSize; i++)
                {
                    if (board[i].type == utility) board[i].currentRent *= 1.20;
                }
                printf(YELLOW "Electricity Tariff Revision.\n" RESET);
                printf("-Utility rents increased by 20%%.\n");
                break;

            case REG_INSURANCE_REGULATION:
                printf(YELLOW "Insurance Regulation.\n" RESET);
                printf("-Insurance premiums reduced by 15%%.\n");
                break;

            case REG_ANTI_SPECULATION:
                printf(YELLOW "Anti-Speculation Act.\n" RESET);
                printf("-Players may own at most 3 undeveloped properties.\n");
                break;

            default:
                break;
        }
    }
}