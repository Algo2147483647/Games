#ifndef GOBANG_H
#define GOBANG_H
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;
/******************************************************************************
* 
*                    GoBang
* 
******************************************************************************/
namespace GoBang {

#define BOARD_SIZE 15
#define BLACK  1
#define WHITE -1

	typedef signed char CHESS;

	//----------------落子----------------
	static bool DropChess(vector<CHESS>& board, char x, char y, CHESS player) {
		if (board.isOut(x, y) || board(x, y) != 0)
			return false;
		board(x, y) = player;
		return true;
	}

	//----------------判断棋子连线----------------
	static char judgeLineChess(vector<CHESS>& board, char x, char y, char dx, char dy, char& flag) {
		flag = 0;  //连线的前后是否被堵住

		//前子
		int xt = x - dx,
			yt = y - dy;

		if (board.isOut(xt, yt))
			flag = 1;
		else {
			if (board(xt, yt) == board(x, y))
				return 0;
			if (board(xt, yt) != 0)
				flag = 1;
		}

		//连线
		char num = 1;
		xt = x + num * dx;
		yt = y + num * dy;

		while (!board.isOut(xt,yt) && board(xt,yt) == board(x, y)) {
			num++; 
			xt += dx;
			yt += dy;
		}

		//后子
		if (!board.isOut(xt, yt) || board(xt, yt) != 0)
			flag++;
		return num;
	}

	//----------------判断输赢----------------
	//算连子，连五判赢
	static CHESS judgeWin(vector<CHESS>& board) {
		const static char
			step_x[4] = { 0, 1, 1, 1 },
			step_y[4] = { 1, 0, 1,-1 };

		for (char y = 0; y < BOARD_SIZE; y++) {
			for (char x = 0; x < BOARD_SIZE; x++) {
				if (board(x, y) == 0) 
					continue;

				for (char k = 0; k < 4; k++) {
					//前子
					int xt = x - step_x[k],
						yt = y - step_y[k];
					if (!board.isOut(xt, yt) && board(xt, yt) == board(x, y))
						continue;

					//连线
					int num = 1;
					xt = x + step_x[k];
					yt = y + step_y[k];
					while (!board.isOut(xt, yt) && board(xt, yt) == board(x, y)) {
						num++;
						xt += step_x[k];
						yt += step_y[k];
					}
					if (num >= 5)
						return board(x, y);
				}
			}
		}
		return 0;
	}
}

#endif