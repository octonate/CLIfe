#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define BOARD_WIDTH 110 
#define BOARD_HEIGHT 70

int gameBoard[BOARD_HEIGHT][BOARD_WIDTH] = {{0}};

void boardRandomize(int board[BOARD_HEIGHT][BOARD_WIDTH]) {
    for (int row = 1; row < BOARD_HEIGHT - 1; row++) {
        for (int col = 1; col < BOARD_WIDTH - 1; col++) {
            board[row][col] = (rand() % 2 == 0);
        }
    }
}

void boardDraw(int board[BOARD_HEIGHT][BOARD_WIDTH]) {
    system("clear");
    char output[BOARD_WIDTH * BOARD_HEIGHT * 2 + BOARD_WIDTH];
    int idx = 0;
    for (int row = 0; row < BOARD_HEIGHT; row++) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            if (board[row][col] == 1) {
                output[idx] = '#';
                idx++;
            } else {
                output[idx] = ' ';
                idx++;
            }
            output[idx] = ' ';
            idx++;
        }
        output[idx] = '\n';
        idx++;
    }
    printf("%s", output);
}

void boardNext(int board[BOARD_HEIGHT][BOARD_WIDTH]) {
    int nextBoard[BOARD_HEIGHT][BOARD_WIDTH] = {{0}};

    for (int row = 1; row < BOARD_HEIGHT - 1; row++) {
        for (int col = 1; col < BOARD_WIDTH - 1; col++) {
            int alive = (board[row][col] == 1);
            int neighbors = 0;
            neighbors += (board[row + 1][col] == 1);
            neighbors += (board[row - 1][col] == 1);
            neighbors += (board[row][col + 1] == 1);
            neighbors += (board[row][col - 1] == 1);
            neighbors += (board[row + 1][col + 1] == 1);
            neighbors += (board[row + 1][col - 1] == 1);
            neighbors += (board[row - 1][col + 1] == 1);
            neighbors += (board[row - 1][col - 1] == 1);

            if (alive && (neighbors == 3 || neighbors == 2)) {
                nextBoard[row][col] = 1;
            }

            if (!alive && neighbors == 3) {
                nextBoard[row][col] = 1;
            }
        }
    }
    memcpy(board, nextBoard, sizeof(nextBoard));
}

int main() {
    srand(time(NULL));
    boardRandomize(gameBoard);
    while (1) {
        boardDraw(gameBoard);
        boardNext(gameBoard);
        usleep(60000);
    }

    return 0;
}
