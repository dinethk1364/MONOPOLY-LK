//player decision-making algorithms
#include "../headerFiles/types.h"

int aggInvDecisions(Player *players, landProperties property, int actionType, double futureRent)
{
    switch(actionType)
    {
        case BUY_PROPERTY_DECISION:
        {
            if(players->cash < property.purchasePrice) return 0;//check have enough cash to buy property

            double remainingCash = players->cash - property.purchasePrice;//get remaing cash if buy the property
            if(remainingCash>=futureRent)// if have money to pay at least one future rent
            {
                return 1;
            }
            //prioritized Properties
            //prioritize completing property groups
            
            return 0;
        }

        default:
            return 0;
    }
}

int consBanDecisions(Player *players, landProperties property, int actionType)
{
    switch(actionType)
    {
        case BUY_PROPERTY_DECISION:
        {
            if(players->cash < property.purchasePrice) return 0;
            double remainingCash = players->cash - property.purchasePrice;
            if(remainingCash>=(players->cash*0.50))
            {
                return 1;
            }
            return 0;
        }

        default:
            return 0;
    }
}

int riskTakDecisions(Player *players, landProperties property, int actionType)
{
    switch(actionType)
    {
        case BUY_PROPERTY_DECISION:
        {
            if(players->cash < property.purchasePrice) return 0;
            double remainingCash = players->cash - property.purchasePrice;
            if(remainingCash>0.0)
            {
                return 1;
            }
    return 0;        
        }

        default:
            return 0;
    }
}

int oppTraDecisions(Player *players, landProperties property,double projectedAppreciation, int currentInflation, int currentSubsidies, int actionType)
{
    switch(actionType)
    {
        case BUY_PROPERTY_DECISION:
        {
            if(players->cash < property.purchasePrice) return 0;
        }

        default:
            return 0;
    }
}