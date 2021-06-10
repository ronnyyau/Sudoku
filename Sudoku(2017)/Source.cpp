#include <iostream>
#include "SudokuPuzzle.h"

using namespace std;

int main(const int args)
{
	SudokuPuzzle puzzle;
	puzzle.Solve("Test4_puzzle.txt");

	system("pause");
}