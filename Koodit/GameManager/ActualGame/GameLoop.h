#pragma once
#include "../../GameManager/States/State.h"
#include "../../Utils/Animation/AnimationHandler.h"
#include "../../Utils/Assets/AssetManager.h"
#include "../../Player/Player.h"


class ActualGame : public State
{
    Player player;
    void init();
    void update(float dt, State* state);
    void render(sf::RenderTarget *window);

};

