#include "world.hpp"
#include "sprite_node.hpp"

World::World(sf::RenderWindow& window)
	: m_window(window)
	, m_camera(window.getDefaultView())
	, m_textures()
	, m_scene_graph()
	, m_scene_layers()
	, m_world_bounds(sf::Vector2f(0.f, 0.f), sf::Vector2f(m_camera.getSize().x, 3000.f))
	, m_spawn_position(m_camera.getSize().x / 2.f, m_world_bounds.size.y - m_camera.getSize().y/2.f)
	, m_scroll_speed(-50.f)
	, m_player_aircraft(nullptr)
{
	LoadTextures();
	BuildScene();
	m_camera.setCenter(m_spawn_position);
}

void World::Update(sf::Time dt)
{
	//Scroll the world
	m_camera.move(sf::Vector2f(0, m_scroll_speed * dt.asSeconds()));

	sf::Vector2f position = m_player_aircraft->getPosition();
	sf::Vector2f velocity = m_player_aircraft->GetVelocity();

	//If the player gets close to the boundaries of the world flip their x-velocity
	if (position.x <= 150.f || position.x >= m_world_bounds.size.x - 150.f)
	{
		velocity.x = -velocity.x;
		m_player_aircraft->SetVelocity(velocity);
	}
	m_scene_graph.Update(dt);
}

void World::Draw()
{
	m_window.setView(m_camera);
	m_window.draw(m_scene_graph);
}

void World::LoadTextures()
{
	m_textures.Load(TextureID::kEagle, "Media/Textures/Eagle.png");
	m_textures.Load(TextureID::kRaptor, "Media/Textures/Raptor.png");
	m_textures.Load(TextureID::kLandscape, "Media/Textures/Desert.png");
}

void World::BuildScene()
{
	//Initialise the different layers
	for (int i = 0; i < static_cast<int>(SceneLayers::kLayerCount); i++)
	{
		SceneNode::Ptr layer(new SceneNode());
		m_scene_layers[i] = layer.get();
		m_scene_graph.AttachChild(std::move(layer));
	}

	//Prepare the background
	sf::Texture& texture = m_textures.Get(TextureID::kLandscape);
	sf::IntRect textureRect(m_world_bounds);
	texture.setRepeated(true);

	//Add the background sprite to the world
	std::unique_ptr<SpriteNode> background_sprite(new SpriteNode(texture, textureRect));
	background_sprite->setPosition(sf::Vector2f(0, m_world_bounds.size.y));
	m_scene_layers[static_cast<int>(SceneLayers::kBackground)]->AttachChild(std::move(background_sprite));

	//Homework add the player's aircraft
	//Add two Raptor escort planes that are 50 units behind the plane and 80 units either side of the player's plane


}
