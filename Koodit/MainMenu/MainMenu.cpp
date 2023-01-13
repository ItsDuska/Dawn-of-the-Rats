#include "MainMenu.h"

void MainMenu::initBackGround()
{
	std::string backgroundPath = "Kuvat/MainMenuStuff/Taustat/";
	this->animationHandle = new AnimationHandler(backGroundsNames,backgroundPath,0.01f,&this->BackGround,sf::Vector2f((float)this->screenWidht / 1000, (float)this->screenHeight / 900));


}

MainMenu::MainMenu(int width,int height)
{
	this->screenWidht = width;
	this->screenHeight = height;
	this->initBackGround();
}

void MainMenu::update()
{
	animationHandle->update();
}

void MainMenu::render(sf::RenderTarget *window)
{
	window->draw(this->BackGround);
}
