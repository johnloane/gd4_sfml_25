#pragma once
#include <SFML/Graphics.hpp>
#include "resource_identifiers.hpp"
#include "scene_node.hpp"
#include "scene_layers.hpp"
#include "aircraft.hpp"

class World
{
public:
	explicit World(sf::RenderWindow& window);
	void Update(sf::Time dt);
	void Draw();

private:
	void LoadTextures();
	void BuildScene();

private:
	sf::RenderWindow& m_window;
	sf::View m_camera;
	TextureHolder m_textures;
	SceneNode m_scene_graph;
	std::array<SceneNode*, static_cast<int>(SceneLayers::kLayerCount)> m_scene_layers;
	sf::FloatRect m_world_bounds;
	sf::Vector2f m_spawn_position;
	float m_scroll_speed;
	Aircraft* m_player_aircraft;
};




};

