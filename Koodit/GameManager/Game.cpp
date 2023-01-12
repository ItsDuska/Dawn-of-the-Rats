#include "Game.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()), "AmogusR�p�");
}

Game::Game()
{
	this->initWindow();
	auto winSize = this->window->getSize();
	menu = new MainMenu ((int) winSize.x,(int)winSize.y);
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
}

void Game::render()
{
	this->window->clear();
	
	//renderaa kaikki kakat t�ss� v�lis
	this->menu->render(window);


	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen()) {
		this->update();
		this->render();
	}
}