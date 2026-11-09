# MONOPOLY-LK 🎲🇱🇰

A strategic property trading and economic simulation game inspired by the traditional game of Monopoly, custom-tailored to model realistic aspects of the Sri Lankan economy. Developed in the C programming language as part of the **SCS 1301 - Data Structures and Program Design using C** module at the **University of Colombo School of Computing (UCSC)**.

## 🌟 Overview

Unlike traditional Monopoly, **MONOPOLY-LK** introduces complex local financial systems, including commercial banking, secured loans, comprehensive insurance policies, taxation, property depreciation, market inflation, economic events, and government regulations.

The game is played entirely by **four autonomous, computer-controlled players**, each possessing unique investment strategies and financial behaviors. Once the simulation begins, no user interaction is required; the players independently make decisions regarding property purchases, bidding in auctions, managing loans, constructing and maintaining buildings, and handling financial resources.

## 👥 Autonomous Player Strategies

1. **Aggressive Investor:** Maximizes long-term wealth through rapid expansion, property development, and monopolies. Bids aggressively up to 120% of market value and builds houses/hotels quickly.

2. **Conservative Banker:** Prioritizes financial stability, maintains large emergency cash reserves, avoids unnecessary loans, and heavily relies on comprehensive insurance and steady utilities/railways.

3. **Risk Taker:** Seeks high returns through speculative investments, incurs significant debt for rapid expansion, borrows maximum loans, and constructs hotels early.

4. **Opportunistic Trader:** Adapts dynamically to market conditions, economic events, and government regulations. Prefers discounted auctions and carefully evaluates expected returns.

## 🏗️ Project Structure & Source Files

The implementation strictly adheres to a modular design pattern with the following file organization:

```text
├── board.c
├── cardEvents.c
├── csv/
│   └── Rent.csv
├── disasters.c
├── displays.c
├── economicEvents.c
├── economy.c
├── fileRead.c
├── finance.c
├── game.c
├── headerFiles/
│   ├── declaration.h
│   └── types.h
├── insuarance.c
├── main.c
└── players.c
```

### Module Descriptions

| File Name | Purpose |
| :--- | :--- |
| `headerFiles/types.h` | Definitions of structures, enumerations, constants, and custom data types. |
| `headerFiles/declaration.h` | Function prototypes across all modules. |
| `board.c` | Board initialization, layout management, and player movement logic. |
| `players.c` | Autonomous player decision-making algorithms and behavior strategies. |
| `finance.c` | Loans, banking transactions, taxation, and financial calculations. |
| `insuarance.c` | Insurance management and policy claims processing. |
| `economy.c` | Market inflation, property valuation, and depreciation engines. |
| `economicEvents.c` & `cardEvents.c` | Economic events, regional development cards, and national event card management. |
| `disasters.c` | Random natural disaster occurrences and structural damage handling. |
| `fileRead.c` | Loading configurations and rent data from CSV files. |
| `displays.c` | Console output formatters, board details, and round summaries. |
| `game.c` | Main game controller, round loops, auction handlers, and simulation engine. |
| `main.c` | Program entry point. |

## 📜 Core Rules & MONOPOLY-LK Extensions

### 1. Baseline Traditional Rules
* **Starting Conditions:** 4 players, each starting with **LKR 30,000.00** cash, zero properties, loans, or insurance.
* **Turn Order:** Determined by rolling two 6-sided dice at the beginning (highest total goes first; ties trigger rerolls). Play proceeds clockwise across 40 board squares.
* **GO Square:** Passing or landing on GO awards **LKR 2,000**.
* **Jail Mechanics:** Players can leave by paying bail (LKR 300), rolling doubles, or remaining imprisoned for 3 turns.

### 2. Advanced Banking & Loans (`finance.c`)
* Players can obtain secured loans exclusively by landing on the **Bank of Ceylon** square.
* **Collateral:** Eligible collateral includes properties, railway stations, and utility companies (buildings are excluded). Pledged properties become *Loan Locked*.
* **Loan Limit:** Maximum loan equals **75% of the total mortgage value** of unmortgaged eligible collateral.
* **Duration & Interest:** Loans have an initial duration of **20 rounds**, compounding interest every complete round based on prevailing economic conditions (5% to 15%).
* **Default & Foreclosure:** Failure to repay within 20 rounds results in loan default, transferring pledged assets to the Bank, demolishing buildings, and cancelling insurance.

### 3. Insurance System (`insuarance.c`)
* Available at *Sri Lanka Insurance* and *Ceylinco Insurance* squares. Policies apply to individual properties and remain valid for 20 rounds.
* **Three Policy Types:**
  1. *Basic Property Insurance (5% premium):* Protects against Fire and Flood (80% repair cost coverage).
  2. *Comprehensive Insurance (10% premium):* Protects against Fire, Flood, Riot, Vandalism, and Earthquakes (100% repair cost coverage).
  3. *Business Interruption Insurance (15% premium):* Covers repair cost and lost hotel rental income for 5 rounds (hotels only).
* **Disasters (`disasters.c`):** Random disasters occur every 10 rounds affecting developed properties. Uninsured properties bear full repair costs.

### 4. Dynamic Economy & Inflation (`economy.c` & `economicEvents.c`)
* **Inflation/Deflation:** Every 10 rounds, an inflation rate (-3% to 12%) is generated, compounding property prices, building costs, rent, insurance premiums, and repair costs.
* **Dynamic Property Market:** Reviewed every 10 rounds, assigning market booms (+15% to +25%) or declines (-15% to -20%) to random property groups.
* **Regional Development & National Events:** Every 15 rounds, regional development cards and national event cards are drawn, introducing unique buffs or penalties.

## 🚀 Getting Started & Compilation

### Prerequisites
* A C compiler (such as `gcc`).
* A Unix/Linux terminal environment.

### Compiling and Running
1. Clone the repository and navigate to the project directory:
   ```bash
   git clone https://github.com/your-username/monopoly-lk.git
   cd monopoly-lk
   ```

2. Compile all modular source files together using `gcc`:
   ```bash
   gcc *.c -o monopoly
   ```

3. Execute the simulation:
   ```bash
   ./monopoly
   ```


* **Module:** SCS 1301 - Data Structures and Program Design using C
* **Institution:** University of Colombo School of Computing (UCSC)
