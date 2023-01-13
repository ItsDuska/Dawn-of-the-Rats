#include "MainMenu.h"

void MainMenu::initBackGround()
{
	std::string backgroundPath = "Kuvat/MainMenuStuff/Taustat/Tausta1.png";
	if (!this->texture.loadFromFile(backgroundPath))
	{
		std::cout << "ERROR! Can't load file";
		return;
	}
	this->BackGround.setTexture(this->texture);
	this->BackGround.setScale((float)this->screenWidht/1000, (float)this->screenHeight/900);

}

MainMenu::MainMenu(int width,int height)
{
	this->screenWidht = width;
	this->screenHeight = height;
	this->initBackGround();
}

void MainMenu::update()
{
}

void MainMenu::render(sf::RenderTarget *window)
{
	window->draw(this->BackGround);
}
