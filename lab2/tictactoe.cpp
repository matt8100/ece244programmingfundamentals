//
//  main.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file


#include <iostream>
#include <string>
using namespace std;

#include "globals.h"
#include "GameState.h"

// Function prototype for playMove
void playMove(GameState&);

// The main function
int main() {

    /**********************************************************************************/
    /* Create an initialized game state object                                        */
    /**********************************************************************************/
    GameState game_state;

    // Read two integers from the user that represent the row and column
    // the player would like to place an X or an O in
    // You can assume there will be no formatting errors in the input

    int row;
    int col;
    while (!game_state.get_gameOver()) {
        cout << "Enter row and column of a grid cell: ";
        cin >> row >> col;
        
        // Check that the read row and column values are valid grid coordinates
        if ( (row < 0) || (row > 2) || (col < 0) || (col > 2) ) {
            cout << "Invalid board coordinates " << row << " " << col << endl << endl;
        continue;
        }
        game_state.set_selectedRow(row);
        game_state.set_selectedColumn(col);
            
        playMove(game_state);

        // print board
        cout << "Selected row " << row << " and column " << col << endl;
        cout << "Game state after playMove:" << endl;
        cout << "Board:" << endl;
        for (int i = 0; i < boardSize; i++) {
            cout << "   ";
            for (int j = 0; j < boardSize; j++) {
                if (game_state.get_gameBoard(i,j) == X)
                    cout << 'X';
                else if (game_state.get_gameBoard(i,j) == O)
                    cout << 'O';
                else
                    cout << 'B';
                if (j != boardSize - 1)
                    cout << " ";
            }
            cout << endl;
        }
        string moveValid = (game_state.get_moveValid()) ? "true" : "false";
        string gameOver = (game_state.get_gameOver()) ? "true" : "false";
        cout << "moveValid: " << moveValid << endl;
        cout << "gameOver: " << gameOver << endl;
        cout << "winCode: " << game_state.get_winCode() << endl;
        cout << endl;
    }
    return 0;
}

