#include "MainMenu.h"

void MainMenu::initBackGround()
{
	this->rats = new AnimationHandler(&this->rat, 0.125f, sf::Vector2i(32, 32), 18);
	this->rat.setPosition(sf::Vector2f(this->screenWidht- (int)this->screenWidht/2,this->screenHeight-(int)this->screenHeight/2));
	this->rat.setScale(sf::Vector2f(4, 4));
	this->backGround.setScale(sf::Vector2f((float)this->screenWidht / 1000, (float)this->screenHeight / 900));
}

void MainMenu::loadSprites(sf::Texture &texture,sf::Sprite &sprite,std::string path)
{
	
	if (!texture.loadFromFile(path))
	{
		std::cout << "ERROR! Can't load file: " << path << "\n ";
		return;
	}
	sprite.setTexture(texture);
}


MainMenu::MainMenu(int width,int height)
{
	this->screenWidht = width;
	this->screenHeight = height;
	this->loadSprites(this->bgTexture, this->backGround, "Kuvat/MainMenuStuff/Taustat/Tausta1.png");
	this->loadSprites(this->ratSheet, this->rat, "Kuvat/MainMenuStuff/Rat/RatSpriteSheet.png");
	this->initBackGround();
	
	this->exitButton = new ExitButton(sf::Vector2f(300, 300), sf::Vector2f(300, 200), sf::Color(147, 112, 219), "Quit");
}

MainMenu::~MainMenu()
{
	//delete this->backgrounds;
	delete this->rats;
	delete this->exitButton;
}

void MainMenu::update()
{
	
	//this->backgrounds->update();
	this->rats->update();
	this->exitButton->checkMousePos(this->mousePos);
}

void MainMenu::render(sf::RenderTarget *window)
{
	this->mousePos = window->mapPixelToCoords(sf::Mouse::getPosition());
	window->draw(this->backGround);
	window->draw(this->rat);
	this->exitButton->render(window);
}
