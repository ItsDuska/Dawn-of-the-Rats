#include "WorldState.h"
#include "Assets/Animation/AnimationHandler.h"
#include "Assets/Textures/AssetManager.h"
#include "World/Chunks/ChunkManager/ChunkManager.h"
#include "ECS/Coordinator/CordinatorOperator/CordinatorOperator.h"
#include "ECS/Prefabs/PlayerPrefab/PlayerPrefab.h"
#include "Assets/Background/Background.h"
#include <cmath>

void WorldState::onResize(sf::Vector2f size)
{
	this->windowSize = size;
}

const bool WorldState::getErrorRaised()
{
	return ErrorRaised;
}

void WorldState::cleanup()
{
}

void WorldState::initShader()
{
	if (!shader.loadFromFile("src\\Assets\\Shaders\\Darkness\\Darkness.vert", "src\\Assets\\Shaders\\Darkness\\Darkness.frag"))
	{
		ErrorRaised = true;
		std::cout << "ERROR: Failed to load shaders from a file!\n";
	}
	std::cout << "INFO: Loaded Shaders!\n";
}

//funny init function that represents a constructor.
void WorldState::init()
{
	this->changeStateTo = 2;
	//entity hämmeli
	this->entities.resize(MAX_ENTITIES);
	this->entityManager.init();
	this->background = std::make_unique<Background>("Background\\Lush", windowSize, assetManager);
	assetManager.loadTexture("Shocked", "NewSprites\\SHOCKED.png");
	
	EntityHelper::initComponents(this->entityManager);
	EntityHelper::initSystem(this->entityManager, this->systems);
	PlayerPreFab::createPlayer(this->entityManager, this->entities[0],assetManager);
	PlayerPreFab::createPlayerWeapon(this->entityManager, this->entities[1],assetManager);
	EntityHelper::createEntity(&this->entityManager, this->entities,assetManager);

	this->systems.inventory->init(assetManager);
	this->systems.inventory->addNewItem(this->entityManager, assetManager);

	this->frameTime.setText(50,"", sf::Vector2f(0,0));
	auto& amog = this->entityManager.getComponent < Component::Hitbox>(this->entities[0]);
	sf::Vector2f tempPos = this->entityManager.getComponent<Component::Transform>(this->entities[0]).position;
	auto tempPlayer = this->entityManager.getComponent <Component::Image>(this->entities[0]).sprite.getGlobalBounds();

	this->pelaajaHitBox.setFillColor(sf::Color(0, 0, 255, 128));
	this->pelaajaHitBox.setOutlineColor(sf::Color::White);
	this->pelaajaHitBox.setOutlineThickness(1);
	this->pelaajaHitBox.setPosition(amog.pos);
	this->pelaajaHitBox.setSize(amog.size);

	initShader();
	std::cout << "BUILD: Loaded cave world.\n";
}

//update function for the game loop.
void WorldState::update(float dt, State* state)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	shader.setUniform("time", dt);

	sf::Vector2f tempPos = this->entityManager.getComponent<Component::Transform>(this->entities[0]).position;
	bool facingLeft = this->entityManager.getComponent<Component::State>(this->entities[0]).facingLeft;
	this->entityManager.getComponent<Component::State>(this->entities[1]).facingLeft = facingLeft;
	this->camera.setCenter(sf::Vector2f((int)tempPos.x,tempPos.y));

	this->chunkManager->update(&this->camera, this->entityManager.getComponent<Component::Transform>(this->entities[0]).futurePosition);
	background->update(tempPos,
		this->entityManager.getComponent<Component::RigidBody>(this->entities[0]).velocity.x);

	////////
	this->systems.playerInput->update(this->entityManager);
	this->systems.movement->update(this->entityManager);
	this->systems.follow->update(this->entityManager, dt);
	this->systems.collision->update(this->entityManager, this->chunkManager->getLoadedChunks(), this->chunkManager->settings, this->chunkManager->chunkCords);
	this->systems.animationHandler->update(this->entityManager);
	this->systems.animation->update(this->entityManager);
	this->systems.render->update(this->entityManager);
	this->systems.inventory->update(this->entityManager);

	this->pelaajaHitBox.setPosition(this->entityManager.getComponent<Component::Hitbox>(this->entities[0]).pos);
	////////

	end = std::chrono::system_clock::now();

	if (this->updateText)
	{
		this->updateTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	}

	this->time += 0.1f;

	if (this->time > 300.f)
	{
		this->time = 0.f;
	}

}

//rendering function for the game loop.s
void WorldState::render(sf::RenderTarget* window)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	sf::Vector2f playerPos = this->entityManager.getComponent<Component::Transform>(this->entities[0]).position;
	//World stuff rendering

	this->background->render(*window, &shader, sf::Vector2f(windowSize.x / 2, windowSize.y / 2));

	window->setView(this->camera);
	this->chunkManager->render(*window, &shader, playerPos); 
	this->systems.render->render(this->entityManager, window, &shader, playerPos);

	//window->draw(this->pelaajaHitBox);
	//this->systems.collision->render(window);

	//Piirrä tän jälkeen GUI asiat.
	window->setView(window->getDefaultView());
	this->systems.inventory->render(this->entityManager, window);
	
	end = std::chrono::system_clock::now();
	std::ostringstream oss;

	if (this->updateText)
	{
		oss << "Game logic: " << this->updateTime.count() << " microseconds\n"
			<< "Rendering logic: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds";
		this->tempString = oss.str();
		this->frameTime.changeString(this->tempString);
	}

	this->updateText = !this->updateText;
	window->draw(this->frameTime.getText());
}

WorldState::WorldState(sf::Vector2f windowSize,AssetManager &assetManager)
	 : chunkManager(std::make_unique<ChunkManager>(windowSize, 6967, 0.45f, threadPool, assetManager)), assetManager(assetManager)
{
	this->windowSize = windowSize;
	this->updateTime = std::chrono::microseconds(0);
	this->camera.reset(sf::FloatRect(sf::Vector2f(0,0), windowSize / 2.f));
	this->time = 0.f;
}

WorldState::~WorldState()
{
	
}
