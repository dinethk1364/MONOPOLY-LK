#include<stdio.h>
#include "../headerFiles/declaraction.h"

double calculateInsPremium(int insType)
{
    switch(insType)
    {
        case INS_BASIC: return 0.05;
        case INS_COMPREHENSIVE: return 0.10;
        case INS_BUISINESS_INTERUPTION: return 0.15;
        default: return 0.0;
    }
}

void handleInsuarace(Player *player, landProperties board[],double marketCondition)
{
    for(int i=0;i<TileSize;i++)
    {
        if(board[i].type==land && board[i].currentOwner==player->id && board[i].InsuranceStatus==FALSE)
        {
            int policyChoice;
            switch(player->id)
            {
                case AGG_INVESTER:
                    policyChoice=aggInvDecisions(player,board[i],BUY_INSURANCE_DECISION,0);
                    break;
                case CONS_BANKER:
                    policyChoice=consBanDecisions(player,board[i],BUY_INSURANCE_DECISION);
                    break;
                case RISK_TAKER:
                    policyChoice=riskTakDecisions(player,board[i],BUY_INSURANCE_DECISION);
                    break;
                case OPP_TRADER:
                    policyChoice=oppTraDecisions(player,board[i],0,0,0,BUY_INSURANCE_DECISION);
                    break;
                default:
                    policyChoice=FALSE;
                    break;
            }
            if(policyChoice != FALSE)
            {
                double premiumRate = calculateInsPremium(policyChoice);

                //gove regulations
                ActiveGovRegulation *reg = getActiveGovReg();
                if (reg->activeReg == REG_INSURANCE_REGULATION)
                {
                    premiumRate *= 0.85;
                }
                
                calPropertyValue(&board[i],marketCondition);
                double premiumCost = board[i].propertyValue * premiumRate;
                
                if(player->cash >= premiumCost)
                {
                    player->cash-= premiumCost;
                    board[i].InsuranceStatus=TRUE;
                    board[i].insuaranceType=policyChoice;
                    board[i].insuaranceRounds = 20;

                    const char *policyName ="";
                    switch(policyChoice)
                    {
                        case INS_BASIC:policyName="Basic Property Insurance"; break;
                        case INS_COMPREHENSIVE:policyName="Comprehensive Insurance"; break;
                        case INS_BUISINESS_INTERUPTION:policyName="Business Interruption Insurance"; break;
                    }
                    printf(BOLD_GREEN "\n Purchasing Insurance \n" RESET);
                    printf("%s purchased %s.\n",player->name,policyName);
                    printf("Property : %s\n", board[i].name);
                    printf("Premium : LKR %'.f.\n", premiumCost);
                }
            }
        }
    }
}

void checkInsuaranceExpiry(landProperties board[])
{
    for (int i=0; i<TileSize;i++)
    {
        if(board[i].type==land && board[i].currentOwner>0 &&board[i].InsuranceStatus==TRUE)
        {
            board[i].insuaranceRounds--;
            if(board[i].insuaranceRounds==3)
                printf(YELLOW"\nInsurance policy on %s expires in 3 rounds.\n"RESET,board[i].name);
    
            if(board[i].insuaranceRounds<=0)
            {
                board[i].InsuranceStatus=FALSE;
                board[i].insuaranceType=0;
                board[i].insuaranceRounds=0;
            }
        }
    }
}