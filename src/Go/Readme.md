# Go  

[TOC]

## Core

|file name|function|
|---|---|
|[Go.h](Go.h)| main |
|[include.h](include.h)| include |
|[state.h](state.h)| state |
|[action.h](action.h)| action |
|[reward.h](reward.h)| reward |
|[updateState.h](updateState.h)| update state |
|||

### State

- action
- player
- board
- mark
- next
- qi

#### Zobrist Hashing

### Action

#### Disable global isomorphism

函数检查当前传入的状态 state 的 board 成员是否与祖父状态的 board 成员相同。

#### Not allow suicide

### $S_t \overset{A_t}{\rightarrow} S_{t+1}$

#### Remove stone block with no Qi

#### Merge stone block

### Reward

#### Score: Number of spaces reachable

1. 函数`calculateReachColor`接收两个参数：一个颜色数组`board`和一个表示特定颜色的整数`color`。`BOARDNUM`是一个预定义的常量，表示`board`数组的大小。
2. `reachable`变量初始化为0，它用于记录可达的空格数量。
3. `bd`是一个布尔类型的向量，初始化所有元素为`false`，用于标记网格中的每个位置是否已经被访问过。
4. `open`是一个队列，用于进行宽度优先搜索（BFS）。
5. 第一个`for`循环遍历游戏板上的所有位置。如果某个位置的颜色与给定的颜色相同，这个位置就被认为是可达的，`reachable`会增加，相应的`bd`数组位置会被标记为`true`，并且该位置会被加入到`open`队列中。
6. 接下来的`while`循环是一个宽度优先搜索，用于找到所有从起始颜色出发可达的`EMPTY`（未被占据的）位置。这个循环会一直进行，直到没有更多的位置需要检查。
7. 在循环内部，它取出队列`open`的前端元素，代表当前正在检查的位置。
8. 接着，内部的`for`循环遍历该位置的四个相邻位置（由`adj_x`和`adj_y`数组给出的偏移量表示）。对于每个相邻位置，计算新的`xt`和`yt`坐标，以及`vt`，即该位置在`board`数组中的索引。
9. 如果计算出的相邻位置坐标在棋盘内，并且该位置未被访问过，同时位置颜色为`EMPTY`，则将其标记为已访问，并将该位置的索引加入到`open`队列中。
10. 最后，函数返回`reachable`的值，即从给定颜色出发，可以到达的`EMPTY`位置的总数。

#### Win or loss calculation (Komi)

		float komi = 7.5;
	
		auto white = calculateReachColor(s.board, WHITE);
		auto black = calculateReachColor(s.board, BLACK);
		return (black - white - komi) >= 0 ? BLACK : WHITE;

## AI 

|file name|function|
|---|---|
|[Go_AI_Multithread.h](Go_AI_Multithread.h)| AI of Go |
|[Go_AI.h](Go_AI.h)| old AI |
|||

## Demo

|file name|function|
|---|---|
|||