#include "GameLoop.h"
//funny init function that represents a constructor.
void ActualGame::init()
{
	this->changeStateTo = 2;
	AssetManager::loadTexture("Blocks", "NewSprites/GrassyBlock.png");
	AssetManager::loadTexture("Shocked", "NewSprites/SHOCKED.jpg");
	//entity hämmeli
	this->entities.resize(MAX_ENTITIES);
	this->entityManager.init();
	
	EntityHelper::initComponents(this->entityManager);
	EntityHelper::initSystem(this->entityManager, this->systems);
	PlayerPreFab::createPlayer(this->entityManager, this->entities[0]);
	EntityHelper::createEntity(&this->entityManager, this->entities);
	this->systems.inventory->addNewItem(this->entityManager);
}

//update function for the game loop.
void ActualGame::update(float dt, State* state)
{
	//std::chrono::time_point<std::chrono::system_clock> start, end;
	//start = std::chrono::system_clock::now();

	
	this->camera.setCenter(this->entityManager.getComponent<Component::Transform>(this->entities[0]).position);
	this->chunkManager.update(&this->camera, this->entityManager.getComponent<Component::Transform>(this->entities[0]).position);

	////////
	this->systems.playerInput->update(this->entityManager);
	this->systems.movement->update(this->entityManager);
	this->systems.animation->update(this->entityManager);
	this->systems.render->update(this->entityManager);
	this->systems.inventory->update(this->entityManager);
	////////

	//end = std::chrono::system_clock::now();
	//std::cout << "Update logic = " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;

	//this->player.update();
}

//rendering function for the game loop.
void ActualGame::render(sf::RenderTarget* window)
{
	//std::chrono::time_point<std::chrono::system_clock> start, end;
	//start = std::chrono::system_clock::now();
	//World stuff rendering

	
	this->fakeWindow.clear();


	fakeWindow.setView(this->camera);
	this->chunkManager.render(&fakeWindow);
	this->systems.render->render(this->entityManager,&fakeWindow);
	//this->player.render(window);

	//Piirrä tän jälkeen GUI asiat.
	fakeWindow.setView(fakeWindow.getDefaultView());
	//this->player.renderInventory(window);
	this->systems.inventory->render(this->entityManager, window);
	//end = std::chrono::system_clock::now();
	//std::cout << "Rendering logic = " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;
	this->fakeWindow.display();
	sf::Sprite newWindow(fakeWindow.getTexture());

	auto radius = 2000 + std::sin((float)this->clock.getElapsedTime().asSeconds()+100);
	this->shader.setUniform("pos", sf::Vector2f(this->camera.getCenter().x + (rand() % 200), this->camera.getCenter().y + (rand() % 145)));
	this->shader.setUniform("storm_inner_radius", radius / 3);
	this->shader.setUniform("storm_total_radius", radius);
	
	window->draw(newWindow, &shader);
}

ActualGame::ActualGame(sf::Vector2f windowSize)
	:chunkManager(windowSize, 47786, 0.45f, &threadPool)
{
	this->windowSize = windowSize;
	fakeWindow.create(windowSize.x,windowSize.y);
	if (!this->shader.loadFromFile("SourceGame/Shaders/Darkness/Darkness.vert",sf::Shader::Vertex))
	{ std::cout << "Error while loading shaders!"; }
	this->clock.restart();
	//this->shader.setUniform("u_resolution", this->windowSize);
	

	this->camera.reset(sf::FloatRect(sf::Vector2f(0,0), windowSize+windowSize));
	
}

ActualGame::~ActualGame()
{
	
}
