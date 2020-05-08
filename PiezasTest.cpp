/**
 * Unit Tests for Piezas
 **/

#include <gtest/gtest.h>

#include "Piezas.h"

class PiezasTest : public ::testing::Test {
 protected:
  PiezasTest() {}             // constructor runs before each test
  virtual ~PiezasTest() {}    // destructor cleans up after tests
  virtual void SetUp() {}     // sets up before each test (after constructor)
  virtual void TearDown() {}  // clean up after each test, (before destructor)
};

TEST(PiezasTest, sanityCheck) { ASSERT_TRUE(true); }

TEST(PiezasTest, check_empty_board) {
  Piezas game = Piezas();
  ASSERT_EQ(game.pieceAt(0, 0), Blank);
}

TEST(PiezasTest, check_empty_board2) {
  Piezas game = Piezas();
  ASSERT_EQ(game.pieceAt(2, 3), Blank);
}

TEST(PiezasTest, piece_at_out_of_bounds) {
  Piezas game = Piezas();
  ASSERT_EQ(game.pieceAt(-1, 3), Invalid);
}

TEST(PiezasTest, piece_at_out_of_bounds2) {
  Piezas game = Piezas();
  ASSERT_EQ(game.pieceAt(0, -1), Invalid);
}

TEST(PiezasTest, piece_at_out_of_bounds3) {
  Piezas game = Piezas();
  ASSERT_EQ(game.pieceAt(8, 0), Invalid);
}

TEST(PiezasTest, piece_at_out_of_bounds4) {
  Piezas game = Piezas();
  ASSERT_EQ(game.pieceAt(0, 8), Invalid);
}

TEST(PiezasTest, empty_board_game_state) {
  Piezas game = Piezas();
  ASSERT_EQ(game.gameState(), Invalid);
}

TEST(PiezasTest, drop_piece_X) {
  Piezas game = Piezas();
  game.dropPiece(0);
  ASSERT_EQ(game.pieceAt(0, 0), X);
}

TEST(PiezasTest, drop_piece_full_column) {
  Piezas game = Piezas();
  game.dropPiece(0);
  game.dropPiece(0);
  game.dropPiece(0);
  ASSERT_EQ(game.dropPiece(0), Blank);
}

TEST(PiezasTest, drop_piece_out_of_range) {
  Piezas game = Piezas();
  ASSERT_EQ(game.dropPiece(-1), Invalid);
}

TEST(PiezasTest, drop_piece_out_of_range2) {
  Piezas game = Piezas();
  ASSERT_EQ(game.dropPiece(5), Invalid);
}

TEST(PiezasTest, drop_piece_out_of_range_toggles_turn) {
  Piezas game = Piezas();
  game.dropPiece(5);
  ASSERT_EQ(game.dropPiece(1), O);
}

TEST(PiezasTest, drop_piece_O) {
  Piezas game = Piezas();
  game.dropPiece(0);
  game.dropPiece(0);
  ASSERT_EQ(game.pieceAt(1, 0), O);
}

TEST(PiezasTest, reset_clears_board) {
  Piezas game = Piezas();
  game.dropPiece(0);
  game.reset();
  ASSERT_EQ(game.pieceAt(0, 0), Blank);
}

TEST(PiezasTest, drop_piece_result) {
  Piezas game = Piezas();
  ASSERT_EQ(game.dropPiece(0), X);
}

TEST(PiezasTest, turn_is_toggled) {
  Piezas game = Piezas();
  game.dropPiece(0);
  ASSERT_EQ(game.dropPiece(0), O);
}

TEST(PiezasTest, reset_turn) {
  Piezas game = Piezas();
  game.dropPiece(0);
  game.reset();
  ASSERT_EQ(game.dropPiece(0), X);
}

TEST(PiezasTest, game_result_x_winner) {
  Piezas game = Piezas();
  game.dropPiece(0);
  game.dropPiece(0);
  game.dropPiece(1);
  game.dropPiece(0);

  game.dropPiece(2);
  game.dropPiece(1);
  game.dropPiece(3);
  game.dropPiece(1);

  game.dropPiece(2);
  game.dropPiece(3);
  game.dropPiece(2);
  game.dropPiece(3);

  ASSERT_EQ(game.gameState(), X);
}

TEST(PiezasTest, game_result_o_winner) {
  Piezas game = Piezas();
  game.dropPiece(0);
  game.dropPiece(0);
  game.dropPiece(0);
  game.dropPiece(1);

  game.dropPiece(2);
  game.dropPiece(1);
  game.dropPiece(3);
  game.dropPiece(2);

  game.dropPiece(2);
  game.dropPiece(3);
  game.dropPiece(3);
  game.dropPiece(1);

  ASSERT_EQ(game.gameState(), O);
}

TEST(PiezasTest, game_result_tie) {
  Piezas game = Piezas();
  game.dropPiece(0);
  game.dropPiece(1);
  game.dropPiece(2);
  game.dropPiece(3);

  game.dropPiece(0);
  game.dropPiece(1);
  game.dropPiece(2);
  game.dropPiece(3);

  game.dropPiece(0);
  game.dropPiece(1);
  game.dropPiece(2);
  game.dropPiece(3);

  ASSERT_EQ(game.gameState(), Blank);
}

TEST(PiezasTest, game_result_x_winner2) {
  Piezas game = Piezas();
  game.dropPiece(0);
  game.dropPiece(1);
  game.dropPiece(0);
  game.dropPiece(2);

  game.dropPiece(1);
  game.dropPiece(3);
  game.dropPiece(2);
  game.dropPiece(0);

  game.dropPiece(3);
  game.dropPiece(1);
  game.dropPiece(2);
  game.dropPiece(3);

  ASSERT_EQ(game.gameState(), O);
}

TEST(PiezasTest, game_result_not_finished) {
  Piezas game = Piezas();
  game.dropPiece(0);
  game.dropPiece(1);
  game.dropPiece(2);
  game.dropPiece(3);

  ASSERT_EQ(game.gameState(), Invalid);
}