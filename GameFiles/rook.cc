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

void Rook::updateValidMoves() {
	if(validMoves.size() != 0) deleteValidMoves();
	//cout << "updating valid moves: rook" << endl;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(isValid(i, j)){
				Posn *temp = new Posn (i, j);
				validMoves.push_back(temp);
			}
		}
	}
}


void Rook::updateLegalMoves() {
	//cout << "updating legal moves: rook" << endl;
	if(legalMoves.size() != 0) deleteLegalMoves();
	for(int i = 0; i < validMoves.size(); i++){
		if(isLegal(validMoves[i]->row, validMoves[i]->col)){
			Posn *temp = new Posn(validMoves[i]->row, validMoves[i]->col);
			legalMoves.push_back(temp);
		}
	}
}

void Rook::deleteValidMoves() {
	for(int i = 0; i < validMoves.size(); i++){
		Posn *temp = validMoves[i];
		if(temp != 0) delete temp;
		temp = 0;
	}
	validMoves.clear();
}

void Rook::deleteLegalMoves() {
        for(int i = 0; i < legalMoves.size(); i++){
                Posn *temp = legalMoves[i];
                if(temp != 0) delete temp;
		temp = 0;
        }
        legalMoves.clear();
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

bool inRange(int, int); //checks if the inputs are between 0 and 7 and checks if the movement is horizontal or vertical

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

bool Rook::inRange(int row, int col){
	if(row < 0 || row > 7 || col < 0 || col > 7){
		return false;
	}
	if(row == position.row && col == position.col) return false;
	return true;
}
