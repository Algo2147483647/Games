#ifndef GOMOKU_STATE_H
#define GOMOKU_STATE_H

#include <array>

using namespace std;

namespace Gomoku {

	static constexpr auto BOARD_SIZE = 15;
	static constexpr auto BOARD_COLOR_NUM = BOARD_SIZE * BOARD_SIZE;

	enum Color : char {
		EMPTY = 0, BLACK = 1, WHITE = -1, INVALID = -2
	};

	const static char step_x[4] = { 0, 1, 1, 1 };
	const static char step_y[4] = { 1, 0, 1,-1 };

	class State {
	public:
		Color player = WHITE;
		array<Color, BOARD_COLOR_NUM> board;

		State() {
			fill(board.begin(), board.end(), EMPTY);
		}

		inline Color& getBoard(int x, int y) {
			return board[y * BOARD_SIZE + x];
		}

		inline bool setBoard(int x, int y, Color color) {
			if (x < 0 || x >= BOARD_SIZE ||
				y < 0 || y >= BOARD_SIZE)
				return false;
			if (board[y * BOARD_SIZE + x] != EMPTY)
				return false;
			board[y * BOARD_SIZE + x] = color;
			return true;
		}

		inline bool isOutBoard(int x, int y) {
			if (x < 0 || x >= BOARD_SIZE ||
				y < 0 || y >= BOARD_SIZE)
				return true;
			return false;
		}

		inline Color isTermination() {
			for (char y = 0; y < BOARD_SIZE; y++) {
				for (char x = 0; x < BOARD_SIZE; x++) {
					if (getBoard(x, y) == EMPTY)
						continue;

					for (char k = 0; k < 4; k++) {
						// Has the location been searched
						int xt = x - step_x[k],
							yt = y - step_y[k];
						if (!isOutBoard(xt, yt) && getBoard(xt, yt) == getBoard(x, y))
							continue;

						// Á¬Ïß
						int num = 0;
						do {
							num++;
							xt = x + step_x[k] * num;
							yt = y + step_y[k] * num;
						} while (!isOutBoard(xt, yt) && getBoard(xt, yt) == getBoard(x, y));
						if (num >= 5)
							return getBoard(x, y);
					}
				}
			}
			return EMPTY;
		}
	};
}

#endif