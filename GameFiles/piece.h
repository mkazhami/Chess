#ifndef _PIECE_H_
#define _PIECE_H_

#include <vector>
#include "posn.h"
class Board;

class Piece {
	public:
	//pointer to a board so that we can formulate a legal move
	Board *board;
	//current position of the piece on the board
	Posn position;
	//keep track of double moves (for pawn)
	int doubleMove;
	//keep track of whether a piece has moves (pawn double move or castling)
	bool hasMoved;
	//set the position
	void setPosition(Posn);
	Piece(Board *board);
	virtual ~Piece();
	//black (b) or white (w)
	char colour;
	//type of piece - p = pawn, b = bishop, r = rook, k = knight, q = queen, k = king -- lower case for black, upper case for white
	char id;
	//vector of legal moves
	std::vector<Posn *> validMoves;
	std::vector<Posn *> legalMoves;
	//determine whether a move is valid - is it positionally possible
	virtual bool isValid(int, int)=0;
	//determine whether a move is legal - does it put you in check
	virtual bool isLegal(int, int)=0;
	//determine whether a move is in the range of the board
	virtual bool inRange(int, int);
	//inRange helper function - returns absolute value
	int absolute(int);
	//update the vectors
	void updateValidMoves();
	void updateLegalMoves();
	//clear the vectors
	void deleteValidMoves();
	void deleteLegalMoves();
	//attempt to update position - returns true if successful, false otherwise
	virtual bool updatePosition(int, int)=0;
};
// most of these functions behave similarily between piece's subclass
// the documentation of the similar functions are in pawn.cc
// but any distinct function in a subclass will has documentation within the function
#endif
