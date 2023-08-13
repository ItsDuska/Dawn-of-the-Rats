#include "MainMenu.h"

void MainMenu::initBackGround()
{
	if (!this->shader.loadFromFile("SourceGame/Shaders/MainMenuShaders/background.vert", "SourceGame/Shaders/MainMenuShaders/background.frag")) {std::cout << "Error while loading shaders!";}
	this->shader.setUniform("u_resolution", this->screenSize);
	this->rats = std::make_unique<AnimationHandler>(&this->rat, 0.1f, sf::Vector2i(32, 32), 18);
	this->rat.setPosition(sf::Vector2f(this->screenSize.x / 2.75f, this->screenSize.y / 3.5f ));
	this->rat.setScale(sf::Vector2f(4, 4));
	this->clock.restart();
	this->background.setSize(this->screenSize);
}

MainMenu::MainMenu(sf::Vector2f screenSize)
{
	this->changeStateTo = 1;
	this->screenSize = screenSize;
	SoundManager::loadSound("Button", "Sounds/ButtonSound.ogg");
	AssetManager::loadTexture("Rat", this->ratPath);
	AssetManager::loadTexture("Logo", "MainMenuStuff/Logo/Logo.png");
	AssetManager::loadTexture("Button", "NewSprites/Button.png");
	this->rat.setTexture(AssetManager::getTexture("Rat"));
	this->logo.setTexture(AssetManager::getTexture("Logo"));
	this->logo.setPosition(sf::Vector2f(this->screenSize.x / 10, 0.05f * this->screenSize.y));
	this->logo.setScale(2, 2);
	this->initBackGround();
	this->exitButton = std::make_unique< ExitButton>(sf::Vector2f(this->screenSize.x / 6, this->screenSize.y / 1.8f), sf::Vector2f(300, 200), sf::Color(200, 200, 200,128), "Quit");
	this->playButton = std::make_unique< PlayButton>(sf::Vector2f(this->screenSize.x / 6, this->screenSize.y / 3.5f), sf::Vector2f(300, 200), sf::Color(200, 200, 200,128), "Play");

	if (!music.openFromFile(ASSETS_PATH + "Audio\\Music\\MainMenu\\Space_Vortex.ogg"))
	{
		std::cout << "\nERROR: CANT PLAY MUSIC!\n";
		return; // error
	}
	this->music.setVolume(10);
	this->music.setLoop(true);
	//this->exitButton = std::make_unique< ExitButton>(sf::Vector2f(300, 600), sf::Vector2f(300, 200), sf::Color(200, 200, 200,128), "Quit");
	//this->playButton = std::make_unique< PlayButton>(sf::Vector2f(300, 300), sf::Vector2f(300, 200), sf::Color(200, 200, 200, 128), "Play");
	this->music.play();

	std::cout << "done";
}

MainMenu::~MainMenu()
{
	this->music.stop();
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
	window->draw(this->logo);
	this->playButton->render(window);
	this->exitButton->render(window);
}

void MainMenu::onResize(sf::Vector2f size)
{
	screenSize = size;
}
