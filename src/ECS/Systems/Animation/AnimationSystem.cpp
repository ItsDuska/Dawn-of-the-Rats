#include "AnimationSystem.h"
#include "ECS/Coordinator/Cordinator.h"

void AnimationSystem::update(Coordinator& entityManager)
{
	for (auto& entity : this->mEntities)
	{
		auto& animation = entityManager.getComponent<Component::Animation>(entity);
		auto& textureCoord = entityManager.getComponent<Component::TextureCoord>(entity);
		const auto& state = entityManager.getComponent<Component::State>(entity);
		animation.finishedAnimation = false;

		if (state.facingLeft)
		{
			if (textureCoord.texCoord.width > 0)
			{
				textureCoord.texCoord.width = -textureCoord.texCoord.width;
			}
			textureCoord.texCoord.left = (animation.lastAnimationFrame + 1) * std::abs(textureCoord.texCoord.width);
		}
		else
		{
			if (textureCoord.texCoord.width < 0)
			{
				textureCoord.texCoord.width = -textureCoord.texCoord.width;
			}
			textureCoord.texCoord.left = animation.lastAnimationFrame * textureCoord.texCoord.width;
		}

		if (animation.currentAnimationRange.y != animation.lastAnimationFrameCheck) // resets animation progress when animation is changed
		{
			animation.lastAnimationFrameCheck = animation.currentAnimationRange.y;
			animation.totalProgress = animation.currentAnimationRange.x;
		}


		animation.totalProgress += animation.animationSpeed;

		if (animation.totalProgress >= animation.currentAnimationRange.y)
		{
			animation.totalProgress = animation.currentAnimationRange.x;
			animation.finishedAnimation = true;
		}


		if (animation.lastAnimationFrame == (int)animation.totalProgress)
		{
			continue;
		}

		animation.lastAnimationFrame = (int)animation.totalProgress;
		//textureCoord.texCoord.left =  animation.lastAnimationFrame * textureCoord.texCoord.width;
	}
}
