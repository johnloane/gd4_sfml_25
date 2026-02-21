#pragma once
#include "component.hpp"
#include "resource_identifiers.hpp"
#include "button_type.hpp"
#include "state.hpp"
#include "sound_player.hpp"
#include <functional>

namespace gui
{
	class Button : public Component
	{
	public:
		typedef std::shared_ptr<Button> Ptr;
		typedef std::function<void()> Callback;

	public:
		Button(State::Context context);
		void SetCallback(Callback callback);
		void SetText(const std::string& text);
		void SetToggle(bool flag);

		virtual bool IsSelectable() const override;
		virtual void Select() override;
		virtual void Deselect() override;
		virtual void Activate() override;
		virtual void Deactivate() override;
		virtual void HandleEvent(const sf::Event& event) override;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void ChangeTexture(ButtonType button_type);

	private:
		Callback m_callback;
		sf::Sprite m_sprite;
		sf::Text m_text;
		bool m_is_toggle;

		SoundPlayer& m_sounds;
	};
}

