#include "RenderSystem.h"



void RenderSystem::update(Coordinator& entityManager)
{
	for (auto const& entity : this->mEntities)
	{
		auto& transform = entityManager.getComponent<Component::Transform>(entity);
		auto& image = entityManager.getComponent<Component::Image>(entity);
		auto const& texCoord = entityManager.getComponent<Component::TextureCoord>(entity);
		auto& hitbox = entityManager.getComponent<Component::Hitbox>(entity);

		//std::cout << "\n size1 : " << image.sprite.getLocalBounds().width << "x  " << image.sprite.getLocalBounds().height << "y\n";
		image.sprite.setTextureRect(texCoord.texCoord);
		//std::cout << "TEXCOORD :" << texCoord.texCoord.left << "x  " << texCoord.texCoord.top << "y\n";
		//&std::cout << "\n size2 : " << image.sprite.getGlobalBounds().width << "x  " << image.sprite.getGlobalBounds().height << "y\n";
		

		transform.position = transform.futurePosition;
		image.sprite.setPosition(transform.position);

		hitbox.pos = sf::Vector2f(transform.position.x - hitbox.size.x/2, transform.position.y - hitbox.size.y/2);
		
		
		//std::cout << "\n\ntransform.position : " << transform.position.x << "x  " << transform.position.y << "y\n";
		//std::cout << "\n size : " << image.sprite.getGlobalBounds().width << "x  " << image.sprite.getGlobalBounds().height << "y\n";
		//std::cout << "\n\nimage.sprite : " << image.sprite.getGlobalBounds().left << "x  " << image.sprite.getGlobalBounds().top << "y\n";


		//image.sprite.setScale(transfrorm.scale);
		//image.sprite.setRotation(transfrorm.rotation);
	}
}

void RenderSystem::render(Coordinator& entityManager, sf::RenderTarget* window, sf::Shader* shader, sf::Vector2f playerPos)
{
	shader->setUniform("lightPos", playerPos);

	for (auto const& entity : this->mEntities)
	{
		window->draw(entityManager.getComponent<Component::Image>(entity).sprite, shader);
	}
}
