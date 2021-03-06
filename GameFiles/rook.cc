#include "piece.h"
#include "rook.h"
#include "posn.h"
#include "board.h"
#include <iostream>
using namespace std;

Rook::Rook(Board *board): Piece(board) {hasMoved = false;}

Rook::~Rook() {
	if(validMoves.size() != 0) deleteValidMoves();
	if(legalMoves.size() != 0) deleteLegalMoves();
}

bool Rook::isLegal(int row, int col) {
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
		

bool Rook::updatePosition(int row, int col) {
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

bool Rook::isValid(int row, int col){
	if(inRange(row, col)){
		//if moving horizontally
		if(row == position.row){
			int greater = (col > position.col) ? col : position.col;
			int lesser = (col < position.col) ? col : position.col;
			for(int i = lesser + 1; i < greater; i++){
				if(board->board[row][i] != 0) return false;
			}
			//check if spot is available or filled by an enemy
			if(board->board[row][col] == 0 || (board->board[row][col]->colour != colour)) return true;
		}
		//if moving vertically
		else if(col == position.col){
			int greater = (row > position.row) ? row : position.row;
			int lesser = (row < position.row) ? row : position.row;
			for(int i = lesser + 1; i < greater; i++){
				if(board->board[i][col] != 0) return false;
			}
			//check if spot is available or filled by an enemy
			if(board->board[row][col] == 0 || (board->board[row][col]->colour != colour)) return true;
		}
		
	}
	//if none of the cases were true, it is an invalid move
	return false;
}
