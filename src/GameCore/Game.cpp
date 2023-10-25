#include "Game.h"

//Create the window.
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()), "AmogusRöpö",sf::Style::Default);
	this->window->setFramerateLimit(60);

	if (!image.loadFromFile(ASSETS_PATH + "Sprites/GameIcon/RottaTausta.png"))
	{
		std::cout << "ERROR: Failed to load window icon form a file!\n";
	}

	//this->window->setIcon()'
	this->window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}

//Change the state if needed to.
void Game::init()
{
	Fonts::initFont();
	this->currentState = 1;
	this->initWindow();
	this->states.addState((std::make_unique<MainMenu>(sf::Vector2f((float)sf::VideoMode::getDesktopMode().width, (float)sf::VideoMode::getDesktopMode().height),assetManager)), true);
}


void Game::changeStates()
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
		this->states.addState(std::make_unique<MainMenu>(
			sf::Vector2f((float)sf::VideoMode::getDesktopMode().width, (float)sf::VideoMode::getDesktopMode().height),
			assetManager)
		);
		break;
	case 2:
		this->states.addState(std::make_unique<WorldState>(
			sf::Vector2f((float)sf::VideoMode::getDesktopMode().width, (float)sf::VideoMode::getDesktopMode().height), assetManager));
		break;
	}
	this->currentState = realState;
}

Game::~Game()
{
	delete this->window;
	SoundManager::clear();
	assetManager.clear();

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
	std::cout << "INFO: Window closed.\n";
}
