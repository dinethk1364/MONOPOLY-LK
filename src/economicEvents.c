#include<stdio.h>
#include<stdlib.h>
#include "../headerFiles/declaraction.h"

GlobalEconomy *initGlobalEco()
{
    static GlobalEconomy globalEco = {NO_EVENT,1.0,1.0,1.0,1.0,1.0};
    return &globalEco;
}

void economicEventProcess(int currentRound, landProperties board[])
{
    static int lastTriggeredRound = 0;//stops call event in same round

    if((currentRound>0) && currentRound % 15==0 && currentRound!=lastTriggeredRound)
    {
        lastTriggeredRound=currentRound;
        EconomicEvent randomEvent=(EconomicEvent)(rand()%8);
        executeEconomicEvents(board,randomEvent,currentRound);
    }
}

void executeEconomicEvents(landProperties board[], EconomicEvent eventId, int currentRound)
{
    GlobalEconomy *eco = initGlobalEco();

    clearEconEvents(board);//clear existing event
    eco->currentEvent=eventId;

    printf(BOLD_RED "\n===========================================================\n" RESET);
    printf(BOLD_RED "             NATIONAL ECONOMIC EVENT TRIGGERED!          \n" RESET);
    printf(BOLD_RED "===========================================================\n" RESET);

    switch(eventId)
    {
        case TOURISM_BOOM:
        {
            printf(BOLD_GREEN "Event: TOURISM BOOM!\n" RESET);
            printf(YELLOW"-Hotels recieve double rent \n-Southern coastal properties 15%%.\n"RESET);

            eco->hotelRentMult = 2.0;
            eco->propertyValueMult = 1.15;

            for(int i=0;i<TileSize;i++)
            {
                if(board[i].type==land &&(i==Unawatuna || i==Hikkaduwa || i==GalleFort))
                {
                    board[i].propertyValue*=eco->propertyValueMult;
                }
                if(board[i].noOfHotels>0)
                {
                    board[i].currentRent*= eco->hotelRentMult;
                }
            }
            break;
        }
        case FUEL_CRISIS:
        {
            printf(BOLD_GREEN "Event: FUEL CRISIS!!\n" RESET);
            printf(YELLOW"-Railway rent doubles. \n-Property development costs increase by 15%%.\n"RESET);

            eco->railwayRentMult = 2.0;
            eco->houseCostMult = 1.2;

            for(int i=0;i<TileSize;i++)
            {
                if(board[i].type == railway)
                {
                    board[i].currentRent *= eco->railwayRentMult;
                }
                if(board[i].type ==land)
                {
                    board[i].houseCost *= eco->houseCostMult;
                    board[i].hotelCost *= eco->houseCostMult;
                }
            }
            break;
        }
        case HEAVY_MONSOON:
        {
            printf(BOLD_GREEN "Event: HEAVY MONSOON!\n" RESET);
            printf(YELLOW"-Flood risk increase. \n-Insurance premium increase. \n-Coastal properties lose 10%%.\n"RESET);

            //flood risk increase
            //insuarance premiums increase

            //coastal properties {Bambalapitiya, mountlavinia,gallefort,unawatuna,hikkaduwa.galleface}
            eco->propertyValueMult = 0.9;

            for(int i=0;i<TileSize;i++)
            {
                if(board[i].type ==land && (i==Bambalapitiya||i==MountLavinia||i==GalleFort||i==Unawatuna||i==Hikkaduwa||i==GalleFace))
                {
                    board[i].propertyValue*=eco->propertyValueMult;
                }
            }
            break;
        }
        case ECONOMIC_RECESSION:
        {
            printf(BOLD_GREEN "Event: ECONOMIC RECESSION!\n" RESET);
            printf(YELLOW"-Property values decrease by 15%%. \n-Rent decreases by 10%%.\n-Loan interest increases by 15%%.\n"RESET);

            //loan int increase

            eco->propertyValueMult = 0.85;
            eco->rentMultiplier = 0.90;

            for(int i=0;i<TileSize;i++)
            {
                if(board[i].type!=nonProperty)
                {
                    board[i].propertyValue*=eco->propertyValueMult;
                    board[i].currentRent*= eco->rentMultiplier;
                }
            }
            break;
        }
        case STOCK_MARKET_BOOM:
        {
            printf(BOLD_GREEN "Event: STOCK MARKET BOOM!\n" RESET);
            printf(YELLOW"-Property values increase by 10%%. \n-Loan interest decrease by 10%%.\n"RESET);

            //loan int decrease

            eco->propertyValueMult=1.10;
            
            for(int i=0;i<TileSize;i++)
            {
                if(board[i].type!=nonProperty)
                {
                    board[i].propertyValue*=eco->propertyValueMult;
                }
            }
            break;
        }
        case GOVT_HOUSING_PROGRAMME:
        {
            printf(BOLD_GREEN "Event: GOVERNMENT HOUSING PROGRAMME!\n" RESET);
            printf(YELLOW"-House construction costs reduce 25%%.\n"RESET);

            eco->houseCostMult=0.75;

            for(int i=0;i<TileSize;i++)
            {
                if(board[i].type==land)
                {
                    board[i].houseCost*=eco->houseCostMult;
                }
            }
            break;
        }
        case FOREIGN_INVESTMENT:
        {
            printf(BOLD_GREEN "Event: FOREIGN INVESTMENT!\n" RESET);
            printf(YELLOW"-Commercial properties increase 20%%.\n"RESET);

            eco->propertyValueMult=1.20;

            for (int i = 0; i < TileSize; i++)
            {
                if (board[i].type==land && (i>=GalleFort && i<=GalleFace))
                {
                    board[i].propertyValue *= eco->propertyValueMult;
                }
            }
            break;
        }
        case POLITICAL_UNREST:
        {
            printf(BOLD_GREEN "Event: POLITICAL UNREST!\n" RESET);
            printf(YELLOW"-Riot probability doubles. \n-Hotel occupancy decreases and the hotel rent drops by 50%%.\n-– Business interruption claims increases.\n"RESET);

            //riot probability doubles
            //hotel occupancy decrease
            //bussiness interruption claims increases

            eco->hotelRentMult=0.50;

            for(int i=0;i<TileSize;i++)
            {
                if(board[i].noOfHotels>0)
                {
                    board[i].currentRent*= eco->hotelRentMult;
                }
            }
            break;
        }
        default:
            break;
    }
    printf(BOLD_RED "\n===========================================================\n" RESET);
}

void clearEconEvents(landProperties board[])
{
    GlobalEconomy *eco = initGlobalEco();
    if(eco->currentEvent==NO_EVENT) return;

    switch (eco->currentEvent)
    {
        case TOURISM_BOOM:
        {
            for(int i=0;i<TileSize;i++)
            {
                if(board[i].type==land &&(i==Unawatuna || i==Hikkaduwa || i==GalleFort))
                {
                    board[i].propertyValue /= eco->propertyValueMult;
                }
                if(board[i].noOfHotels>0)
                {
                    board[i].currentRent /= eco->hotelRentMult;
                }
            }
            break;
        }
        case FUEL_CRISIS:
        {
            for(int i=0;i<TileSize;i++)
            {
                if(board[i].type == railway)
                {
                    board[i].currentRent /= eco->railwayRentMult;
                }
                if(board[i].type ==land)
                {
                    board[i].houseCost /= eco->houseCostMult;
                    board[i].hotelCost /= eco->houseCostMult;
                }
            }
            break;
        }
        case HEAVY_MONSOON:
        {
            for(int i=0;i<TileSize;i++)
            {
                if(board[i].type ==land && (i==Bambalapitiya||i==MountLavinia||i==GalleFort||i==Unawatuna||i==Hikkaduwa||i==GalleFace))
                {
                    board[i].propertyValue /= eco->propertyValueMult;
                }
            }
            break;
        }
        case ECONOMIC_RECESSION:
        {
            for(int i=0;i<TileSize;i++)
            {
                if(board[i].type!=nonProperty)
                {
                    board[i].propertyValue /= eco->propertyValueMult;
                    board[i].currentRent /= eco->rentMultiplier;
                }
            }
            break;
        }
        case STOCK_MARKET_BOOM:
        {
            for(int i=0;i<TileSize;i++)
            {
                if(board[i].type!=nonProperty)
                {
                    board[i].propertyValue/=eco->propertyValueMult;
                }
            }
            break;
        }
        case GOVT_HOUSING_PROGRAMME:
        {
            for(int i=0;i<TileSize;i++)
            {
                if(board[i].type==land)
                {
                    board[i].houseCost /= eco->houseCostMult;
                }
            }
            break;
        }
        case FOREIGN_INVESTMENT:
        {
            for (int i = 0; i < TileSize; i++)
            {
                if (board[i].type==land && (i>=GalleFort && i<=GalleFace))
                {
                    board[i].propertyValue /= eco->propertyValueMult;
                }
            }
            break;
        }
        case POLITICAL_UNREST:
        {
            for(int i=0;i<TileSize;i++)
            {
                if(board[i].noOfHotels>0)
                {
                    board[i].currentRent /= eco->hotelRentMult;
                }
            }
            break;
        }
        default:
            break;
    }

    eco->currentEvent=NO_EVENT;
    eco->propertyValueMult = 1.0;
    eco->rentMultiplier = 1.0;
    eco->houseCostMult = 1.0;
    eco->hotelRentMult = 1.0;
    eco->railwayRentMult = 1.0;
}
