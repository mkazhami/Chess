#include "piece.h"
#include "board.h"

Piece::Piece(Board *board): board(board), position(Posn(0,0)), hasMoved(false) {}

void Piece::setPosition(Posn p) {
	position = p;
}

Piece::~Piece() {
	if(validMoves.size() != 0) validMoves.clear();
	if(legalMoves.size() != 0) legalMoves.clear();
}
