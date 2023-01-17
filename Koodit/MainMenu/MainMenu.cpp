#include "MainMenu.h"

void MainMenu::initBackGround()
{
	this->backgrounds = new AnimationHandler(backGroundsNames, "Kuvat/MainMenuStuff/Taustat/",0.01f,&this->backGround,sf::Vector2f((float)this->screenWidht / 1000, (float)this->screenHeight / 900));
	this->rats = new AnimationHandler(this->initRat(), "Kuvat/MainMenuStuff/Rat/", .25, &this->rat, sf::Vector2f(-1,-1));
	this->rat.setPosition(sf::Vector2f(this->screenWidht- (int)this->screenWidht/10,this->screenHeight-(int)this->screenHeight/10));
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
	
	this->exitButton = new ExitButton(sf::Vector2f(300, 300), sf::Vector2f(300, 200), sf::Color(147, 112, 219), "Quit");
}

MainMenu::~MainMenu()
{
	delete this->backgrounds;
	delete this->rats;
	delete this->exitButton;
}

void MainMenu::update()
{
	
	this->backgrounds->update();
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
