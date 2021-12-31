#pragma once
#include <utility> /* std::pair */
#include <vector> /* std::vector<T> */
#include <iostream> /* std::cout, std::endl */

namespace sudoku {

	//!\brief Class that handles the board and the solving methods (and it's also the most dangerous class in existance)
	class Board {
	public:
		Board() {
			_board = std::vector<int>(81, 0);
		};

		Board(int const row, int const col, int const SquareSize = 3) 
			: _row(row), _col(col), _board(std::vector<int>(col*row)), _SquareSize(SquareSize)
		{
			if (row % SquareSize != 0 || col % SquareSize != 0) {
				std::cout << "Time for you to join mex son. Invalid col, row or SquareSize" << std::endl;
				std::exit(-1);
			};
		}
		
		//Getters

		int static getRow(Board& board);
		int static getCol(Board& board);
		int static getSquareSize(Board& board);

		//Misc

		void static showBoard(Board& board);
		std::vector<std::pair<int, int>> static getAllEmptyPositions(Board& board);
		void static generateRndProblem(Board& board, const int n);
		void static solveProblem(Board& board);
		void static solveProblemUnique(Board& board);

		//setters and checkers (Cell related)
		
		bool static isEmptyCell(Board& board, const std::pair<int, int>& coords);
		bool static isInBoard(Board& board, const std::pair<int, int>& coords);
		bool static checkForCell(Board& board, const std::pair<int, int>& coords, const int num);
		void static setNumCell(Board& board, const std::pair<int, int>& coords, const int num);
		void static removeNumCell(Board& board, const std::pair<int, int>& coords);
		std::vector<int> static getPossibleNumCell(Board& board, const std::pair<int, int>& coords);
		

	private:
		int _row{ 9 };
		int _col{ 9 };
		int _SquareSize{3}; // aka 3*3 = 1 square
		std::vector<int> _board; // We use a vector since arrays can't handle things like int[n] where n isn't constant when we compile the code because the compiler doesn't like that
	};
}
