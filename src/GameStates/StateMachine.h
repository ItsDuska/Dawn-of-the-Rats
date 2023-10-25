#pragma once
#include <stack>
#include <memory>
#include <iostream>


class State;

//class that handles different states like main menu and the actual game.
class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void addState(std::unique_ptr<State> newState, bool isReplacing = true);
	void removeState();
	void procssStateChanges();
	State &getActiveState();
private:
	std::stack<std::unique_ptr<State>> _states;
	std::unique_ptr<State> _newState;
	bool _isRemoving;
	bool _isAdding;
	bool _isReplacing;
};

