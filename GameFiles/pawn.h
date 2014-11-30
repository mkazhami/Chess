#ifndef _PAWN_H_
#define _PAWN_H_

#include "piece.h"
class Board;

class Pawn: public Piece {
	public:
	Pawn(Board *board);
	~Pawn();
	//see piece.h for details
	void updateValidMoves();
	void updateLegalMoves();
	void deleteValidMoves();
	void deleteLegalMoves();
	bool updatePosition(int, int);
	bool isValid(int, int);
	bool isLegal(int, int);
	bool inRange(int, int);
	//determines whether the pawn is performing the en passant move
	bool isEnPassant(int, int);
};

#endif
