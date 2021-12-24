//
//  GameState.cpp
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

#include "globals.h"
#include "GameState.h"

// ECE244 Student: add you code below

GameState::GameState() {
  selectedRow = 0;
  selectedColumn = 0;
  moveValid = true;
  gameOver = false;
  winCode = 0;
  turn = true;
  for (int i = 0; i < boardSize; i++)
    for (int j = 0; j < boardSize; j++)
      gameBoard[i][j] = Empty;
}

int GameState::get_selectedRow() {
  return selectedRow;
}

int GameState::get_selectedColumn() {
  return selectedColumn;
}

void GameState::set_selectedRow(int value) {
  if (value >= 0 && value <= boardSize - 1)
    selectedRow = value;
}

void GameState::set_selectedColumn(int value) {
  if (value >= 0 && value <= boardSize - 1)
    selectedColumn = value;
}

bool GameState::get_moveValid() {
  return moveValid;
}

void GameState::set_moveValid(bool value) {
  moveValid = value;
}

bool GameState::get_gameOver() {
  return gameOver;
}

void GameState::set_gameOver(bool value) {
  gameOver = value;
}

int GameState::get_winCode() {
  return winCode;
}

void GameState::set_winCode(int value) {
  if (value >= 0 && value <= 8)
    winCode = value;
}

bool GameState::get_turn() {
  return turn;
}

void GameState::set_turn(bool value) {
  turn = value;
}

int GameState::get_gameBoard(int row, int col) {
  if ((row >= 0 && row <= boardSize - 1) && (col >= 0 && col <= boardSize -1))
    return gameBoard[row][col];
  return 0;
}

void GameState::set_gameBoard(int row, int col, int value) {
  if ((row >= 0 && row <= boardSize - 1) && (col >= 0 && col <= boardSize -1) && (value >= -1 && value <= 1))
    gameBoard[row][col] = value;
}