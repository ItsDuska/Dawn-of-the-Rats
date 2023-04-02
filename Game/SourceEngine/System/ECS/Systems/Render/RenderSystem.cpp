#include "RenderSystem.h"



void RenderSystem::update(Coordinator& entityManager)
{
	for (auto const& entity : this->mEntities)
	{
		auto const& transfrorm = entityManager.getComponent<Transform>(entity);
		auto& image = entityManager.getComponent<Image>(entity);

		image.sprite.setPosition(transfrorm.position);
		image.sprite.setScale(transfrorm.scale);
		image.sprite.setRotation(transfrorm.rotation);
	}
}

void RenderSystem::render(Coordinator& entityManager, sf::RenderTarget* window)
{
	for (auto const& entity : this->mEntities)
	{
		window->draw(entityManager.getComponent<Image>(entity).sprite);
	}
}
