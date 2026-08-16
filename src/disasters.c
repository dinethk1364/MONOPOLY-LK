#include<stdio.h>
#include<stdlib.h>
#include "../headerFiles/declaration.h"

double getDisasterRepairCost(landProperties *property)
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
    const char *disasterName="";
    switch (disasterType)
    {
        case DISASTER_FIRE:disasterName="Fire"; break;
        case DISASTER_FLOOD:disasterName="Flood"; break;
        case DISASTER_RIOT:disasterName="Riot"; break;
        case DISASTER_BUILDING_COLLAPSE:disasterName="Building Collapse"; break;
        case DISASTER_ELECTRICAL_FAILURE:disasterName="Electrical Failure"; break;
        default: break;
    } 
    printf("Disaster Type       : " BOLD_YELLOW "%s\n" RESET, disasterName);
    printf("Location            : %s\n", property->name);
    if (property->currentOwner > 0)
    {
        Player *owner = NULL;
        for(int i=0;i<Maxplayers;i++)
        {
            if(playerlist[i].id==property->currentOwner)
            {
                owner=&playerlist[i];
                break;
            }
        }
        printf("Owner               : %s\n", owner->name);

        double repairCost = getDisasterRepairCost(property);
        printf("Repair Cost         : LKR %'.f\n", repairCost);

        //Check Insuarance Coverage
        int isCovered =FALSE;
        if(property->InsuranceStatus==TRUE)
        {
            if(property->insuaranceType==INS_COMPREHENSIVE || property->insuaranceType==INS_BUISINESS_INTERUPTION)
            {
                isCovered=TRUE;
            }
            else if(property->insuaranceType==INS_BASIC)
            {
                if(disasterType==DISASTER_FIRE || disasterType==DISASTER_FLOOD)
                {
                    isCovered=TRUE;
                }
            }
        }

        if(property->InsuranceStatus==TRUE && isCovered==TRUE)
        {
            double compensation=0.0;
            switch (property->insuaranceType)
            {
            case INS_BASIC:
                compensation = repairCost *0.80;
                break;
            case INS_COMPREHENSIVE:
                compensation = repairCost;
                break;
            case INS_BUISINESS_INTERUPTION:
                compensation = repairCost +(property->currentRent *5);
                break;            
            default: break;
            }

            owner->cash += compensation;
            printf(BOLD_GREEN "\n Insurance Claim Approved.\n" RESET);
            printf("Compensation Paid   : LKR %'.f\n", compensation);

            //expire after claim
            property->InsuranceStatus=FALSE;
            property->insuaranceType=FALSE;
            property->insuaranceRounds=0;
        }
        else
        {
            if(property->InsuranceStatus == TRUE && isCovered == FALSE)
            {
                printf(BOLD_RED "Insurance Status    : Policy does NOT cover %s!\n" RESET, disasterName);
                owner->hadDamage=TRUE;//risktaker decisions
            }
            else
            {
                printf(BOLD_RED "Insurance Status    : UNINSURED!\n" RESET);
            }
        }

        if(owner->cash>= repairCost)
        {
            owner->cash-=repairCost;
            property->isDamage=FALSE;
            property->buildingCondition=100.0;
            owner->hadDamage=TRUE;//risktaker decisions
            printf(YELLOW "\n%s paid LKR %'.f to repair %s.\n" RESET, owner->name, repairCost, property->name);
        }
        else
        {
            property->isDamage=TRUE;
            owner->hadDamage=TRUE;//risktaker decisions
            printf(RED"PROPERTY DAMAGED\n"RESET);
        }
    }

    printf(BOLD_RED "\n===========================================================\n" RESET);
}

void randomDisaster(landProperties board[],Player playerlist[],int currentRound)
{
    if(currentRound>0 && currentRound%10==0)
    {
        int developedProperties[TileSize];
        int propertyCount=0;

        //get developed properties
        printf("\n----- Developed Properties -----\n");
        for(int i=0;i<TileSize;i++)
        {
            if(board[i].type ==land && (board[i].noOfHouses > 0 || board[i].noOfHotels > 0))
            {
                developedProperties[propertyCount] = i;
                printf("-%s\n",board[i].name);

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

