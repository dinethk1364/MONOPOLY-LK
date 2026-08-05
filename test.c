// #include <stdio.h>
// #include "types.h"

// // Aggressive Investor ගේ සියලුම තීරණ එකම function එකක් ඇතුළත හැසිරවීම
// double aggInvDecisions(Player *player, landProperties *property, int actionType, double extraParam)
// {
//     /* 
//        actionType meanings:
//        1 = Buy Property Decision (Returns 1 for Yes, 0 for No)
//        2 = Auction Max Bid Decision (Returns max bid amount)
//        3 = Build House Decision (Returns 1 for Yes, 0 for No)
//        4 = Take Loan Decision (Returns 1 for Yes, 0 for No)
//        5 = Insurance Type Decision (Returns 0: None, 1: Basic, 2: Comprehensive)
//     */

//     switch (actionType)
//     {
//         case 1: // 1. Property Buying Decision
//         {
//             double estimatedFutureRent = extraParam;

//             // අතේ සල්ලි මදි නම් ගන්න බැහැ
//             if (player->cash < property->purchasePrice) return 0;

//             // Rule: Prioritizes acquiring premium properties such as Galle Face and Nuwara Eliya
//             if (property->purchasePrice == board[GalleFace].purchasePrice || 
//                 property->purchasePrice == board[NuwaraEliya].purchasePrice)
//             {
//                 return 1; // Buy True
//             }

//             // Rule: Always purchases an unowned property if sufficient funds remain to pay at least one future rent.
//             double remainingCash = player->cash - property->purchasePrice;
//             if (remainingCash >= estimatedFutureRent)
//             {
//                 return 1; // Buy True
//             }

//             return 0; // Buy False
//         }

//         case 2: // 2. Auction Max Bid Decision
//         {
//             // Rule: Bids aggressively until the property reaches 120% of its estimated market value.
//             double maxBid = property->purchasePrice * 1.20;
//             return (maxBid <= player->cash) ? maxBid : player->cash;
//         }

//         case 3: // 3. Build House / Hotel Decision
//         {
//             int isMonopoly = (int)extraParam;

//             // Rule: Constructs max possible houses immediately after obtaining monopoly & converts to hotels
//             if (!isMonopoly || property->mortgageStatus || property->noOfHotels > 0)
//             {
//                 return 0;
//             }

//             double cost = (property->noOfHouses == 4) ? property->hotelCost : property->houseCost;
//             if (player->cash >= cost)
//             {
//                 return 1; // Build True
//             }

//             return 0;
//         }

//         case 4: // 4. Take Loan Decision
//         {
//             double projectedRentalIncomeIncrease = extraParam;
//             // Rule: Obtains loans whenever additional funds can increase projected rental income.
//             if (projectedRentalIncomeIncrease > 0)
//             {
//                 return 1; // Take Loan
//             }
//             return 0;
//         }

//         case 5: // 5. Insurance Type Decision
//         {
//             // Rule: Purchases only Basic Insurance for houses and Comprehensive Insurance for hotels.
//             if (property->noOfHotels > 0)
//             {
//                 return 2; // Comprehensive Insurance
//             }
//             else if (property->noOfHouses > 0)
//             {
//                 return 1; // Basic Insurance
//             }
//             return 0; // No insurance for raw land
//         }

//         default:
//             return 0;
//     }
// }