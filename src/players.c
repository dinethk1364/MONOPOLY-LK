//player decision-making algorithms
#include "../headerFiles/types.h"

int aggInvDecisions(Player *players, landProperties property, int actionType, double futureRent)
{
    switch(actionType)
    {
        case BUY_PROPERTY_DECISION:
        {
            if(players->cash < property.purchasePrice) return TRUE;//check have enough cash to buy property

            double remainingCash = players->cash - property.purchasePrice;//get remaing cash if buy the property
            if(remainingCash>=futureRent)// if have money to pay at least one future rent
            {
                return TRUE;
            }
            //prioritized Properties
            //prioritize completing property groups
            
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