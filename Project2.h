// File Name: Project2.h
// Author: Verginia Mae Dole, Adrian Lopez, James Helgren

#ifndef PROJECT2
#define PROJECT2
#include <vector>
#include <array>
#include <random>
using namespace std;

typedef array< array<int, 7>, 6> board;
struct pathAndScore
{
    vector<board> path;
    int value;
};
//Enums for places
enum whichPlayer{blank=0, xMax=1, oMin=2};
enum evalFunction{firstEval, secondEval, thirdEval};

// Declaring a class
class ConnectFour
{
private:
    evalFunction xMaxEvaluation;
    evalFunction oMinEvaluation;
    int maxTurns;
    int currTurn;
    int nodesGenerated;
    int nodesExpanded;
    bool noPathMode;

    const int ROW = 6;
    const int COL = 7;

    mt19937 ranNum;
    
    //Master board
    board masterBoard{};
    /*
     * Note intended board structure
     *     C1 ...                          C7
     * R6  R6C1 (masterBoard[5][0])        R6C7 (masterBoard[5][6])
     * .
     * .
     * .
     * R1  R1C1 (masterBoard[0][0])        R1C7 (masterBoard[0][6]) 
    */ 
     void printBoard(board);
          
     //MinMax helper functions
     bool deepEnough(int);
     vector<board> moveGenerate(board, whichPlayer);
     int evaluationFunctionSwitcher(board, whichPlayer);
     bool isWinningMove(board, int);


     //MinMax evaluation functions
     //Designation of eval functions will be 1, 2, 3
     //Eval function 1
     int scoreSet(vector<int>, int);
     int keepScore1(board, int);
     int evalFunction1(int, int, int);
     
     int evalFunction2(board, int);
     int evalFunction3(board, int);

public:
    //Constructor
    ConnectFour(int, evalFunction, evalFunction, bool);
    //Destructor
    ~ConnectFour();
    board testState;
    void setMasterToTestState();

    // Public member function prototypes
    void printMasterBoard();
    void addPiece(board);
    void xMaxMove(int cutoff);
    void oMinMove(int cutoff);
    bool gameFinished(whichPlayer);
    board copyBoard(board);
    pathAndScore miniMaxAB(board currBoard, int cutoff, whichPlayer plyer, int alpha, int beta);
    //Function to return stats
    int getCurrTurn();
    int getNodesGenerated();
    int getNodesExpanded();
};

#endif
