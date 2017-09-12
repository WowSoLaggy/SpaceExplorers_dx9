#pragma once


namespace Model
{

enum class State
{
  None,
  Open,
};


class StateSet
{
public:

  StateSet() : d_states(0) { }

  bool Test(State i_state) const { return (d_states & (int)i_state) != 0; }
  void Add(State i_state) { d_states |= (int)i_state; }
  void Remove(State i_state) { d_states &= ~(int)i_state; }

private:

  int d_states;

};

} // ns Model
