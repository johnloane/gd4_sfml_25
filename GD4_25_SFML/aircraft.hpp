#pragma once
#include "entity.hpp"
#include "aircraft_type.hpp"
#include "resource_identifiers.hpp"

class Aircraft : public Entity
{
public:
	Aircraft(AircraftType type, const TextureHolder& textures);

private:
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	AircraftType m_type;
	sf::Sprite m_sprite;
};

