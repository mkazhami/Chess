#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "piece.h"
class Board;

class Queen: public Piece {
	public:
	Queen(Board *board);
	~Queen();
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
