#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "piece.h"
class Board;

class Knight: public Piece {
	public:
	Knight(Board *board);
	~Knight();
	//see piece.h for details
	void updateValidMoves();
	void updateLegalMoves();
	void deleteValidMoves();
	void deleteLegalMoves();
	bool updatePosition(int, int);
	bool isValid(int, int);
	bool isLegal(int, int);
	bool inRange(int, int);
};

#endif
