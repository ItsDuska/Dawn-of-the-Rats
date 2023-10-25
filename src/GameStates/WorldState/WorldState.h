#pragma once
#include "GameStates/State.h"
#include "ECS/Coordinator/Cordinator.h"
#include "ECS/Systems/Systems.h"
#include "Utils/ThreadPool/ThreadPool.h"
#include <sstream>
#include <chrono>

class AssetManager;
class ChunkManager;
class ThreadPool;
class Background;


namespace engine
{
    class Text;
}


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
    std::unique_ptr<ChunkManager> chunkManager;
    sf::Vector2f windowSize;
    ThreadPool threadPool;
    Coordinator entityManager;
    std::vector<uint32_t> entities;
    Systems systems;
    sf::Shader shader;
    sf::Clock clock;
    engine::Text frameTime;
    AssetManager& assetManager;
    std::unique_ptr<Background> background;
    sf::RectangleShape pelaajaHitBox;
    std::chrono::microseconds updateTime;
    float time;
    bool ErrorRaised = false;
    bool updateText = true;
    std::string tempString;
};

