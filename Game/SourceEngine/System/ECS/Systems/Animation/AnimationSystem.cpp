#include "AnimationSystem.h"

void AnimationSystem::update(Coordinator& entityManager)
{
	for (auto& entity : this->mEntities)
	{
		auto& animation = entityManager.getComponent <Component::Animation>(entity);
		auto& textureCoord = entityManager.getComponent <Component::TextureCoord>(entity);


		if (animation.currentAnimationRange.y != animation.lastAnimationFrameCheck)
		{
			animation.lastAnimationFrameCheck = animation.currentAnimationRange.y;
			animation.totalProgress = animation.currentAnimationRange.x;
		}


		animation.totalProgress += animation.animationSpeed;

		if (animation.totalProgress >= animation.currentAnimationRange.y)
		{
			animation.totalProgress = animation.currentAnimationRange.x;
		}

		if (animation.lastAnimationFrame == (int)animation.totalProgress)
		{
			continue;
		}

		animation.lastAnimationFrame = (int)animation.totalProgress;
		textureCoord.texCoord.left = animation.lastAnimationFrame * textureCoord.texCoord.width;
	}
}
