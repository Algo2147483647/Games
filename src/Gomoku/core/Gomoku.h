#ifndef GOMOKU_H
#define GOMOKU_H

#include "state.h"

namespace Gomoku {
	inline Color play(State& s, short x, short y) {
		if (!s.setBoard(x, y, s.player)) {
			return INVALID;
		}
		s.player = (s.player == BLACK ? WHITE : BLACK);
		return s.isTermination();
	}
}

#endif