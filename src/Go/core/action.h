#ifndef GO_ACTION_H
#define GO_ACTION_H

#include "include.h"
#include "state.h"

using namespace std;

namespace Go {
	/*
	 *  Disable global isomorphism
	 */
	inline bool judgeJie(State& state) {
		State* s = &state;

		for (int i = 0; i <= 2; i++) {
			if (s->parent != NULL && s->parent->parent != NULL) {
				s = s->parent->parent;

				if (state.board == s->board)
					return true;
			}
			else break;
		}
		return false;
	}

	/*
	 *  not allow suicide
	 */
	inline bool isSuicide(State& s) {
		for (int j = 0; j < 4; j++) {
			int xt = s.action % BOARD_SIZE + adj_x[j],
				yt = s.action / BOARD_SIZE + adj_y[j],
				vt = yt * BOARD_SIZE + xt;

			if (xt < 0 || xt >= BOARD_SIZE ||
				yt < 0 || yt >= BOARD_SIZE)
				continue;

			//�����ж�
			if (s.board[vt] == EMPTY)
				return false;

			if ((s.board[vt] == s.player && s.qi[s.mark[vt]] != 1) || 	//�����ң�Ӧֻһ��
				(s.board[vt] != s.player && s.qi[s.mark[vt]] == 1)) 	//���ǵУ�Ӧ�ز�ֻһ��
				return false;
		}

		return true;
	}
}
#endif