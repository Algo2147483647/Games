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
#define BOARD_STONE_NUM BOARD_SIZE * BOARD_SIZE

	const static int
		adj_x[] = { 0, 0, 1,-1 },
		adj_y[] = { 1,-1, 0, 0 };
}
#endif