#ifndef _LEVEL4_H_
#define _LEVEL4_H_

#include "level.h"
#include <queue>
class Board;

struct Move {
	int oldRow, oldCol, newRow, newCol;
	Move(int, int, int, int);
};

class Level4: public Level {
	std::queue<Move> whiteMoves;
	std::queue<Move> blackMoves;	
	//see level.h for details
	public:
	Level4(Board *board);
	~Level4();
	void move();
};

#endif
