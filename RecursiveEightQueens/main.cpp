/**
*	Eight-Queens Problem
*	Reading: 7.5
*/
#include <iostream>
#include <vector>

using namespace std;

const int UNASSIGN_VALUE = -1;

const int NUMBER_ROWS = 8; // Number of rows in our chess board
const int NUMBER_COLS = 8; // Number of columns in our chess board

// RowPlacement is a vector of column queen assignments to each row.
// If we assign a queen in column x to row y, then RowPlacement[y] = x.
// We assume columns are numbered from 0 to NUMBER_COLS-1
vector<int> RowPlacement(NUMBER_ROWS, UNASSIGN_VALUE); // Create NUMBER_ROWS element vector, initializing each element to the value "-1"

/**
*	This function checks if a previous assignment of a queen to a row
*	will have a diagonal that invalidates this assigning a col_pos queen to row_pos.
*/
bool ValidPosition(int col_pos, int row_pos) {
	for (int i = 0; i < RowPlacement.size(); ++i) {
		if (i == row_pos) // we are only checking if another row assignment will make row_pos invalid
			continue;
		if (RowPlacement[i] != UNASSIGN_VALUE) { // if this other row has been assigned
			if (abs(RowPlacement[i] - col_pos) == abs(i - row_pos)) // a previous row assignment has a diagonal that will cross row_pos
				return false;
		}
	}
	return true;
}

/**
*	This function displays the assignment of each column queen in each row of the chess board
*/
void DisplayBoard(vector<int> &Row)
{
	for (int row = 0; row < NUMBER_ROWS; ++row) {
		if (Row[row] == UNASSIGN_VALUE) {
			cout << "ERROR!  Row " << row + 1 << " has not been assigned\n\n";
			continue;
		}
		for (int col = 0; col < Row[row]; ++col) {
			cout << " - ";
		}
		cout << " * "; // Dislay queen at column Row[row]
		for (int col = Row[row] + 1; col < NUMBER_COLS; ++col) {
			cout << " - ";
		}
		cout << endl << endl;
	}
	cout << endl;
}

/**
*	Recursive implementation of the solution to the eight-queens problem
*/
bool PlaceQueen(int column) {
	if (column == NUMBER_COLS) { // Base Condition
		return true; // Successfully assigned all column queens in the board.  We can just return true.
	}
	else {
		// Try to assign this column's queen to a valid row
		for (int row = 0; row < RowPlacement.size(); ++row) {

			// If RowPlacement[row] is not UNASSIGN_VALUE, we want to move to the next row
			if (RowPlacement[row] != UNASSIGN_VALUE) // means there is already a queen in this row
				continue;

			// Check if assigning a column queen to this row is valid
			if (!ValidPosition(column, row)) // a diagonal invalidates this position
				continue;

			// Assign column to Row[row]
			RowPlacement[row] = column;

			// Recursively call PlaceQueen to place a queen in the next column.
			// Remember to check if the recursive call to placing the queen in the next column 
			// was successful, i.e. it returned true.
			// If it was successful, you can assume the assigment of this column's queen 
			// to RowPlacement[row] was also successful, and hence return true here.
			if (PlaceQueen(column + 1)) {
				return true;
			}

			// Unassign the assignment of the column's queen to this row, and try the next one
			RowPlacement[row] = UNASSIGN_VALUE; 
		}
		return false; // Tried every available row, so it is time to call it quits
	}
}

int main()
{
	PlaceQueen(0); // Begin the process of placing queens, starting at column 0
	DisplayBoard(RowPlacement); // Display the chess board with the queen placements
	system("PAUSE");
}