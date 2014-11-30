#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "piece.h"
class Board;

class Bishop: public Piece {
	public:
	Bishop(Board *board);
	~Bishop();
	//see piece.h for details
	void deleteValidMoves();
	void deleteLegalMoves();
	void updateValidMoves();
	void updateLegalMoves();
	bool updatePosition(int, int);
	bool isValid(int, int);
	bool isLegal(int, int);
	bool inRange(int, int);
};

#endif
