#pragma once

#ifndef INC_REALTHINGSTATES_H
#define INC_REALTHINGSTATES_H


enum class State : int
{
	None = 0,
	Open = 1,
};


class StateSet
{
public:

	bool Test(State pState) const { return (m_states & (int)pState) != 0; }
	void Add(State pState) { m_states |= (int)pState; }
	void Remove(State pState) { m_states &= ~(int)pState; }

private:

	int m_states;

};


#endif // INC_REALTHINGSTATES_H
