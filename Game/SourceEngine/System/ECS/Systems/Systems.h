#pragma once
#include <memory>
#include "System/ECS/Systems/Render/RenderSystem.h"
#include "System/ECS/Systems/Movement/MovementSystem.h"
#include "System/ECS/Systems/PlayerInput/PlayerInputSystem.h"
#include "System/ECS/Systems/Animation/AnimationSystem.h"
#include "System/ECS/Systems/Inventory/InventorySystem.h"
#include "System/ECS/Systems/Collision/CollisionSystem.h"
#include "System/ECS/Systems/AnimationHandler/AnimationHalderSystem.h"

//All of the Systems that entities use.
struct Systems
{
    std::shared_ptr<RenderSystem> render;
    std::shared_ptr<MovementSystem> movement;
    std::shared_ptr<PlayerInputSystem> playerInput;
    std::shared_ptr<AnimationSystem> animation;
    std::shared_ptr<AnimationHalderSystem> animationHandler;
    std::shared_ptr<InventorySystem> inventory;
    std::shared_ptr<CollisionSystem> collision;
    //physic system
    //collision system
};