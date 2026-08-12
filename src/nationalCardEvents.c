//events and government regulation
#include<stdio.h>
#include<stdlib.h>
#include "../headerFiles/declaraction.h"

GlobalEconomy *intGloabalEco()
{
    static GlobalEconomy globalEco = {NO_EVENT,1.0,1.0,1.0,1.0,1.0};
    return &globalEco;
}

void nationalEventCardProcess(Player playerlist[], Player *player, landProperties board[])
{
    static int topIndex =0;

    static nationalEventCards cards[20]=
    {
        {0, "Tourism Hype", "Hotels earn double rent for 5 rounds"},
        {1, "Fuel Shortage", "Railway rent doubles for 5 rounds"},
        {2, "Heavy Floods", "Random coastal property damaged"},
        {3, "Political Rally", "One random property closed for 2 rounds"},
        {4, "Stock Market Rise", "All property values increase by 10%"},
        {5, "Economic Downturn", "Property values decrease by 15%"},
        {6, "Housing Subsidy", "House construction cost reduced by 30%"},
        {7, "Interest Rate Cut", "Loan interest reduced by 2%"},
        {8, "Interest Rate Increase", "Loan interest increased by 2%"},
        {9, "Tax Amnesty", "Each player receives LKR 2,000"},
        {10, "Power Failure", "Utility income halved for 3 rounds"},
        {11, "Foreign Funding", "Commercial property values increase by 15%"},
        {12, "Port Expansion", "Railway station values increase by 20%"},
        {13, "Festival Season", "Hotels receive 50% additional rent"},
        {14, "Labour Strike", "Construction suspended for 2 rounds"},
        {15, "Insurance Discount", "Premiums reduced by 20%"},
        {16, "Property Revaluation", "Random property group appreciates by 15%"},
        {17, "Currency Depreciation", "Construction costs increase by 10%"},
        {18, "Government Grant", "Random player receives LKR 5,000"},
        {19, "National Disaster", "Random developed property damaged"}
    };
    
    nationalEventCards drawnCard = cards[topIndex];
    printf(BOLD_BLUE "\n National Event Card Drawn \n" RESET);
    printf(YELLOW "%s drew card: %s\n" RESET, player->name, drawnCard.name);
    printf("Effect: %s\n", drawnCard.description);

    executeNationalEvents(playerlist,player,board,drawnCard.cardId);

    topIndex = (topIndex+1)%20;
}

void executeNationalEvents(Player playerlist[],Player *player,landProperties board[],int cardId)
{
    //if player have active event clear it
    clearPlayerEvent(player,board);

    switch (cardId)
    {
        case TOURISM_HYPE:
        {
            player->activeCard = cardId;
            player->eventValueMultiplier = 2.0;//2x rent
            player->eventExpiryRound=player->roundCount+5;
            for(int i=0;i<TileSize;i++)
            {
                if(board[i].currentOwner==player->id && board[i].noOfHotels>0)
                {
                    board[i].currentRent *= player->eventValueMultiplier;
                }
            }
            break;
        }
        case FUEL_SHORTAGE:
        {
            player->activeCard = cardId;
            player->eventValueMultiplier = 2.0;//2x rent
            player->eventExpiryRound=player->roundCount+5;

            for(int i=0;i<TileSize;i++)
            {
                if(board[i].currentOwner==player->id && board[i].type == railway)
                {
                    board[i].currentRent *= player->eventValueMultiplier;
                }
            }
            break;
        }
        case HEAVY_FLOODS:
        {
            player->activeCard = cardId;
            break;
        }
        case POLITICAL_RALLY:
        {
            player->activeCard = cardId;
            break;
        }
        case STOCK_MARKET_RISE:
        {
            player->activeCard = cardId;
            player->eventValueMultiplier = 1.1;
            player->eventExpiryRound = player->roundCount+15;

            for(int i=0;i<TileSize;i++)
            {
                if(board[i].currentOwner==player->id && board[i].type!=nonProperty)
                {
                    board[i].propertyValue *= player->eventValueMultiplier;
                }
            }
            break;
        }
        case ECONOMIC_DOWNTURN:
        {
            player->activeCard = cardId;
            player->eventValueMultiplier = 0.85;
            player->eventExpiryRound = player->roundCount + 15;

            for(int i = 0; i < TileSize; i++)
            {
                if(board[i].currentOwner == player->id && board[i].type != nonProperty)
                {
                    board[i].propertyValue *= player->eventValueMultiplier;
                }
            }
            break;
        }
        case HOUSING_SUBSIDY:
        {
            player->activeCard = cardId;
            player->eventValueMultiplier = 0.7;
            player->eventExpiryRound = player->roundCount + 15;

            for(int i = 0; i < TileSize; i++)
            {
                if(board[i].currentOwner == player->id && board[i].type == land)
                {
                    board[i].houseCost *= player->eventValueMultiplier;
                }
            }
            break;
        }
        case INTEREST_RATE_CUT:
        {
            player->activeCard = cardId;
            break;
        }
        case INTEREST_RATE_INCREASE:
        {
            player->activeCard = cardId;
            break;
        }
        case TAX_AMNESTY:
        {
            player->activeCard = cardId;
            for(int i = 0; i < Maxplayers; i++)
            {
                if(playerlist[i].isBankrupt == FALSE)
                {
                    playerlist[i].cash += 2000;
                }
            }
            break;
        }
        case POWER_FAILURE:
        {
            player->activeCard = cardId;
            player->eventValueMultiplier = 0.5;
            player->eventExpiryRound = player->roundCount+3;

            for(int i=0;i<TileSize;i++)
            {
                if(board[i].currentOwner==player->id && board[i].type == utility)
                {
                    board[i].currentRent *= player->eventValueMultiplier;
                }
            }
            break;
        }
        case FOREIGN_FUNDING:
        {
            player->activeCard = cardId;
            player->eventValueMultiplier = 1.15;
            player->eventExpiryRound = player->roundCount+15;

            for(int i=0;i<TileSize;i++)
            {
                if(board[i].currentOwner==player->id && board[i].type == land)
                {
                    if(i>=GalleFort && i<= GalleFace)
                    {
                        board[i].propertyValue *= player->eventValueMultiplier;
                    }
                }
            }
            break;
        }
        case PORT_EXPANSION:
        {
            player->activeCard = cardId;
            player->eventValueMultiplier = 1.2;
            player->eventExpiryRound=player->roundCount+5;

            for(int i=0;i<TileSize;i++)
            {
                if(board[i].currentOwner==player->id && board[i].type == railway)
                {
                    board[i].propertyValue *= player->eventValueMultiplier;
                }
            }
            break;
        }
        case FESTIVAL_SEASON:
        {
            player->activeCard = cardId;
            player->eventValueMultiplier = 1.5;
            player->eventExpiryRound=player->roundCount+5;
            for(int i=0;i<TileSize;i++)
            {
                if(board[i].currentOwner==player->id && board[i].noOfHotels>0)
                {
                    board[i].currentRent *= player->eventValueMultiplier;
                }
            }
            break;
        }
        case LABOUR_STRIKE:
        {
            player->activeCard = cardId;
            break;
        }
        case INSURANCE_DISCOUNT:
        {
            player->activeCard = cardId;
            break;
        }
        case PROPERTY_REVALUATION:
        {
            player->activeCard = cardId;
            break;
        }
        case CURRENCY_DEPRECIATION:
        {
            player->activeCard = cardId;
            player->eventValueMultiplier = 1.10;
            player->eventExpiryRound = player->roundCount + 15;

            for(int i = 0; i < TileSize; i++)
            {
                if(board[i].currentOwner == player->id && board[i].type == land)
                {
                    board[i].houseCost *= player->eventValueMultiplier;
                    board[i].hotelCost *= player->eventValueMultiplier;
                }
            }
            break;
        }
        case GOVERNMENT_GRANT:
        {
            player->activeCard = cardId;
            int targetPlayer;
            do
            {
                targetPlayer = rand()%Maxplayers;
            }while(playerlist[targetPlayer].isBankrupt==TRUE);

            playerlist[targetPlayer].cash += 5000;
            printf(GREEN"Government Grant! %s recieved LKR 5000\n"RESET,playerlist[targetPlayer].name);
            break;
        }
        case NATIONAL_DISASTER:
        {
            player->activeCard = cardId;
            break;
        }
    }
}
void checkEventExpiry(Player *player,landProperties board[])
{
    if (player->eventExpiryRound > 0 && player->roundCount >= player->eventExpiryRound)
    {
        clearPlayerEvent(player,board);
        printf(YELLOW "\nEvent Expired %s's event modifiers ended.\n" RESET, player->name);
    }
}
void clearPlayerEvent(Player *player, landProperties board[])
{
    if (player->eventExpiryRound <= 0) return;

    switch (player->activeCard)
    {
        case TOURISM_HYPE:
        case FESTIVAL_SEASON:
        {
            for(int i=0;i<TileSize;i++)
            {
                if(board[i].currentOwner==player->id && board[i].noOfHotels>0)
                {
                    board[i].currentRent /= player->eventValueMultiplier;
                }
            }
            break;
        }
        case FUEL_SHORTAGE:
        {
            for(int i = 0; i < TileSize; i++)
            {
                if(board[i].currentOwner == player->id && board[i].type == railway)
                {
                    board[i].currentRent /= player->eventValueMultiplier;
                }
            }
            break;
        }
        case STOCK_MARKET_RISE:
        case ECONOMIC_DOWNTURN:
        {
            for(int i = 0; i < TileSize; i++)
            {
                if(board[i].currentOwner == player->id && board[i].type != nonProperty)
                {
                    board[i].propertyValue /= player->eventValueMultiplier;
                }
            }
            break;
        }
        case HOUSING_SUBSIDY:
        {
            for(int i = 0; i < TileSize; i++)
            {
                if(board[i].currentOwner == player->id && board[i].type == land)
                {
                    board[i].houseCost /= player->eventValueMultiplier;
                }
            }
            break;
        }       
        case POWER_FAILURE:
        {
            for(int i = 0; i < TileSize; i++)
            {
                if(board[i].currentOwner == player->id && board[i].type == utility)
                {
                    board[i].currentRent /= player->eventValueMultiplier;
                }
            }
            break;
        }
        case FOREIGN_FUNDING:
        {
            for(int i = 0; i < TileSize; i++)
            {
                if(board[i].currentOwner == player->id && board[i].type == land)
                {
                    if(i >= GalleFort && i <= GalleFace)
                    {
                        board[i].propertyValue /= player->eventValueMultiplier;
                    }
                }
            }
            break;
        }
        case PORT_EXPANSION:
        {
            for(int i = 0; i < TileSize; i++)
            {
                if(board[i].currentOwner == player->id && board[i].type == railway)
                {
                    board[i].propertyValue /= player->eventValueMultiplier;
                }
            }
            break;
        }
        case CURRENCY_DEPRECIATION:
        {
            for(int i = 0; i < TileSize; i++)
            {
                if(board[i].currentOwner == player->id && board[i].type == land)
                {
                    board[i].houseCost /= player->eventValueMultiplier;
                    board[i].hotelCost /= player->eventValueMultiplier;
                }
            }
            break;
        } 
    }

    player->eventExpiryRound = 0;
    player->eventValueMultiplier = 1.0;
    player->activeCard = -1;
}

