#include "PlayerInputSystem.h"

void PlayerInputSystem::update(Coordinator& entityManager)
{
	for (auto& entity : this->mEntities)
	{
		auto& rigidBody = entityManager.getComponent<Component::RigidBody>(entity);
		auto& transform = entityManager.getComponent<Component::Transform>(entity);
		auto& state = entityManager.getComponent <Component::State>(entity);
		auto& speed = entityManager.getComponent<Component::Speed>(entity);
		auto& inventory = entityManager.getComponent<Component::Inventory>(entity);

		bool keyPressed = false;

		/*
		
		FOR FUTURE OLLI:


		Lol luuseri joudut kirjottaan tän uudelleen
		
		erotat siis animaation päivittämisen omaan classiin

		
		*/



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			state.facingLeft = false;
			keyPressed = true;
			rigidBody.direction.x = speed.speed;
			state.possibleState = Component::EntityStates::WALKING;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			state.facingLeft = true;
			keyPressed = true;
			rigidBody.direction.x = -speed.speed;
			state.possibleState = Component::EntityStates::WALKING;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && state.onGround)
		{
			keyPressed = true;
			state.onGround = false;
			rigidBody.velocity.y = -speed.jumpingSpeed;
			state.possibleState = Component::EntityStates::JUMP;
			state.triggerJump = true;
		}

		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			keyPressed = true;
			rigidBody.direction = { 0,0 };
			state.possibleState = Component::EntityStates::ATTACK;
			//state.onGround = true; // debug röpöö varten
		}

		else if (!keyPressed)
		{
			rigidBody.direction.x = 0;
			state.possibleState = Component::EntityStates::IDLE;
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