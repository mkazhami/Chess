#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "piece.h"
class Board;

class Queen: public Piece {
	public:
	Queen(Board *board);
	~Queen();
	//see piece.h for details
	bool updatePosition(int, int);
	bool isValid(int, int);
	bool isLegal(int, int);
};

#endif
