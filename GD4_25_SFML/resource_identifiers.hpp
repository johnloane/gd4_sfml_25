#pragma once
#include "texture_id.hpp"
#include "resource_holder.hpp"

namespace sf
{
	class Texture;
}

//template<typename Identifier, typename Resource>

typedef ResourceHolder<TextureID, sf::Texture> TextureHolder;
