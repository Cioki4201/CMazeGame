#include <stdio.h>
#include "maze_gen.c"

#include <conio.h>
#include <ctype.h>

//---------------------------- Variables ----------------------------

#define PLAYER '@'
#define EMPTY_CELL ' '

int width, height, seed, cellSize, fogRadius;
int currentPlayerCell[2] = {1,0};
int gameOver = 0;
int collectedPotions = 0;
char exitMessage[75] = "";

//---------------------------- Functions ----------------------------
void displayMazeAndPotions(struct maze maze){
    printf("Potions: %i\n", collectedPotions);

    int y; //row selector
    int x; //row element selector
    for(y=0; y<maze.h; y++){
        for(x=0; x<maze.w; x++){
            printf("%c", maze.a[y][x]);
        }
        printf("\n");
    }
}

void displayMazeAndPotionsWithFog(struct maze maze,char mazeWithFog[(height*2)+1][(width*2)+1], int fog){
    printf("Potions: %i\n", collectedPotions);

    int currentY = currentPlayerCell[0];
    int currentX = currentPlayerCell[1];
    mazeWithFog[maze.h][maze.w];


    for (int i=1; i<=fog; i++){
        mazeWithFog[currentY][currentX] = maze.a[currentY][currentX]; //Updates player position

        if (currentY-i >= 0) { //if not out of bounds ->
            mazeWithFog[currentY - i][currentX] = maze.a[currentY - i][currentX]; //Reveals cell above
        } else{}

        if(currentY+i <= (height*2)+1) { //if not out of bounds ->
            mazeWithFog[currentY + i][currentX] = maze.a[currentY + i][currentX]; //Reveals cell below
        } else{}

        if(currentX-i >= 0) { //if not out of bounds ->
            mazeWithFog[currentY][currentX - i] = maze.a[currentY][currentX - i]; //Reveals left cell
        } else{}

        if(currentX+i <= (width*2)+1) {  //if not out of bounds ->
            mazeWithFog[currentY][currentX + i] = maze.a[currentY][currentX + i]; //Reveals right cell
        } else{}

        if((currentY-i >= 0) && (currentX+i <= (width*2)+1)) {  //if not out of bounds ->
            mazeWithFog[currentY - i][currentX + i] = maze.a[currentY - i][currentX + i]; //Reveals top-right cell
        } else{}

        if((currentY-i >= 0) && (currentX-i >= 0)) {  //if not out of bounds ->
            mazeWithFog[currentY - i][currentX - i] = maze.a[currentY - i][currentX - i]; //Reveals top-left cell
        } else{}

        if((currentY+i <= (height*2)+1) && (currentX-i >= 0)) {  //if not out of bounds ->
            mazeWithFog[currentY + i][currentX - i] = maze.a[currentY + i][currentX - i]; //Reveals bottom-left cell
        } else{}

        if((currentY+i <= (height*2)+1) && (currentX+i <= (width*2)+1)) {  //if not out of bounds ->
            mazeWithFog[currentY + i][currentX + i] = maze.a[currentY + i][currentX + i]; //Reveals bottom-right cell
        } else{}
   }

    int y; //row selector
    int x; //row element selector
    for(y=0; y<maze.h; y++){
        for(x=0; x<maze.w; x++){
            printf("%c", mazeWithFog[y][x]);
        }
        printf("\n");
    }
}


void moveInDirection(struct maze maze){
    char direction;
    direction = getch();
    int currentY = currentPlayerCell[0];
    int currentX = currentPlayerCell[1];

    // Scenario detection
    int scenario = 0;
    if(direction == 'w'){scenario = 1;}
    else if(direction == 's'){scenario = 2;}
    else if(direction == 'a'){scenario = 3;}
    else if(direction == 'd'){scenario = 4;}
    else{scenario = 5;}

    // Switch Implementation
    switch (scenario) {
        case 1: //--------------------------- Move up [w] ---------------------------
            if ( maze.a[currentY-1] [currentPlayerCell[1]] == WALL){break;} //Cannot move into wall

            else if (maze.a[currentY-1] [currentX] == EMPTY_CELL){ //If move is valid, adjust 2D array
                maze.a[currentY-1] [currentX] = PLAYER; //Sets next chosen cell character to the player character '@'
                maze.a[currentY] [currentX] = EMPTY_CELL; //Sets previous player cell to a blank space ' '
                currentPlayerCell[0]--; //Update currentPlayerCell variable
                break;
            }


            else if (maze.a[currentY-1] [currentX] == POTION){ //If next chosen cell contains potion, adjust 2D array and increase potion counter
                maze.a[currentY-1] [currentX] = PLAYER; //Sets next chosen cell character to the player character '@'
                maze.a[currentY] [currentX] = EMPTY_CELL; //Sets previous player cell to a blank space ' '
                collectedPotions++;
                currentPlayerCell[0]--; //Update currentPlayerCell variable
                break;
            }else {break;}


        case 2: //--------------------------- Move down [s] ---------------------------
            if ( maze.a[currentY+1] [currentPlayerCell[1]] == WALL){break;} //Cannot move into wall

            else if (maze.a[currentY+1] [currentX] == EMPTY_CELL){ //If move is valid, adjust 2D array
                maze.a[currentY+1] [currentX] = PLAYER; //Sets next chosen cell character to the player character '@'
                maze.a[currentY] [currentX] = EMPTY_CELL; //Sets previous player cell to a blank space ' '
                currentPlayerCell[0]++; //Update currentPlayerCell variable
                break;
            }


            else if (maze.a[currentY+1] [currentX] == POTION){ //If next chosen cell contains potion, adjust 2D array and increase potion counter
                maze.a[currentY+1] [currentX] = PLAYER; //Sets next chosen cell character to the player character '@'
                maze.a[currentY] [currentX] = EMPTY_CELL; //Sets previous player cell to a blank space ' '
                collectedPotions++;
                currentPlayerCell[0]++; //Update currentPlayerCell variable
                break;
            } else {break;}


        case 3: //--------------------------- Move left [a] ---------------------------
            if ( maze.a[currentY] [currentX-1] == WALL){break;} //Cannot move into wall

            else if (maze.a[currentY] [currentX-1] == EMPTY_CELL){ //If move is valid, adjust 2D array
                maze.a[currentY] [currentX-1] = PLAYER; //Sets next chosen cell character to the player character '@'
                maze.a[currentY] [currentX] = EMPTY_CELL; //Sets previous player cell to a blank space ' '
                currentPlayerCell[1] = currentPlayerCell[1] - 1; //Update currentPlayerCell variable
                break;
            }

            else if (maze.a[currentY] [currentX-1] == POTION){ //If next chosen cell contains potion, adjust 2D array and increase potion counter
                maze.a[currentY] [currentX-1] = PLAYER; //Sets next chosen cell character to the player character '@'
                maze.a[currentY] [currentX] = EMPTY_CELL; //Sets previous player cell to a blank space ' '
                collectedPotions++;
                currentPlayerCell[1] = currentPlayerCell[1] - 1; //Update currentPlayerCell variable
                break;
            }else {break;}


        case 4: //--------------------------- Move right [d] ---------------------------
            if ( maze.a[currentY] [currentX+1] == WALL){break;} //Cannot move into wall

            else if (maze.a[currentY] [currentX+1] == EMPTY_CELL){ //If move is valid, adjust 2D array
                maze.a[currentY] [currentX+1] = PLAYER; //Sets next chosen cell character to the player character '@'
                maze.a[currentY] [currentX] = EMPTY_CELL; //Sets previous player cell to a blank space ' '
                currentPlayerCell[1]++; //Update currentPlayerCell variable
                break;
            }

            else if (maze.a[currentY] [currentX+1] == POTION){ //If next chosen cell contains potion, adjust 2D array and increase potion counter
                maze.a[currentY] [currentX+1] = PLAYER; //Sets next chosen cell character to the player character '@'
                maze.a[currentY] [currentX] = EMPTY_CELL; //Sets previous player cell to a blank space ' '
                collectedPotions++;
                currentPlayerCell[1]++; //Update currentPlayerCell variable
                break;
            }

            //If player has all potions and reaches exit, print message and exit...
            else if ((currentY == maze.h-2 ) && (currentX == maze.w-1 ) && (collectedPotions == 3)){
                system("@cls||clear");
                displayMazeAndPotions(maze);
                printf("\nYou have succeeded in escaping the maze!\n\nPress any key to exit...");
                getch();
                exit(0);
            }

            //If player does not have all potions and reaches exit, print message telling them you need all potions to finish
            else if ((currentY == maze.h-2 ) && (currentX == maze.w-1 ) && (collectedPotions != 3)){
                strcpy(exitMessage, "\nYou need three potions to pass!");
                break;
            }

            else {break;}


        case 5: //--------------------------- Invalid Keystroke ---------------------------
            break;
    }
}

int main() {

    //---------------------------- User Inputs for Maze Generation ----------------------------

    printf("Width=");
    scanf("%i", &width);

    printf("Height=");
    scanf("%i", &height);

    printf("Random seed=");
    scanf("%i", &seed);

    printf("Cell size=");
    scanf("%i", &cellSize);

    printf("Fog radius=");
    scanf("%i", &fogRadius);
    printf("\n");

    struct maze mainMaze = generate_maze(width, height, cellSize, seed); //Generates Maze

    char mazeWithFog[mainMaze.h][mainMaze.w]; // Generating empty maze to be filled in by player if fog = true
    mainMaze.a[1][0] = PLAYER;

    int y; //row selector
    int x; //row element selector
    for(y=0; y<mainMaze.h; y++){
        for(x=0; x<mainMaze.w; x++){
            mazeWithFog[y][x] = ' ';
        }
        printf("\n");
    }

    system("@cls||clear");

    while(gameOver < 1) {

        if(fogRadius <= 0){displayMazeAndPotions(mainMaze); }
        else {displayMazeAndPotionsWithFog(mainMaze, mazeWithFog, fogRadius);}

        printf("%s\n", exitMessage);
        moveInDirection(mainMaze);
        system("@cls||clear");

    }

    return 0;
}


