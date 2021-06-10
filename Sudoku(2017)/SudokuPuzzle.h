#pragma once
#include <vector>
#include"Cell.h"

using namespace std;

class SudokuPuzzle
{
public:
	SudokuPuzzle() : m_puzzleSize(9), m_blockSize(m_puzzleSize / 3){}
	void GetPossibleValue();
	bool CheckRow(int row, int number);
	bool CheckColumn(int column, int number);
	bool CheckSubGrid(int SubRow, int SubColumn, int number);
	bool SameNumber(int row, int column, int number);
	void Solve(const char filenameIn[]);
	void FindSingle();
	void FindHidden(int setrow, int row, int setcolumn, int column);
	void erase(std::vector<int>& v, int key);
	bool CheckDone();
private:
	void output() const;
	void readPuzzle(const char filenameIn[]);
	int m_grid[9][9];
	Cell m_Clist[9][9];
	vector<vector<int>> m_list;
	vector<int> empty_X;
	vector<int> empty_Y;
	bool Backed = false;
	int SolveRow = 0;
	int SolveColumn = 0;
	int hiddenRow = 0;
	int hiddenColumn = 0;
	bool checkNum = false;
	int IntCount = 0;
	int EndCount = 0;
	int GridPasses = 0;
	int CandidatePasses = 0;
	int unsolve = 0;
	int m_puzzleSize;
	int m_blockSize;
};
