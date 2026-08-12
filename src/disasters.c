#include<stdio.h>
#include<stdlib.h>
#include "../headerFiles/declaraction.h"

double getDisasterRapairCost(landProperties *property)
{
    if(property->noOfHouses==0 && property->noOfHotels==0)
        return 0.0;
    
    if(property->noOfHotels>0)
        return property->hotelCost*0.25;
    else
        return property->houseCost*property->noOfHouses*0.25;
}

void processDisaster(landProperties *property,Player playerlist[])
{
    printf(BOLD_RED "\n===========================================================\n" RESET);
    printf(BOLD_RED "                      NATURAL DISASTER!                    \n" RESET);
    printf(BOLD_RED "===========================================================\n" RESET);

    int disasterType = rand()%5;
    switch (disasterType)
    {
        case DISASTER_FIRE:
        {
            printf("Disaster Type       : " BOLD_YELLOW "Fire\n" RESET);
            break;
        }
        case DISASTER_FLOOD:
        {
            printf("Disaster Type       : " BOLD_YELLOW "Flood\n" RESET);
            break;
        }
        case DISASTER_RIOT:
        {
            printf("Disaster Type       : " BOLD_YELLOW "Riot\n" RESET);
            break;
        }
        case DISASTER_BUILDING_COLLAPSE:
        {
            printf("Disaster Type       : " BOLD_YELLOW "Building Collapse\n" RESET);
            break;
        }
        case DISASTER_ELECTRICAL_FAILURE:
        {
            printf("Disaster Type       : " BOLD_YELLOW "Electrical Failure\n" RESET);
            break;
        }
        default:
            break;
    } 
    printf("Location            : %s\n", property->name);
    if (property->currentOwner > 0)
    {
        printf("Owner               : %s\n", playerlist[property->currentOwner - 1].name);
    }
    double repairCost = getDisasterRapairCost(property);
    printf("Repair Cost         : LKR %'.f\n", repairCost);
    printf(BOLD_RED "\n===========================================================\n" RESET);

}

void randomDisaster(landProperties board[],Player playerlist[],int currentRound)
{
    if(currentRound>0 && currentRound%10==0)
    {
        int developedProperties[TileSize];
        int propertyCount=0;

        //get developed properties
        for(int i=0;i<TileSize;i++)
        {
            if(board[i].type ==land && (board[i].noOfHouses > 0 || board[i].noOfHotels > 0))
            {
                developedProperties[propertyCount] = i;
                propertyCount++;
            }
        }

        if(propertyCount>0)
        {
            int randIndex = rand()%propertyCount;
            int targetProperty = developedProperties[randIndex];

            processDisaster(&board[targetProperty],playerlist);
        }
        else
        {
            printf(YELLOW "\nDISASTER SKIP No developed properties on the board to strike!\n" RESET);
        }
    }
}

