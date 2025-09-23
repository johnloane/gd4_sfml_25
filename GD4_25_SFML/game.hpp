#pragma once
#include <SFML/Graphics.hpp>

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
	sf::Texture m_texture;
	std::unique_ptr<sf::Sprite> m_player;
	
	bool m_is_moving_up = false;
	bool m_is_moving_down = false;
	bool m_is_moving_right = false;
	bool m_is_moving_left = false;
};

