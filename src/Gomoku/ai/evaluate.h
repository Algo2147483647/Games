#ifndef GOMOKU_AI_EVALUATE_H
#define GOMOKU_AI_EVALUATE_H

#include "./core/Gomoku.h"

using namespace Gomoku;

namespace Gomoku_AI {
	inline short getNumberLineChess(State& s, short i, short k, short& block_num) {
		const static short step_x[4] = { 0, 1, 1, 1 };
		const static short step_y[4] = { 1, 0, 1,-1 };
		int x = i % BOARD_SIZE;
		int y = i / BOARD_SIZE;
		block_num = 0;

		// 前子
		int xt = x - step_x[k];
		int yt = y - step_y[k];
		if (s.isOutBoard(xt, yt))
			block_num = 1;
		else if (s.getBoard(xt, yt) == s.getBoard(x, y))
			return 0;
		else if (s.getBoard(xt, yt) != 0)
			block_num = 1;

		// 连线
		short num = 0;
		do {
			num++;
			xt = x + num * step_x[k];
			yt = y + num * step_y[k];
		} while (!s.isOutBoard(xt, yt) && s.getBoard(xt, yt) == s.getBoard(x, y));

		// 后子
		if (s.isOutBoard(xt, yt) || s.getBoard(xt, yt) != EMPTY)
			block_num++;
		return num;
	}

	inline int evaluate(State& s) {
		int reward = 0;

		for (short i = 0; i < BOARD_COLOR_NUM; i++) {
			if (s.getBoard(i) == EMPTY)
				continue;

			short sign = s.getBoard(i) == s.player ? 1 : -1;

			for (short k = 0; k < 4; k++) {
				short block_num = 0;
				int num = getNumberLineChess(s, i, k, block_num);

				if (num == 0) continue;
				else if (num >= 5)
					reward += sign * pow(10, 5);
				else if (block_num < 2)
					reward += sign * pow(10, num - block_num);
			}
		}
		return reward;
	}
}
#endif