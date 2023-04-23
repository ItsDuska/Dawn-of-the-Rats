#pragma once


#include "Window/Game.h"


#include "MainMenu/MainMenu.h"
#include "GameManager/GameState/GameLoop.h"



class WindowManager : public Game
{
private:
	void changeStates();

public:
	void init();
};
