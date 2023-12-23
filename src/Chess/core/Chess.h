#ifndef CHESS_H
#define CHESS_H

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include "state.h"
#include "action.h"

using namespace std;

namespace Chess {
	inline State& play(State& s) {
		updateState(s);
		s.player = -s.player;
		createActionSet(s);
		return s;
	}
}
#endif