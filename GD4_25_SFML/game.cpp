#include "game.hpp"
#include "utility.hpp"
#include "constants.hpp"
#include "scene_node.hpp"

Game::Game()
	: m_window(sf::VideoMode({ 640, 480 }), "SFML Refactor"), m_textures(), m_player()
{
	m_textures.Load(TextureID::kEagle, "Media/Textures/Eagle.png");
	m_player = std::make_unique<sf::Sprite>(m_textures.Get(TextureID::kEagle));
	m_player->setPosition({ 100.f, 100.f });
}

void Game::Run()
{
	sf::Clock clock;
	sf::Time time_since_last_update = sf::Time::Zero;
	while (m_window.isOpen())
	{
		time_since_last_update += clock.restart();
		while(time_since_last_update.asSeconds() > kTimePerFrame)
		{
			time_since_last_update -= sf::seconds(kTimePerFrame);
			ProcessEvents();
			Update(sf::seconds(kTimePerFrame));
		}	
		Render();
	}
}

void Game::ProcessEvents()
{
	while (const std::optional event = m_window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			m_window.close();
		}
		else if (const auto* KeyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			HandlePlayerInput(KeyPressed->scancode, true);
		}
		else if (const auto* KeyReleased = event->getIf<sf::Event::KeyReleased>())
		{
			HandlePlayerInput(KeyReleased->scancode, false);
		}
	}
}

void Game::Update(sf::Time delta_time)
{
	sf::Vector2f movement(0.f, 0.f);
	if (m_is_moving_up)
	{
		movement.y -= 1;
	}
	if (m_is_moving_down)
	{
		movement.y += 1;
	}
	if (m_is_moving_left)
	{
		movement.x -= 1;
	}
	if (m_is_moving_right)
	{
		movement.x += 1;
	}
	m_player->move(Utility::Normalise(movement) * kPlayerSpeed * delta_time.asSeconds());

}

sf::Vector2f SceneNode::GetWorldPosition() const
{
	return sf::Vector2f();
}

sf::Transform SceneNode::GetWorldTransform() const
{
	return sf::Transform();
}

void SceneNode::UpdateCurrent(sf::Time dt)
{
}

void SceneNode::UpdateChildren(sf::Time dt)
{
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void SceneNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void SceneNode::DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
}


void Game::Render()
{
	m_window.clear();
	m_window.draw(*m_player);
	m_window.display();
}

void Game::HandlePlayerInput(sf::Keyboard::Scancode key, bool is_pressed)
{
	if (key == sf::Keyboard::Scancode::W)
	{
		m_is_moving_up = is_pressed;
	}
	if (key == sf::Keyboard::Scancode::S)
	{
		m_is_moving_down = is_pressed;
	}
	if (key == sf::Keyboard::Scancode::A)
	{
		m_is_moving_left = is_pressed;
	}
	if (key == sf::Keyboard::Scancode::D)
	{
		m_is_moving_right = is_pressed;
	}
}
