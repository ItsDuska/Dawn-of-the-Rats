#include "Game.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()), "AmogusRöpö");
}

Game::Game()
{
	this->initWindow();
	auto winSize = this->window->getSize();
	menu = new MainMenu ( winSize.x,winSize.y);

	/*
	["Tausta1.png", "Tausta2.png", "Tausta3.png",
                        "Tausta3.png", "Tausta4.png", "Tausta5.png"]
	
	*/

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
	
	//renderaa kaikki kakat tässä välis
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
