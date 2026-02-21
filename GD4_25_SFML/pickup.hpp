#pragma once
#include "entity.hpp"
#include "pickup_type.hpp"
#include "resource_identifiers.hpp"
#include "aircraft.hpp"

class Pickup : public Entity
{
public:
	Pickup(PickupType type, const TextureHolder& textures);
	virtual unsigned int GetCategory() const override;
	void Apply(Aircraft& player) const;
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual sf::FloatRect GetBoundingRect() const;

private:
	PickupType m_type;
	sf::Sprite m_sprite;
};

