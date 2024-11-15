#include<stdio.h>
#include<time.h>
#include<ctype.h>
#include<stdlib.h>

const char PLAYER ='T';
const char BOT = 'Z';
char board[3][3];
char winner = ' ';

void menuScreen();
void menuSelect();
void selectDifficulty();
void playEasyGame();
void playHardGame();
void exitGame();
int checkFreeSpaces();
void resetMap();
void playerMove();
void computerEasyMove();
void computerHardMove();
char checkWinner();
void printWinner();
void map();
int checkWinningMove(char symbol);
int fibonacci();
int randomizer();

int main() {
    resetMap();
    menuScreen();
    return 0;
}

void resetMap () {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
    winner = ' ';
}

void map() {
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

void menuScreen() {
    printf("             _               _   _        _____\n");
    printf("  __ _  __ _| |    __ _  ___| |_(_) ___  |  ___|__  __ _ _ __\n");
    printf(" / _` |/ _` | |   / _` |/ __| __| |/ __| | |_ / _ \\/ _` | '__|\n");
    printf("| (_| | (_| | |__| (_| | (__| |_| | (__  |  _|  __/ (_| | |\n");
    printf(" \\__, |\\__,_|____|\\__,_|\\___|\\__|_|\\___| |_|  \\___|\\__,_|_|\n");
    printf(" |___/\n");
    printf("Welcome to gaLactic Fear!\n");
    printf("1. Play\n");
    printf("2. Exit\n");
    printf("Select an Option : (1|2)...");
    menuSelect();
}

void menuSelect() {
    char C;
    scanf("%c", &C);
    switch (C) {
        case '1':
            selectDifficulty();
            break;
        case '2':
            exitGame();
            break;
        default:
            for(int i = 0; i<32;i++) {
                printf("\n");
            }
            menuScreen();
            break;
    }
}

void exitGame() {
    for(int i = 0; i < 32; i++) {
        printf("\n");
    }
    printf ("Thank you for playing!!");
    printf("\nExiting the game...\n");
    //Make a pause before exiting fully.
    for(int i = 0; i < 1599999999; i++){
    }
    return 0;
}

void selectDifficulty() {
    char Diff;
    for(int i = 0; i<32; i++) {
        printf("\n");
    }
    printf("Select Difficulty: \n");
    printf("1. Easy\n");
    printf("2. Hard\n");
    printf("Select an Option (1|2): ... ");
    scanf("%c", &Diff);
    switch (Diff) {
        case '1': playEasyGame(); break;
        case '2': playHardGame(); break;
        default: selectDifficulty(); break;
    }
}

int checkFreeSpaces() {
    int freeSpaces = 9;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] != ' '){
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

char checkWinner() {
    //rows
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return board[i][0];
        }
    }
    //Columns
    for(int j = 0; j < 3; j++) {
        if(board[0][j] == board[1][j] && board[0][j] == board[2][j]) {
            return board[0][j];
        }
    }
    //diagonals
    for(int j = 0; j < 3; j++) {
        if(board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
            return board[0][0];
        }
    }
    for(int j = 0; j < 3; j++) {
        if(board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
            return board[0][2];
        }
    }
    return ' ';
}

void playerMove() {
    int x, y;
    do {
        printf("You are playing as 'T' and the bot is playing as 'Z'\n\n");
        printf("To make a move, enter the row and column seperated by a space.\n");
        printf("For example, to mark the top-left corner , input: 1 1\n");
        printf("Enter your move (row[1-3] and column[1-3]): ");
        scanf("%d %d", &x, &y);
        x--; y--;
        //check if board space inputted is empty or not
        if(board[x][y] != ' '){
            printf("Invalid Move!\n");
        } else {
            board[x][y] = PLAYER;
            break;
        }
    } while(board[x][y] != ' ');

}

void computerEasyMove() {
    //randomize move with time
    srand(time(0));
    int x, y;

    if(checkFreeSpaces() > 0){
        do{
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = BOT;
    } else {
        printWinner(' ');
    }
}

void computerHardMove() {
    //Fibonacci if even = choose winning, if odd, choose defense, if no win or defense needed = random
    int fibovalue = fibonacci(randomizer());
    if(fibovalue % 2 == 0) {
        int move = -1;

        // 1. Check if BOT can win
        move = checkWinningMove(BOT);
        if (move != -1) {
            board[move / 3][move % 3] = BOT;
            return;
        }

        // 2. Check if player can win (block them)
        move = checkWinningMove(PLAYER);
        if (move != -1) {
            board[move / 3][move % 3] = BOT;
            return;
        }

        // 3. Take center
        if (board[1][1] == ' ') {
            board[1][1] = BOT;
            return;
        }

        // 4. Take a corner
        int corners[] = {0, 2, 6, 8};
        for (int i = 0; i < 4; i++) {
            if (board[corners[i] / 3][corners[i] % 3] == ' ') {
                board[corners[i] / 3][corners[i] % 3] = BOT;
                return;
            }
        }

        // 5. Take a side
        int sides[] = {1, 3, 5, 7};
        for (int i = 0; i < 4; i++) {
            if (board[sides[i] / 3][sides[i] % 3] == ' ') {
                board[sides[i] / 3][sides[i] % 3] = BOT;
                return;
            }
        }
    } else {
        int move = -1;

        // 1. Check if player can win (block them)
        move = checkWinningMove(PLAYER);
        if (move != -1) {
            board[move / 3][move % 3] = BOT;
            return;
        }

        // 2. Take center
        if (board[1][1] == ' ') {
            board[1][1] = BOT;
            return;
        }

        // 3. Take a corner
        int corners[] = {0, 2, 6, 8};
        for (int i = 0; i < 4; i++) {
            if (board[corners[i] / 3][corners[i] % 3] == ' ') {
                board[corners[i] / 3][corners[i] % 3] = BOT;
                return;
            }
        }

        // 4. Take a side
        int sides[] = {1, 3, 5, 7};
        for (int i = 0; i < 4; i++) {
            if (board[sides[i] / 3][sides[i] % 3] == ' ') {
                board[sides[i] / 3][sides[i] % 3] = BOT;
                return;
            }
        }
    }
}

void playEasyGame() {

    for(int i = 0; i < 32; i++){
        printf("\n");
    }
    while (winner == ' ' && checkFreeSpaces() != 0) {
        map();
        playerMove();
        winner = checkWinner();
        if (winner != ' ' || checkFreeSpaces() == 0) {
            break;
        }

        computerEasyMove();
        winner = checkWinner();
        if (winner != ' ' || checkFreeSpaces() == 0) {
            break;
        }
    }
    map();
    printWinner(winner);
    printf("Press any key to return to menu...");
    char key;
    getchar();
    scanf("%c", &key);
    if(key){
        for(int i = 0; i < 32; i++) {
            printf("\n");
        }
        resetMap();
        menuScreen();
    }
}

void playHardGame() {
    for(int i = 0; i < 32; i++){
        printf("\n");
    }
    while (winner == ' ' && checkFreeSpaces() != 0) {
        map();
        playerMove();
        winner = checkWinner();
        if (winner != ' ' || checkFreeSpaces() == 0) {
            break;
        }

        computerHardMove();
        winner = checkWinner();
        if (winner != ' ' || checkFreeSpaces() == 0) {
            break;
        }
    }
    map();
    printWinner(winner);
    printf("Press any key to return to menu...");
    char key;
    getchar();
    scanf("%c", &key);
    if(key){
        for(int i = 0; i < 32; i++) {
            printf("\n");
        }
        resetMap();
        menuScreen();
    }
}

void printWinner() {
    if (winner == PLAYER) {
        printf("You Win!\n");
    } else if (winner == BOT) {
        printf("You Lose!\n");
    } else {
        printf("It's a Tie!\n");
    }
}

int randomizer() {
    srand(time(0));
    int x = rand() % 10;
    return x;
}

int fibonacci(int n) {
    if (n == 1 || n == 2) return 1;
	return fibonacci(n-1) + fibonacci(n-2); //This will loop until n == 1 or n == 2
}

int checkWinningMove(char symbol) {
    for (int i = 0; i < 3; i++) {
        // Check rows
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == ' ') return i * 3 + 2;
        if (board[i][0] == symbol && board[i][1] == ' ' && board[i][2] == symbol) return i * 3 + 1;
        if (board[i][0] == ' ' && board[i][1] == symbol && board[i][2] == symbol) return i * 3 + 0;

        // Check columns
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == ' ') return 2 * 3 + i;
        if (board[0][i] == symbol && board[1][i] == ' ' && board[2][i] == symbol) return 1 * 3 + i;
        if (board[0][i] == ' ' && board[1][i] == symbol && board[2][i] == symbol) return 0 * 3 + i;
    }

    // Check diagonals
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == ' ') return 8;
    if (board[0][0] == symbol && board[1][1] == ' ' && board[2][2] == symbol) return 4;
    if (board[0][0] == ' ' && board[1][1] == symbol && board[2][2] == symbol) return 0;

    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == ' ') return 6;
    if (board[0][2] == symbol && board[1][1] == ' ' && board[2][0] == symbol) return 4;
    if (board[0][2] == ' ' && board[1][1] == symbol && board[2][0] == symbol) return 2;

    return -1;
}
