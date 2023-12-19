#ifndef GO_REWARD_H
#define GO_REWARD_H

#include "include.h"
#include "state.h"

using namespace std;

namespace Go {
	/*
	 *	calculate reach color to help compute reward
	 */
	inline int calculateReachColor(array<Color, BOARD_STONE_NUM>& board, const int color) {
		auto reachable = 0;
		auto bd = vector<bool>(BOARD_STONE_NUM, false);
		auto open = queue<int>();

		for (auto i = 0; i < BOARD_STONE_NUM; i++) {
			if (board[i] == color) {
				reachable++;
				bd[i] = true;
				open.push(i);
			}
		}

		while (!open.empty()) {
			auto v = open.front();
			open.pop();

			for (auto j = 0; j < 4; j++) {
				int xt = v % BOARD_SIZE + adj_x[j],
					yt = v / BOARD_SIZE + adj_y[j],
					vt = yt * BOARD_SIZE + xt;

				if (xt >= 0 && xt < BOARD_SIZE &&
					yt >= 0 && yt < BOARD_SIZE &&
					!bd[vt] && board[vt] == EMPTY) {
					reachable++;
					bd[vt] = true;
					open.push(vt);
				}
			}
		}
		return reachable;
	}

	/*
	 *  compute reward of termination state and judge victory
	 */
	inline char computeReward(State& s) {
		float komi = 7.5;

		auto white = calculateReachColor(s.board, WHITE);
		auto black = calculateReachColor(s.board, BLACK);
		return (black - white - komi) >= 0 ? BLACK : WHITE;
	}
}
#endif
