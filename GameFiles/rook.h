#ifndef _ROOK_H_
#define _ROOK_H_

#include "piece.h"
class Board;

class Rook: public Piece {
	public:
	Rook(Board *board);
	~Rook();
	//see piece.h for details
	bool updatePosition(int, int);
	bool isValid(int, int);
	bool isLegal(int, int);
};

#endif
