#ifndef GO_STATE_H
#define GO_STATE_H

#include "include.h"

using namespace std;

namespace Go {
	/*
	 * possible contents of a vertex
	 */
	enum Color : char {
		EMPTY = 0, BLACK = 1, WHITE = 2
	};

	class State {
	public:
		// action (x, y, c)
		short action = -2;
		Color player = BLACK;

		array<Color, BOARD_STONE_NUM> board;
		array<short, BOARD_STONE_NUM> mark, next;
		array<unsigned char, BOARD_STONE_NUM> qi;

		vector<uint64_t> historyState;

		State() {
			fill(board.begin(),  board.end(), EMPTY);
			fill(mark.begin(),   mark.end(), -1);
			fill(next.begin(),   next.end(), -1);
			fill(qi.begin(),     qi.end(),    0);

			historyState.push_back(0);
		}
	};

	/*
	 *  judge whether a state is terminated
	 */
	inline bool isTermination(State& s) {
		if (s.action == PASS &&
			s.parent != NULL &&
			s.parent->action == PASS)
			return true;
		return false;
	}

}
#endif
