#pragma once
#include "System/GameStates/State.h"
#include "Assets/Animation/AnimationHandler.h"
#include "Assets/Textures/AssetManager.h"
#include "../../Player/Player.h"
#include "../../World/Generation/Chunks/ChunkManager/ChunkManager.h"
#include "System/ThreadPool/ThreadPool.h"
#include "../../Entities/ECSManager/CordinatorOperator.h"
#include "../../Entities/Components/Components.h"
#include "../../Entities/Systems/RenderSystem.h"

#include <chrono>



struct Systems
{
    std::shared_ptr<RenderSystem> render;
    //physic system
    //collision system
};

class ActualGame : public State
{
private:
    Player player;
    sf::View camera;
    ChunkManager chunkManager;
    sf::Vector2f windowSize;
    ThreadPool threadPool;
    Coordinator entityManager;
    std::vector<uint32_t> entities;
    Systems systems;
    // class jolla on tallessa jokainen System
public:
    void init();
    void update(float dt, State* state);
    void render(sf::RenderTarget *window);
    ActualGame(sf::Vector2f windowSize);
    ~ActualGame();
};

