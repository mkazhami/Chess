#include "piece.h"
#include "queen.h"
#include "posn.h"
#include "board.h"
#include <iostream>
using namespace std;


int absolute(int);

Queen::Queen(Board *board): Piece(board) {}

Queen::~Queen() {
	if(validMoves.size() != 0) deleteValidMoves();
	if(legalMoves.size() != 0) deleteLegalMoves();
}

void Queen::updateValidMoves() {
	if(validMoves.size() != 0) deleteValidMoves();
//	cout << "updating moves: queen" << endl;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(isValid(i,j)){
				Posn *temp = new Posn(i,j);
				validMoves.push_back(temp);
			}
		}
	}
}

void Queen::updateLegalMoves() {
       if(legalMoves.size() != 0) deleteLegalMoves();
//       cout << "updating moves" << endl;
       for(int i = 0; i < validMoves.size(); i++){
               if(isLegal(validMoves[i]->row, validMoves[i]->col)){
                       Posn *temp = new Posn(validMoves[i]->row, validMoves[i]->col);
                       legalMoves.push_back(temp);
               }
       }
}

void Queen::deleteValidMoves() {
	for(int i = 0; i < validMoves.size(); i++){
		Posn *temp = validMoves[i];
		if(temp != 0) delete temp;
		temp = 0;
	}
	validMoves.clear();
}

void Queen::deleteLegalMoves() {
        for(int i = 0; i < legalMoves.size(); i++){
                Posn *temp = legalMoves[i];
                if(temp != 0) delete temp;
		temp = 0;
        }
        legalMoves.clear();
}


bool Queen::isLegal(int row, int col){
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
		if(enemy != 0){
			if(enemy->colour == 'b') board->black->push_back(enemy);
			else board->white->push_back(enemy);
		}
		board->updateValidMoves();
	}
	return isLegal;
}

bool Queen::updatePosition(int row, int col) {
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
			enemy = 0;
		}
		
		char opp = colour == 'w' ? 'b' : 'w';

		if(board->isCheck(opp)){
			board->display->notifyCheck(opp);
		}

		board->updateLegalMoves();
		return true;
	}
	else{
		cout << "Illegal move" << endl << endl;
		return false;
	}
}

bool inRange(int, int); //combines the inRange of rook and bishop

int abs(int num){
	if(num < 0) return -num;
	return num;
}

bool Queen::isValid(int row, int col){
	int rowTemp = row;
	int colTemp = col;
	//combines the code in Rook::isValid and Bishop::isValid
	if(inRange(row, col) && (abs(position.row - row) == abs(position.col - col))){
		if(row > position.row){
			if(col > position.col){
				while(rowTemp > position.row + 1 && colTemp > position.col + 1){
					rowTemp--;
					colTemp--;
					if(board->board[rowTemp][colTemp] != 0) return false;
				}
			}
			else{
				while(rowTemp > position.row + 1 && colTemp < position.col - 1){
					rowTemp--;
					colTemp++;
					if(board->board[rowTemp][colTemp] != 0) return false;
				}
			}
		}
		else{
			if(col > position.col){
				while(rowTemp < position.row - 1 && colTemp > position.col + 1){
					rowTemp++;
					colTemp--;
					if(board->board[rowTemp][colTemp] != 0) return false;
				}
			}
			else{
				while(rowTemp < position.row - 1 && colTemp < position.col - 1){
					rowTemp++;
					colTemp++;
					if(board->board[rowTemp][colTemp] != 0) return false;
				}
			}
		}
		
		//check if spot is empty or contains an enemy
		if(board->board[row][col] == 0 || (board->board[row][col]->colour != colour)) return true;
	}
	else if(inRange(row, col) && (row == position.row || col == position.col)){
		if(row == position.row){
			int greater = (col > position.col) ? col : position.col;
			int lesser = (col < position.col) ? col : position.col;
			for(int i = lesser + 1; i < greater; i++){
				if(board->board[row][i] != 0) return false;
			}
			if(board->board[row][col] == 0 || (board->board[row][col]->colour != colour)) return true;
		}
		else if(col == position.col){
			int greater = (row > position.row) ? row : position.row;
			int lesser = (row < position.row) ? row : position.row;
			for(int i = lesser + 1; i < greater; i++){
				if(board->board[i][col] != 0) return false;
			}
			if(board->board[row][col] == 0 || (board->board[row][col]->colour != colour)) return true;
		}
	}
	//if none of the cases were true, it is an invalid move
	return false;
}

bool Queen::inRange(int row, int col){
	if(row < 0 || row > 7 || col < 0 || col > 7) return false;
	if(row == position.row && col == position.col) return false;
	return true;
}
