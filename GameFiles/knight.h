#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "piece.h"
class Board;

class Knight: public Piece {
	public:
	Knight(Board *board);
	~Knight();
	//see piece.h for details
	bool updatePosition(int, int);
	bool isValid(int, int);
	bool isLegal(int, int);
};

#endif
