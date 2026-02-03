#include "pause_state.hpp"
#include "utility.hpp"

PauseState::PauseState(StateStack& stack, Context context) : State(stack, context), m_paused_text(context.fonts->Get(FontID::kMain)), m_instruction_text(context.fonts->Get(FontID::kMain))
{
    sf::Vector2f view_size = context.window->getView().getSize();

    m_paused_text.setString("Game Paused");
    m_paused_text.setCharacterSize(70);
    Utility::CentreOrigin(m_paused_text);
    m_paused_text.setPosition(sf::Vector2f(0.5f * view_size.x, 0.4f * view_size.y));

    m_instruction_text.setString("Press backspace to return to the main menu, esc to return to the game");
    Utility::CentreOrigin(m_instruction_text);
    m_instruction_text.setPosition(sf::Vector2f(0.5f * view_size.x, 0.6f * view_size.y));
    GetContext().music->SetPaused(true);
}

PauseState::~PauseState()
{
    GetContext().music->SetPaused(false);
}

void PauseState::Draw()
{
    sf::RenderWindow& window = *GetContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(m_paused_text);
    window.draw(m_instruction_text);
}

bool PauseState::Update(sf::Time dt)
{
    return false;
}

bool PauseState::HandleEvent(const sf::Event& event)
{
    const auto* key_pressed = event.getIf<sf::Event::KeyPressed>();
    if (!key_pressed)
    {
        return false;
    }
    if (key_pressed->scancode == sf::Keyboard::Scancode::Escape)
    {
        RequestStackPop();
    }
    if (key_pressed->scancode == sf::Keyboard::Scancode::Backspace)
    {
        RequestStackClear();
        RequestStackPush(StateID::kMenu);
    }
    return false;
}
