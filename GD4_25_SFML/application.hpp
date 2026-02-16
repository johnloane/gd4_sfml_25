#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "player.hpp"
#include "resource_holder.hpp"
#include "resource_identifiers.hpp"
#include "statestack.hpp"
#include "music_player.hpp"
#include "sound_player.hpp"
#include "key_binding.hpp"

class Application
{
public:
	Application();
	void Run();

private:
	void ProcessInput();
	void Update(sf::Time dt);
	void Render();
	void RegisterStates();

private:
	sf::RenderWindow m_window;

	TextureHolder m_textures;
	FontHolder m_fonts;

	StateStack m_stack;

	MusicPlayer m_music;
	SoundPlayer m_sound;

	KeyBinding m_key_binding_1;
	KeyBinding m_key_binding_2;
};

