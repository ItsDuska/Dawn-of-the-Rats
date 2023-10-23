#pragma once
#include <memory>
#include "ECS/Systems/Render/RenderSystem.h"
#include "ECS/Systems/Movement/MovementSystem.h"
#include "ECS/Systems/PlayerInput/PlayerInputSystem.h"
#include "ECS/Systems/Animation/AnimationSystem.h"
#include "ECS/Systems/Inventory/InventorySystem.h"
#include "ECS/Systems/Collision/CollisionSystem.h"
#include "ECS/Systems/AnimationHandler/AnimationHalderSystem.h"
#include "ECS/Systems/Follow/FollowSystem.h"

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
    std::shared_ptr<FollowSystem> follow;
    //physic system
    //collision system
};