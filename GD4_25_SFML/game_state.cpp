#include "game_state.hpp"
#include "mission_status.hpp"

GameState::GameState(StateStack& stack, Context context) : State(stack, context), m_world(*context.window, *context.fonts, *context.sound, false), m_player(nullptr, 1, context.keys1)
{
	m_world.AddAircraft(1);
	m_player.SetMissionStatus(MissionStatus::kMissionRunning);
	context.music->Play(MusicThemes::kMissionTheme);
}

void GameState::Draw()
{
	m_world.Draw();
}

bool GameState::Update(sf::Time dt)
{
	m_world.Update(dt);

	if (!m_world.HasAlivePlayer())
	{
		m_player.SetMissionStatus(MissionStatus::kMissionFailure);
		RequestStackPush(StateID::kGameOver);
	}
	else if (m_world.HasPlayerReachedEnd())
	{
		m_player.SetMissionStatus(MissionStatus::kMissionSuccess);
		RequestStackPush(StateID::kMissionSuccess);
	}

	CommandQueue& commands = m_world.GetCommandQueue();
	m_player.HandleRealTimeInput(commands);
	return true;
}

bool GameState::HandleEvent(const sf::Event& event)
{
	CommandQueue& commands = m_world.GetCommandQueue();
	m_player.HandleEvent(event, commands);

	//Escape should bring up the pause menu
	const auto* keypress = event.getIf<sf::Event::KeyPressed>();
	if(keypress && keypress->scancode == sf::Keyboard::Scancode::Escape)
	{
		RequestStackPush(StateID::kPause);
	}
	return true;
}


