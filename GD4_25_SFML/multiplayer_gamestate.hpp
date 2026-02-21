#pragma once
#include "state.hpp"
#include "world.hpp"
#include "player.hpp"
#include "game_server.hpp"
#include "network_protocol.hpp"

class MultiplayerGameState : public State
{
public:
	MultiplayerGameState(StateStack& stack, Context context, bool is_host);
	virtual void Draw();
	virtual bool Update(sf::Time dt);
	virtual bool HandleEvent(const sf::Event& event);
	virtual void OnActivate();
	void OnDestroy();
	void DisableAllRealtimeActions(bool enable);

private:
	void UpdateBroadcastMessage(sf::Time elpased_time);
	void HandlePacket(uint8_t packet_type, sf::Packet& packet);

private:
	typedef std::unique_ptr<Player> PlayerPtr;

private:
	World m_world;
	sf::RenderWindow& m_window;
	TextureHolder& m_texture_holder;

	std::map<uint8_t, PlayerPtr> m_players;
	std::vector<uint8_t> m_local_player_identifiers;
	sf::TcpSocket m_socket;
	bool m_connected;
	std::unique_ptr<GameServer> m_game_server;
	sf::Clock m_tick_clock;

	std::vector<std::string> m_broadcasts;
	sf::Text m_broadcast_text;
	sf::Time m_broadcast_elapsed_time;

	sf::Text m_player_invitation_text;
	sf::Time m_player_invitation_time;

	sf::Text m_failed_connection_text;
	sf::Clock m_failed_connection_clock;

	bool m_active_state;
	bool m_has_focus;
	bool m_host;
	bool m_game_started;
	sf::Time m_client_timeout;
	sf::Time m_time_since_last_packet;
};

