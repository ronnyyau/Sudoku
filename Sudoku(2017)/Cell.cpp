#include"Cell.h"

using namespace std;

Cell::Cell(const int p_value, const bool p_given)
{
	m_value = p_value;
	m_given = p_given;
	for (int i = 1; i <= 9; ++i)
	{
		m_candidateList.push_back(i);
	}
}
Cell::~Cell()
{
}

int Cell::Value() const
{
	return m_value;
}

bool Cell::Given() const
{
	return m_given;
}
int Cell::index(int index) const
{
	return m_candidateList[index];
}
void Cell::setValue(int Value)
{
	m_value = Value;
}

void Cell::setGiven(bool Given)
{
	m_given = Given;
}
int Cell::Size() const
{
	return m_candidateList.size();
}

void Cell::remove(int removalCandidate)
{
	//Find the position of the element to remove and reomve it from that position
	for (size_t i = 0; i < m_candidateList.size(); ++i) {
		if (m_candidateList[i] == removalCandidate) {
			m_candidateList.erase(m_candidateList.begin() + i);
		}
	}
}