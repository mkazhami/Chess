#ifndef _LEVEL1_H_
#define _LEVEL1_H_

#include "level.h"
class Board;

class Level1: public Level {
	//see level.h for details
	public:
	Level1(Board *board);
	void move();
};

#endif
