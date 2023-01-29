#include "MainMenu.h"

void MainMenu::initBackGround()
{
	this->rats = new AnimationHandler(&this->rat, 0.1f, sf::Vector2i(32, 32), 18);
	this->rat.setPosition(sf::Vector2f(this->screenWidht- (int)this->screenWidht/2,this->screenHeight-(int)this->screenHeight/2));
	this->rat.setScale(sf::Vector2f(4, 4));
	this->backGround.setScale(sf::Vector2f((float)this->screenWidht / 1000, (float)this->screenHeight / 900));
}

MainMenu::MainMenu(int width,int height)
{
	this->screenWidht = width;
	this->screenHeight = height;
	this->assets.loadTexture("Background", this->backgroundPath);
	this->assets.loadTexture("Rat", this->ratPath);
	this->backGround.setTexture(this->assets.getTexture("Background"));
	this->rat.setTexture(this->assets.getTexture("Rat"));
	this->initBackGround();
	this->exitButton = new ExitButton(sf::Vector2f(300, 300), sf::Vector2f(300, 200), sf::Color(147, 112, 219), "Quit");
	this->playButton = new PlayButton(sf::Vector2f(300, 600), sf::Vector2f(300, 200), sf::Color(147, 112, 219), "Play");
}

MainMenu::~MainMenu()
{
	//delete this->backgrounds;
	delete this->rats;
	delete this->exitButton;
}

void MainMenu::update(float dt, State* state)
{
	
	//this->backgrounds->update();
	this->rats->update(dt);
	this->exitButton->checkMousePos(this->mousePos, state);
	this->playButton->checkMousePos(this->mousePos, state);
}

void MainMenu::render(sf::RenderTarget *window)
{
	this->mousePos = window->mapPixelToCoords(sf::Mouse::getPosition());
	window->draw(this->backGround);
	window->draw(this->rat);
	this->playButton->render(window);
	this->exitButton->render(window);
}
