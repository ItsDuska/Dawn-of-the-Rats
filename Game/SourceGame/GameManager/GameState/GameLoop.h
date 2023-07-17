#pragma once
#include "System/GameStates/State.h"
#include "Assets/Animation/AnimationHandler.h"
#include "Assets/Textures/AssetManager.h"
#include "../../World/Generation/Chunks/ChunkManager/ChunkManager.h"
#include "System/ThreadPool/ThreadPool.h"
#include "System/ECS/Coordinator/CordinatorOperator/CordinatorOperator.h"
#include "System/ECS/Systems/Systems.h"

#include "Background/Background.h"
#include "Entities/Prefabs/PlayerPrefab/PlayerPrefab.h"
#include <sstream>
#include <chrono>
#include <cmath>



class ActualGame : public State
{
private:
    //Player player;
    sf::View camera;
    ChunkManager chunkManager;
    sf::Vector2f windowSize;
    ThreadPool threadPool;
    Coordinator entityManager;
    std::vector<uint32_t> entities;
    Systems systems;
    //sf::RenderTexture fakeWindow;
    sf::Shader shader;
    sf::Clock clock;
    bool updateText = true;
    std::chrono::microseconds updateTime;
    engine::Text frameTime;
    std::string tempString;

    std::unique_ptr<Background> background;

    sf::RectangleShape pelaajaHitBox;
public:
    void init();
    void update(float dt, State* state);
    void render(sf::RenderTarget *window);
    void onResize(sf::Vector2f size);
    ActualGame(sf::Vector2f windowSize);
    ~ActualGame();
};

