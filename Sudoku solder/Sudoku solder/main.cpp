#include <iostream>
#include <string>
#include "Board.hpp"

int main(int argc, char** argv) {
	auto board = sudoku::Board::Board(2 ,2 ,2);
	sudoku::Board::generateRndProblem(board, 1);
	sudoku::Board::showBoard(board);
	sudoku::Board::solveProblemUnique(board);
	return 0;
}

