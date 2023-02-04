#include "StateMachine.h"

//Amogus moment
StateMachine::StateMachine()
{
	this->_isAdding = NULL;
	this->_isRemoving = false;
	this->_isReplacing = NULL;
	this->_newState = NULL;
}

//Delete every state.
StateMachine::~StateMachine()
{
	while (!this->_states.empty())
	{
		delete this->_states.top();
		this->_states.pop();
	}
}

//Add a new state.
void StateMachine::addState(State *newState, bool isReplacing)
{
	this->_isAdding = true;
	this->_isReplacing = isReplacing;
	this->_newState = std::move(newState);
}

void StateMachine::removeState()
{
	this->_isRemoving = true;
}

//The actual brain of the States that switches between different states and puts them on different levels on the stack.
void StateMachine::procssStateChanges()
{
	if (this->_isRemoving && !this->_states.empty())
	{
		delete this->_states.top();
		this->_states.pop();
		if (!this->_states.empty())
		{
			this->_states.top()->resume();
		}
		this->_isRemoving = false;
	}
	
	if (this->_isAdding)
	{
		if (!this->_states.empty())
		{
			if (this->_isReplacing)
			{
				delete this->_states.top();
				this->_states.pop();
			}
			else
			{
				this->_states.top()->pause();
			}
		}
		this->_states.push(std::move(this->_newState));
		this->_states.top()->init();
		this->_isAdding = false;
	}
}

//Get the current state.
State& StateMachine::getActiveState()
{
	return *this->_states.top();
}
