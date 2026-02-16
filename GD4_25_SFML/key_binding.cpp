#include "key_binding.hpp"
#include <string>
#include <algorithm>

KeyBinding::KeyBinding(int control_preconfiguration)
	: m_key_map()
{
	// Set initial key bindings for player 1
	if (control_preconfiguration == 1)
	{
		m_key_map[sf::Keyboard::Scancode::Left] = Action::kMoveLeft;
		m_key_map[sf::Keyboard::Scancode::Right] = Action::kMoveRight;
		m_key_map[sf::Keyboard::Scancode::Up] = Action::kMoveUp;
		m_key_map[sf::Keyboard::Scancode::Down] = Action::kMoveDown;
		m_key_map[sf::Keyboard::Scancode::Space] = Action::kBulletFire;
		m_key_map[sf::Keyboard::Scancode::M] = Action::kMissileFire;
	}
	else if (control_preconfiguration == 2)
	{
		// Player 2
		m_key_map[sf::Keyboard::Scancode::A] = Action::kMoveLeft;
		m_key_map[sf::Keyboard::Scancode::D] = Action::kMoveRight;
		m_key_map[sf::Keyboard::Scancode::W] = Action::kMoveUp;
		m_key_map[sf::Keyboard::Scancode::S] = Action::kMoveDown;
		m_key_map[sf::Keyboard::Scancode::F] = Action::kBulletFire;
		m_key_map[sf::Keyboard::Scancode::R] = Action::kMissileFire;
	}
}

void KeyBinding::AssignKey(Action action, sf::Keyboard::Scancode key)
{
	// Remove all keys that already map to action
	for (auto itr = m_key_map.begin(); itr != m_key_map.end(); )
	{
		if (itr->second == action)
			m_key_map.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	m_key_map[key] = action;
}

sf::Keyboard::Scancode KeyBinding::GetAssignedKey(Action action) const
{
	for (auto pair : m_key_map)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Scancode::Unknown;
}

bool KeyBinding::CheckAction(sf::Keyboard::Scancode key, Action& out) const
{
	auto found = m_key_map.find(key);
	if (found == m_key_map.end())
	{
		return false;
	}
	else
	{
		out = found->second;
		return true;
	}
}

std::vector<Action> KeyBinding::GetRealtimeActions() const
{
	// Return all realtime actions that are currently active.
	std::vector<Action> actions;

	for (auto pair : m_key_map)
	{
		// If key is pressed and an action is a realtime action, store it
		if (sf::Keyboard::isKeyPressed(pair.first) && IsRealtimeAction(pair.second))
			actions.push_back(pair.second);
	}

	return actions;
}

bool IsRealtimeAction(Action action)
{
	switch (action)
	{
	case Action::kMoveLeft:
	case Action::kMoveRight:
	case Action::kMoveDown:
	case Action::kMoveUp:
	case Action::kBulletFire:
		return true;

	default:
		return false;
	}
}