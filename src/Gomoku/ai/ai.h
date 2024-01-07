#ifndef GOMOKU_AI_H
#define GOMOKU_AI_H

#include "./core/Gomoku.h"
#include "evaluate.h"
#include "policy.h"

using namespace Gomoku;
namespace Gomoku_AI {
	inline int run(State& s) {
		fill(evaluate_result.begin(), evaluate_result.end(), -0x7FFFFFFF);
		return Policy(s);
	}
};

#endif