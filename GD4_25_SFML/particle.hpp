#pragma once
#include "particletype.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>

struct Particle
{
	ParticleType m_type;
	sf::Vector2f m_position;
	sf::Color m_color;
	sf::Time m_lifetime;
};