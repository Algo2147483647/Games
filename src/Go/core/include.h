#ifndef GO_INCLUDE_H
#define GO_INCLUDE_H

#include <stdio.h>
#include <vector>
#include <array>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

namespace Go {
#define PASS  -1
#define BOARD_SIZE 19 // For a standard board
#define BOARD_COLOR_NUM (BOARD_SIZE * BOARD_SIZE)

	/*
	 * possible contents of a vertex
	 */
	enum Color : char {
		EMPTY = 0, BLACK = 1, WHITE = -1
	};
}
#endif