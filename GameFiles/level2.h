#ifndef _LEVEL2_H_
#define _LEVEL2_H_

#include "level.h"
class Board;

class Level2: public Level {
	//see level.h for details
	public:
	Level2(Board *board);
	void move();
};

#endif
