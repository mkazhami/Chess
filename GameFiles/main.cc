#include "board.h"
#include "display.h"
#include "textdisplay.h"
#include "graphicdisplay.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "king.h"
#include "level.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

//function prints who's turn it is
void printTurn(char c) {
	if(c == 'w') cout << endl << "White's move" << endl;
	else cout << endl << "Black's move" << endl;
}

int main() {
	Board *board = Board::getInstance(); //instance of the board
	Level *comp1 = 0; //computer levels
	Level *comp2 = 0;
	board->setDisplay();
	string input, whitePlayer, blackPlayer;
	int x, y; 
	int count = 0; //game count
	char turn = 'w';
	char c;
	char x1, y1;	
	char loser;
	float whiteScore = 0;
	float blackScore = 0;
	bool gameOn = false;
	bool moveSuccess = true; //used to see if a move was successful or not
	bool resign = false; //used to see if a game was resigned or ended from checkmate/stalemate
	board->gDisplay->updateScore(whiteScore, blackScore);

	while(cin >> input){
		if(input == "game"){
			cin >> whitePlayer >> blackPlayer; //reads whether the players are human or computers
			board->setPlayers(whitePlayer, blackPlayer);
			if(whitePlayer != "human"){ //if it's not human, it chooses the level of AI depending on the input
				if(whitePlayer == "level[1]"){
					comp1 = new Level1(board);
				}
				else if(whitePlayer == "level[2]"){
					comp1 = new Level2(board);
				}
				else if(whitePlayer == "level[3]"){
					comp1 = new Level3(board);
				}
				else if(whitePlayer == "level[4]"){
					comp1 = new Level4(board);
				}
				comp1->colour = 'w';
			}
			if(blackPlayer != "human"){
				if(blackPlayer == "level[1]"){
					comp2 = new Level1(board);
				}
				else if(blackPlayer == "level[2]"){
					comp2 = new Level2(board);
				}
				else if(blackPlayer == "level[3]"){
					comp2 = new Level3(board);
				}
				else if(blackPlayer == "level[4]"){
					comp2 = new Level4(board);
				}
				comp2->colour = 'b';
			}
			gameOn = true;
			board->clearBoard(); //clear the board of any pieces 
		}
		else if(input == "resign" && gameOn == true){
			if(turn == 'w'){
				board->display->notifyResign('b');
				blackScore++;
			}
			else if(turn == 'b'){
				board->display->notifyResign('w');
				whiteScore++;
			}
			cout << "Score:" << endl << "White: " << whiteScore << endl << "Black: " << blackScore << endl;
			board->gDisplay->updateScore(whiteScore, blackScore);
			turn = 'w';
		}
		else if(input == "move" && gameOn == true){ //can only move if there is a game currently active
			if(whitePlayer != "human" && turn == 'w'){
				comp1->move(); //computer's move function
				//for testing purposes - delete later
				//usleep(300000);
				//WHITE COMPUTER'S TURN
			}
			else if(blackPlayer != "human" && turn == 'b'){
				comp2->move();
				//for testing purposes - delete later
				//usleep(300000);
				//BLACK COMPUTER'S TURN
			}
			else{ //move for a human player
				if(turn == 'w'){ //checks turn
					bool moved = false; //used to print who's move it is properly
					do{
						if(moved == true){ 
							printTurn(turn);
							cin >> input;
						}
						if(input == "resign"){
							resign = true;
							if(turn == 'w'){
								board->display->notifyResign('b');
								blackScore++;
							}
							else if(turn == 'b'){
								board->display->notifyResign('w');
								whiteScore++;
							}
							cout << "Score:" << endl << "White: " << whiteScore << endl << "Black: " << blackScore << endl;
							gameOn = false;
							turn = 'w';
							board->gDisplay->updateScore(whiteScore, blackScore);
							break;
						}
						moved = true;
						cin >> x1 >> x; //reads in the starting coordinates
						//converts the coordinates input to match the numbers we need for the board class
						//the follow loop is executed if a player is trying to move a piece that is not his/her
						while(board->board[x-1][(int) (x1-'a')] == 0 || board->board[x-1][(int) (x1 - 'a')]->colour != 'w'){ 
							cin >> y1 >> y; //read in the destination coordinates. Will not be used since starting coordinates are invalid
							cout << "Not your piece to move." << endl << endl;
							printTurn(turn);
							cin >> input;
							if(input == "resign"){
								resign = true;
								if(turn == 'w'){
									board->display->notifyResign('b');
									blackScore++;
								}
								else if(turn == 'b'){
									board->display->notifyResign('w');
									whiteScore++;
								}
								cout << "Score:" << endl << "White: " << whiteScore << endl << "Black: " << blackScore << endl;
								gameOn = false;
								turn = 'w';
								board->gDisplay->updateScore(whiteScore, blackScore);
								break;
							}
							cin >> x1 >> x; //tries again
						}
						if(resign == true) break; //ends the game if someone resigns
						cin >> y1 >> y;
						moveSuccess = board->movePiece(x-1, (int) (x1 - 'a'), y-1, (int) (y1 - 'a')); //moveSuccess is true if move the move was successful
					} while(moveSuccess == false); //if the move wasn't successful the player must try again
				}
				else if(turn == 'b'){ //same as above but with different colour
					bool moved = false;
					do{
						if(moved == true){
							printTurn(turn);
							cin >> input;
						}
						if(input == "resign"){
							resign = true;
							if(turn == 'w'){
								board->display->notifyResign('b');
								blackScore++;
							}
							else if(turn == 'b'){
								board->display->notifyResign('w');
								whiteScore++;
							}
							cout << "Score:" << endl << "White: " << whiteScore << endl << "Black: " << blackScore << endl;
							gameOn = false;
							turn = 'w';
							board->gDisplay->updateScore(whiteScore, blackScore);
							break;
						}
						moved = true;
						cin >> x1 >> x;
						while(board->board[x-1][(int) (x1-'a')] == 0 || board->board[x-1][(int) (x1 - 'a')]->colour != 'b'){
							cin >> y1 >> y;
							cout << "Not your piece to move." << endl << endl;
							printTurn(turn);
							cin >> input;
							if(input == "resign"){
								resign = true;
								if(turn == 'w'){
									board->display->notifyResign('b');
									blackScore++;
								}
								else if(turn == 'b'){
									board->display->notifyResign('w');
									whiteScore++;
								}
								cout << "Score:" << endl << "White: " << whiteScore << endl << "Black: " << blackScore << endl;
								gameOn = false;
								turn = 'w';
								board->gDisplay->updateScore(whiteScore, blackScore);
								break;
							}
							cin >> x1 >> x;
						}
						if(resign == true) break;
						cin >> y1 >> y;
						moveSuccess = board->movePiece(x-1, (int) (x1 - 'a'), y-1, (int) (y1 - 'a'));
					} while(moveSuccess == false);
				}
				count++;
			}
			if(moveSuccess == true){
				if(turn == 'w') turn = 'b';
				else if(turn == 'b') turn = 'w';
				board->display->print();
				loser = board->isCheckmate();

				if(board->isDraw(turn)){
					board->display->notifyDraw();
					whiteScore += 0.5;
					blackScore += 0.5;
					cout << "Score:" << endl << "White: " << whiteScore << endl << "Black: " << blackScore << endl;
					turn = 'w';
					gameOn = false;
					board->gDisplay->updateScore(whiteScore, blackScore);
					continue;
				}
				else if(loser == 'w' || loser == 'b'){
					board->display->notifyWin(loser == 'b' ? 'w' : 'b');
					if(loser == 'b'){
						whiteScore++;
					}
					else if(loser == 'w'){
						blackScore++;
					}
					cout << "Score:" << endl << "White: " << whiteScore << endl << "Black: " << blackScore << endl;
					gameOn = false;
					turn = 'w';
					board->gDisplay->updateScore(whiteScore, blackScore);
					continue;
				}
				printTurn(turn);
			}
		}
		else if(input == "setup" && gameOn == true){ //setup mode. Only enters if there is not a game currently active
			while(true){
				cin >> input;
				if(input == "default"){ //sets up the board to have a standard chess game start
					board->defaultSetup();
					cout << endl;
					board->display->print();
					printTurn(turn);
					break;
				}
				else if(input == "done" && board->isSetupProper()){ //if setup move is done, it has to check if setup was done properly
					cout << endl;
					printTurn(turn); //			     .. if not then it stays in setup move until they are fixed
					break;
				}
				else if(input == "+"){ //adding a piece to the board
					cin >> c;
					cin >> x1 >> x;
					board->setPiece(c, x-1, (int) (x1-'a'));
					board->display->print();
				}
				else if(input == "-"){ //removing a piece from the board
					cin >> x1 >> x;
					board->removePiece(x-1, (int) (x1 - 'a'));
					board->deletePiece(x-1, (int) (x1 - 'a'));
				}
				else if(input == "="){ //setting which side goes first
					cin >> input;
					if(input == "white") turn = 'w';
					else turn = 'b';
				}
			}
		}
	}
	cout << endl << "Final Score: " << endl << "White: " << whiteScore << endl << "Black: " << blackScore << endl;
	board->gDisplay->updateScore(whiteScore, blackScore);
	delete board;
	if(whitePlayer != "human") delete comp1;
	if(blackPlayer != "human") delete comp2;
}
