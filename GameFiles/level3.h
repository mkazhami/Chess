#ifndef _LEVEL3_H_
#define _LEVEL3_H_

#include "level.h"
class Board;

class Level3: public Level {
	//see level.h for details
	public:
	Level3(Board *board);
	void move();
};

#endif
