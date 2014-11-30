#include "level.h"
#include "level2.h"
#include "board.h"
#include "piece.h"
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

Level2::Level2(Board *board): Level(board) {}

void Level2::move() {
	srand(time(0));
	if(colour == 'w'){
		bool canCheck = false;
		Posn oldPosn(-1, -1);
		Posn newPosn(-1, -1);
		for(int i = 0; i < board->white->size(); i++){
			for(int j = 0; j < (*(board->white))[i]->legalMoves.size(); j++){
				Piece *current = (*(board->white))[i];
				int oldRow = (*(board->white))[i]->position.row;
		                int oldCol = (*(board->white))[i]->position.col;
				int newRow = (*(board->white))[i]->legalMoves[j]->row;
				int newCol = (*(board->white))[i]->legalMoves[j]->col;
                		Piece *enemy = board->board[newRow][newCol];
		                if(enemy != 0){
					oldPosn.row = oldRow;
					oldPosn.col = oldCol;
					newPosn.row = newRow;
					newPosn.col = newCol;
					board->removePiece(newRow, newCol);
				}
        		        (*(board->white))[i]->position.row = newRow;
                		(*(board->white))[i]->position.col = newCol;
	                	board->board[newRow][newCol] = current;
	        	        board->board[oldRow][oldCol] = 0;
        	        	board->updateValidMoves();
	
		                if(board->isCheck('b')){
        		                canCheck = true;
                		}

        		        (*(board->white))[i]->position.row = oldRow;
                		(*(board->white))[i]->position.col = oldCol;
	                	board->board[newRow][newCol] = enemy;
	        	        board->board[oldRow][oldCol] = current;

                		if(enemy != 0){
                        		if(enemy->colour == 'b') board->black->push_back(enemy);
	                        	else board->white->push_back(enemy);
        	        	}
				board->updateValidMoves();
				if(canCheck == true){
					board->movePiece(oldRow, oldCol, newRow, newCol);
					return;
				}
			}
		}
		if(canCheck == false && oldPosn.row != -1 && newPosn.row != -1){
			board->movePiece(oldPosn.row, oldPosn.col, newPosn.row, newPosn.col);
		}
		//if no attacking moves, do a random move
		else{
			board->updateValidMoves();
        	        board->updateLegalMoves();
                	int piece = rand() % board->white->size();
	                while((*(board->white))[piece]->legalMoves.size() == 0){
        	                piece = rand() % board->white->size();
                	}
	                int moveRand = rand() % ((*(board->white))[piece]->legalMoves.size());
        	        Posn *move = (*(board->white))[piece]->legalMoves[moveRand];
                	board->movePiece((*(board->white))[piece]->position.row, (*(board->white))[piece]->position.col, move->row, move->col);
		}
	}

	else if(colour == 'b'){
		bool canCheck = false;
                Posn oldPosn(-1, -1);
                Posn newPosn(-1, -1);
                for(int i = 0; i < board->black->size(); i++){
                        for(int j = 0; j < (*(board->black))[i]->legalMoves.size(); j++){
                                Piece *current = (*(board->black))[i];
                                int oldRow = (*(board->black))[i]->position.row;
                                int oldCol = (*(board->black))[i]->position.col;
                                int newRow = (*(board->black))[i]->legalMoves[j]->row;
                                int newCol = (*(board->black))[i]->legalMoves[j]->col;
                                Piece *enemy = board->board[newRow][newCol];
                                if(enemy != 0){
                                        oldPosn.row = oldRow;
                                        oldPosn.col = oldCol;
                                        newPosn.row = newRow;
                                        newPosn.col = newCol;
                                        board->removePiece(newRow, newCol);
                                }
                                (*(board->black))[i]->position.row = newRow;
                                (*(board->black))[i]->position.col = newCol;
                                board->board[newRow][newCol] = current;
                                board->board[oldRow][oldCol] = 0;
                                board->updateValidMoves();

                                if(board->isCheck('w')){
                                        canCheck = true;
                                }

                                (*(board->black))[i]->position.row = oldRow;
                                (*(board->black))[i]->position.col = oldCol;
                                board->board[newRow][newCol] = enemy;
                                board->board[oldRow][oldCol] = current;

                                if(enemy != 0){
                                        if(enemy->colour == 'w') board->white->push_back(enemy);
                                        else board->black->push_back(enemy);
                                }
                                board->updateValidMoves();
                                if(canCheck == true){
                                        board->movePiece(oldRow, oldCol, newRow, newCol);
					return;
                                }
                        }
                }
                if(canCheck == false && oldPosn.row != -1 && newPosn.row != -1){
                        board->movePiece(oldPosn.row, oldPosn.col, newPosn.row, newPosn.col);
                }
                //if no attacking moves, do a random move
                else{
                        board->updateValidMoves();
                        board->updateLegalMoves();
                        int piece = rand() % board->black->size();
                        while((*(board->black))[piece]->legalMoves.size() == 0){
                                piece = rand() % board->black->size();
                        }
                        int moveRand = rand() % ((*(board->black))[piece]->legalMoves.size());
                        Posn *move = (*(board->black))[piece]->legalMoves[moveRand];
                        board->movePiece((*(board->black))[piece]->position.row, (*(board->black))[piece]->position.col, move->row, move->col);
                }
	}

}
