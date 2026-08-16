#include <stdio.h>
#include <stdlib.h>
#include "../headerFiles/declaration.h"

economicState *getActiveGovReg()
{
    static economicState state = {
        .activeReg = NO_REGULATION,
        .activeRound = 0,
        .activeBoomGroup = 0,
        .activeDeclineGroup = 0,
        .boomRoundsRemaining = 0,
        .declineRoundsRemaining = 0,
        .lastAffectedRound = {0},
        .currentInflationRate = 0.0,
        .currentBaseInterest = 0.08 
    };
    return &state;
}

void clearPreviousRegulation(landProperties board[])
{
    economicState *reg = getActiveGovReg();
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
    double mktCond = getCurrentMarketMultiplier();
    if (currentRound > 0 && currentRound % 20 == 0)
    {
        clearPreviousRegulation(board); //clear previous regulation

        economicState *reg = getActiveGovReg();
        GovRegulation selectedReg = (GovRegulation)(rand() % 8);
        reg->activeReg = selectedReg;
        reg->activeRound = currentRound;

        printf(BOLD_GREEN "\n Government Regulations\n" RESET);

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
                                playerlist[j].cash -= tax;

                                if(playerlist[j].cash>=0)
                                {
                                    printf("%s paid LKR %'.f Luxury Tax for Hotel on %s.\n", playerlist[j].name, tax, board[i].name);
                                }
                                else
                                {
                                    printf(RED "%s cannot pay Luxury Tax on %s! Bankrupt Risk!\n" RESET, playerlist[j].name, board[i].name);
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
void clearDynamicMarket(landProperties board[])
{
    economicState *mkt = getActiveGovReg();
    if (mkt->activeBoomGroup > 0)
    {
        for (int i = 0; i < TileSize; i++)
        {
            if (board[i].type == land && board[i].cGroup == mkt->activeBoomGroup)
            {
                board[i].purchasePrice /= 1.15;
                board[i].mortgagePrice /= 1.15;
                board[i].baseRental /= 1.25;
                board[i].currentRent /= 1.25;
                board[i].houseCost /= 1.10;
                board[i].hotelCost /= 1.10;
                board[i].propertyValue /= 1.20;
            }
        }
    }
    if (mkt->activeDeclineGroup > 0)
    {
        for (int i = 0; i < TileSize; i++)
        {
            if (board[i].type == land && board[i].cGroup == mkt->activeDeclineGroup)
            {
                board[i].propertyValue /= 0.85;
                board[i].baseRental /= 0.80;
                board[i].currentRent /= 0.80;
                board[i].mortgagePrice /= 0.90;
            }
        }
    }
    mkt->activeBoomGroup = 0;
    mkt->activeDeclineGroup = 0;
}
void processDynamicMarket(int currentRound, landProperties board[])
{
    if (currentRound > 0 && currentRound % 10 == 0)
    {
        clearDynamicMarket(board);//clear last event

        economicState *mkt = getActiveGovReg();

        int eligibleGroups[8];//get groups which completed 30 round cool down
        int eligibleCount = 0;

        for(int g=G_BROWN;g<=G_DARK_BLUE;g++)
        {
            if(mkt->lastAffectedRound[g]==0 || (currentRound-mkt->lastAffectedRound[g]>=30))
            {
                eligibleGroups[eligibleCount]=g;
                eligibleCount++;
            }
        }
        //if eligible group not enough get all groups
        if (eligibleCount < 2)
        {
            eligibleCount = 0;
            for (int g = G_BROWN; g <= G_DARK_BLUE; g++)
            {
                eligibleGroups[eligibleCount++] = g;
            }
        }

        int boomIdx = rand()%eligibleCount;
        int boomGroup = eligibleGroups[boomIdx];

        int decIdx;
        do
        {
            decIdx=rand()% eligibleCount;
        }while(decIdx==boomIdx && eligibleCount>1);

        int decGroup = eligibleGroups[decIdx];

        mkt->activeBoomGroup = boomGroup;
        mkt->activeDeclineGroup = decGroup;
        mkt->boomRoundsRemaining = 10;
        mkt->declineRoundsRemaining = 10;
        mkt->lastAffectedRound[boomGroup] = currentRound;
        mkt->lastAffectedRound[decGroup] = currentRound;

        for (int i=0; i<TileSize; i++)
        {
            if (board[i].type == land && board[i].cGroup == boomGroup)
            {
                board[i].purchasePrice *= 1.15;
                board[i].mortgagePrice *= 1.15;
                board[i].baseRental *= 1.25;
                board[i].currentRent *= 1.25;
                board[i].houseCost *= 1.10;
                board[i].hotelCost *= 1.10;
                board[i].propertyValue *= 1.20;
            }
        }
        for (int i = 0; i < TileSize; i++)
        {
            if (board[i].type == land && board[i].cGroup == decGroup)
            {
                board[i].propertyValue *= 0.85;
                board[i].baseRental *= 0.80;
                board[i].currentRent *= 0.80;
                board[i].mortgagePrice *= 0.90;
            }
        }
        printf(BOLD_BLUE "\n===========================================================\n" RESET);
        printf(BOLD_BLUE "              DYNAMIC PROPERTY MARKET REVIEW               \n" RESET);
        printf(BOLD_BLUE "===========================================================\n\n" RESET);
        printf(BOLD_GREEN "Market Boom (+20%% Val, +25%% Rent, +10%% Build Cost):\n" RESET);
        printf("   Group: %s\n", getColorGroupName(boomGroup));
        printf(BOLD_RED "Market Decline (-15%% Val, -20%% Rent, -10%% Mortgage):\n" RESET);
        printf("   Group: %s\n", getColorGroupName(decGroup));
        printf("Duration: Active for the next 10 Rounds\n");
        printf(BOLD_BLUE "===========================================================\n\n" RESET);
    }
}

double calculateCurrentInterestRate()
{
    economicState *state = getActiveGovReg();
    double baseRate =0.08;

    if (state->currentInflationRate >= 0.12)
    {
        baseRate = 0.12;
    }
    else if (state->currentInflationRate >= 0.02)
    {
        baseRate = 0.10;
    }
    else if (state->currentInflationRate < 0.0)
    {
        baseRate = 0.08;
    }

    //gov regulation
    if (state->activeReg == REG_REDUCE_LOAN_INTEREST)
    {
        baseRate -= 0.02;
    }

    if (baseRate < 0.03) baseRate = 0.03; 
    state->currentBaseInterest = baseRate;

    return baseRate;
}

void processInflation(int currentRound, landProperties board[])
{
    if(currentRound>0 && currentRound%10==0)
    {
        economicState *state = getActiveGovReg();

        double inflationRates[]={-0.03,0.00,0.02,0.05,0.08,0.12};
        int randIdx = rand()%6;
        double rate = inflationRates[randIdx];
        state->currentInflationRate=rate;

        printf(BOLD_YELLOW "\n====================================================================================\n" RESET);
        if (rate < 0)
        {
            printf(BOLD_RED "                       MACROECONOMIC SHIFT: DEFLATION (%.0f%%)       \n" RESET, rate * 100.0);
        }
        else
        {
            printf(BOLD_YELLOW "                    MACROECONOMIC SHIFT: INFLATION (+%.0f%%)      \n" RESET, rate * 100.0);
        }
        printf(BOLD_YELLOW "====================================================================================\n" RESET);

        double multiplier = 1.0+rate;

        for(int i=0;i<TileSize;i++)
        {
            if (board[i].type != nonProperty)
            {
                board[i].purchasePrice *= multiplier;
                board[i].propertyValue *= multiplier;
                board[i].baseRental *= multiplier;
                board[i].currentRent *= multiplier;
                board[i].mortgagePrice *= multiplier;

                if (board[i].type == land)
                {
                    board[i].houseCost *= multiplier;
                    board[i].hotelCost *= multiplier;
                }
            }
        }
        calculateCurrentInterestRate();
    }
}
double getCurrentMarketMultiplier()
{
    economicState *reg = getActiveGovReg();
    double multiplier = 1.0 + reg->currentInflationRate;
    return multiplier;
}