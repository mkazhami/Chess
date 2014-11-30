#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <iostream>
#include "piece.h"
#include "display.h"
#include "textdisplay.h"
#include "graphicdisplay.h"


class Board {
	//singleton pattern
	static Board *instance;
	Board();

	//human or AI
	std::string whitePlayer;
	std::string blackPlayer;

	public:
	//variables to keep track of board information - used for Levels mostly
	int moveCount;
	bool wasBlackCheck;
	char whoCheckedBlack;
	bool wasWhiteCheck;
	char whoCheckedWhite;

	//2d array of Piece pointers - main board
	Piece ***board;
	
	//set players to be human or Level
	void setPlayers(std::string, std::string);
	
	//vector of the white pieces
	std::vector<Piece *> *white;
	//vector of the black pieces
	std::vector<Piece *> *black;
	
	//displays
	TextDisplay *display;
	GraphicDisplay *gDisplay;
	
	//text if TextDisplay, graphic if GraphicDisplay
	void setDisplay();
	
	//singleton pattern, constructs the object if necessary
	static Board *getInstance();
	
	//destructor
	~Board();
	
	//clears the pieces from the board
	void clearBoard();
	
	//set the given piece to the given position on the board
	void setPiece(char, int, int);
	
	//checks board for valid positions
	bool checkSetup();
	
	//automatically gives the default setup for chess
	void defaultSetup();
	
	//move the piece of the given position to the other given position - true if successful, false otherwise
	bool movePiece(int, int, int ,int);
	
	//remove piece from corresponding team vector
	void removePiece(int, int);
	
	//deletes the piece at the given position
	void deletePiece(int, int);
	
	//checks if given player is in check
	bool isCheck(char);
	
	//checks if either player is in checkmate
	char isCheckmate();
	
	//checks if there are no legal moves left
	bool isDraw(char);
	
	//promotes the pawn at the given position
	void promote(int, int);
	
	//update the valid moves of every Piece in the board
	void updateValidMoves();
	
	//update the legal moves of every Piece in the board
	void updateLegalMoves();
	
	//determine whether the setup of the board is legal or not
	bool isSetupProper();
};

#endif
