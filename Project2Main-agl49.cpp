// File Name: Project2Main-agl49.cpp
// Author: Verginia Mae Dole, Adrian Lopez, James Helgren

#include "Project2.h"
#include <iostream>
#include <ostream>
#include <vector>
#include <cstring>
using namespace std;

// Nonmember function prototypes
whichPlayer game(const whichPlayer, const whichPlayer, int, int, evalFunction, evalFunction, bool, 
                 bool);
//function to add up win lose stats
void addWins(int &w, int &l);

// The main function
int main(int argc, char* argv[])
{

    int maxEV1_W = 0;
    int maxEV1_L = 0;
    int maxEV2_W = 0;
    int maxEV2_L = 0;

    int minEV2_W = 0;
    int minEV2_L = 0;
    int minEV3_W = 0;
    int minEV3_L = 0;
    
    whichPlayer winner = blank;

    //Determine mode
    if (argc > 3)
    {
        cout << "Error: incorrect params" << endl;
        return -1;
    }
    bool fastMode = false;
    bool noPathMode = false;
    if (argc == 2 && strcmp(argv[1], "-f") == 0) 
        fastMode = true;
    else if(argc == 2 && strcmp(argv[1], "-np") == 0)
        noPathMode = true;
    else if(argc == 3 && strcmp(argv[1], "-f") == 0 && strcmp(argv[2], "-np") == 0)
    {
        fastMode = true;
        noPathMode =  true;
    }
    else if(argc == 3 && strcmp(argv[1], "-np") == 0 && strcmp(argv[2], "-f") == 0)
    {
        fastMode = true;
        noPathMode =  true;
    }
    else
    {
        cout << "Unrecognized flag, proceeding with default..." << endl;
    }

    // Beginning text
    cout << "Welcome to Connect 4!" << endl << endl;
    cout << "Player 1: X" << endl;
    cout << "Player 2: O" << endl;

    // Game (EV1 vs EV2, depth 2)
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Game: EV1 vs EV2 (Depth 2)" << endl << endl;
    winner = game(xMax, oMin, 2, 2, firstEval, secondEval, fastMode, noPathMode);

    //function to record the winner
    if (winner == xMax)
        addWins(maxEV1_W, minEV2_L);
    else
        addWins(minEV2_W, maxEV1_L);
        
    //Game (EV1(Depth 2) vs EV3(Depth 4))
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Game: EV1 (Depth 2) vs EV3 (Depth 4)" << endl << endl;
    winner = game(xMax, oMin, 2, 4, firstEval, thirdEval, fastMode, noPathMode);

    //function to record winner
    if (winner == xMax)
        addWins(maxEV1_W, minEV3_L);
    else
        addWins(minEV3_W, maxEV1_L);
     
    
    //Game (EV2(Depth 2) vs EV3(Depth 8))
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Game: EV2 (Depth 2) vs EV3 (Depth 8)" << endl << endl;
    winner = game(xMax, oMin, 2, 8, secondEval, thirdEval, fastMode, noPathMode);

    //function to record winner
    if (winner == xMax)
        addWins(maxEV2_W, minEV3_L);
    else
        addWins(minEV3_W, maxEV2_L);
    

    //Game (EV1(Depth 4) vs EV2(Depth 2))
    cout << endl << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Game: EV1 (Depth 4) vs EV2 (Depth 2)" << endl << endl;
    winner = game(xMax, oMin, 4, 2, firstEval, secondEval, fastMode, noPathMode);

    // function to record winner
    if (winner == xMax)
        addWins(maxEV1_W, minEV2_L);
    else
        addWins(minEV2_W, maxEV1_L);
    
    
    //Game (EV1(Depth 4) vs EV3(Depth 4))
    cout << endl << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Game: EV1 (Depth 4) vs EV3 (Depth 4)" << endl << endl;
    winner = game(xMax, oMin, 4, 4, firstEval, thirdEval, fastMode, noPathMode);

    // function to record winner
    if (winner == xMax)
        addWins(maxEV1_W, minEV3_L);
    else
        addWins(minEV3_W, maxEV1_L);
    

        
    //Game (EV2(Depth 4) vs EV3(Depth 8))
    cout << endl << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Game: EV2 (Depth 4) vs EV3 (Depth 8)" << endl << endl;
    winner = game(xMax, oMin, 4, 8, secondEval, thirdEval, fastMode, noPathMode);

    // function to record winner
    if (winner == xMax)
        addWins(maxEV2_W, minEV3_L);
    else
        addWins(minEV3_W, maxEV2_L);
    
    
    
    //Game (EV1(Depth 8) vs EV2 (Depth 2))
    cout << endl << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Game: EV1 (Depth 8) vs EV2 (Depth 2)" << endl << endl;
    winner = game(xMax, oMin, 8, 2, firstEval, secondEval, fastMode, noPathMode);

    // function to record winner
    if (winner == xMax)
        addWins(maxEV1_W, minEV2_L);
    else
        addWins(minEV2_W, maxEV1_L);
    
    //Game (EV1(Depth 8) vs EV3(Depth 4))
    cout << endl << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Game: EV1 (Depth 8) vs EV3 (Depth 4)" << endl << endl;
    winner = game(xMax, oMin, 8, 4, firstEval, thirdEval, fastMode, noPathMode);

    // function to record winner
    if (winner == xMax)
        addWins(maxEV1_W, minEV3_L);
    else
        addWins(minEV3_W, maxEV1_L);
    
    //Game (EV2(Depth 8) vs EV3(Depth 8))
    cout << endl << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Game: EV2 (Depth 8) vs EV3 (Depth 8)" << endl << endl;
    winner = game(xMax, oMin, 8, 8, secondEval, thirdEval, fastMode, noPathMode);

    // function to record winner
    if (winner == xMax)
        addWins(maxEV2_W, minEV3_L);
    else
        addWins(minEV3_W, maxEV2_L);

    // Ending text
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Win/Lose Statistics" << endl;
    cout << "EV 1" << endl
         << "  MAX Wins: " << maxEV1_W << endl
         << "  MAX Losses: " << maxEV1_L << endl
         << "EV 2" << endl
         << "  MAX Wins: " << maxEV2_W << endl
         << "  MAX Losses: " << maxEV2_L << endl
         << "  MIN Wins: " << minEV2_W << endl
         << "  MIN Losses: " << minEV2_L << endl
         << "EV 3" << endl
         << "  MIN Wins: " << minEV3_W << endl
         << "  MIN Losses: " << minEV3_L << endl;

    cout << "Terminating program..." << endl;

    return 0;
}


// The game1v2 function
whichPlayer game(const whichPlayer firstPlayer, const whichPlayer secondPlayer, int xMaxCutOff, 
                 int oMinCutOff, evalFunction xMaxEvalFunc, evalFunction oMinEvalFunc,
                 bool fastMode, bool noPathMode)
{
    // Declaring variables
    const int TOTAL_TURNS = 42;
    ConnectFour c4(TOTAL_TURNS, xMaxEvalFunc, oMinEvalFunc, noPathMode);
    char input;
    bool game_over = false;
    int turns = 0;
    whichPlayer curr_player = firstPlayer;
    whichPlayer winner = blank;

    //Cout declaring game params
    cout << "--- GAME Specifics ---" << endl
         << "First player: ";
    switch (firstPlayer) 
    {
		case xMax:
            cout << "Max = X" << endl
                 << "Second player: Min = O" << endl
                 << "Max's depth limit: " << xMaxCutOff << endl
                 << "Min's depth limit: " << oMinCutOff << endl
                 << "Max's evaluation function: " << xMaxEvalFunc + 1 << endl
                 << "Min's evaluation function: " << oMinEvalFunc + 1 << endl;
            break;
        case oMin:
            cout << "Min = O" << endl
                 << "Second player: Max = X" << endl
                 << "Max's depth limit: " << xMaxCutOff << endl
                 << "Min's depth limit: " << oMinCutOff << endl
                 << "Max's evaluation function: " << xMaxEvalFunc + 1 << endl
                 << "Min's evaluation function: " << oMinEvalFunc + 1 << endl;
            break;
	}
    
    // Printing the board
    cout << "Turn " << turns << endl;
	c4.printMasterBoard();
    
    if (!fastMode)
    {
        //Slow mode
        cout << "Press y to continue: ";
        cin >> input;
        while (input != 'y')
        {
            cout << "Invalid input. Try again: ";
            cin >> input;
        }
        cout << endl;
    }

	// A while-loop for the game
	while (!game_over)
    {
        // Player 1 or 2 makes a move
		switch (curr_player) 
        {
		    case xMax:
                c4.xMaxMove(xMaxCutOff);
                break;
            case oMin:
                c4.oMinMove(oMinCutOff);
                break;
		}

        // Checking if there are any moves left
		if (c4.getCurrTurn() == 42)
		{
			game_over = true;
			break;
		}

		// Determining if the game is over
		game_over = c4.gameFinished(curr_player);
        if (game_over) winner = curr_player; 

		// Switching the players
	    if (curr_player == xMax)
        {
            curr_player = oMin;
        }
        else
        {
            curr_player = xMax;
        }

		// Printing the board
        cout << endl;
        cout << "Turn " << c4.getCurrTurn() << endl;
        c4.printMasterBoard();
       
        if(!fastMode)
        {
            //Slow Mode
            cout << "Press y to continue: ";
            cin >> input;
            while (input != 'y')
            {
                cout << "Invalid input. Try again: ";
                cin >> input;
            }
            cout << endl;
        }
	}

	// Determining the outcome of the game
    // Here is also where games show nodes stats
	if (c4.getCurrTurn() == TOTAL_TURNS)
    {
		cout << "It's A Draw!" << endl;
        cout << "Nodes generated: " << c4.getNodesGenerated() << endl;
        cout << "Nodes Expanded: " << c4.getNodesExpanded() << endl;
        return blank;
	}
	else
	{
        if (winner == xMax)
        {
            cout << "MAX Wins!" << endl;
            cout << "Nodes generated: " << c4.getNodesGenerated() << endl;
            cout << "Nodes Expanded: " << c4.getNodesExpanded() << endl;
            return winner;
        }
        else
        {
            cout << "MIN Wins!" << endl;
            cout << "Nodes generated: " << c4.getNodesGenerated() << endl;
            cout << "Nodes Expanded: " << c4.getNodesExpanded() << endl;
            return winner;
        }
	}
}

void addWins(int &w, int &l)
{
    w++;
    l++;
}



