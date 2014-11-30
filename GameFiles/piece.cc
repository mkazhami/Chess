#include "piece.h"
#include "board.h"

Piece::Piece(Board *board): board(board), position(Posn(0,0)), hasMoved(false) {}

void Piece::updateValidMoves() {
	deleteValidMoves();
        for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                        if(isValid(i, j)){
                                Posn *temp = new Posn(i,j);
                                validMoves.push_back(temp);
                        }
                }
        }
}

void Piece::updateLegalMoves() {
	deleteLegalMoves();
	for(int i = 0; i < validMoves.size(); i++){
		if(isLegal(validMoves[i]->row, validMoves[i]->col)){
			Posn *temp = new Posn(validMoves[i]->row, validMoves[i]->col);
			legalMoves.push_back(temp);
		}
	}
}

void Piece::deleteValidMoves() {
	for(int i = 0; i < validMoves.size(); i++){
                Posn *temp = validMoves[i];
                delete temp;
                temp = 0;
        }
        validMoves.clear();
}

void Piece::deleteLegalMoves() {
	for(int i = 0; i < legalMoves.size(); i++){
                Posn *temp = legalMoves[i];
                delete temp;
                temp = 0;
        }
        legalMoves.clear();
}

bool Piece::inRange(int row, int col) {
        if(row < 0 || row > 7 || col < 0 || col > 7) return false;
        if(row == position.row && col == position.col) return false;
        return true;
}


void Piece::setPosition(Posn p) {
	position = p;
}

int Piece::absolute(int num) {
	if(num < 0) return -num;
	return num;
}

Piece::~Piece() {
	if(validMoves.size() != 0) validMoves.clear();
	if(legalMoves.size() != 0) legalMoves.clear();
}
