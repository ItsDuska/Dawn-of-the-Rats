#include "MainMenu.h"

void MainMenu::initBackGround()
{
	if (!this->shader.loadFromFile("Shaders/MainMenuShaders/background.vert", "Shaders/MainMenuShaders/background.frag")) {std::cout << "Error while loading shaders!";}
	this->shader.setUniform("u_resolution", sf::Vector2f(this->screenWidht,this->screenHeight));
	this->rats = new AnimationHandler(&this->rat, 0.1f, sf::Vector2i(32, 32), 18);
	this->rat.setPosition(sf::Vector2f(this->screenWidht- (int)this->screenWidht/2,this->screenHeight-(int)this->screenHeight/2));
	this->rat.setScale(sf::Vector2f(4, 4));
	this->clock.restart();
	this->background.setSize(sf::Vector2f(this->screenWidht, this->screenHeight));
}

MainMenu::MainMenu(int width,int height)
{
	this->screenWidht = width;
	this->screenHeight = height;
	AssetManager::loadTexture("Rat", this->ratPath);
	this->rat.setTexture(AssetManager::getTexture("Rat"));
	this->initBackGround();
	this->exitButton = new ExitButton(sf::Vector2f(300, 600), sf::Vector2f(300, 200), sf::Color(79, 121, 66,128), "Quit");
	this->playButton = new PlayButton(sf::Vector2f(300, 300), sf::Vector2f(300, 200), sf::Color(79, 121, 66,128), "Play");
}

MainMenu::~MainMenu()
{
	delete this->rats;
	delete this->exitButton;
	delete this->playButton;
}

void MainMenu::update(float dt, State* state)
{
	this->shader.setUniform("u_time", this->clock.getElapsedTime().asSeconds());
	this->rats->update(false);
	this->exitButton->checkMousePos(this->mousePos, state);
	this->playButton->checkMousePos(this->mousePos, state);
}

void MainMenu::render(sf::RenderTarget *window)
{
	this->mousePos = window->mapPixelToCoords(sf::Mouse::getPosition());
	window->draw(this->background, &shader);
	window->draw(this->rat);
	this->playButton->render(window);
	this->exitButton->render(window);
}
