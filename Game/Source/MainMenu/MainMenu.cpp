#include "MainMenu.h"

void MainMenu::initBackGround()
{
	if (!this->shader.loadFromFile("Source/Shaders/MainMenuShaders/background.vert", "Source/Shaders/MainMenuShaders/background.frag")) {std::cout << "Error while loading shaders!";}
	this->shader.setUniform("u_resolution", this->screenSize);
	this->rats = std::make_unique<AnimationHandler>(&this->rat, 0.1f, sf::Vector2i(32, 32), 18);
	this->rat.setPosition(sf::Vector2f(this->screenSize.x - this->screenSize.x / 2.0f, this->screenSize.y - this->screenSize.y / 2.0f ));
	this->rat.setScale(sf::Vector2f(4, 4));
	this->clock.restart();
	this->background.setSize(this->screenSize);
}

MainMenu::MainMenu(sf::Vector2f screenSize)
{
	this->changeStateTo = 1;
	this->screenSize = screenSize;
	SoundManager::loadSound("Button", "Sounds/ButtonSound.wav");
	AssetManager::loadTexture("Rat", this->ratPath);
	this->rat.setTexture(AssetManager::getTexture("Rat"));
	this->initBackGround();
	this->exitButton = std::make_unique< ExitButton>(sf::Vector2f(300, 600), sf::Vector2f(300, 200), sf::Color(79, 121, 66,128), "Quit");
	this->playButton = std::make_unique< PlayButton>(sf::Vector2f(300, 300), sf::Vector2f(300, 200), sf::Color(79, 121, 66,128), "Play");
	std::cout << "done";
}

MainMenu::~MainMenu()
{
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
