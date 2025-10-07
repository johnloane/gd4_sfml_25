#pragma once
#include <SFML/Graphics.hpp>
#include "resource_holder.hpp"
#include "texture_id.hpp"

class Game
{
public:
	Game();
	void Run();

private:
	void ProcessEvents();
	void Update(sf::Time delta_time);
	void Render();
	void HandlePlayerInput(sf::Keyboard::Scancode key, bool is_pressed);

private:
	sf::RenderWindow m_window;
	ResourceHolder<TextureID, sf::Texture> m_textures;
	std::unique_ptr<sf::Sprite> m_player;
	
	bool m_is_moving_up = false;
	bool m_is_moving_down = false;
	bool m_is_moving_right = false;
	bool m_is_moving_left = false;
};

