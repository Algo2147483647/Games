#ifndef GOMOKU_AI_POLICY_H
#define GOMOKU_AI_POLICY_H

#include <vector>
#include "./core/Gomoku.h"
#include "evaluate.h"

using namespace Gomoku;

namespace Gomoku_AI {
	static constexpr auto MaxLevel = 5;
	static array<int, BOARD_COLOR_NUM> evaluate_result;

	inline bool updateState(State& s, short& action) {
		const static short step_x[] = { 0, 0, 1,-1, 1,-1, 1,-1 };
		const static short step_y[] = { 1,-1, 0, 0, 1,-1,-1, 1 };

		for (; action < BOARD_COLOR_NUM; action++) {
			if (s.getBoard(action) != EMPTY)
				continue;

			for (int k = 0; k < 8; k++) {
				int xt = action % BOARD_SIZE + step_x[k],
					yt = action / BOARD_SIZE + step_y[k];

				if (!s.isOutBoard(xt, yt) && s.getBoard(xt, yt) != EMPTY && s.setBoard(action, s.player)) {
					s.player = (s.player == BLACK ? WHITE : BLACK);
					return true;
				}
			}
		}
		return false;
	}

	inline int Policy(State& s, short level = 0, int alpha = -0x7fffffff, int beta = 0x7fffffff) {
		if (level > MaxLevel || s.isTermination() != EMPTY)
			return evaluate(s);
		int max =-0x7fffffff,
			min = 0x7fffffff;

		short action = 0;
		while (updateState(s, action)) {
			int score = Policy(s, level + 1, alpha, beta);

			// restore the original state
			s.board[action] = EMPTY;
			s.player = (s.player == BLACK ? WHITE : BLACK);
			if(level == 0)
				evaluate_result[action] = score;
			action++;

			if (level % 2 == 0)
				max = max >= score ? max : score, alpha = alpha >= score ? alpha : score;
			else 
				min = min <= score ? min : score, beta = beta <= score ? beta : score;
			if (alpha >= beta) break;
		}
		
		return level % 2 == 0 ? max : min;
	}

}
#endif