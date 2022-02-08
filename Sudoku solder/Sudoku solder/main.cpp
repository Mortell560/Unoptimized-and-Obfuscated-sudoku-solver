#include <iostream>
#include <string>
#include "Board.hpp"

int main(int argc, char** argv) {
	auto board = sudoku::Board::Board();
	sudoku::Board::generateRndProblem(board, 200);
	sudoku::Board::showBoard(board);
	sudoku::Board::solveProblem(board);
	sudoku::Board::showBoard(board);
	return 0;
}

