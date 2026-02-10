#pragma once
#include <SFML/System/Vector2.hpp>
const unsigned short SERVER_PORT = 50000; //Greater than 49151, in dynamic port range
namespace Server
{
	enum class PacketType
	{
		kBroadcastMessage, //Takes a std::string and sends it to all clients, they show on their screens for a number of seconds
		kInitialState, //takes two float values, the world height, and the initial scrolling in the world, then sf::Int32 with the number of aircraft, then for each aircraft its identifier, position, health and missiles
		kPlayerEvent, //This takes two sf::Int32 variables, the aircraft identifier and the action identifier from action.hpp, this is used to tell that a particular plane has triggered some action
		kPlayerRealtimeChange, //Same as playerevent for real time actions
		kPlayerConnect, //The same as SpawnSelf but indicates that an aircraft from a different client is connecting
		kPlayerDisconnect, //Takes sf::Int32 aircraft identifier that is disconnecting
		kAcceptCoopPartner, //This says we are free to spawn another local plane. It takes sf::Int32 and two float values with the id of the hot seat multiplayer and its position
		kSpawnEnemy, //Takes one sf::Int32 with the type of Aircraft defined in AircraftType.hpp and two floats as to where to spawn the enemy
		kSpawnPickup, //Similar to kSpawnEnemy. sf::Int32 for pickup type in PickupType.hpp and two floats for position
		kSpawnSelf, //This takes an sf::Int32 for the aircraft identifier and two float values for the initial position. 
		kUpdateClientState, //This takes one float with the current scrolling of the world in the server, and then a sf::Int32 for the number of aircraft. For each aircraft, it packs one sf::Int32 value with the identifier, two floats for position, health, and ammo. Think about enemies. If we don't send anything they will be locally tracked
		kMissionSuccess // This has no arguments. It just informs the client that the game is over and the client can show the appropriate state
	};
}

namespace Client
{
	enum class PacketType
	{
		kPlayerEvent, // Two sf::Int32, aircraft identifer and event. It is used to request the server to trigger an event on the aircraft
		kPlayerRealtimeChange, // The same kPlayerEvent, additionally takes a boolean for real time action
		kRequestCoopPartner, //No parameters. It is sent when the user presses Return to request a local partner. The server will AcceptCoopPartner 
		kStateUpdate, //sf::Int32 with number of local aircraft, for each aircraft send sf::Int32 identifier, two floats for position, health and ammo 
		kGameEvent, //This is for explosions
		kQuit
	};
}

namespace GameActions
{
	enum Type
	{
		kEnemyExplode
	};

	struct Action
	{
		Action() = default;
		Action(Type type, sf::Vector2f position) :type(type), position(position)
		{

		}

		Type type;
		sf::Vector2f position;
	};
}

