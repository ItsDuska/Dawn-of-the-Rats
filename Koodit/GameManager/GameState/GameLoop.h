#pragma once
#include "../../GameManager/States/State.h"
#include "../../Utils/Animation/AnimationHandler.h"
#include "../../Utils/Assets/AssetManager.h"
#include "../../Player/Player.h"
#include "../../World/Generation/WorldCreator/ChunkManager.h"
#include "../../Utils/ThreadPool/ThreadPool.h"
#include "../../Entities/Coordinator/Cordinator.h"
#include "../../Entities/Coordinator/CordinatorOperator/CordinatorOperator.h"
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

