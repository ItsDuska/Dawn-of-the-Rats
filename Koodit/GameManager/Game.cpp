#include "Game.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()), "AmogusRöpö");
	this->window->setFramerateLimit(60);
}

Game::Game()
{
	this->initWindow();
	auto winSize = this->window->getSize();
	menu = new MainMenu ( winSize.x,winSize.y);
}

Game::~Game()
{
	delete this->menu;
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
	this->updateSFMLEvents();
	this->menu->update();
}

void Game::render()
{
	this->window->clear();
	this->menu->render(window);
	this->window->display();
}

void Game::run()
{
	//std::chrono::time_point<std::chrono::system_clock> start, end;
	while (this->window->isOpen()) {
		//start = std::chrono::system_clock::now();
		this->update();
		this->render();
		//end = std::chrono::system_clock::now();
		//std::chrono::duration<double, std::milli> elapsed = end - start;
		//std::cout << "Elapsed Time: " << elapsed.count() << "ms" << std::endl;
	}
}
