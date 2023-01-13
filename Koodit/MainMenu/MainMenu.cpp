#include "MainMenu.h"

void MainMenu::initBackGround()
{
	this->backgrounds = new AnimationHandler(backGroundsNames, "Kuvat/MainMenuStuff/Taustat/",0.01f,&this->backGround,sf::Vector2f((float)this->screenWidht / 1000, (float)this->screenHeight / 900));
	this->rats = new AnimationHandler(this->initRat(), "Kuvat/MainMenuStuff/Rat/", .25, &this->rat, sf::Vector2f(-1,-1));
	this->rat.setPosition(sf::Vector2f(this->screenWidht-this->screenWidht/10,this->screenHeight-this->screenHeight/10));
}

std::vector<std::string> MainMenu::initRat()
{

	std::vector<std::string> ratNames;
	for (int i = 1; i < 46; i++) {
		std::string name = "rat-spinning" + std::to_string(i);
		ratNames.push_back(name.append(".png"));
	}
	return ratNames;
}

MainMenu::MainMenu(int width,int height)
{
	this->screenWidht = width;
	this->screenHeight = height;
	this->initBackGround();
}

void MainMenu::update()
{
	this->backgrounds->update();
	this->rats->update();
}

void MainMenu::render(sf::RenderTarget *window)
{
	window->draw(this->backGround);
	window->draw(this->rat);
}
