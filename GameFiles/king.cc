#include "piece.h"
#include "king.h"
#include "posn.h"
#include "board.h"
#include <iostream>
using namespace std;

//see piece.h for information on how these functions work
King::King(Board *board): Piece(board) {hasMoved = false;}

King::~King() {
	deleteLegalMoves();
	deleteValidMoves();
}

bool King::isLegal(int row, int col){
	bool isLegal = false;
	if(isValid(row, col)){
		int oldRow = position.row;
		int oldCol = position.col;
		Piece *enemy = board->board[row][col];
		if(enemy != 0) board->removePiece(row, col);
		position.row = row;
		position.col = col;
		board->board[row][col] = this;
		board->board[oldRow][oldCol] = 0;
		board->updateValidMoves();

		if(board->isCheck(colour)){
			isLegal = false;
		}
		else isLegal = true;
		position.row = oldRow;
		position.col = oldCol;
		board->board[row][col] = enemy;
		board->board[oldRow][oldCol] = this;
		//board->updateValidMoves();
		if(enemy != 0){
			if(enemy->colour == 'b') board->black->push_back(enemy);
			else board->white->push_back(enemy);
			//board->display->draw(enemy->id, row, col);
		}
		board->updateValidMoves();
	}
	return isLegal;
}

bool King::isCastling(int row, int col){ //checks if the king can castle
	if(board->isCheck(colour)){
		return false;
	}
	board->updateValidMoves();
	board->updateLegalMoves();
	if(row == 0 && col == 2){
		if(board->board[0][0] != 0 && board->board[0][0]->id == 'r' && board->board[0][1] == 0 && board->board[0][2] == 0 && board->board[0][3] == 0){
			if(hasMoved == false && board->board[0][0]->hasMoved == false && isLegal(0,3)){
				board->board[0][0]->position.col = 3;
                                board->board[0][3] = board->board[0][0];
                                board->board[0][0] = 0;
                                position.col = col;
                                board->board[0][2] = board->board[0][4];
                                board->board[0][4] = 0;
                                board->updateValidMoves();

                                if(board->isCheck(colour)){
                                        position.col = 4;
                                        board->board[0][3]->position.col = 0;
                                        board->board[0][0] = board->board[0][3];
                                        board->board[0][3] = 0;
                                        board->board[0][4] = board->board[0][2];
                                        board->board[0][2] = 0;
                                        cout <<"move puts king in check" << endl;
                                        board->updateValidMoves();
                                        return false;
                                }
                                char opp = colour == 'w' ? 'b' : 'w';
                                if(board->isCheck(opp)){
                                        board->display->notifyCheck(opp);
                                }
                                board->display->draw('r', 0, 3);
                                board->display->undraw(0, 0);
                                board->updateLegalMoves();
				return true;
			}
		}
	}

	else if(row == 0 && col == 6){
		if(board->board[0][7] != 0 && board->board[0][7]->id == 'r' && board->board[0][6] == 0 && board->board[0][5] == 0){
			if(hasMoved == false && board->board[0][7]->hasMoved == false && isLegal(0,5)){
				board->board[0][7]->position.col = 5;
                                board->board[0][5] = board->board[0][7];
                                board->board[0][7] = 0;
                                position.col = col;
                                board->board[0][6] = board->board[0][4];
                                board->board[0][4] = 0;
                                board->updateValidMoves();
                                if(board->isCheck(colour)){
                                        position.col = 4;
                                        board->board[0][5]->position.col = 7;
                                        board->board[0][7] = board->board[0][5];
                                        board->board[0][5] = 0;
                                        board->board[0][4] = board->board[0][6];
                                        board->board[0][6] = 0;
                                        cout <<"move puts king in check" << endl;
                                        board->updateValidMoves();
                                        return false;
                                }
                                char opp = colour == 'w' ? 'b' : 'w';
                                if(board->isCheck(opp)){
                                        board->display->notifyCheck(opp);
                                }
                                board->display->draw('r', 0, 5);
                                board->display->undraw(0, 7);
                                board->updateLegalMoves();
				return true;
			}
		}
	}
	
	else if(row == 7 && col == 2){
		if(board->board[7][0] != 0 && board->board[7][0]->id == 'R' && board->board[7][1] == 0 && board->board[7][2] == 0 && board->board[7][3] == 0){
			if(hasMoved == false && board->board[7][0]->hasMoved == false && isLegal(7,3)){
				board->board[7][0]->position.col = 3;
                                board->board[7][3] = board->board[7][0];
                                board->board[7][0] = 0;
                                position.col = col;
                                board->board[7][2] = board->board[7][4];
                                board->board[7][4] = 0;
                                board->updateValidMoves();
                                if(board->isCheck(colour)){
                                        position.col = 4;
                                        board->board[7][3]->position.col = 0;
                                        board->board[7][0] = board->board[7][3];
                                        board->board[7][3] = 0;
                                        board->board[7][4] = board->board[7][2];
                                        board->board[7][2] = 0;
                                        cout <<"move puts king in check" << endl;
                                        board->updateValidMoves(); 
                                        return false;
                                }
                                char opp = colour == 'w' ? 'b' : 'w';
                                if(board->isCheck(opp)){
                                        board->display->notifyCheck(opp);
                                }
                                board->display->draw('R', 7, 3);
                                board->display->undraw(7, 0);
                                board->updateLegalMoves();				
				return true;
			}
		}
	}
	
	else if(row == 7 && col == 6){
		if(board->board[7][7] != 0 && board->board[7][7]->id == 'R' && board->board[7][6] == 0 && board->board[7][5] == 0){
			if(hasMoved == false && board->board[7][7]->hasMoved == false && isLegal(7,5)){
				board->board[7][7]->position.col = 5;
				board->board[7][5] = board->board[7][7];
				board->board[7][7] = 0;
				position.col = col;
				board->board[7][6] = board->board[7][4];
				board->board[7][4] = 0;
				board->updateValidMoves();
				if(board->isCheck(colour)){
					position.col = 4;
					board->board[7][5]->position.col = 7;
					board->board[7][7] = board->board[7][5];
					board->board[7][5] = 0;
					board->board[7][4] = board->board[7][6];
					board->board[7][6] = 0;
					cout <<"move puts king in check" << endl;
					board->updateValidMoves();
					return false;
				}
				char opp = colour == 'w' ? 'b' : 'w';
				if(board->isCheck(opp)){
					board->display->notifyCheck(opp);
				}
				board->display->draw('R', 7, 5);
				board->display->undraw(7, 7);
				board->updateLegalMoves();
				return true;
			}
		}
	}	
	return false;
}

bool King::updatePosition(int row, int col) {
	if(isCastling(row, col)) return true;
	else if(isValid(row, col)){
		int oldRow = position.row;
		int oldCol = position.col;
		Piece *enemy = board->board[row][col];
		if(enemy != 0) board->removePiece(row, col);
		position.row = row;
		position.col = col;
		board->board[row][col] = this;
		board->board[oldRow][oldCol] = 0;
		board->updateValidMoves();

		if(board->isCheck(colour)){
			position.row = oldRow;
			position.col = oldCol;
			board->board[row][col] = enemy;
			board->board[oldRow][oldCol] = this;
			cout << "Move puts king in check" << endl << endl;
			board->updateValidMoves();
			if(enemy != 0){
				if(enemy->colour == 'b') board->black->push_back(enemy);
				else board->white->push_back(enemy);
			}
			return false;
		}

		if(board->board[oldRow][oldCol] == 0 && enemy != 0){
			delete enemy;
			enemy = 0;
		}
		
		char opp = colour == 'w' ? 'b' : 'w';
		if(board->isCheck(opp)){
			board->display->notifyCheck(opp);
		}
		hasMoved = true;
		board->updateLegalMoves();
		return true;
	}
	else{
		cout << "Illegal move" << endl << endl;
		return false;
	}
}

bool King::isValid(int row, int col){
	int rowTemp = row;
	int colTemp = col;
	if(inRange(row, col)){
		if(absolute(row - position.row) <= 1 && absolute(col - position.col) <= 1){ //moving any direction as long as its distance is one
			//check if spot is empty or contains an enemy
			if(board->board[row][col] == 0 || (board->board[row][col]->colour != colour)) return true;
		}
	}
	//if none of the cases were true, it is an invalid move
	return false;
}
