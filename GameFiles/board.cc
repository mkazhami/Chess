#include "board.h"
#include "display.h"
#include "textdisplay.h"
#include "graphicdisplay.h"
#include "piece.h"
#include "pawn.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "queen.h"
#include "king.h"
#include "posn.h"
#include <vector>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
using namespace std;

Board *Board::instance = 0;

Board *Board::getInstance() {
	//if board was not yet constructed
	if(instance == 0){
		instance = new Board;
	}
	return instance;
}

void Board::setDisplay() { //sets the displays for the board
	gDisplay = new GraphicDisplay;
	display = new TextDisplay(gDisplay);
}

void Board::setPlayers(string white, string black){
	whitePlayer = white;
	blackPlayer = black;
}

Board::Board() { //constructor creates a 2D array of piece pointers. It's a virtual board that the piece and board class will use
	board = new Piece **[8];
	for(int i = 0; i < 8; i++){
		board[i] = new Piece*[8];
		for(int j = 0 ; j < 8; j++){
			board[i][j] = 0;
		}
	}
	//creating a vector of pieces for each side
	white = new vector<Piece *>;
	black = new vector<Piece *>;
	moveCount = 0;
	wasBlackCheck = false;
	wasWhiteCheck = false;
}


Board::~Board() { //destructor that frees its 2D array and the pieces currently on the board
	clearBoard();
	for(int i = 0; i < 8; i++){
		delete []board[i];
	}
	delete []board;
	board = 0;
	if(display != 0) delete display;
	if(gDisplay != 0) delete gDisplay;
	white->clear();
	black->clear();
	delete white;
	delete black;
}

void Board::defaultSetup() { //sets up the board to have pieces in their traditional proper starting positions
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(i == 0){
				if(j == 0 || j == 7){
					setPiece('r', i, j);
				}
				else if(j == 1 || j == 6){
					setPiece('n', i, j);
				}
				else if(j == 2 || j == 5){
					setPiece('b', i, j);
				}
				else if(j == 3){
					setPiece('q', i, j);
				}
				else if(j == 4){
					setPiece('k', i, j);
				}
			}
			else if(i == 1){
				setPiece('p', i, j);
			}
			else if(i == 6){
				setPiece('P', i, j);
			}
			else if(i == 7){
				if(j == 0 || j == 7){
					setPiece('R', i, j);
				}
				else if(j == 1 || j == 6){
					setPiece('N', i, j);
				}
				else if(j == 2 || j == 5){
					setPiece('B', i, j);
				}
				else if(j == 3){
					setPiece('Q', i, j);
				}
				else if(j == 4){
					setPiece('K', i, j);
				}
			}
		}
	}
}

void Board::clearBoard() { //used at the beginning of each game to remove all the pieces off the board
	//for all the pieces it has to free all their fields
	for(int i = 0; i < white->size(); i++){
		Piece *temp = (*white)[i];
		board[temp->position.row][temp->position.col] = 0;
		temp->deleteValidMoves();
		temp->deleteLegalMoves();
		if(temp != 0) delete temp;
		temp = 0;
	}
	white->clear();
	for(int i = 0; i < black->size(); i++){
		Piece *temp = (*black)[i];
		board[temp->position.row][temp->position.col] = 0;
		temp->deleteValidMoves();
		temp->deleteLegalMoves();
		if(temp != 0) delete temp;
		temp = 0;
	}
	black->clear();
	display->clearBoard();
	gDisplay->clearMessage();
	moveCount = 0;
}


bool Board::isSetupProper() { //checks if the board is setup properly before a game can begin
	bool wKing = false; //checks if there exists a white king
	bool bKing = false; //checks if there exists a black king
	bool moreThanOneWhite = false; //checks if there is more than one white king
	bool moreThanOneBlack = false; //checks if there is more than one black king
	bool whitePawnFail = false; //checks if the white pawn is not at the top or bottom of the row
	bool blackPawnFail = false; //checks if the black pawn is not at the top or bottom of the row
	bool blackCheck = false; //checks if the black king is in check 
	bool whiteCheck = false; //checks if the white king is in check


	for(int i = 0; i < white->size(); i++){
		if((*white)[i]->id == 'K'){
			if(wKing == true) moreThanOneWhite = true;
			else wKing = true;
		}
		else if((*white)[i]->id == 'P'){
			if((*white)[i]->position.row == 0 || (*white)[i]->position.row == 7){
				whitePawnFail = true;
			}
		}
	}



	for(int i = 0; i < black->size(); i++){
		if((*black)[i]->id == 'k'){
			if(bKing == true) moreThanOneBlack = true;
			else bKing = true;
		}
		else if((*black)[i]->id == 'p'){
			if((*black)[i]->position.row == 0 || (*black)[i]->position.row == 7){
				blackPawnFail = true;
			}
		}
	}
	
	updateValidMoves();
	updateLegalMoves();
	//has to update possible and legal moves before it can check for checks
	if(isCheck('b')) blackCheck = true;
	if(isCheck('w')) whiteCheck = true;
	for(int i = 0; i < white->size(); i++){
		(*white)[i]->deleteValidMoves();
		(*white)[i]->deleteLegalMoves();
	}
	for(int i = 0; i < black->size(); i++){
		(*black)[i]->deleteValidMoves();
		(*black)[i]->deleteLegalMoves();
	}

	//To have a proper setup, it must not make any of the following errors
	if(wKing == false || bKing == false || moreThanOneWhite == true || moreThanOneBlack == true || whitePawnFail == true || blackPawnFail == true || blackCheck == true || whiteCheck == true){
		cout << endl << "Setup is not complete:" << endl;
		if(wKing == false) cout << "White king does not exist" << endl;
		if(bKing == false) cout << "Black king does not exist" << endl;
		if(moreThanOneWhite == true) cout << "Only one white king allowed" << endl;
		if(moreThanOneBlack == true) cout << "Only one black king allowed" << endl;
		if(whitePawnFail == true) cout << "White pawn is not allowed on rows 0 or 7" << endl;
		if(blackPawnFail == true) cout << "Black pawn is not allowed on rows 0 or 7" << endl;
		if(blackCheck == true) cout << "Black king is in check" << endl;
		if(whiteCheck == true) cout << "White king is in check" << endl;
		return false;
	}
	return true;
}


void Board::setPiece(char piece, int row, int col) { //sets a piece for the board
	if(board[row][col] != 0){ //if a piece already exists in its position, it gets deleted
		removePiece(row, col);
		deletePiece(row, col);
	}

	//chooses the appropriate piece subclass
	if(piece == 'p' || piece == 'P') board[row][col] = new Pawn(instance);
	else if(piece == 'r' || piece == 'R') board[row][col] = new Rook(instance);
	else if(piece == 'b' || piece == 'B') board[row][col] = new Bishop(instance);
	else if(piece == 'n' || piece == 'N') board[row][col] = new Knight(instance);
	else if(piece == 'q' || piece == 'Q') board[row][col] = new Queen(instance);
	else if(piece == 'k' || piece == 'K') board[row][col] = new King(instance);
	
	//selects the colour for the piece
	if(piece >= 'a' && piece <= 'z'){
		board[row][col]->colour = 'b';
		black->push_back(board[row][col]);
	}
	else{
		board[row][col]->colour = 'w';
		white->push_back(board[row][col]);
	}
	
	//sets the fields for the piece
	board[row][col]->id = piece;
	Posn position(row, col);
	board[row][col]->setPosition(position);

	display->draw(piece, row, col); //notifies the display
}

bool Board::movePiece(int oldrow, int oldcol, int newrow, int newcol) { //moves a piece in the board. Returns true if move was successful, false otherwise
	gDisplay->clearMessage(); //clear any messages about checks in the graphics display
	if(board[oldrow][oldcol]->updatePosition(newrow, newcol) == false){ 
		//the piece could not move to the specified position, the function returns false
		return false;
	}
	else{
		board[oldrow][oldcol] = 0; //sets the hold position in the 2D array to be null
		
		//if pawn needs to be promoted
		if((board[newrow][newcol]->id == 'p' || board[newrow][newcol]->id == 'P') && (newrow == 0 || newrow == 7)){
			promote(newrow, newcol);
		}
		
		display->undraw(oldrow, oldcol); //undraws where it was 
		display->draw(board[newrow][newcol]->id, newrow, newcol); //draws the piece in its new position
		moveCount++;
		return true;
	}
}

void Board::removePiece(int row, int col) { //removes a piece from the vector of pieces
	char piece = board[row][col]->id;
	if(piece >= 'a' && piece <= 'z'){ //has to find which vector it's in by checking its colour
		for(int i = 0; i < black->size(); i++){
			if((*black)[i]->position.row == row && (*black)[i]->position.col == col){
				black->erase(black->begin() + i); //removes it from the vector
			}
		}
	}
	else{
		for(int i = 0; i < white->size(); i++){
			if((*white)[i]->position.row == row && (*white)[i]->position.col == col){
				white->erase(white->begin() + i);
			}
		}
	}
	//display->undraw(row, col);
}

void Board::deletePiece(int x, int y) { //removes the piece at the coordinates from the board and frees it 
	if(board[x][y] != 0) delete board[x][y];
	board[x][y] = 0;
	display->undraw(x, y); //notifies display
}

void Board::updateValidMoves(){ //calls updateValidMoves on all the pieces
	for(int i = 0; i < black->size(); i++){
		(*black)[i]->updateValidMoves();
	}
	for(int i = 0; i < white->size(); i++){
		(*white)[i]->updateValidMoves();
	}
}

void Board::updateLegalMoves(){ //same as updateValidMoves but with legal moves
	for(int i = 0; i < black->size(); i++){
		(*black)[i]->updateLegalMoves();
	}
	for(int i = 0; i < white->size(); i++){
		(*white)[i]->updateLegalMoves();
	}
}

bool Board::isCheck(char colour) { //checks if the side with the colour as same as the argument is in check. Returns true if it is
	Posn *temp;
	Piece *king;
	if(colour == 'w'){
		//find the white king
		for(int i = 0; i < white->size(); i++){
			if((*white)[i]->id == 'K') king = (*white)[i];
		}
		//see if any black piece can attack the white king
		for(int i = 0; i < black->size(); i++){
			for(int j = 0; j < (*black)[i]->validMoves.size(); j++){
				temp = (*black)[i]->validMoves[j];
				if(temp->row == king->position.row && temp->col == king->position.col){
					return true;
				}
			}
		}
		return false;
	}


	else if(colour == 'b'){
		//find the black king
		for(int i = 0; i < black->size(); i++){
			if((*black)[i]->id == 'k') king = (*black)[i];
		}
		//see if any white piece can attack the black king
		for(int i = 0; i < white->size(); i++){
			for(int j = 0; j < (*white)[i]->validMoves.size(); j++){
				temp = (*white)[i]->validMoves[j];
				if(temp->row == king->position.row && temp->col == king->position.col){
					return true;
				}
			}
		}
		return false;
	}
	return false;
}





char Board::isCheckmate() { //returns the colour of the side that is in checkmate. 0 otherwise
	//the function doesn't officially check for checkmate but rather if a side has any legal moves
	Piece *wKing;
	Piece *bKing;
	bool isWhite = true;
	bool isBlack = true;
	//has to update valid and legal moves first
	updateValidMoves();
	updateLegalMoves();
	//checks if black has any legal moves
	for(int i = 0; i < black->size(); i++)	{
		if((*black)[i]->legalMoves.size() != 0){
			isBlack = false;
		}
	}
	//checks if white has any legal moves
	for(int i = 0; i < white->size(); i++){
		if((*white)[i]->legalMoves.size() != 0){
			isWhite = false;
		}
	}
	if(isBlack == true) return 'b';
	else if(isWhite == true) return 'w';
	else return 0;
}





bool Board::isDraw(char turn) { //checks for stalemate. Returns true if it is, false otherwise
	//returns true if there is only one white king and one black king since it's physically
	//impossible to have a checkmate/check with two kings
	if(white->size() == 1 && black->size() == 1){
		if((*white)[0]->id == 'K' && (*black)[0]->id == 'k'){
			return true;
		}
	}

	if(isCheckmate() == 0) return false; //has to check if the side has any legal moves
	
	//if a side has no legal moves, it has to check if the side's king is not in check
	Piece *king;
	if(turn == 'w'){
		//finds the white king
		for(int i = 0; i < white->size(); i++){
			if((*white)[i]->id == 'K') king = (*white)[i];
		}		
		//checks if the white king is currently in check by going through all of black's possible moves
		for(int i = 0; i < black->size(); i++){
			for(int j = 0; j < (*black)[i]->legalMoves.size(); j++){
				if((*black)[i]->legalMoves[j]->row == king->position.row && (*black)[i]->legalMoves[j]->col == king->position.col){
					return false;
				}
			}
		}
	}
	//does the same thing but for the other side
	else if(turn == 'b'){
		for(int i = 0; i < black->size(); i++){
			if((*black)[i]->id == 'k') king = (*black)[i];
		}
		
		for(int i = 0; i < white->size(); i++){
			for(int j = 0; j < (*white)[i]->legalMoves.size(); j++){
				if((*white)[i]->legalMoves[j]->row == king->position.row && (*white)[i]->legalMoves[j]->col == king->position.col){
					return false;
				}
			}
		}
	}
	
	return true;
}




void Board::promote(int x, int y) { //promotes a pawn if it reaches the end of the board
	char colour = board[x][y]->colour;
	char enemy = colour == 'w' ? 'b' : 'w';
	removePiece(x,y);
	deletePiece(x,y);
	char c;
	//if it is a computer playing, the pawn is always promoted to a queen
	if(colour == 'w' && whitePlayer != "human"){
		c = 'Q';
	}
	else if(colour == 'b' && blackPlayer != "human"){
		c = 'q';
	}
	//if it is a human, it reads what piece it was to promote to
	else{
		do{
			cin >> c;
		} while(c == 'p' || c == 'P' || c == 'k' || c == 'K');
	}
	setPiece(c, x, y);
	updateValidMoves();
	updateLegalMoves();
	if(isCheck(enemy)){
		display->notifyCheck(enemy);
	}
}
