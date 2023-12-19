#ifndef GO_H
#define GO_H

#include "state.h"
#include "updateState.h"
#include "reward.h"
#include "zobristHash.h"

using namespace std;

namespace Go {
	/*
	 *  generate next state
	 */
	//void init() {
	//	zobrist_init();
	//}

	inline State* nextState(State& s, int action) {
		State* s_ = new State();
		*s_ = s;
		s_->parent = &s;
		s_->player = (BLACK ? WHITE : BLACK);
		s_->action = action;

		if(updateState(*s_))
			return s_;
		else {
			s_->parent = NULL;
			delete s_;
			return NULL;
		}
	}
}

#endif