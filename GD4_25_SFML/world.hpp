#pragma once
#include <SFML/Graphics.hpp>
#include "resource_identifiers.hpp"
#include "scene_node.hpp"
#include "scene_layers.hpp"
#include "aircraft.hpp"
#include "command_queue.hpp"
#include "bloom_effect.hpp"
#include "sound_player.hpp"
#include "sprite_node.hpp"

#include <array>
#include "pickup_type.hpp"
#include "network_node.hpp"

class World
{
public:
	explicit World(sf::RenderTarget& output_target, FontHolder& font, SoundPlayer& sounds, bool networked = false);
	void Update(sf::Time dt);
	void Draw();

	sf::FloatRect GetViewBounds() const;
	CommandQueue& GetCommandQueue();

	Aircraft* AddAircraft(uint8_t identifier);
	void RemoveAircraft(uint8_t identifier);
	void SetCurrentBattleFieldPosition(float line_y);
	void SetWorldHeight(float height);

	void AddEnemy(AircraftType type, float relx, float rely);
	void SortEnemies();

	bool HasAlivePlayer() const;
	bool HasPlayerReachedEnd() const;

	void SetWorldScrollCompensation(float compensation);
	Aircraft* GetAircraft(int identifier) const;
	sf::FloatRect GetBattleFieldBounds() const;
	void CreatePickup(sf::Vector2f position, PickupType type);
	bool PollGameAction(GameActions::Action& out);

private:
	void LoadTextures();
	void BuildScene();
	void AdaptPlayerVelocity();
	void AdaptPlayerPosition();

	void SpawnEnemies();
	void AddEnemies();

	void GuideMissiles();

	void HandleCollisions();

	void DestroyEntitiesOutsideView();

	void UpdateSounds();

private:
	struct SpawnPoint
	{
		SpawnPoint(AircraftType type, float x, float y) :m_type(type), m_x(x), m_y(y)
		{

		}
		AircraftType m_type;
		float m_x;
		float m_y;
	};

private:
	sf::RenderTarget& m_target;
	sf::RenderTexture m_scene_texture;
	sf::View m_camera;
	TextureHolder m_textures;
	FontHolder& m_fonts;
	SoundPlayer& m_sounds;
	SceneNode m_scene_graph;
	std::array<SceneNode*, static_cast<int>(SceneLayers::kLayerCount)> m_scene_layers;
	sf::FloatRect m_world_bounds;
	sf::Vector2f m_spawn_position;
	float m_scroll_speed;
	float m_scrollspeed_compensation;

	std::vector<Aircraft*> m_player_aircraft;

	CommandQueue m_command_queue;

	std::vector<SpawnPoint> m_enemy_spawn_points;
	std::vector<Aircraft*> m_active_enemies;

	BloomEffect m_bloom_effect;
	bool m_networked_world;
	NetworkNode* m_network_node;
	SpriteNode* m_finish_sprite;
};

