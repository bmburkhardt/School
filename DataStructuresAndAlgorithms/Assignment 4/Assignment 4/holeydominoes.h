// holeydominoes.h
// Bryan Burkhardt
// 24 Oct 2016
//
// Assignment 4 for CS311 Fall 2016
// Header for holeydominoes

#ifndef HOLEYDOMINOES_H_INCLUDED
#define HOLEYDOMINOES_H_INCLUDED

#include <vector>
using std::vector;

typedef vector< vector<int> > board2dVector;


// holeyDominoes
// Pre:
//		0 <= height and width
//		0 <= forbid_row <= height
//		0 <= forbid_column <= width
// Post:
//		Returns number of combinations possible given the forbidden square.
int holeyDominoes(int height, int width, int forbid_row, int forbid_column);



// holeyDominoesRecursion
// Finds possible combinations on the board.
// Pre:
//		None.
// Post:
// 		Return number of combinations possible given the forbidden square.
int holeyDominoesRecursion(board2dVector & board, int combinations);

#endif // HOLEYDOMINOES_H_INCLUDED
