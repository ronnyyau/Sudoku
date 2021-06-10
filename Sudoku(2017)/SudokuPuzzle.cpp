#include "SudokuPuzzle.h"
#include <fstream>
#include <iostream>
#include<cstdlib>
#include <chrono>
#include <algorithm>
#include <list>
using namespace std;

void SudokuPuzzle::readPuzzle(const char filenameIn[])
{
	ifstream fin;
	const string input = filenameIn;
	fin.open(input);
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			fin >> m_grid[x][y];
		}
	}
	fin.close();
}

void SudokuPuzzle::output() const
{
	std::ofstream fout;
	fout.open("Test4_solution.txt");
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			fout << m_grid[x][y] << " ";
		}
		fout << '\n';
	}
	fout.close();
}

void SudokuPuzzle::Solve(const char filenameIn[])
{
	// Read puzzle from text file
	readPuzzle(filenameIn);
	//Start timing
	const auto startTime = std::chrono::high_resolution_clock::now();
	//The amount of runs to try finding naked single and hidden single.
	int run = 0;
	//This is used for counting initial data set solved cells and unsolve cells.
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			if (m_grid[row][column] != 0)
			{
				IntCount++;
			}
			else
			{
				unsolve++;
			}
		}
		cout << endl;
	}
	GridPasses++;
	//Try to find all the naked single in the first try
	FindSingle();
	GetPossibleValue();
	//This is used for counting initial data set first set of solved cells
	EndCount -= IntCount;
	//Enter a loop to try to solve the puzzle, exit condition is solved the puzzle completely
	//or the amount of runs to try finding naked single and hidden single reach 20 times
	while(CheckDone() && run < 20)
	{
		FindSingle();
		const int row = 0;
		const int fixedrow = 0;
		const int column = 0;
		const int fixedcolumn = 0;
		FindHidden(row, fixedrow, column, fixedcolumn);
		run++;
	}
	if(!CheckDone())
	{
		//When the projram managed to solve, it will print out the grid.
		cout << "Solved!" << endl;
		GridPasses++;
		for (int row = 0; row < 9; row++)
		{
			for (int column = 0; column < 9; column++)
			{
				cout << m_grid[row][column] << " ";
			}
			cout << endl;
		}
	}
	else if (run == 20)
	{
		//If the loop ran 20 times and still not able to solve the puzzle, it will try to brute force to solve
		//the puzzle if possible
		GridPasses++;
		for (int x = 0; x < 9; x++)
		{
			for (int y = 0; y < 9; y++)
			{
				if (m_grid[x][y] == 0)
				{
					int tempX = x*9;
					int tempY = y;
					if(m_list[x * 9 + y][0] != 0);
					{
						m_grid[x][y] = m_list[x * 9 + y][0];
						const int num = m_list[x * 9 + y][0];
						m_list[x * 9 + y].clear();
						m_list[x * 9 + y].push_back(0);
						CandidatePasses++;
						checkNum = true;
						CheckSubGrid(x - x % 3, y - y % 3, num);
						for (; tempX < x*9 + 9; tempX++)
						{
							erase(m_list[tempX], num);
							CandidatePasses++;
						}
						for (; tempY < y + 73; tempY += 9)
						{
							erase(m_list[tempY], num);
							CandidatePasses++;
						}

					}
				}
				
			}
		}
		if (!CheckDone())
		{
			//Here is the program second check if the puzzle is solved or not by using brute force
			cout << "Solved using brute force" << endl;
			GridPasses++;
			for (int row = 0; row < 9; row++)
			{
				for (int column = 0; column < 9; column++)
				{
					cout << m_grid[row][column] << " ";
				}
				cout << endl;
			}
		}
		else
		{
			//Here will print out the unsolve puzzle to let user to see which cells are unsolve
			cout << "Can't solve " << endl;
			GridPasses++;
			for (int row = 0; row < 9; row++)
			{
				for (int column = 0; column < 9; column++)
				{
					cout << m_grid[row][column] << " ";
				}
				cout << endl;
			}
		}
	}
	//End the time for timing the solving process
	const auto endTime = std::chrono::high_resolution_clock::now();
	const auto duration = (endTime - startTime).count();
	//Print out the useful informations for me to evaulate
	cout << "Initial data unsolved cells: " << unsolve << endl;
	cout << "Initial data set solved cells: " << EndCount << endl;
	cout << "Total Grid passes: " << GridPasses << endl;
	cout << "Total Candidate passes: " << CandidatePasses << endl;

	// Sample timing output in nanoseconds
	std::cout << duration << "ns" << std::endl;
	output();
}

void SudokuPuzzle::GetPossibleValue()
{
	//Here is where the program will run through the grid and 
	//get each cells' possible candidates and put them into candidate list called 'm_list'
	const vector<int> cell;
	int num = 0;
	GridPasses++;
	for (; SolveRow < 9; SolveRow++)
	{
		for (; SolveColumn < 9; SolveColumn++)
		{
			if (m_grid[SolveRow][SolveColumn] == 0)
			{
				//Generate a new vector list inside the candidate list
				m_list.push_back(cell);
				for (int i = 1; i < 10; i++)
				{
					if (SameNumber(SolveRow, SolveColumn, i))
					{
						//Put the possible candidate into candidate list
						m_list[num].push_back(i);
						CandidatePasses++;
					}
				}
				num++;
			}
			else
			{
				//Here is where the program checking the solved cell, which the program will
				//put a 0 into candidate list which mean no need to consider
				m_list.push_back(cell);
				m_list[num].push_back(0);
				CandidatePasses++;
				num++;
				EndCount++;
			}
		}
		SolveColumn = 0;
	}
}

bool SudokuPuzzle::CheckRow(const int row, const int number)
{
	//Check row of the cell
	for (int column = 0; column < 9; column++)
	{
		if (m_grid[row][column] == number)
		{
			return true;
		}
	}
	return false;
}

bool SudokuPuzzle::CheckColumn(const int column, const int number)
{
	//Check column of the cell
	for (int row = 0; row < 9; row++)
	{
		if (m_grid[row][column] == number)
		{
			return true;
		}
	}
	return false;
}

bool SudokuPuzzle::CheckSubGrid(const int SubRow, const int SubColumn, const int number)
 {
	//Check 3x3Grid of the cell
	for (int row = 0; row < 3; row++)
	{
		for (int column = 0; column < 3; column++)
		{
			const int index = (row + SubRow) * 9 + (column + SubColumn);
			if (checkNum == true)
			{
				//This if statment is for removing the found value from their candidate lists in 3x3Grid
				CandidatePasses++;
				if (binary_search(m_list[index].begin(), m_list[index].end(), number))
				{
					erase(m_list[index], number);
				}
			}
			else if (m_grid[row+SubRow][column+SubColumn] == number)
			{
				return true;
			}
		}
	}
	checkNum = false;
	return false;
}

bool SudokuPuzzle::SameNumber(const int row, const int column, const int number)
{
	//It will return a true or false if the cell have same number as other cells
	//in the same row, column and 3x3Grid
	GridPasses += 3;
	return (!CheckRow(row, number) &&
		!CheckColumn(column, number) &&
		!CheckSubGrid(row - row % 3, column - column % 3, number));
}

void SudokuPuzzle::FindSingle()
{
	//This is where the program will perform finding the naked single
	GridPasses++;
	vector<int> temp;
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			if (m_grid[x][y] == 0)
			{
				for (int i = 1; i < 10; i++)
				{
					if (SameNumber(x, y, i))
					{
						temp.push_back(i);
					}
				}
				if (temp.size() == 1)
				{
					//Here is where the program found naked single
					//it will then run the method again to check if previous unsolve cell have naked single.
					m_grid[x][y] = temp[0];
					temp.clear();
					FindSingle();
				}
				temp.clear();
			}
		}
	}
}

void SudokuPuzzle::FindHidden(int setrow, int row, int setcolumn, int column)
{
	//This is where the program will perform finding the naked single
	vector<int>Rowtemp;
	vector<int>index;
	int num = 0;
	int Count = 0;
	vector<int>Columntemp;
	vector<int>index2;
	int num2 = 0;
	int Count2 = 0;
	//loop the possible numbers which are 1 to 9
	for (int i = 1; i < 10; i++)
	{
		//Check row if there are hidden 
		for (; setrow < row + 9; setrow++)
		{
			for (int intercolumn = 0; intercolumn < m_list[setrow].size(); intercolumn++)
			{
				if (m_list[setrow][intercolumn] == 0)
				{
					CandidatePasses++;
					break;
				}
				else if (m_list[setrow][intercolumn] == i)
				{
					CandidatePasses++;
					num++;
				}
			}
		}
		//Check column if there are hidden 
		for (; setcolumn < column + 73; setcolumn += 9)
		{
			for (int intercolumn = 0; intercolumn < m_list[setcolumn].size(); intercolumn++)
			{
				if (m_list[setcolumn][intercolumn] == 0)
				{
					CandidatePasses++;
					break;
				}
				else if (m_list[setcolumn][intercolumn] == i)
				{
					CandidatePasses++;
					num2++;
				}
			}
		}
		//These two vectors will store value for a row and a column for later use
		Rowtemp.push_back(num);
		Columntemp.push_back(num2);
		//Reset these four values for next row and column use
		setrow = row;
		setcolumn = column;
		num = 0;
		num2 = 0;
	}
	//Using vector's index to determine which numbers are hidden single candidate
	//For example, if index 0 have only one value, then is mean 1 is hidden single
	// as possible number is 1-9, so it needs to move one number up
	//A row or a column might have multiples hidden singles
	//so there is a vector to store them
	for (int i = 0; i < Rowtemp.size(); i++)
	{
		Count = count(Rowtemp.begin(), Rowtemp.end(), 1);
		if (Rowtemp[i] == 1)
		{
			num = i + 1;
			index.push_back(num);
		}
	}
	for (int i = 0; i < Columntemp.size(); i++)
	{
		Count2 = count(Columntemp.begin(), Columntemp.end(), 1);
		if (Columntemp[i] == 1)
		{
			num2 = i + 1;
			index2.push_back(num2);
		}
	}
	//Loop the candidate list to find where the hidden single is using the vector which store
	//all hidden singles from a row or a column
	for (int x = 0; x < index.size(); x++)
	{
		for (; setrow < row + 9; setrow++)
		{
			if (binary_search(m_list[setrow].begin(), m_list[setrow].end(), index[x]))
			{
				//Here is where the binary search found the index of the hidden single shoud be
				GridPasses++;
				//Convert the index back to row and column
				//so it can be use to pue the hidden single into the right location
				hiddenRow = setrow / 9;
				hiddenColumn = setrow -(hiddenRow*9);
				m_grid[hiddenRow][hiddenColumn] = index[x];
				//Since that cell is solved, the program will clear its list
				//and put a 0 in to show that it is solved
				m_list[setrow].clear();
				m_list[setrow].push_back(0);
				CandidatePasses++;
				//Here is where it will update others candidate list
				checkNum = true;
				CheckSubGrid(hiddenRow - hiddenRow % 3, hiddenColumn - hiddenColumn % 3, index[x]);
				const int temp = hiddenColumn + 73;
				for (; hiddenColumn < temp; hiddenColumn += 9)
				{
					if (binary_search(m_list[hiddenColumn].begin(), m_list[hiddenColumn].end(), index[x]))
					{	
						CandidatePasses++;
						erase(m_list[hiddenColumn],index[x]);
					}
				}
			}
		}
		setrow = row;
	}
	//This loop is the same as above, but this is for column
	//and above is for row
	for (int x = 0; x < index2.size(); x++)
	{
		for (; setcolumn < column + 73; setcolumn += 9)
		{
			if (binary_search(m_list[setcolumn].begin(), m_list[setcolumn].end(), index2[x]))
			{
				GridPasses++;
				hiddenColumn = setcolumn / 9;
				hiddenRow = setcolumn - (hiddenColumn*9);
				m_grid[hiddenColumn][hiddenRow] = index2[x];
				m_list[setcolumn].clear();
				m_list[setcolumn].push_back(0);
				CandidatePasses++;
				checkNum = true;
				CheckSubGrid(hiddenColumn - hiddenColumn % 3, hiddenRow - hiddenRow % 3, index2[x]);
				hiddenColumn *= 9;
				const int temp = hiddenColumn + 9;
				for (; hiddenColumn < temp; hiddenColumn++)
				{
					if (binary_search(m_list[hiddenColumn].begin(), m_list[hiddenColumn].end(), index2[x]))
					{
						CandidatePasses++;
						erase(m_list[hiddenColumn], index2[x]);
					}
				}
			}
		}
		setcolumn = column;
	}
	//Set the value to next row and column
	setrow += 9;
	setcolumn += 1;
	row = setrow;
	column = setcolumn;
	if (setrow == m_list.size() || setcolumn == m_list.size())
	{
		//when it reaches the end of the candidate list
		return;
	}
	else
	{
		//it will run this method again until it reach the end of the candidate list
		FindHidden(setrow, row, setcolumn, column);
	}
}
void SudokuPuzzle::erase(std::vector<int>& v, const int key)
{
	//This method is for deleting the value from of the candidate list list
	for (auto it = v.begin(); it != v.end();)
	{
		if (*it == key) {
			it = v.erase(it);
		}
		else {
			++it;
		}
	}
}
bool SudokuPuzzle::CheckDone()
{
	//This method is for checking if all cell is solved or not
	GridPasses++;
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (m_grid[row][col] == 0)
			{
				return true;
			}
		}
	}	
	return false;
}