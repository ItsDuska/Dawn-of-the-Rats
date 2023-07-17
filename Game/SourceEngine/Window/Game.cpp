#include "Game.h"

//Create the window.
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()), "AmogusRöpö",sf::Style::Default);
	this->window->setFramerateLimit(60);
}

//Change the state if needed to.
void Game::init()
{

}

void Game::changeStates()
{

}

Game::~Game()
{
	delete this->window;
	SoundManager::clear();
	AssetManager::clear();

}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent)) {
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (this->sfEvent.type == sf::Event::Resized)
		{
			sf::Vector2u size = window->getSize();
			this->states.getActiveState().onResize(sf::Vector2f((float) size.x, (float) size.y));
		}
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
	this->window->clear(sf::Color(79,82,107,255));
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
