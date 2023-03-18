#include "RenderSystem.h"


void RenderSystem::update(Coordinator& entityManager)
{
	for (auto const& entity : this->mEntities)
	{
		auto const& transfrorm = entityManager.getComponent<component::Transform>(entity);
		auto& image = entityManager.getComponent<component::Image>(entity);

		image.sprite.setPosition(transfrorm.position);
	}
}

void RenderSystem::render(Coordinator& entityManager, sf::RenderTarget* window)
{
	for (auto const& entity : this->mEntities)
	{
		window->draw(entityManager.getComponent<component::Image>(entity).sprite);
	}
}
