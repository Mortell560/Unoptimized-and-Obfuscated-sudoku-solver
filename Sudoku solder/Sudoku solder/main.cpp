#include <iostream>
#include <string>
#include "Board.hpp"

int main(int argc, char** argv) {
	auto board = sudoku::Board::Board(4 ,4 , 2);
	sudoku::Board::generateRndProblem(board, 3);
	sudoku::Board::showBoard(board);
	sudoku::Board::solveProblemUnique(board);
	return 0;
}

