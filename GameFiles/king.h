#ifndef _KING_H_
#define _KING_H_

#include "piece.h"
class Board;

class King: public Piece {
	public:
	King(Board *board);
	~King();
	//see piece.h for details
	bool updatePosition(int, int);
	bool isValid(int, int);
	bool isLegal(int, int);
	//determine whether castling is being attempted and if it is valid/legal
	bool isCastling(int, int);
};

#endif
