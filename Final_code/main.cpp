/* Filename: Final_code
Objective: Making final adjustments to game mechanics
Author: Roberto Akankwasa Sanchez
Date:04/05/2024
Version: 1
*/

#include <iostream>
#include <time.h>

#define GRID_SIZE 12
#define NUM_OBSTACLES 10
#define NUM_GEMS 8
#define NUM_ORES 15

//Storage for mined minerals//
struct backPack{
    int minedGems;
    int minedOres;
    int totalMoney;
};

void printGrid(int playerX, int playerY, int shopX,int shopY,int obstacles[][2], int gems[][2], int ores[][2]);//Prototype for function to print grid//
void playerMovement(char move, int &playerX, int &playerY,int obstacles[][2],int ores[][2], int gems[][2], struct backPack *bag,int shopX,int shopY); //Prototype for function for player movement
int foundObstacle(int playerX, int playerY, int obstacles[][2]);//Prototype for function for player movement
int foundOre(int playerX, int playerY, int ores[][2],struct backPack *bag);
int foundGem(int playerX, int playerY, int gems[][2],struct backPack *bag);
int shopInteraction(int playerX, int playerY, int shopX, int shopY, struct backPack *bag);
void viewInventory(struct backPack *bag);



int main() {

    srand(time(nullptr)); // Seed for random number generation


    int obstacles[NUM_OBSTACLES][2];
    int ores[NUM_ORES][2];
    int gems[NUM_GEMS][2];
    int shopX = 0, shopY = 0;
    int playerX = 0, playerY = 0;
    char move;
    backPack *bag;

    bag->minedGems = 0;
    bag->minedOres = 0;
    bag->totalMoney = 0;


    // Generate random obstacle coordinates
    for (int i = 0; i < NUM_OBSTACLES; i++) {
        obstacles[i][0] = rand() % GRID_SIZE; // Random X coordinate
        obstacles[i][1] = rand() % GRID_SIZE; // Random Y coordinate
    }

    // Generate random gem coordinates
    for (int i = 0; i < NUM_GEMS; i++) {
        gems[i][0] = rand() % GRID_SIZE; // Random X coordinate
        gems[i][1] = rand() % GRID_SIZE; // Random Y coordinate
    }

    // Generate random ore coordinates
    for (int i = 0; i < NUM_ORES; i++) {
        ores[i][0] = rand() % GRID_SIZE; // Random X coordinate
        ores[i][1] = rand() % GRID_SIZE; // Random Y coordinate
    }

    printf("Welcome to Oreopolis, oh great miner. The lands filled with plenty of unearthed minerals."
           "gems(G) and ores(O) are hidden deep in the earth.\nThere is a shop (S) that you will have access to where"
           "you will be able to sell the mined minerals. but beware there are obstacles (X) that you will ecounter "
           "while on you journey. \nOnce you have made $100 or more in the shop you may access the shop. Good luck\n");

    while (true){

        // Print the grid
        printGrid(playerX,playerY,shopX,shopY,obstacles, gems, ores);

        // Ask for player movement input
        printf("\nUse WASD keys to move: ");
        scanf(" %c", &move);

        //The player movement around the grid//
        playerMovement(move,playerX,playerY,obstacles,ores,gems,bag,shopX,shopY);


        if (bag->totalMoney>=100){
            printf("Congrats oh daring miner. You have successfully made sufficient money");
            break;

        }

    }



    return 0;
}

// Function to print grid
void printGrid(int playerX, int playerY, int shopX,int shopY, int obstacles[][2], int gems[][2], int ores[][2]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {

            // Initialize boolean variables to track the presence of obstacles, gems, and ores
            bool isObstacle = false;
            bool isGem = false;
            bool isOre = false;
            bool isShop = false;
            bool isPlayer = false;

            // Check if the current cell contains an obstacle
            for (int k = 0; k < NUM_OBSTACLES; k++) {
                if (obstacles[k][0] == j && obstacles[k][1] == i) {
                    isObstacle = true;
                    break;
                }
            }

            // Check if the current cell contains a gem
            for (int k = 0; k < NUM_GEMS; k++) {
                if (gems[k][0] == j && gems[k][1] == i) {
                    isGem = true;
                    break;
                }
            }

            // Check if the current cell contains an ore
            for (int k = 0; k < NUM_ORES; k++) {
                if (ores[k][0] == j && ores[k][1] == i) {
                    isOre = true;
                    break;
                }
            }

            // Check if the current cell contains a shop
            if (j == shopX && i == shopY) {
                isShop = true;
            }

            // Check if the current cell contains a shop
            if (j == playerX && i == playerY) {
                isPlayer = true;
            }

            // Print appropriate symbol for the current cell
            if(isPlayer)
                printf("P  "); // Player symbol
            else if(isShop)
                printf("S  ");//Shop symbol
            else if (isGem)
                printf("G  "); // Gem symbol
            else if (isOre)
                printf("O  "); // Ore symbol
            else if(isObstacle)
                printf("X  "); // Obstacle symbol
            else
                printf(".  "); // Empty symbol
        }

        // Move to the next line after printing a row of the grid
        printf("\n");
    }
}


//Function for player movement//
void playerMovement(char move, int &playerX, int &playerY, int obstacles[][2],int ores[][2],int gems[][2],struct backPack *bag,int shopX,int shopY){

    int newX = playerX;
    int newY = playerY;

    //The player's new position depending on WASD key entered//
    if(playerX > 0 && move == 'A' || move == 'a'){
        newX--;
    }
    else if(playerX < GRID_SIZE-1 && move == 'D' || move == 'd'){
        newX++;
    }
    else if(playerY > 0 && move == 'W' || move == 'w'){
        newY--;
    }
    else if(playerY < GRID_SIZE-1 && move == 'S' || move == 's'){
        newY++;
    }
    else if(move =='I' || move == 'i'){
        viewInventory(bag);
    }
    else{
        printf("Invalid input, Re-enter input.\n");
    }

    //Determines the player position depending on whether they have found an obstacle, gem or ore//
    if(foundOre(newX,newY,ores,bag)== 1){
        playerX = newX;
        playerY = newY;
    }
    else if(foundGem(newX,newY,gems,bag) == 1){
        playerX = newX;
        playerY = newY;
    }
    else if(shopInteraction(newX,newY,shopX,shopY,bag) == 1){
        playerX = newX;
        playerY = newY;
    }
    else if(foundObstacle(newX,newY,obstacles) == 0){
        playerX = newX;
        playerY = newY;
    }



}

//Function to determine if player has found a obstacle//
int foundObstacle(int playerX, int playerY, int obstacles[][2]){
    for (int i = 0; i < NUM_OBSTACLES; i++) {
        if (obstacles[i][0] == playerX && obstacles[i][1] == playerY) {
            printf("You hit an obstacle\n");
            return 1;
        }
    }
    return 0;
}

//Function to determine if player has found an ore//
int foundOre(int playerX, int playerY,int ores[][2],struct backPack *bag){
    for (int k = 0; k < NUM_ORES; k++) {
        if (ores[k][0] == playerX && ores[k][1] == playerY) {
            //Adds mined ore to backpack//
            bag->minedOres += 1;

            //Remove mined ore from grid//
            ores[k][0] = -1;
            ores[k][1] = -1;

            //Alerts player of mined ore//
            printf("You have mined an ore\n");
            return 1;
        }
    }
    return 0;
}

//Function to determine if player has found a gem//
int foundGem(int playerX, int playerY,int gems[][2], struct backPack *bag){
    for (int k = 0; k < NUM_GEMS; k++) {
        if (gems[k][0] == playerX && gems[k][1] == playerY) {
            //Adds mined gem to backpack//
            bag->minedGems += 1;

            //Remove mined gem from grid//
            gems[k][0] = -1;
            gems[k][1] = -1;

            //Alerts player of mined gem//
            printf("You have mined an gem\n");
            return 1;
        }
    }
    return 0;
}

int shopInteraction(int playerX, int playerY, int shopX, int shopY, struct backPack *bag){
    //Variables//
    int oresSold = 0;
    int gemsSold = 0;

    if ( shopX== playerX && shopY == playerY) {
        printf("\nWelcome to the shop. Each gem is $10 and each ore is $5");

        //Checks how many gems the player would like to sell//
        printf("\nHow many gems would you like to sell: ");
        scanf("%d",&gemsSold);

        //Verify the number of gems entered by the user//
        if (gemsSold>bag->minedGems) {
            while(true){
                printf("Invalid entry, please re-enter the number of gems to sell: ");
                scanf("%d",&gemsSold);

                if (gemsSold<=bag->minedGems){
                    break;
                }
            }
        }

        bag->minedGems -=gemsSold;



        //Checks how many ores the player would like to sell//
        printf("\nHow many ores would you like to sell: ");
        scanf("%d",&oresSold);

        //Verify the number of ores entered by the user//
        if (oresSold>bag->minedOres) {
            while(true){
                printf("Invalid entry, please re-enter the number of ores to sell: ");
                scanf("%d",&oresSold);

                if (gemsSold<=bag->minedOres){
                    break;
                }
            }
        }

        //Subtract the number sold ores and gems from those in the bag//
        bag->minedOres -=oresSold;

        //Add the amount of money earned after selling//
        bag->totalMoney = bag->totalMoney+(gemsSold*10) + (oresSold*5);

        return 1;
    }


    return 0;

}

// Function to access the inventory
void viewInventory(struct backPack *bag) {

    // Write the inventory contents to a text file
    FILE *file = fopen("inventory.txt", "w");
    if (file == NULL) {
        printf("Error opening file!");
        return;
    }

    fprintf(file, "Bag contents:\n");
    fprintf(file, "Mined Gems: %d\n", bag->minedGems);
    fprintf(file, "Mined Ores: %d\n", bag->minedOres);
    fprintf(file, "Total Money: $%d\n", bag->totalMoney);

    fclose(file);

    // Open the text file
    system("notepad inventory.txt");
}