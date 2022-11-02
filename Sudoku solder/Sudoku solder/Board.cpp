#include "Board.hpp"
#include <iostream> /* std::cout */
#include <utility> /* std::pair */
#include <string> /* std::string */
#include <time.h> /* time */
#include <random> /* srand, rand */

namespace sudoku {

	//!\brief Shows a board smh
	void Board::showBoard(Board& board) {
		for (int i{ 0 }; i < Board::getRow(board); i++) {
			if (i % Board::getSquareSize(board) == 0) {
				std::cout << '\n';
			}

			std::string to_show{ " " };

			for (int j{ 0 }; j < Board::getCol(board); j++) {
				to_show += std::to_string(board._board[j + i * Board::getCol(board)]) + " ";

				if ((j + 1) % Board::getSquareSize(board) == 0) {
					to_show += " ";
				}
			}
			std::cout << to_show << '\n';
		}
	}
	//!\brief Generates a random sudoku problem with n random numbers added
	//! (which is kind of problematic since sometimes boards won't have any solution and as n decreases this might reach a critical threshold where solutions go nullref)
	//! --> solution: input your own board and problem yourself and use solveProblemUnique
	void Board::generateRndProblem(Board& board, const int n) {
		srand(time(0));
		/*
		if (n > Board::getCol(board) * Board::getRow(board)) {
			std::cout << "Unfortunately i don't like memory leaks so use a smaller n. Thanks" << '\n';
			return;
		}
		*/
		for (int i{ 0 }; i < n; i++) {
			int randNum = rand() % 9 + 1;
			int x = rand() % Board::getCol(board);
			int y = rand() % Board::getRow(board);
			auto coord = std::pair<int, int>(x, y);
			if (Board::checkForCell(board, coord, randNum)){ Board::setNumCell(board, coord, randNum); }
		}
	}

	//!\brief Checks if we can put a number in a cell.
	//! It basically checks the square, row and column at the given coords to check if the same number num exists in the formers
	bool Board::checkForCell(Board& board, const std::pair<int, int>& coords, const int num) {
		auto& [x, y] = coords;
		if (Board::isInBoard(board, coords) && 0 < num && num << 10) {

			for (int i{ 0 }; i < Board::getRow(board); i++) {
				if (board._board[x + i * Board::getRow(board)] == num) {
					return false;
				}
			}

			for (int j{ 0 }; j < Board::getCol(board); j++) {
				if (board._board[j + y * Board::getCol(board)] == num) {
					return false;
				}
			}

			const int squareSize = Board::getSquareSize(board);
			//just use a board to understand this bullshit oh and also // doesn't work in C++
			int x_square_coord = (int)(x /squareSize) * squareSize;
			int y_square_coord = (int)(y / squareSize) * squareSize;

			for (int k{ 0 }; k < Board::getSquareSize(board); k++) {
				for (int l{ 0 }; l < Board::getSquareSize(board); l++) {
					if (board._board[x_square_coord + l + (k + y_square_coord) * Board::getCol(board)] == num) {
						return false;
					}
				}
			}
		}
		return true;
	}
	
	//!\brief This one is obvious you banana
	void Board::setNumCell(Board& board, const std::pair<int, int>& coords, const int num) {
		auto& [x, y] = coords;
		if (Board::isInBoard(board, coords) && 0 < num && num < 10) { board._board[x + y * Board::getCol(board)] = num; }
	}

	//!\brief Resets a cell back to 0
	void Board::removeNumCell(Board& board, const std::pair<int, int>& coords) {
		auto& [x, y] = coords;
		if (Board::isInBoard(board, coords)) {
			auto pos = x + y * Board::getCol(board);
			board._board[pos] = 0;
		}
	}

	//!\brief Returns true if the given coords correspond to an empty spot
	bool Board::isEmptyCell(Board& board, const std::pair<int, int>& coords) {
		auto& [x, y] = coords;
		int pos = x + y * Board::getCol(board);
		if (Board::isInBoard(board, coords) && board._board[pos] == 0) { return true; }
		return false;
	}

	//!\brief Returns a vector with all the empty positions
	std::vector<std::pair<int, int>> Board::getAllEmptyPositions(Board& board) {
		std::vector<std::pair<int, int>> list_pos;
		for (int i{ 0 }; i < Board::getRow(board); i++) {
			for (int j{ 0 }; j < Board::getCol(board); j++) {
				auto coords = std::pair<int, int>(j, i);
					if (Board::isEmptyCell(board, coords)) {
						list_pos.push_back(coords);
					}
			}
		}
		return list_pos; //if the board is full, vector.size() will be equal to 0
	}

	//!\brief Returns True if the pos is in the board
	bool Board::isInBoard(Board& board, const std::pair<int,int>& coords) {
		auto& [x, y] = coords;
		return (0 <= x && x < Board::getCol(board)) && (0 <= y && y < Board::getRow(board));
	}

	std::vector<int> Board::getPossibleNumCell(Board& board, const std::pair<int,int>& coords) {
		std::vector<int> list;
		for (int i{ 9 }; i > 0; i--) {
			if (Board::checkForCell(board, coords, i)) { list.push_back(i); }
		}
		return list;
	}

	//!\brief Solves the problem for ya (all solutions are included and it's very fast unless there are too many solutions)
	void Board::solveProblem(Board& board) {
		for (int j{ 0 }; j < Board::getCol(board); j++) {
			for (int i{ 0 }; i < Board::getRow(board); i++) {
				if (Board::isEmptyCell(board, std::make_pair(i, j))) {
					for (int num{ 1 }; num < 10; num++) {
						auto coords = std::pair<int, int>(i, j);
						if (Board::checkForCell(board, coords, num)) {
							setNumCell(board, coords, num);
							Board::solveProblem(board);
							removeNumCell(board, coords);
						}
					}
					return;
				}
			}
		}
		Board::showBoard(board);
	}

	//!\brief Same thing as solveProblem but for one solution
	void Board::solveProblemUnique(Board& board) {
		if (Board::getAllEmptyPositions(board).size() == 0) {
			std::cout << "\nHere's one solution \n";
			Board::showBoard(board);
			return;
		}
		auto possible_pos = Board::getAllEmptyPositions(board);
		auto possible_num = Board::getPossibleNumCell(board, possible_pos[0]);
		if (possible_num.size() > 0) {
			setNumCell(board, possible_pos[0], possible_num[0]);
			Board::solveProblem(board);
			removeNumCell(board, possible_pos[0]);
		}
	}

	//!\brief Get the total number of rows in a given board
	int Board::getRow(Board& board) { return board._row; }
	
	//!\brief Get the total number of columns in a given board
	int Board::getCol(Board& board) { return board._col; }

	//!\brief Get the size of a square in a given board (sudoku related)
	int Board::getSquareSize(Board& board) { return board._SquareSize; }

	
}
