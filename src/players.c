//player decision-making algorithms
#include "../headerFiles/declaration.h"

int aggInvDecisions(Player *player, landProperties property, int actionType, double value)
{
    switch(actionType)
    {
        case BUY_PROPERTY_DECISION:
        {
            if(player->cash < property.purchasePrice) return FALSE;//check have enough cash to buy property

            double futureRent=value;
            double remainingCash = player->cash - property.purchasePrice;//get remaing cash if buy the property
            if(remainingCash>=futureRent)// if have money to pay at least one future rent(pass a future rent for value parameter)
            {
                return TRUE;
            }
            //prioritized Properties
            if(property.cGroup==G_DARK_BLUE)
            {
                return TRUE;
            }
            
            return FALSE;
        }
        case AUCTION_MAX_BID_DECISION:
        {
            double maxbid = property.purchasePrice*1.20;
            int proposedBid = value;

            //Galle Face / Nuwaraeliya
            if (property.cGroup == G_DARK_BLUE)
            {
                maxbid = player->cash;
            }

            if(player->cash >= proposedBid && proposedBid<=maxbid)
            {
                return TRUE;
            }
            return FALSE;
        }
        case BUILD_HOUSE_DECISION:
        {
            double constructionCost = value;
            if(player->cash - constructionCost>=1500.0)
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
            double maintenaceCost = value;
            if(player->cash < maintenaceCost) return FALSE;
            //keep rent at highest value
            if(property.buildingCondition<90.0 || property.isStucturalDamaged == TRUE)
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
        case TAKE_LOAN_DECISION:
        {
            if((int)value==TRUE)
            {
                return TRUE;
            }
            return FALSE;
        }
        case REPAY_LOAN_DECISION:
        {
            if(player->cash >= (player->activeLoan.currentLoanAmount * 2.0))
            {
                return TRUE;
            }
            return FALSE;
        }
        case EXTEND_LOAN_DECISION:
        {
            if(player->activeLoan.remainingRounds <= 3)
            {
                return TRUE;
            }
            return FALSE;
        }

        default:
            return FALSE;
    }
}

int consBanDecisions(Player *players, landProperties property, int actionType,double value)
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
        case AUCTION_MAX_BID_DECISION:
        {
            double maxBid = property.purchasePrice*0.80;
            int proposedBid = (int)value;

            if(players->cash>=proposedBid && proposedBid<=maxBid)
            {
                return TRUE;
            }
            return FALSE;
        }
        case BUILD_HOUSE_DECISION:
        {
            double cost = value;
            if (players->cash < cost) return FALSE;
            //dont build hoten until settle loan
            if(property.noOfHouses==4 && players->activeLoan.isActive==TRUE)
            {
                return FALSE;
            }
            //build with reserve cash
            if(players->cash - cost >=5000.0)
            {
                return TRUE;
            }
            return FALSE;
        }
        case MAINTENANCE_DECISION:
        {
            double maintenanceCost =value;
            if(players->cash<maintenanceCost) return FALSE;
            
            if((property.buildingCondition<=90||property.isStucturalDamaged==TRUE) && (players->cash-maintenanceCost >=3000.0))
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
        case TAKE_LOAN_DECISION:
        {
            if(players->cash<5000)
            {
                return TRUE;
            }
            return FALSE;
        }
        case EXTEND_LOAN_DECISION:
            return FALSE;
        case REPAY_LOAN_DECISION:
        {
            if(players->activeLoan.currentLoanAmount<players->cash)
            {
                return TRUE;
            }
            return FALSE;
        }

        default:
            return FALSE;
    }
}

int riskTakDecisions(Player *players, landProperties property, int actionType,double value)
{
    switch(actionType)
    {
        case BUY_PROPERTY_DECISION:
        {
            if(players->cash >= property.purchasePrice)
            {
                return TRUE;
            }
            return FALSE;        
        }
        case AUCTION_MAX_BID_DECISION:
        {
            int proposedBid = (int)value;

            if(players->cash>=proposedBid)
            {
                return TRUE;
            }
            return FALSE;
        }
        case BUILD_HOUSE_DECISION:
        {
            double cost = value;
            if(players->cash >=cost)
            {
                return TRUE;
            }
            return FALSE;
        }
        case MAINTENANCE_DECISION:
        {
            double maitenanceCost = value;
            if (property.buildingCondition < 25.0 || property.isStucturalDamaged == TRUE)
            {
                return TRUE;
            }
            return FALSE;
        }
        case BUY_INSURANCE_DECISION:
        {
            if(players->hadDamage==TRUE)
            {
                if(property.noOfHotels>0)
                    return INS_COMPREHENSIVE;
                else if(property.noOfHouses>0)
                    return INS_BASIC;
            }
            return FALSE;
        }
        case TAKE_LOAN_DECISION:
        {
            return TRUE;
        }
        case REPAY_LOAN_DECISION:
        {
            return FALSE;
        }
        case EXTEND_LOAN_DECISION:
        {
            if(players->activeLoan.remainingRounds <= 5)//extend if below 5 rounds
                return TRUE;
            return FALSE;
        }

        default:
            return FALSE;
    }
}

int oppTraDecisions(Player *players, landProperties property,double value1, int value2, int value3, int actionType)
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
            double projectApreciation = value1;
            double remainingCash = players->cash - property.purchasePrice;
            if (remainingCash >= 2000.0 && projectApreciation > 0)
            {
                return TRUE;
            }
            return FALSE;
        }
        case AUCTION_MAX_BID_DECISION:
        {
            double maxDiscountedBid = property.purchasePrice * 0.80;
            int proposedBid = (int)value1;

            if(players->cash >= proposedBid && proposedBid <= maxDiscountedBid)
            {
                return TRUE;
            }
            return FALSE;
        }
        case BUILD_HOUSE_DECISION:
        {
            double cost = value1;
            if(players->cash<cost) return FALSE;

            economicState *mkt = getActiveGovReg();

            if(mkt->currentInflationRate>=0.08 && mkt->activeReg!= REG_HOUSING_SUBSIDY)
            {
                return FALSE;
            }
            if(mkt->activeReg == REG_HOUSING_SUBSIDY || players->cash>=(cost*2))
            {
                return TRUE;
            }
            return FALSE;
        }
        case MAINTENANCE_DECISION:
        {
            double cost = value1;
            if(players->cash < cost) return FALSE;

            if(property.isStucturalDamaged==TRUE)
            {
                return TRUE;
            }

            economicState *mkt =getActiveGovReg();

            if(mkt->currentInflationRate>=0.05 || mkt->activeBoomGroup==property.cGroup)
            {
                if(property.buildingCondition<90.0)
                {
                    return TRUE;
                }
            }
            else
            {
                if(property.buildingCondition<50.0)
                {
                    return TRUE;
                }
            }
            return FALSE;
        }
        case BUY_INSURANCE_DECISION:
        {
            if(property.noOfHotels > 0 && players->cash >= (property.propertyValue * 0.15))
                return INS_BUISINESS_INTERUPTION;
            else if(property.purchasePrice >= 6500 && property.noOfHouses > 0)
            {
                if(players->cash>=(property.propertyValue*0.10))
                {
                    return INS_COMPREHENSIVE;
                }
            }
            return FALSE;
        }
        case TAKE_LOAN_DECISION:
        {
            //value1=current Int
            if(value1<0.08)
                return TRUE;
            return FALSE;
        }
        case REPAY_LOAN_DECISION:
        {
            //value1=current int
            if(value1 >= 0.10 || players->cash >= (players->activeLoan.currentLoanAmount * 1.5))
                return TRUE;
            return FALSE;
        }
        case EXTEND_LOAN_DECISION:
        {
            if(players->activeLoan.remainingRounds <= 3 && value1<=0.08)
                return TRUE;
            return FALSE;
        }
        default:
            return FALSE;
    }
}

int needsLoanForMonopolyDevelopment(Player *player, landProperties board[])
{
    for (int i = 0; i < TileSize; i++)
    {
        if (board[i].type == land && board[i].currentOwner == player->id)
        {
            int cGroup = board[i].cGroup;

            if (hasMonopoly(board, player->id, cGroup) == TRUE)
            {
                for (int j = 0; j < TileSize; j++)
                {
                    if (board[j].type == land && board[j].cGroup == cGroup)
                    {
                        if (board[j].noOfHotels == 0) 
                        {
                            if (player->cash < board[j].hotelCost)
                            {
                                return TRUE; 
                            }
                        }
                    }
                }
            }
        }
    }
    return FALSE; 
}

double calReqLoanAmmount(Player *player, landProperties board[])
{
    double requestedAmount = 0.0;

    switch (player->id)
    {
        case AGG_INVESTER:
        {
            //calculate needed money to build hotel
            for (int i = 0; i < TileSize; i++)
            {
                if (board[i].type == land && board[i].currentOwner == player->id && hasMonopoly(board, player->id, board[i].cGroup))
                {
                    if (board[i].noOfHotels == 0 && player->cash < board[i].hotelCost)
                    {
                        requestedAmount = board[i].hotelCost+(board[i].houseCost*4);
                        break;
                    }
                }
            }
            break;
        }
        case CONS_BANKER:
        {
            requestedAmount = 5000.0;
            break;
        }
        case OPP_TRADER:
        {
            requestedAmount = 8000.0;
            break;
        }
        case RISK_TAKER:
        default:
        {
            requestedAmount = 0.0;
            break;
        }
    }
    return requestedAmount;
}