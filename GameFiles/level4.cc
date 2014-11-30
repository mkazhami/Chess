#include "level.h"
#include "level4.h"
#include "board.h"
#include "piece.h"
#include <vector>
#include <queue>
#include <iostream>
#include <cstdlib>
using namespace std;

Move::Move(int oldRow, int oldCol, int newRow, int newCol): oldRow(oldRow), oldCol(oldCol), newRow(newRow), newCol(newCol) {}

Level4::Level4(Board *board): Level(board) {
	whiteMoves.push(Move(6, 4, 4, 4));
	blackMoves.push(Move(1, 4, 3, 4));
	whiteMoves.push(Move(7, 6, 5, 5));
	blackMoves.push(Move(0, 1, 2, 2));
	whiteMoves.push(Move(7, 5, 4, 2));
	blackMoves.push(Move(0, 6, 2, 5));
	whiteMoves.push(Move(6, 3, 5, 3));
	blackMoves.push(Move(0, 5, 3, 2));
	whiteMoves.push(Move(6, 2, 5, 2));
	blackMoves.push(Move(0, 4, 0, 6));
	whiteMoves.push(Move(7, 4, 7, 6));
	blackMoves.push(Move(1, 3, 3, 3));
}

Level4::~Level4() {
	queue<Move> empty;
 	swap( whiteMoves, empty );
	queue<Move> empty2;
	swap( blackMoves, empty2);
}

void Level4::move() {
	board->updateValidMoves();
	board->updateLegalMoves();
	srand(time(0));
	if(colour == 'w'){
		bool canCheck = false;
		bool canCheckmate = false;
		Posn oldPosn(-1, -1);
		Posn newPosn(-1, -1);
		vector<Piece *> pieces;
		for(int i = (int)board->white->size() - 1; i >= 0; i--){
			pieces.push_back((*(board->white))[i]);
		}
		//PUTS IN CHECKMATE?
		for(int i = 0; i < (int)pieces.size(); i++){
			Piece *piece = pieces[i];
			for(int j = 0; j < (int)piece->legalMoves.size(); j++){
							
				Posn *move = piece->legalMoves[j];
				int oldRow = piece->position.row;
				int oldCol = piece->position.col;
				int newRow = move->row;
				int newCol = move->col;
				Piece *temp = board->board[newRow][newCol];
				if(temp != 0) board->removePiece(newRow, newCol);
				piece->position.row = newRow;
				piece->position.col = newCol;
				board->board[newRow][newCol] = piece;
				board->board[oldRow][oldCol] = 0;
				board->updateValidMoves();
				if(board->isCheckmate() == 'b'){
					canCheckmate = true;
				}
				
				board->board[newRow][newCol] = temp;
				piece->position.row = oldRow;
				piece->position.col = oldCol;
				board->board[oldRow][oldCol] = piece;
				if(temp != 0){
					if(temp->colour == 'b') board->black->push_back(temp);
					else board->white->push_back(temp);
				}
				board->updateValidMoves();
				board->updateLegalMoves();
				if(canCheckmate == true){
					if(board->movePiece(oldRow, oldCol, newRow, newCol)) return;
				}
			}
		}
		
		while(whiteMoves.size() > 0){
			Move temp = whiteMoves.front();
			whiteMoves.pop();
			if(board->board[temp.oldRow][temp.oldCol] != 0 && board->movePiece(temp.oldRow, temp.oldCol, temp.newRow, temp.newCol)) return;
		}
	
		board->updateValidMoves();
		board->updateLegalMoves();
			
		//can promote?
		for(int i = 0; i < (int) board->white->size(); i++){
			Piece *piece = (*(board->white))[i];
			if(piece->id == 'P' && piece->position.row == 1){
				int row = piece->position.row;
				int col = piece->position.col;
				if(piece->isLegal(row-1, col-1)){
					if(board->movePiece(row, col, row-1, col-1)) return;
				}
				else if(piece->isLegal(row-1, col+1)){
					if(board->movePiece(row, col, row-1, col+1)) return;
				}
				else if(piece->isLegal(row-1, col)){
					if(board->movePiece(row, col, row-1, col)) return;
				}
			}
		}


		//AVOID CAPTURE
		for(int i = (int)board->white->size() -1; i >=  0; i--){
			Piece *piece = (*(board->white))[i];
			int curRow = (*(board->white))[i]->position.row;
			int curCol = (*(board->white))[i]->position.col;
			bool inDanger = false;
			for(int j = 0; j < (int)board->black->size(); j++){
				for(int h = 0; h < (int) (*(board->black))[j]->legalMoves.size(); h++){
					Posn *enemy = (*(board->black))[j]->legalMoves[h];
					if(enemy->row == curRow && enemy->col == curCol){
						inDanger = true;
						if(piece->isLegal((*(board->black))[j]->position.row, (*(board->black))[j]->position.col)){
							if(board->movePiece(curRow, curCol, (*(board->black))[j]->position.row, (*(board->black))[j]->position.col)) return;
						}
						else{
							for(int x = 0; x < (int) piece->legalMoves.size(); x++){
								int random = rand() % piece->legalMoves.size();
								Posn *move = piece->legalMoves[random];
								int row = move->row;
								int col = move->col;
								bool isSafe = true;
								Piece *temp = board->board[move->row][move->col];
								if(temp != 0) board->removePiece(move->row, move->col);
								board->board[move->row][move->col] = board->board[curRow][curCol];
								board->board[curRow][curCol] = 0;
								board->updateValidMoves();
								
								for(int y = 0; y < (int) board->black->size(); y++){
									if((*(board->black))[y]->isValid(row, col)) isSafe = false;								
								}

								board->board[curRow][curCol] = board->board[row][col];
								board->board[row][col] = temp;
								if(temp != 0){
									if(temp->colour == 'b') board->black->push_back(temp);
									else board->white->push_back(temp);
								}
								board->updateValidMoves();

								if(isSafe == true){
									if(board->movePiece(curRow, curCol, row, col)) return;
								}
							}
						}
					}
					if(inDanger == true) break;
				}
				if(inDanger == true) break;
			}
		}

		board->updateValidMoves();
		board->updateLegalMoves();

		//LOOK FOR CHECKING MOVES
		for(int i = 0; i < (int)board->white->size(); i++){

			for(int j = 0; j < (int) (*(board->white))[i]->legalMoves.size(); j++){
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
					if(board->wasBlackCheck == true && board->whoCheckedBlack == current->id){
						board->wasBlackCheck = false;
						continue;
					}
					else if(board->movePiece(oldRow, oldCol, newRow, newCol)){
						board->wasBlackCheck = true;
						board->whoCheckedBlack = current->id;
						return;
					}
				}
			}
		}
		if(canCheck == false && oldPosn.row != -1 && newPosn.row != -1){
			if(board->movePiece(oldPosn.row, oldPosn.col, newPosn.row, newPosn.col)) return;
		}
		board->updateValidMoves();
		board->updateLegalMoves();

		//look for safe moves
                for(int i = 0; i < (int) board->white->size(); i++){
                        int random = rand() % board->white->size();
                        while((*(board->white))[random]->legalMoves.size() == 0){
                                random = rand() % board->white->size();
                        }
                        for(int x = 0; x < (int) (*(board->white))[random]->legalMoves.size(); x++){
                                Posn *move = (*(board->white))[random]->legalMoves[x];
                                int row = move->row;
                                int col = move->col;
                                int curRow = (*(board->white))[random]->position.row;
                                int curCol = (*(board->white))[random]->position.col;
                                bool isSafe = true;
                                Piece *temp = board->board[move->row][move->col];
                                if(temp != 0) board->removePiece(move->row, move->col);
                                board->board[move->row][move->col] = board->board[curRow][curCol];
                                board->board[curRow][curCol] = 0;
                                board->updateValidMoves();

                                for(int y = 0; y < board->white->size(); y++){
                                        if((*(board->white))[y]->isValid(row, col)) isSafe = false;
                                }

                                board->board[curRow][curCol] = board->board[row][col];
                                board->board[row][col] = temp;
                                if(temp != 0){
                                        if(temp->colour == 'w') board->white->push_back(temp);
                                        else board->black->push_back(temp);
                                }
                                board->updateValidMoves();

                                if(isSafe == true){
                                        if(board->movePiece(curRow, curCol, row, col)) return;
                                }
                        }
                }

		board->updateValidMoves();
		board->updateLegalMoves();

		//if no attacking moves, do a random move
                int piece = rand() % board->white->size();
	        while((*(board->white))[piece]->legalMoves.size() == 0){
        	        piece = rand() % board->white->size();
		}                
	        int moveRand = rand() % ((*(board->white))[piece]->legalMoves.size());
        	Posn *move = (*(board->white))[piece]->legalMoves[moveRand];
                board->movePiece((*(board->white))[piece]->position.row, (*(board->white))[piece]->position.col, move->row, move->col);
	}

	else if(colour == 'b'){
		bool canCheck = false;
		bool canCheckmate = false;
                Posn oldPosn(-1, -1);
                Posn newPosn(-1, -1);

		vector<Piece *> pieces;
                for(int i = board->black->size() - 1; i >= 0; i--){
                        pieces.push_back((*(board->black))[i]);
                }
                //PUTS IN CHECKMATE?
                for(int i = 0; i < pieces.size(); i++){
                        Piece *piece = pieces[i];
                        for(int j = 0; j < piece->legalMoves.size(); j++){
                                Posn *move = piece->legalMoves[j];
                                int oldRow = piece->position.row;
                                int oldCol = piece->position.col;
                                int newRow = move->row;
                                int newCol = move->col;
                                Piece *temp = board->board[newRow][newCol];
                                if(temp != 0) board->removePiece(newRow, newCol);
                                piece->position.row = newRow;
                                piece->position.col = newCol;
                                board->board[newRow][newCol] = piece;
                                board->board[oldRow][oldCol] = 0;
                                board->updateValidMoves();


                                if(board->isCheckmate() == 'w'){
                                        canCheckmate = true;
                                }

                                board->board[newRow][newCol] = temp;
                                piece->position.row = oldRow;
                                piece->position.col = oldCol;
                                board->board[oldRow][oldCol] = piece;
                                if(temp != 0){
                                        if(temp->colour == 'w') board->white->push_back(temp);
                                        else board->black->push_back(temp);
                                }
                                board->updateValidMoves();
                                board->updateLegalMoves();
                                if(canCheckmate == true){
                                        if(board->movePiece(oldRow, oldCol, newRow, newCol)) return;
                                }
                        }
                }
		
		while(blackMoves.size() > 0){
                        Move temp = blackMoves.front();
                        blackMoves.pop();
                        if(board->board[temp.oldRow][temp.oldCol] != 0 && board->movePiece(temp.oldRow, temp.oldCol, temp.newRow, temp.newCol)) return;
                }
	
		board->updateValidMoves();
		board->updateLegalMoves();


		//can promote?
                for(int i = 0; i < (int) board->black->size(); i++){
                        Piece *piece = (*(board->black))[i];
                        if(piece->id == 'p' && piece->position.row == 6){
                                int row = piece->position.row;
                                int col = piece->position.col;
                                if(piece->isValid(row+1, col-1)){
                                        if(board->movePiece(row, col, row+1, col-1)) return;
                                }
                                else if(piece->isValid(row+1, col+1)){
                                        if(board->movePiece(row, col, row+1, col+1)) return;
                                }
                                else if(piece->isValid(row+1, col)){
                                        if(board->movePiece(row, col, row+1, col)) return;
                                }
                        }
                }

		board->updateValidMoves();
		board->updateLegalMoves();

		
		//look for defensive moves
                for(int i = board->black->size() -1; i >= 0; i--){
			Piece *piece = (*(board->black))[i];
			int curRow = (*(board->black))[i]->position.row;
			int curCol = (*(board->black))[i]->position.col;
			bool inDanger = false;
			for(int j = 0; j < board->white->size(); j++){
				for(int h = 0; h < (*(board->white))[j]->legalMoves.size(); h++){
					Posn *enemy = (*(board->white))[j]->legalMoves[h];
					if(enemy->row == curRow && enemy->col == curCol){
						inDanger = true;
						if(piece->isLegal((*(board->white))[j]->position.row, (*(board->white))[j]->position.col)){
							board->movePiece(curRow, curCol, (*(board->white))[j]->position.row, (*(board->white))[j]->position.col);
							return;
						}
						else{
							for(int x = 0; x < piece->legalMoves.size(); x++){
								int random = rand() % piece->legalMoves.size();
								Posn *move = piece->legalMoves[random];
								int row = move->row;
								int col = move->col;
								bool isSafe = true;
								Piece *temp = board->board[move->row][move->col];
								if(temp != 0) board->removePiece(move->row, move->col);

								board->board[move->row][move->col] = board->board[curRow][curCol];
								board->board[curRow][curCol] = 0;
								board->updateValidMoves();
								
								for(int y = 0; y < board->white->size(); y++){
									if((*(board->white))[y]->isValid(row, col)) isSafe = false;								
								}

								board->board[curRow][curCol] = board->board[row][col];
								board->board[row][col] = temp;
								if(temp != 0){
									if(temp->colour == 'w') board->white->push_back(temp);
									else board->black->push_back(temp);
								}
								board->updateValidMoves();

								if(isSafe == true){
									if(board->movePiece(curRow, curCol, row, col)) return;
								}
							}
						}
					}
					if(inDanger == true) break;
				}
				if(inDanger == true) break;
			}
		}

		board->updateValidMoves();
		board->updateLegalMoves();
		
		//look for attacking moves
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
					if(board->wasWhiteCheck == true && board->whoCheckedWhite == current->id){
						board->wasWhiteCheck = false;
						continue;
					}
                                        else if(board->movePiece(oldRow, oldCol, newRow, newCol)){
						board->wasWhiteCheck = true;
						board->whoCheckedWhite = current->id;
						return;
					}
                                }
                        }
                }
                if(canCheck == false && oldPosn.row != -1 && newPosn.row != -1){
                        if(board->movePiece(oldPosn.row, oldPosn.col, newPosn.row, newPosn.col)) return;
                }


		board->updateValidMoves();
		board->updateLegalMoves();

		//look for safe moves
		for(int i = 0; i < (int) board->black->size(); i++){
			int random = rand() % board->black->size();
			while((*(board->black))[random]->legalMoves.size() == 0){
				random = rand() % board->black->size();
			}
			for(int x = 0; x < (int) (*(board->black))[random]->legalMoves.size(); x++){
				Posn *move = (*(board->black))[random]->legalMoves[x];
				int row = move->row;
				int col = move->col;
				int curRow = (*(board->black))[random]->position.row;
				int curCol = (*(board->black))[random]->position.col;
				bool isSafe = true;
				Piece *temp = board->board[move->row][move->col];
				if(temp != 0) board->removePiece(move->row, move->col);
				board->board[move->row][move->col] = board->board[curRow][curCol];
				board->board[curRow][curCol] = 0;
				board->updateValidMoves();
	
				for(int y = 0; y < board->white->size(); y++){
					if((*(board->white))[y]->isValid(row, col)) isSafe = false;                       
				}

				board->board[curRow][curCol] = board->board[row][col];
				board->board[row][col] = temp;
				if(temp != 0){
					if(temp->colour == 'w') board->white->push_back(temp);
					else board->black->push_back(temp);
				}
				board->updateValidMoves();

				if(isSafe == true){
					if(board->movePiece(curRow, curCol, row, col)) return;
				}
			}
		}


	
		board->updateValidMoves();
		board->updateLegalMoves();
		
                //if no attacking or safe moves, do a random move
		int piece = rand() % board->black->size();
		while((*(board->black))[piece]->legalMoves.size() == 0){
			piece = rand() % board->black->size();
		}
		int moveRand = rand() % ((*(board->black))[piece]->legalMoves.size());
		Posn *move = (*(board->black))[piece]->legalMoves[moveRand];
 		board->movePiece((*(board->black))[piece]->position.row, (*(board->black))[piece]->position.col, move->row, move->col);
	}

}
