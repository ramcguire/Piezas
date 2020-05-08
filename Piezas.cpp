#include "Piezas.h"

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
 **/

/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and
 * specifies it is X's turn first
 **/
Piezas::Piezas() {
  board = vector<vector<Piece> >(4, vector<Piece>(3, Blank));
  turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
 **/
void Piezas::reset() {
  board = vector<vector<Piece> >(4, vector<Piece>(3, Blank));
  turn = X;
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
 **/
Piece Piezas::dropPiece(int column) {
  Piece current = turn;
  if (column > 3 || column < 0) {
    turn = (turn == X ? O : X);
    return Invalid;

  } else if (board[column][2] != Blank) {
    turn = (turn == X ? O : X);
    return Blank;
  }
  int row = 0;
  while (board[column][row] != Blank) {
    row++;
  }
  board[column][row] = current;
  turn = (turn == X ? O : X);
  return current;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
 **/
Piece Piezas::pieceAt(int row, int column) {
  if (row > 2 || row < 0 || column > 3 || column < 0) {
    return Invalid;
  }
  return board[column][row];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
 **/
Piece Piezas::gameState() {
  // check if board not filled/game not over
  // iterate all columns and check highest row (2)
  for (int i = 0; i < 4; i++) {
    if (board[i][2] == Blank) {
      return Invalid;
    }
  }
  int x_highest = 0;
  int o_highest = 0;
  int currentScore = 0;

  Piece currentPiece = board[0][0];
  if (currentPiece == X) x_highest = 1;
  if (currentPiece == O) o_highest = 1;

  // check all the columns
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      // if currentPiece does not match next spot
      // check if current score is higher, and store if it is
      if (currentPiece != board[i][j]) {
        switch (currentPiece) {
          case X:
            if (currentScore > x_highest) x_highest = currentScore;
            break;
          case O:
            if (currentScore > o_highest) o_highest = currentScore;
            break;
          default:
            break;
        }
        // reset current score for new piece
        currentScore = 0;
        currentPiece = board[i][j];
      }
      // increment current score
      currentScore++;
    }
  }
  switch (currentPiece) {
    case X:
      if (currentScore > x_highest) x_highest = currentScore;
      break;
    case O:
      if (currentScore > o_highest) o_highest = currentScore;
      break;
    default:
      break;
  }
  currentScore = 0;
  currentPiece = board[0][0];

  // check all the rows
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      if (currentPiece != board[j][i]) {
        switch (currentPiece) {
          case X:
            if (currentScore > x_highest) x_highest = currentScore;
            break;
          case O:
            if (currentScore > o_highest) o_highest = currentScore;
            break;
          default:
            break;
        }
        // reset current score for new piece
        currentScore = 0;
        currentPiece = board[j][i];
      }
      // increment current score
      currentScore++;
    }
  }
  switch (currentPiece) {
    case X:
      if (currentScore > x_highest) x_highest = currentScore;
      break;
    case O:
      if (currentScore > o_highest) o_highest = currentScore;
      break;
    default:
      break;
  }

  if (x_highest > o_highest) {
    return X;
  } else if (o_highest > x_highest) {
    return O;
  }
  return Blank;
}