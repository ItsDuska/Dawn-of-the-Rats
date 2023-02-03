#include "Game.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()), "AmogusRöpö");
	this->window->setFramerateLimit(60);
}

void Game::changeStates()
{
	if (this->states.getActiveState().changeStateTo == this->currentState) { return; }
	switch (this->states.getActiveState().changeStateTo)
	{
	default:
		break;
	case 0:
		return;
	case 1:
		this->states.addState((new MainMenu(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)));
	case 2:
		this->states.addState(new ActualGame());
	}
	this->currentState = this->states.getActiveState().changeStateTo;
}

Game::Game()
{
	this->currentState = 1;
	this->initWindow();
	this->states.addState((new MainMenu(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)),true);
}

Game::~Game()
{
	delete this->window;
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent)) {
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}	
}

void Game::update()
{
	sf::Time deltaTime = deltaClock.restart();
	this->updateSFMLEvents();
	this->states.getActiveState().update(deltaTime.asSeconds(),&this->states.getActiveState());
	this->changeStates();
}

void Game::render()
{
	this->window->clear();
	this->states.getActiveState().render(window);
	this->window->display();
}

void Game::run()
{
	//std::chrono::time_point<std::chrono::system_clock> start, end;
	while (this->window->isOpen()) {
		//start = std::chrono::system_clock::now();
		this->states.procssStateChanges();
		this->update();
		this->render();
		if (this->states.getActiveState().exit) { this->window->close(); }
		//end = std::chrono::system_clock::now();
		//std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "[microsecs]" << std::endl;
	}
}
