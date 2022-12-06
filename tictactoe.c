#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define BOARDSIZE 3


int* board_create() {
    int* board = (int*)malloc(
        ((BOARDSIZE) * (BOARDSIZE)) * sizeof(int)
    );
    for(int i = 0; i < ((BOARDSIZE) * (BOARDSIZE)); i++) {
        board[i] = 0;
    }
    return board;
}


void board_print(int* board) {
    printf("Col:   0 1 2\n");
    for(int i = 0; i < (BOARDSIZE); i++) {
        printf("Row %d: ", i);
        for(int j = 0; j < (BOARDSIZE); j++) {
            switch(board[(i*(BOARDSIZE) + j)]) {
                case 0:
                    printf("_ ");
                    break;
                case 1:
                    printf("X ");
                    break;
                case 2:
                    printf("O ");
                    break;
            }
        }
        printf("\n");
    }
}


bool board_set(int* board, int pid, int xpos, int ypos) {
    if(board[xpos * (BOARDSIZE) + ypos] == 0) {
        board[xpos * (BOARDSIZE) + ypos] = pid;
        return true;
    }
    return false;
}


void board_destroy(int* board) {
    free(board);
}


char player_print(int pid) {
    switch(pid) {
        case 1:
            return 'X';
        case 2:
            return 'O';
        default:
            return '?';
    }
}


int player_next(int pid) {
    if (pid == 1) return 2;
    return 1;
};


int game_get_winner(int* board) {
    // 0 1 2
    // 3 4 5
    // 6 7 8
    if (board[0] != 0 && board[0] == board[1] && board[1] == board[2]) return board[0];
    if (board[3] != 0 && board[3] == board[4] && board[4] == board[5]) return board[3];
    if (board[6] != 0 && board[6] == board[7] && board[7] == board[8]) return board[6];
    if (board[0] != 0 && board[0] == board[3] && board[3] == board[6]) return board[0];
    if (board[1] != 0 && board[1] == board[4] && board[4] == board[7]) return board[1];
    if (board[2] != 0 && board[2] == board[5] && board[5] == board[8]) return board[2];
    if (board[0] != 0 && board[0] == board[4] && board[4] == board[8]) return board[0];
    if (board[2] != 0 && board[2] == board[4] && board[4] == board[6]) return board[2];
    return 0;
}


int game_play(int* board, int player) {
    printf("Current board: \n");
    board_print(board);
    
    printf("Current Player: %c\n", player_print(player));

    printf("Enter your play: ");
    int xpos, ypos;
    int res = scanf("%d %d", &xpos, &ypos);
    assert(res==2);
    printf("\n\n");

    if(!board_set(board, player, xpos, ypos)) {
        printf("Setting positon failed! (did someone play there already?)");
        return player;
    }

    return player_next(player);
}


void game_show_winner(int* board) {
    printf("Current board: \n");
    board_print(board);
    printf("Winner! %c\n", player_print(game_get_winner(board)));
}


int main() {
    int* board = board_create();
    int current_player = 1;

    while(!game_get_winner(board)) {
        current_player = game_play(board, current_player);
    };
    game_show_winner(board);

    board_destroy(board);
}
