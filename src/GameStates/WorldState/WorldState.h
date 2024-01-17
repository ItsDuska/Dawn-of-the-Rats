#pragma once
#include "GameStates/State.h"
#include "Assets/Animation/AnimationHandler.h"
#include "Assets/Textures/AssetManager.h"
#include "World/Chunks/ChunkManager/ChunkManager.h"
#include "Utils/ThreadPool/ThreadPool.h"
#include "ECS/Coordinator/CordinatorOperator/CordinatorOperator.h"
#include "ECS/Systems/Systems.h"
#include "ECS/Prefabs/PlayerPrefab/PlayerPrefab.h"
#include "Assets/Background/Background.h"
#include <sstream>
#include <chrono>
#include <cmath>


class WorldState : public State
{
public:
    WorldState(sf::Vector2f windowSize, AssetManager &assetManager);
    ~WorldState();
    void init();
    void update(float dt, State* state);
    void render(sf::RenderTarget* window);
    void onResize(sf::Vector2f size);
    const bool getErrorRaised();
    void cleanup();
private:
    void initShader();

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
    float time;
    AssetManager& assetManager;
    std::unique_ptr<Background> background;
    sf::RectangleShape pelaajaHitBox;
    bool ErrorRaised = false;
};

