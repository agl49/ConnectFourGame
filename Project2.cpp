// File Name: Project2.cpp
// Author: Verginia Mae Dole, Adrian Lopez, James Helgren

#include "Project2.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <array>
#include <stdio.h>
#include <limits.h>
#include <cstring>
#include <chrono>
using namespace std;


ConnectFour::ConnectFour(int turns, evalFunction firstP, evalFunction secondP, bool noPath)
{
    //First player (goes first in alg) 

    auto rseed = chrono::high_resolution_clock::now().time_since_epoch().count();
    ranNum.seed(rseed);
    
    noPathMode = noPath;
    maxTurns = turns;
    currTurn = 0;
    nodesExpanded = 0;
    nodesGenerated = 0;
    xMaxEvaluation = firstP;
    oMinEvaluation = secondP;
}

ConnectFour::~ConnectFour()
{
}

// The printBoard function
void ConnectFour::printBoard(board currBoard)
{
    // Printing the column numbers
	for (int i = 0; i < 7; i++)
    {
        if (i == 0)
        {
            cout << "  C" << i;
        }
        else
        {
            cout << "  C" << i;
        }
	}
	cout << endl;

	// Printing the board
	for (int row = 0; row < 6; row++)
    {
        cout << "R" << ROW - row - 1 << " ";
		for (int col = 0; col < 7; col++)
		{
		    if (col != 0)
            {
                cout << "   ";
            }
			switch (currBoard[ROW - row - 1][col])
			{
                case blank:
                    cout << "_";
                    break;
                case xMax:
                    cout << "X";
                    break;
                case oMin:
                    cout << "O";
                    break;
                default:
                    cout << "!";
                    break;
			}
		}
		cout << endl;
	}
}

void ConnectFour::printMasterBoard()
{
    printBoard(masterBoard);
}

// The makeMove function
void ConnectFour::addPiece(board newBoard)
{
    // Adding piece
	for (int col = 0; col < COL; col++)
    {
		for (int row = ROW - 1; row >= 0; --row)
        {
            if (newBoard[row][col] != masterBoard[row][col])
            {
                masterBoard[row][col] = newBoard[row][col];
                return;
            }
        }
    }
}

void ConnectFour::setMasterToTestState()
{
    for (int col = 0; col < COL; col++)
    {
		for (int row = ROW - 1; row >= 0; --row)
        {
            if (testState[row][col] != masterBoard[row][col])
            {
                masterBoard[row][col] = testState[row][col];
            }
        }
    }

}

void ConnectFour::xMaxMove(int cutoff)
{
    // Player 1 makes their move
    cout << "Performing miniMaxAB for Max" << endl;
    pathAndScore nextMove = miniMaxAB(masterBoard, cutoff, xMax, 0 - INT_MAX, INT_MAX);

    addPiece(nextMove.path[1]);

    //Print path generated
    if (!noPathMode)
    {
        cout << endl;
        cout << "Path generated for move" << endl;
        for (int i = 0; i < nextMove.path.size(); i++)
        {
            cout << "Node: " << i << endl;
            printBoard(nextMove.path[i]);
        }
        cout << "End of path" << endl << endl;
    }
    currTurn++;
}

void ConnectFour::oMinMove(int cutoff)
{
    // Player 2 makes their move
    cout << "Performing miniMaxAB for Min" << endl;
    pathAndScore nextMove = miniMaxAB(masterBoard, cutoff, oMin, 0 - INT_MAX, INT_MAX);
   
    addPiece(nextMove.path[1]);

    if (!noPathMode)
    {
        //print path generated
        cout << endl;
        cout << "Path generated for move" << endl;
        for (int i = 0; i < nextMove.path.size(); i++)
        {
            cout << "Node: " << i << endl;
            printBoard(nextMove.path[i]);
        }
        cout << "End of path" << endl << endl;
    }

    currTurn++;
}

int ConnectFour::getCurrTurn()
{
    return currTurn;
}

int ConnectFour::getNodesGenerated()
{
    return nodesGenerated;
}

int ConnectFour::getNodesExpanded()
{
    return nodesExpanded;
}

// The copyBoard function
board ConnectFour::copyBoard(board originalBoard)
{
    // Creating a copy of the board
    board newBoard;

	// Copying the board element for element
	for (int row = 0; row < ROW; row++)
    {
        for (int col = 0; col < COL; col++)
        {
            newBoard[row][col] = originalBoard[row][col];
        }
	}

	// Returning the board copy
	return newBoard;
}

// The isWinningMove function
bool ConnectFour::isWinningMove(board currBoard, int plyer)
{
    // The win variable
	int win = 0;

	// Checking rows
	for (int col = 0; col < 4; col++)
    {
		for (int row = 0; row < 6; row++)
		{
			for (int i = 0; i < 4; i++)
			{
			    // Checking if there is 4 in a row
				if (currBoard[row][col + i] == plyer)
				{
					win++;
				}

				// Returning true if there is 4 in a row
				if (win == 4)
                {
                    return true;
                }
			}

			// Resetting the counter
			win = 0;
		}
	}

	// Checking columns
	for (int col = 0; col < 7; col++)
    {
		for (int row = 0; row < 3; row++)
		{
			for (int i = 0; i < 4; i++)
			{
			    // Checking if there is 4 in a column
				if (currBoard[row + i][col] == plyer)
				{
					win++;
				}

				// Returning true if there is 4 in a column
				if (win == 4)
                {
                    return true;
                }
			}

			// Resetting the counter
			win = 0;
		}
	}

	// Checking diagonals
	for (int col = 0; col < 4; col++)
    {
		for (int row = 3; row < 6; row++)
		{
			for (int i = 0; i < 4; i++)
			{
			    // Checking if there is 4 in a diagonal
				if (currBoard[row - i][col + i] == plyer)
				{
					win++;
				}

				// Returning true if there is 4 in a diagonal
				if (win == 4)
                {
                    return true;
                }
			}

			// Resetting the counter
			win = 0;
		}
	}
	for (int col = 0; col < 4; col++)
    {
		for (int row = 0; row < 3; row++)
		{
			for (int i = 0; i < 4; i++)
			{
			    // Checking if there is 4 in a diagonal
				if (currBoard[row + i][col + i] == plyer)
				{
					win++;
				}

                // Returning true if there is 4 in a diagonal
				if (win == 4)
                {
                    return true;
                }
			}

			// Resetting the counter
			win = 0;
		}
	}

	// Returning false if there is no win
	return false;
}

bool ConnectFour::gameFinished(whichPlayer plyer)
{
    return isWinningMove(masterBoard, plyer);
}

// The evalFunction1 function
int ConnectFour::evalFunction1(int good, int bad, int none)
{
    // The score
	int score = 0;

	// Determining the score

    if (good == 4)
        score += 100000;
	else if (good == 3 && none == 1)
        score += 100000;
	else if (good == 2 && none == 2)
        score += 1000;
    else if (good == 1 && none == 3)
        score += 100;
    else if (good == 3 && bad == 1)
        score -= 100;
    else if (good == 2 && bad == 2)
        score += 200;
    else if (good == 1 && bad == 3)
        score += 500;
    else if (bad == 1 && none == 3)
        score -= 100;
	else if (bad == 2 && none == 2)
        score -= 1000;
	else if (bad == 3 && none == 1)
        score -= 10000;
	else if (bad == 4)
        score -= 100000;

    // Returning the score
	return score;
}

// The scoreSet function
int ConnectFour::scoreSet(vector<int> arr, int piece)
{
    // Declaring variables
	int good = 0;
	int bad = 0;
	int none = 0;

	// Keeping score of good, bad, and none
	for (int i = 0; i < arr.size(); i++)
    {
		// Counting up the favorable spaces
		if (arr[i] == piece)
        {
            good += 1;
        }

		// Counting up all spaces
		if (piece == xMax)
        {
            if (arr[i] == oMin)
                bad += 1;
        }
        else
        {
            if (arr[i] == xMax)
                bad += 1;
        }

        // Counting up empty spaces
        if (arr[i] == 0)
        {
            none += 1;
        }
	}

	// Returning the results of evalFunction1
	return evalFunction1(good, bad, none);
}

// The keepScore1 function
// Top function of Ginney's 'evaluation' function of the 
// minmax alg. Other score function and eval function 
// function as helper functions
int ConnectFour::keepScore1(board currBoard, int piece)
{
    // The score
	int score = 0;

	// Declaring arrays
	vector<int> row_arr(COL);
	vector<int> col_arr(ROW);
	vector<int> window(4);

    // Checking rows
	for (int row = 0; row < ROW; row++)
    {
        // Creating the row array
		for (int col = 0; col < COL; col++)
		{
			row_arr[col] = currBoard[row][col];
		}

        // Counting up the pieces
		for (int col = 0; col < COL - 3; col++)
        {
			for (int i = 0; i < 4; i++)
			{
				window[i] = row_arr[col + i];
			}
			score += scoreSet(window, piece);
		}
	}

	// Checking columns
	for (int col = 0; col < COL; col++)
    {
        // Creating the column array
		for (int row = 0; row < ROW; row++)
		{
			col_arr[row] = currBoard[row][col];
		}

        // Counting up the pieces
		for (int row = 0; row < ROW - 3; row++)
        {
			for (int i = 0; i < 4; i++)
			{
				window[i] = col_arr[row + i];
			}
			score += scoreSet(window, piece);
		}
	}

	// Checking diagonals
	for (int row = 0; row < ROW - 3; row++)
    {
        // Counting up the pieces
		for (int col = 0; col < COL; col++)
        {
			row_arr[col] = currBoard[row][col];
		}
        for (int col = 0; col < COL - 3; col++)
        {
            for(int i = 0; i < 4; i++)
            {
                window[i] = currBoard[row + i][col + i];
            }
            score += scoreSet(window, piece);
        }
	}
	for (int row = 0; row < ROW - 3; row++)
    {
        for (int col = 0; col < COL; col++)
        {
            row_arr[col] = currBoard[row][col]; 
        }
        // Counting up the pieces
		for (int col = 0; col < COL - 3; col++)
        {
			for (int i = 0; i < 4; i++)
            {
				window[i] = currBoard[row + 3 - i][col + i];
			}
			score += scoreSet(window, piece);
		}
	}

	// Returning the score
	return score;
}

int ConnectFour::evalFunction2(board currBoard, int player)
{
    if (ranNum() % (player + 1) == 0)
    {
        auto number = ranNum();
        number *= -1;
        return number;
    }
    return ranNum(); 
}

int ConnectFour::evalFunction3(board currBoard, int player)
{
    int score = 0;
    int howManyUpperSpotsTaken = 0;
    const int middle_col = 3;
    const int leftMiddleCol = 2;
    const int rightMiddleCol = 4;

    for(int i = 0; i < 7; i++)
    {
        if (currBoard[4][i] != blank)
            howManyUpperSpotsTaken++;
    }

    if (howManyUpperSpotsTaken > 5)
    {
        if (ranNum() % ranNum() * player)
        {
            return ranNum() * -1;
        }
        else
        {
            return ranNum();
        }

    } 

    for(int row = 0; row < 4; row++)
    {
        if (player == xMax)
        {
            if(currBoard[row][middle_col] == xMax)
                score += 10000;
            else if(currBoard[row][leftMiddleCol] == xMax)
                score += 8000;   
            else if(currBoard[row][rightMiddleCol] == xMax)
                score += 5000;
            else if(currBoard[row][rightMiddleCol] == oMin)
                score -= 5000;
            else if(currBoard[row][leftMiddleCol] == oMin)
                score -= 8000;
            else if(currBoard[row][middle_col] == oMin)
                score -= 10000;
            else 
                score -= 1000;
        }
        else 
        {
            if(currBoard[row][middle_col] == oMin)
                score += 10000;
            else if(currBoard[row][leftMiddleCol] == oMin)
                score += 8000;   
            else if(currBoard[row][rightMiddleCol] == oMin)
                score += 5000;
            else if(currBoard[row][rightMiddleCol] == xMax)
                score -= 5000;
            else if(currBoard[row][leftMiddleCol] == xMax)
                score -= 8000;
            else if(currBoard[row][middle_col] == xMax)
                score -= 10000;
            else 
                score -= 1000;
        }
    }
    
    if (player == oMin)
        score *= -1; 

    return score;
}

bool ConnectFour::deepEnough(int cutoff)
{
    if(cutoff == 0)
        return true;
    else
        return false;
}

vector<board> ConnectFour::moveGenerate(board currBoard, whichPlayer plyer)
{
   vector<board> successors; 

   //recording expansion of node
   nodesExpanded++;

   for (int col = 0; col < COL; col++)
   {
       //if column not full
       if(currBoard[ROW - 1][col] == blank)
       {
           //Generate child
           board child = copyBoard(currBoard);

           //find the lowest available spot
           for (int row = 0; row < ROW; row++)
           {
               //If spot empty fill
               if (child[row][col] == blank)
               {
                   child[row][col] = plyer;

                   //Add child
                   successors.push_back(child);
                   
                   //recording nodes generated
                   nodesGenerated++;
                   break;
               }
           }
       }
   }
   return successors;
}

int ConnectFour::evaluationFunctionSwitcher(board currBoard, whichPlayer plyer)
{
    int value = 0;

    if (plyer == xMax)
    {
        //xMax
        switch(xMaxEvaluation)
        {
            case firstEval:
                value = keepScore1(currBoard, plyer);
                break;
            case secondEval:
                value = evalFunction2(currBoard, plyer);
                break;
            case thirdEval:
                value =  evalFunction3(currBoard, plyer);
                break;
            default:
                cout << "Error with switcher" << endl;
                break;
        }

    }
    else 
    {
        //oMin
        switch(oMinEvaluation)
        {
            case firstEval:
                value = keepScore1(currBoard, plyer);
                break;
            case secondEval:
                value = evalFunction2(currBoard, plyer);
                break;
            case thirdEval:
                value =  evalFunction3(currBoard, plyer);
                break;
            default:
                cout << "Error with switcher" << endl;
                break;
        }
    }

    return value;
}

// The miniMaxAB1 function
pathAndScore ConnectFour::miniMaxAB(board currBoard, int cutoff, whichPlayer plyer, int alpha, int beta)
{
    // Returning current score if cutoff meets requirements
    if (deepEnough(cutoff)) 
    {
		pathAndScore ps;
        ps.value = evaluationFunctionSwitcher(currBoard, plyer);

        ps.path.push_back(currBoard);
        return ps;
	}

    if(plyer == xMax)
    {
        // Lowest possible value to start
        pathAndScore maxEvaluation;
        maxEvaluation.value = INT_MIN;
        maxEvaluation.path.push_back(currBoard);

        // If other player is about to win, return best_move
        if (isWinningMove(currBoard, plyer) == true)
        {
            maxEvaluation.value =  evaluationFunctionSwitcher(currBoard, plyer);
            return maxEvaluation;
        }
       
        //generate children
        vector<board> successors = moveGenerate(currBoard, plyer);

        if (successors.empty() == true)
        {
            pathAndScore ps;
            ps.value = evaluationFunctionSwitcher(currBoard, plyer);
            ps.path.push_back(currBoard);
            return ps;
        }

        // Checking each child
        for (int i = 0; i < successors.size(); i++)
        {

            // Recursively finding the best move
            pathAndScore eval = miniMaxAB(successors[i], cutoff - 1, oMin, alpha, beta);

            //4 b skipped due to if(plyer == xMax) statment

            // If better score, replace the old one
            // Add to path
            if (eval.value > maxEvaluation.value)
            {
               if (maxEvaluation.path.size() == 1) 
               {
                   //No path, only self of root node
                   maxEvaluation.value = eval.value;
                   maxEvaluation.path.insert(maxEvaluation.path.end(), 
                           eval.path.begin(), eval.path.end());
               }
               else
               {
                   //Have a path but found a better one
                   //Note that path should always be 1 or greater,
                   //never 0
                   maxEvaluation.value = eval.value;
                   //Delete previous path, keeping only first element of
                   //path and replacing the rest with incoming best path
                   
                   while(maxEvaluation.path.size() != 1)
                       maxEvaluation.path.pop_back();

                   for(board b : eval.path)
                   {
                       maxEvaluation.path.push_back(b);
                   }

               }
            }

            // Setting a new alpha
            alpha = max(alpha, maxEvaluation.value);

            // Alpha-Beta pruning
            if (alpha >= beta)
            {
                break;
            }
        }

        // Returning the best move
        return maxEvaluation;
    }
    else  // The minimizing player (Player 2)
    {
        // Lowest possible value to start
        pathAndScore minEvaluation;
        minEvaluation.value = INT_MAX;
        minEvaluation.path.push_back(currBoard);

        // If other player is about to win, return best_move
        if (isWinningMove(currBoard, plyer) == true)
        {
            minEvaluation.value = evaluationFunctionSwitcher(currBoard, plyer);
            return minEvaluation;
        }
       
        //generate children
        vector<board> successors = moveGenerate(currBoard, plyer);

        if (successors.empty() == true)
        {
            pathAndScore ps;
            ps.value = evaluationFunctionSwitcher(currBoard, plyer);
            minEvaluation.path.push_back(currBoard);
            return ps;
        }

        // Checking each child
        for (int i = 0; i < successors.size(); i++)
        {

            // Recursively finding the best move
            pathAndScore eval = miniMaxAB(successors[i], cutoff - 1, xMax, alpha, beta);

            //4 b skipped due to if(plyer == xMax) statment
            
            // If better score, replace the old one
            if (eval.value < minEvaluation.value)
            {
                if (minEvaluation.path.size() == 1) 
                {
                    //No path, only self of root node
                    minEvaluation.value = eval.value;
                    minEvaluation.path.insert(minEvaluation.path.end(), 
                            eval.path.begin(), eval.path.end());
                    

                }
                else
                {
                    //Have a path but found a better one
                    //Note that path should always be 1 or greater,
                    //never 0
                    minEvaluation.value = eval.value;
                    //Delete previous path, keeping only first element of
                    //path and replacing the rest with incoming best path
                    while(minEvaluation.path.size() != 1)
                        minEvaluation.path.pop_back();

                    for(board b : eval.path)
                    {
                        minEvaluation.path.push_back(b);
                    }

                }
            }

            // Setting a new beta
            beta = min(beta, minEvaluation.value);

            // Alpha-Beta pruning
            if (beta <= alpha)
            {
                break;
            }
        }

        // Returning the best move
        return minEvaluation;
	}
}


