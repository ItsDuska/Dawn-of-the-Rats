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
			animation.animationSpeed = 0.125;
			rigidBody.direction.x = speed.speed;
			animation.currentAnimationRange = animation.AnimationFrames[1];
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			transform.facingLeft = true;
			keyPressed = true;
			animation.animationSpeed = 0.125;
			rigidBody.direction.x = -speed.speed;
			animation.currentAnimationRange = animation.AnimationFrames[1];
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			keyPressed = true;
			transform.onGround = false;
			rigidBody.direction.y = -speed.jumpingSpeed;
			animation.animationSpeed = 0.07f;
			animation.currentAnimationRange = animation.AnimationFrames[2];
		}

		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			keyPressed = true;
			animation.animationSpeed = 0.2f;
			rigidBody.direction = { 0,0 };
			animation.currentAnimationRange = animation.AnimationFrames[4];
		}

		else if (!keyPressed) {
			animation.animationSpeed = 0.1f;
			rigidBody.direction = { 0,0 };
			animation.currentAnimationRange = animation.AnimationFrames[0];
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab))
		{
			if (inventory.clock.getElapsedTime().asSeconds() > inventory.cooldownTime.asSeconds())
			{
				inventory.showInventory = !inventory.showInventory;
				inventory.clock.restart();
			}
		}
		
	}
}
//TO DO: JUMPING