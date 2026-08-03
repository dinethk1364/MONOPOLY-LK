//player decision-making algorithms
#include "../headerFiles/types.h"

int aggInvDecisions(Player *players, landProperties property, int actionType, double value)
{
    switch(actionType)
    {
        case BUY_PROPERTY_DECISION:
        {
            if(players->cash < property.purchasePrice) return FALSE;//check have enough cash to buy property

            double remainingCash = players->cash - property.purchasePrice;//get remaing cash if buy the property
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

            if(players->cash >= proposedBid && proposedBid<=maxbid)
            {
                return TRUE;
            }
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
        }

        default:
            return FALSE;
    }
}