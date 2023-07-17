#include "Background.h"

Background::Background(std::string filePath, sf::Vector2f windowSize)
{
	std::filesystem::path path = std::filesystem::current_path().parent_path() / "Assets\\Sprites" / filePath;
	initBackground(path, windowSize);
}

void Background::render(sf::RenderTarget& window)
{
	for (const auto& image : backgrounds)
	{
		window.draw(image->first);
		window.draw(image->second);
	}
}

void Background::update(sf::Vector2f playerPosition, float velocity)
{
	if (velocity == 0.f)
	{
		return;
	}

	for (int i = 0; i < imageCount; i++)
	{
		float value = -(velocity * 0.2f * (i + 1));
		backgrounds[i]->first.move(value, 0);
		backgrounds[i]->second.move(value, 0);

		//liikutaan oikealle (pelaaja) eli sitten tausta on vasemmalle
		if (velocity > 0)
		{
			if (backgrounds[i]->first.getGlobalBounds().left < -windowSize.x)
			{
				backgrounds[i]->first.move(windowSize.x * 2, 0);
			}

			if (backgrounds[i]->second.getGlobalBounds().left < -windowSize.x)
			{
				backgrounds[i]->second.move(windowSize.x * 2, 0);
			}
		}
		else // vasemmalle (pelaaja) | tausta liikkuu oikealle
		{
			if (backgrounds[i]->first.getGlobalBounds().left > windowSize.x)
			{
				backgrounds[i]->first.move(-windowSize.x * 2, 0);
			}

			if (backgrounds[i]->second.getGlobalBounds().left > windowSize.x)
			{
				backgrounds[i]->second.move(-windowSize.x * 2, 0);
			}
		}
	}
}

void Background::initBackground(std::filesystem::path path, sf::Vector2f windowSize)
{ 
	std::vector<std::string> fileNames;

	for (const auto& imagePath : std::filesystem::recursive_directory_iterator(path))
	{
		std::string name = imagePath.path().filename().string();

		AssetManager::loadTexture(name, imagePath.path().string(), true);
		fileNames.push_back(name);
		std::cout << imagePath.path().filename() << std::endl;
		imageCount++;
	}

	this->windowSize = windowSize;
	sf::Vector2u tempSize = AssetManager::getTexture(fileNames[0]).getSize();
	imageSize = { (float)tempSize.x, (float)tempSize.y };
	backgrounds.resize(imageCount);

	for (int i = 0; i < imageCount; i++)
	{
		backgrounds[i] = std::make_unique<BackgroundLayer>();
		auto& texture = AssetManager::getTexture(fileNames[imageCount - 1 - i]);
		backgrounds[i]->first.setTexture(texture);
		backgrounds[i]->second.setTexture(texture);
		backgrounds[i]->first.setScale(windowSize.x / imageSize.x, windowSize.y / imageSize.y);
		backgrounds[i]->second.setScale(windowSize.x / imageSize.x, windowSize.y / imageSize.y);
		backgrounds[i]->first.setPosition(0, 0);
		backgrounds[i]->second.setPosition(windowSize.x, 0);
	}
}
