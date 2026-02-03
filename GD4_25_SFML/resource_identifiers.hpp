#pragma once
#include "texture_id.hpp"
#include "resource_holder.hpp"
#include <SFML/Graphics/Font.hpp>
#include "fontID.hpp"
#include "shader_types.hpp"
#include "sound_effect.hpp"

namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

//template<typename Identifier, typename Resource>

typedef ResourceHolder<TextureID, sf::Texture> TextureHolder;
typedef ResourceHolder<FontID, sf::Font> FontHolder;
typedef ResourceHolder<ShaderTypes, sf::Shader> ShaderHolder;
typedef ResourceHolder<SoundEffect, sf::SoundBuffer> SoundBufferHolder;