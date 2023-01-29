#pragma once
#include <stack>
#include "State.h"
#include <iostream>

//typedef std::unique_ptr<State> StateRef;

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void addState(State *newState, bool isReplacing = true);
	void removeState();
	void procssStateChanges();
	State &getActiveState();
private:
	std::stack<State*> _states;
	State* _newState;
	bool _isRemoving;
	bool _isAdding;
	bool _isReplacing;
};

