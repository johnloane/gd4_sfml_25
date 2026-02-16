#pragma once
#include <map>
#include <vector>
#include <SFML/Window/Keyboard.hpp>
#include "Action.hpp"

class KeyBinding
{
public:
	explicit KeyBinding(int control_preconfiguration);

	void AssignKey(Action action, sf::Keyboard::Scancode key);
	sf::Keyboard::Scancode GetAssignedKey(Action action) const;

	bool CheckAction(sf::Keyboard::Scancode key, Action& out) const;
	std::vector<Action>	GetRealtimeActions() const;

private:
	std::map<sf::Keyboard::Scancode, Action>	m_key_map;
};

bool IsRealtimeAction(Action action);

