#include "RenderSystem.h"



void RenderSystem::update(Coordinator& entityManager)
{
	for (auto const& entity : this->mEntities)
	{
		auto& transform = entityManager.getComponent<Component::Transform>(entity);
		auto& image = entityManager.getComponent<Component::Image>(entity);
		auto const& texCoord = entityManager.getComponent<Component::TextureCoord>(entity);

		image.sprite.setTextureRect(texCoord.texCoord);

		if (transform.facingLeft)
		{
			if (image.sprite.getScale().x > 0)
			{
				image.sprite.scale(-1.f, 1);
			}
		}
		else {
			if (image.sprite.getScale().x < 0)
			{
				image.sprite.scale(-1.f, 1);
			}
		}

		transform.position = transform.futurePosition;
		image.sprite.setPosition(transform.position);

		//image.sprite.setScale(transfrorm.scale);
		//image.sprite.setRotation(transfrorm.rotation);
	}
}

void RenderSystem::render(Coordinator& entityManager, sf::RenderTarget* window)
{
	for (auto const& entity : this->mEntities)
	{
		window->draw(entityManager.getComponent<Component::Image>(entity).sprite);
	}
}
