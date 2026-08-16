#include<stdio.h>
#include"../headerFiles/declaraction.h"

void calPropertyValue(landProperties *property)
{
    if(property->type==nonProperty)
    {
        property->propertyValue=0.0;
        return;
    }
    if(property->propertyValue<=0)
    {
        property->propertyValue=property->purchasePrice;
    }
}
void calMortgageValue(landProperties *property)
{
    calPropertyValue(property);
    property->mortgagePrice = property->propertyValue*0.5;
}

void mortgageProperty(Player *player,landProperties board[],landProperties *property,double marketcondition)
{
    if(property->currentOwner == player->id && property->mortgageStatus==FALSE && property->isLoanLocked==FALSE)
    {
        if(property->type == land && hasBuildings(board,property->cGroup)==TRUE)
        {
            printf(RED"Cannot mortgage %s! property has buildings.\n"RESET,property->name);
        }
        else
        {
            calMortgageValue(property);//update property value
            property->mortgageStatus=TRUE;
            property->currentRent=0;//mortgage properties cannot collect rent
            player->cash+=property->mortgagePrice;

            printf(BOLD_GREEN "\n Property Mortgaged \n" RESET);
            printf(GREEN "%s mortgaged %s for LKR %'.f\n" RESET, player->name, property->name, property->mortgagePrice);
            printf("Updated Cash Balance: LKR %'.f\n", player->cash);
        }
    }
}

void unmortgageProperty(Player *player, landProperties board[])
{   
    for(int i=0;i<TileSize;i++)
    {        
        if(board[i].currentOwner==player->id && board[i].mortgageStatus==TRUE)
        {
            int shouldUnmortgage = FALSE;

            switch(player->id)
            {
                case AGG_INVESTER:
                    shouldUnmortgage = aggInvDecisions(player, board[i],UNMORTGAGE,2000);
                    break;
                case CONS_BANKER:
                    shouldUnmortgage = aggInvDecisions(player, board[i],UNMORTGAGE,2000);
                    break;
                case RISK_TAKER:
                    shouldUnmortgage = aggInvDecisions(player, board[i],UNMORTGAGE,2000);
                    break;
                case OPP_TRADER:
                    shouldUnmortgage = aggInvDecisions(player, board[i],UNMORTGAGE,2000);
                    break;
                default:
                    shouldUnmortgage = FALSE;
                    break;
            }

            if(shouldUnmortgage==TRUE)
            {
                double unmortgageCost = board[i].mortgagePrice*1.10;//10% interest
                player->cash -= unmortgageCost;
                board[i].mortgageStatus = FALSE;
                updateLandRent(&board[i]);

                printf(BOLD_GREEN"\n Property is Unmortgaged\n"RESET);
                printf(YELLOW"%s unmortgaged %s for LKR %.f\n"RESET, player->name, board[i].name, unmortgageCost);
                printf("Remaining Balance : LKR %.f\n", player->cash);
            }
        }
    }
}

void incomeTax(Player *player, double marketCondition)
{
    double taxRate = 0.15*marketCondition;

    //gov regulations
    economicState *reg = getActiveGovReg();
    if (reg->activeReg == REG_INCREASE_PROPERTY_TAX)
    {
        taxRate *= 1.15;
    }
    double taxAmount = player->cash*taxRate;

    player->cash -= taxAmount;
    printf(BOLD_GREEN"\n Tax Payment\n"RESET);
    printf(RED"%s paid Income Tax: LKR %'.f (Rate: %.1f%%)\n"RESET,player->name,taxAmount,taxRate*100);
    printf("Remaining Balance: LKR %'.f\n", player->cash);
}

void communityDevFund(Player *player,Player playerlist[],landProperties board[],double marketCondition)
{
    double totalAssets = player->cash;
    for(int i=0;i<TileSize;i++)
    {
        if(board[i].currentOwner==player->id && board[i].type != nonProperty)
        {
            calPropertyValue(&board[i]);
            totalAssets+=board[i].propertyValue;
        }
    }
    double taxRate = 0.10*marketCondition;
    double taxAmount = totalAssets * taxRate;

    player->cash -= taxAmount;
    printf(BOLD_GREEN"\n Tax Payment\n"RESET);
    printf(RED"%s paid Community Development Fund Tax: LKR %'.f (Rate: %.1f%%)\n"RESET,player->name,taxAmount,taxRate*100);
    printf("Total Assets: LKR %'.f\n",totalAssets);

    //check bankrupt
    if(player->cash >= 0)
    {
        printf("Remaining Balance: LKR %'.f\n", player->cash);
    }
    else
    {
        printf(RED"\n%s doesn't have enough money to pay TAX! Bankrupt Risk!\n"RESET,player->name);
        Bankrupt(player,playerlist,board,marketCondition);
    }
}

//========================LOANS==========================
double takeLoan(Player *player, landProperties board[],double requestedAmount,double currentIntRate)
{
    if(player->activeLoan.isActive==TRUE)
    {
        return 0.0;
    }
    double totalMortgageValue = 0.0;
    int count =0;
    int avalablePropertiesForLoan[TileSize];
    for(int i=0;i<TileSize;i++)
    {
        if(board[i].currentOwner==player->id && board[i].mortgageStatus==FALSE&& board[i].isLoanLocked==FALSE)
        {
            totalMortgageValue+=board[i].mortgagePrice;
            avalablePropertiesForLoan[count]=i;
            count++;
        }
    }
    double maxLoanAmount=totalMortgageValue*0.75;

    if(maxLoanAmount<=0 || count==0)
    {
        return 0.0;
    }

    double approvedLoanAmount=0.0;
    if(requestedAmount<=0 || requestedAmount>maxLoanAmount)
    {
        approvedLoanAmount = maxLoanAmount;
    }
    else approvedLoanAmount= requestedAmount;

    player->cash+=approvedLoanAmount;
    player->activeLoan.isActive=TRUE;
    player->activeLoan.currentLoanAmount=approvedLoanAmount;
    player->activeLoan.originalLoanAmount=approvedLoanAmount;
    player->activeLoan.intRate=currentIntRate;
    player->activeLoan.remainingRounds=20;
    player->activeLoan.collateralCount = count;

    printf(BOLD_GREEN "\n Obtaining a Loan \n" RESET);
    printf("%s obtained a secured loan.\n", player->name);
    printf("Loan Amount : LKR %'.f\n", approvedLoanAmount);
    printf("Collateral :\n");

    for (int i = 0; i < count; i++)
    {
        int idx = avalablePropertiesForLoan[i];
        player->activeLoan.collateralProperties[i] = idx;
        board[idx].isLoanLocked = TRUE; 
        printf("%s\n", board[idx].name);
    }
    printf("\nInterest Rate : %.f%%\n", currentIntRate * 100.0);
    printf("Duration : 20 Rounds\n");


    return approvedLoanAmount;
}

void repayLoan(Player *player,landProperties board[],double amount)
{
    if(player->activeLoan.isActive==FALSE) return;

    if(amount>player->activeLoan.currentLoanAmount)
    {
        amount=player->activeLoan.currentLoanAmount;
    }

    if(player->cash<amount)
    {
        amount=player->cash;
    }

    if(amount<0.0) return;

    player->cash-=amount;
    player->activeLoan.currentLoanAmount -= amount;

    printf(BOLD_GREEN "\n Loan Repayment \n" RESET);
    printf("%s repaid LKR %'.f.\n", player->name, amount);
    printf("Outstanding Balance :\nLKR %'.f.\n", player->activeLoan.currentLoanAmount);

    if (player->activeLoan.currentLoanAmount <= 0.0)
    {
        player->activeLoan.isActive = FALSE;
        player->activeLoan.currentLoanAmount = 0.0;
        player->activeLoan.remainingRounds = 0;

        for (int i = 0; i < player->activeLoan.collateralCount; i++)
        {
            int idx = player->activeLoan.collateralProperties[i];
            board[idx].isLoanLocked = FALSE; 
        }
        player->activeLoan.collateralCount = 0;
        printf(GREEN "Loan settled in full! All collateral unlocked.\n" RESET);
    }
}

void extendLoan(Player *player)
{
    if(player->activeLoan.isActive==TRUE)
    {
        player->activeLoan.remainingRounds=20;
        printf(BOLD_GREEN "\n Loan Extend \n" RESET);
        printf(YELLOW "\n%s extended the loan duration to 20 rounds.\n" RESET, player->name);
    }
}

void handleLoanDefault(Player *player, landProperties board[])
{
    printf(BOLD_GREEN "\n Loan Default \n" RESET);
    printf("%s has defaulted.\n", player->name);
    printf("Collateral has been foreclosed.\n");
    printf("Outstanding debt cleared.\n");

    for(int i=0;i<player->activeLoan.collateralCount;i++)
    {
        int idx=player->activeLoan.collateralProperties[i];

        board[idx].currentOwner =-1;
        board[idx].isLoanLocked =FALSE;
        board[idx].mortgageStatus =FALSE;

        board[idx].noOfHouses= 0;
        board[idx].noOfHotels=0;
        board[idx].buildingCondition = 100.0;
        board[idx].isDamage =FALSE;
        board[idx].isStucturalDamaged = FALSE;

        board[idx].insuaranceType=0;
        board[idx].InsuranceStatus=FALSE;
        board[idx].insuaranceRounds=0;
        board[idx].currentRent = board[idx].baseRental;
    }
    player->activeLoan.isActive = FALSE;
    player->activeLoan.currentLoanAmount = 0.0;
    player->activeLoan.remainingRounds = 0;
    player->activeLoan.collateralCount = 0;
}

void updateLoanInterest(Player playerlist[],landProperties board[])
{
    GlobalEconomy *eco = initGlobalEco();

    for(int i=0;i<Maxplayers;i++)
    {
        Player *player = &playerlist[i];

        if(player->isBankrupt==FALSE && player->activeLoan.isActive==TRUE)
        {
            double currentRate = player->activeLoan.intRate;

            //national event
            if ((player->activeCard == INTEREST_RATE_CUT || player->activeCard == INTEREST_RATE_INCREASE) && player->roundCount < player->eventExpiryRound)
            {
                currentRate *= player->eventValueMultiplier;
            }
            //gov regulationa
            economicState *reg = getActiveGovReg();
            if (reg->activeReg == REG_REDUCE_LOAN_INTEREST)
            {
                currentRate -= 0.02;
            }
            //eco event
            if (eco->loanIntMult != 1.0)
            {
                currentRate *= eco->loanIntMult;
            }

            if (currentRate < 0) currentRate = 0;

            double interest = player->activeLoan.currentLoanAmount*currentRate;
            player->activeLoan.currentLoanAmount+=interest;
            player->activeLoan.remainingRounds--;

            if(player->activeLoan.remainingRounds<=0)
            {
                handleLoanDefault(player,board);
            }
        }
    }
}
