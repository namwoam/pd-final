#include <C:/SFML-2.5.1/include/SFML/Graphics.hpp>
#include <map>
#include <string>

#include "Texture_Manager.hpp"

void Texture_Manager::loadTexture(const std::string& name, const std::string& filename)
{
	/* Load the texture */
	sf::Texture tex;
	tex.loadFromFile(filename);

	/* Add it to the list of textures */
	this->textures[name] = tex;

	return;
}

sf::Texture& Texture_Manager::getRef(const std::string& texture)
{
	return this->textures.at(texture);
}