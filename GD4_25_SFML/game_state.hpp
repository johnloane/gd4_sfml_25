#pragma once
#include "State.hpp"
#include "world.hpp"

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);
	virtual bool Update(sf::Time delta_time) override;
	virtual void Draw() override;
	virtual bool HandleEvent(const sf::Event& event) override;

private:
	World m_world;
	Player m_player;
};

