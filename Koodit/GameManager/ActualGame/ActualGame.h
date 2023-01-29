#pragma once
#include "../../GameManager/States/State.h"
class ActualGame : public State
{
    void init();
    void update(float dt, State* state);
    void render(sf::RenderTarget *window);
};

