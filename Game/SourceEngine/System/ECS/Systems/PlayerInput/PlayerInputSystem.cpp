#include "PlayerInputSystem.h"

void PlayerInputSystem::update(Coordinator& entityManager)
{
	for (auto& entity : this->mEntities)
	{
		auto& rigidBody = entityManager.getComponent<Component::RigidBody>(entity);
		auto& transform = entityManager.getComponent<Component::Transform>(entity);
		auto& animation = entityManager.getComponent <Component::Animation>(entity);
		auto& speed = entityManager.getComponent<Component::Speed>(entity);
		auto& inventory = entityManager.getComponent<Component::Inventory>(entity);

		bool keyPressed = false;

		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			transform.facingLeft = false;
			keyPressed = true;
			rigidBody.direction.x = speed.speed;

			if (animation.currentAnimation != Component::AnimationStates::FALLING)
			{
				animation.animationSpeed = 0.125;
				animation.currentAnimationRange = animation.AnimationFrames[1];
				animation.currentAnimation = Component::AnimationStates::WALKING_RIGHT;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			transform.facingLeft = true;
			keyPressed = true;
			rigidBody.direction.x = -speed.speed;
			
			if (animation.currentAnimation != Component::AnimationStates::FALLING)
			{
				animation.animationSpeed = 0.125;
				animation.currentAnimationRange = animation.AnimationFrames[1];
				animation.currentAnimation = Component::AnimationStates::WALKING_LEFT;
			}

			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && transform.onGround)
		{
			keyPressed = true;
			transform.onGround = false;
			rigidBody.velocity.y = -speed.jumpingSpeed;
			if (animation.currentAnimation != Component::AnimationStates::FALLING)
			{
				animation.animationSpeed = 0.07f;
				animation.currentAnimationRange = animation.AnimationFrames[2];
				animation.currentAnimation = Component::AnimationStates::JUMP;
			}
		}

		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			keyPressed = true;
			animation.animationSpeed = 0.2f;
			rigidBody.direction = { 0,0 };
			transform.onGround = true;
			animation.currentAnimationRange = animation.AnimationFrames[4];
			animation.currentAnimation = Component::AnimationStates::ATTACK;
		}

		else if (!keyPressed && transform.onGround) {
			animation.animationSpeed = 0.1f;
			rigidBody.direction = { 0,0 };

			if (animation.currentAnimation != Component::AnimationStates::FALLING)
			{
				animation.currentAnimationRange = animation.AnimationFrames[0];
				animation.currentAnimation = Component::AnimationStates::IDLE;
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab))
		{
			if (inventory.clock.getElapsedTime().asSeconds() > inventory.cooldownTime.asSeconds())
			{
				inventory.showInventory = !inventory.showInventory;
				inventory.clock.restart();
			}
		}
		
		if (animation.currentAnimation == Component::AnimationStates::JUMP && animation.lastAnimationFrame == animation.currentAnimationRange.y)
		{
			animation.animationSpeed = 0.1f;
			animation.currentAnimationRange = animation.AnimationFrames[3];
			animation.currentAnimation = Component::AnimationStates::FALLING;

		}
	}
}
//TO DO: JUMPING