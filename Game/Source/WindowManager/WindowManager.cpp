#include "WindowManager.h"

void WindowManager::changeStates()
{
	int realState = this->states.getActiveState().changeStateTo;
	if (realState == this->currentState) { return; }
	switch (realState)
	{
	default:
		break;
	case 0:
		return;
	case 1:
		this->states.addState((std::make_unique<MainMenu>(sf::Vector2f((float)sf::VideoMode::getDesktopMode().width, (float)sf::VideoMode::getDesktopMode().height))));
	case 2:
		this->states.addState(std::make_unique<ActualGame>(sf::Vector2f((float)sf::VideoMode::getDesktopMode().width, (float)sf::VideoMode::getDesktopMode().height)));
	}
	this->currentState = realState;
}

void WindowManager::init()
{
	Fonts::initFont();
	this->currentState = 1;
	this->initWindow();
	this->states.addState((std::make_unique<MainMenu>(sf::Vector2f((float)sf::VideoMode::getDesktopMode().width, (float)sf::VideoMode::getDesktopMode().height))), true);
}
