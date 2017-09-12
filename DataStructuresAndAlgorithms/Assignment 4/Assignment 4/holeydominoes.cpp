// holeydominoes.cpp
// Bryan Burkhardt
// 24 Oct 2016
// 
// Assignment 4 for CS311 Fall 2016
// Source file for holeydominoes

#include "holeydominoes.h"
#include <vector>
using std::size_t;
using std::vector;

// int holeyDominoes
// (see header for docs.)
int holeyDominoes(int height, int width, int forbid_row, int forbid_column)
{
    if ((height*width)%2 == 0)
    {
        return 0;
    }
    int rv = 0;
    board2dVector board;

    // Initialize domino board with proper dimensions and fill with 0's
    board.resize(width, vector<int>(height, 0));
    board[forbid_column][forbid_row] = 1; // Set forbidden square to 1
    rv += holeyDominoesRecursion(board, 0);
    return rv;
}


// holeyDominoesRecursion
// (see header for docs.)
int holeyDominoesRecursion(board2dVector & board, int combinations)
{
    if ( board.size()*board[0].size() == 2*combinations+1 )
    {
        return 1;
    }
    int rv = 0;
    for (size_t i=0; i < board.size(); ++i)
    {
    	for (size_t j=0; j < board[i].size(); ++j)
    	{

    		if (board[i][j] == 1)
            {
                continue;
            }
    		if (j+1 < board[i].size() && board[i][j+1] == 0)
            {
				board[i][j] = 1;
				board[i][j+1] = 1;
				rv += holeyDominoesRecursion(board, combinations+1);
				board[i][j] = 0;
				board[i][j+1] = 0;
			}
    		if (i+1 < board.size() && board[i+1][j] == 0)
            {
    			board[i][j] = 1;
    			board[i+1][j] = 1;
    			rv += holeyDominoesRecursion(board, combinations+1);
    			board[i][j] = 0;
    			board[i+1][j] = 0;
    		}
            return rv;
    	}
    }
    return 0;
}
