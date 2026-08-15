//player decision-making algorithms
#include "../headerFiles/types.h"

int aggInvDecisions(Player *player, landProperties property, int actionType, double value)
{
    switch(actionType)
    {
        case BUY_PROPERTY_DECISION:
        {
            if(player->cash < property.purchasePrice) return FALSE;//check have enough cash to buy property

            double remainingCash = player->cash - property.purchasePrice;//get remaing cash if buy the property
            if(remainingCash>=value)// if have money to pay at least one future rent(pass a future rent for value parameter)
            {
                return TRUE;
            }
            //prioritized Properties
            //prioritize completing property groups
            
            return FALSE;
        }
        case AUCTION_MAX_BID_DECISION:
        {
            double maxbid = property.purchasePrice*1.20;
            int proposedBid = value;

            if(player->cash >= proposedBid && proposedBid<=maxbid)
            {
                return TRUE;
            }
            return FALSE;
        }
        case BUILD_HOUSE_DECISION:
        {
            //value = construction cost
            if(player->cash >= value)
            {
                return TRUE;
            }
            return FALSE;
        }
        case UNMORTGAGE:
        {
            double unmortgageCost = property.mortgagePrice * 1.10;
            double reservedCash = value;//one future rent
            if(player->cash >= unmortgageCost)
            {
                double remainingCash = player->cash - unmortgageCost;
                if(remainingCash >= reservedCash)
                {
                    return TRUE;
                }
            }
            return FALSE;
        }
        case MAINTENANCE_DECISION:
        {
            //value = maintenance cost
            if(property.buildingCondition<75.0 && player->cash >=value)
            {
                return TRUE;
            }
            return FALSE;
        }
        case BUY_INSURANCE_DECISION:
        {
            if(property.noOfHotels>0)
                return INS_COMPREHENSIVE;
            if(property.noOfHouses>0)
                return INS_BASIC;
            return FALSE;
        }

        default:
            return FALSE;
    }
}

int consBanDecisions(Player *players, landProperties property, int actionType)
{
    switch(actionType)
    {
        case BUY_PROPERTY_DECISION:
        {
            if(players->cash < property.purchasePrice) return FALSE;
            double remainingCash = players->cash - property.purchasePrice;
            if(remainingCash>=(players->cash*0.50))
            {
                return TRUE;
            }
            return FALSE;
        }
        case BUY_INSURANCE_DECISION:
        {
            if(property.noOfHotels>0||property.noOfHouses>0)
                return INS_COMPREHENSIVE;
            return FALSE;
        }

        default:
            return FALSE;
    }
}

int riskTakDecisions(Player *players, landProperties property, int actionType)
{
    switch(actionType)
    {
        case BUY_PROPERTY_DECISION:
        {
            if(players->cash < property.purchasePrice) return FALSE;
            double remainingCash = players->cash - property.purchasePrice;
            if(remainingCash>0.0)
            {
                return TRUE;
            }
            return FALSE;        
        }
        case BUY_INSURANCE_DECISION:
            return FALSE;
        default:
            return FALSE;
    }
}

int oppTraDecisions(Player *players, landProperties property,double projectedAppreciation, int currentInflation, int currentSubsidies, int actionType)
{
    switch(actionType)
    {
        case BUY_PROPERTY_DECISION:
        {
            if(players->cash < property.purchasePrice) return FALSE;
            if(property.type == railway || property.type == utility)
            {
                return TRUE;
            }
            return FALSE;
        }
        case BUY_INSURANCE_DECISION:
        {
            if(property.noOfHotels > 0 && players->cash >= (property.propertyValue * 0.15))
                return INS_BUISINESS_INTERUPTION;
            else if(property.purchasePrice >= 6500 && property.noOfHouses > 0)
                return INS_COMPREHENSIVE;
            return FALSE;
        }
        default:
            return FALSE;
    }
}