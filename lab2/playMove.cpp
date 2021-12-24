//
//  playMove.cpp
//  TicTacToe
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: write your code for playMove in this file

#include "globals.h"
#include "GameState.h"

void playMove(GameState& game_state) {
  int selectedRow = game_state.get_selectedRow();
  int selectedCol = game_state.get_selectedColumn();
  int move = (game_state.get_turn()) ? X : O;

  // check if move invalid
  if (game_state.get_gameBoard(selectedRow, selectedCol) != Empty)
    game_state.set_moveValid(false);
  else
    game_state.set_moveValid(true);

  // if move valid, make board and turn changes
  if (game_state.get_moveValid()) {
    game_state.set_gameBoard(selectedRow, selectedCol, move);
    game_state.set_turn(!game_state.get_turn());
  }

  // winCode check; select highest applicable
  int counter;

  // reverse diagonal check
  counter = 0;
  for (int i = boardSize - 1, j = 0; i >= 0 && j < boardSize; i--, j++) {
    if (game_state.get_gameBoard(i, j) == move)
      counter++;
    if (counter == 3) {
      game_state.set_winCode(8);
      goto endcheck;
    }
  }

  // diagonal check
  counter = 0;
  for (int i = 0, j = 0; i < boardSize && j < boardSize; i++, j++) {
    if (game_state.get_gameBoard(i, j) == move)
      counter++;
    if (counter == 3) {
      game_state.set_winCode(7);
      goto endcheck;
    }
  }

  // vertical check
  for (int j = 0; j < boardSize; j++) {
    counter = 0;
    for (int i = 0; i < boardSize; i++) {
      if (game_state.get_gameBoard(i, j) == move)
        counter++;
    }
    if (counter == 3) {
      game_state.set_winCode(j + 4);
      goto endcheck;
    }
  }

  // horizontal check
  for (int i = 0; i < boardSize; i++) {
    counter = 0;
    for (int j = 0; j < boardSize; j++) {
      if (game_state.get_gameBoard(i,j) == move)
        counter++;
    }
    if (counter == 3) {
      game_state.set_winCode(i + 1);
      goto endcheck;
    }
  }
  
  // tie check
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardSize; j++) {
      if (game_state.get_gameBoard(i, j) == Empty)
        goto endcheck;
    }
  }
  game_state.set_gameOver(true);

  endcheck:
  if (game_state.get_winCode())
    game_state.set_gameOver(true);
}
