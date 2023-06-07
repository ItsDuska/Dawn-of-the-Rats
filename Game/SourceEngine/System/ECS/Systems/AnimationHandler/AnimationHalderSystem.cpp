#include "AnimationHalderSystem.h"

void AnimationHalderSystem::update(Coordinator& entityManager)
{
	for (auto& entity : this->mEntities)
	{
		auto& state = entityManager.getComponent<Component::State>(entity);

		if (state.currentState == state.possibleState && state.currentState != Component::EntityStates::JUMP)
		{
			continue;
		}

		auto& animation = entityManager.getComponent<Component::Animation>(entity);
		
		if (state.onGround)
		{
			switch (state.possibleState)
			{
			case Component::EntityStates::WALKING:
				state.currentState = state.possibleState;
				animation.currentAnimationRange = animation.AnimationFrames[1];
				animation.animationSpeed = 0.125f;
				break;
			case Component::EntityStates::ATTACK:
				state.currentState = state.possibleState;
				animation.currentAnimationRange = animation.AnimationFrames[4];
				animation.animationSpeed = 0.2f;
				break;
			case Component::EntityStates::IDLE:
				state.currentState = state.possibleState;
				animation.currentAnimationRange = animation.AnimationFrames[0];
				animation.animationSpeed = 0.1f;
				break;
			default:
				break;
			}
		}

		else if (state.possibleState == Component::EntityStates::JUMP && state.triggerJump)
		{
			state.currentState = state.possibleState;
			animation.currentAnimationRange = animation.AnimationFrames[2];
			animation.animationSpeed = 0.1f;
			state.triggerJump = false;
		}

		else if (animation.finishedAnimation && state.currentState == Component::EntityStates::JUMP)
		{
			state.currentState = Component::EntityStates::FALLING;
			animation.currentAnimationRange = animation.AnimationFrames[3];
			animation.animationSpeed = 0.075f;
		}
		
		//std::cout << "\n"<< (int)state.currentState << "\n";
	}

}

