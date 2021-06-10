#pragma once
#include<vector>
using namespace std;


class Cell
{
public:
	Cell(const int p_value, const bool p_given);
	~Cell();


	int Value() const;
	bool Given() const;
	int Size() const;
	int index(int index) const;

	void setValue(int newValue);
	void setGiven(bool newValue);
	void addCandidate(int newCandidate);
	void remove(int removalCandidate);

private:
	vector<int> m_candidateList;
	int m_value;
	bool m_given;
	
};