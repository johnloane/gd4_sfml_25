#pragma once
#include "statestack.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include "container.hpp"
#include "button.hpp"
#include "label.hpp"

class SettingsState : public State
{
public:
	SettingsState(StateStack& stack, Context context);
	virtual void Draw() override;
	virtual bool Update(sf::Time dt) override;
	virtual bool HandleEvent(const sf::Event& event) override;

private:
	void UpdateLabels();
	void AddButtonLabel(std::size_t index, std::size_t x, std::size_t y, const std::string& text, Context context);

private:
	sf::Sprite m_background_sprite;
	gui::Container m_gui_container;
	std::array<gui::Button::Ptr, static_cast<int>(Action::kActionCount)*2> m_binding_buttons;
	std::array<gui::Label::Ptr, static_cast<int>(Action::kActionCount)*2> m_binding_labels;
};

