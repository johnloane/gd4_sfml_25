#include "particle_node.hpp"
#include "data_tables.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace
{
	const std::vector<ParticleData> Table = InitializeParticleData();
}

ParticleNode::ParticleNode(ParticleType type, const TextureHolder& textures)
	: SceneNode()
	, m_texture(textures.Get(TextureID::kParticle))
	, m_type(type)
	, m_vertex_array(sf::PrimitiveType::TriangleStrip)
	, m_needs_vertex_update(true)
{
}

void ParticleNode::AddParticle(sf::Vector2f position)
{
	Particle particle;
	particle.m_position = position;
	particle.m_color = Table[static_cast<int>(m_type)].m_color;
	particle.m_lifetime = Table[static_cast<int>(m_type)].m_lifetime;

	m_particles.emplace_back(particle);
}

ParticleType ParticleNode::GetParticleType() const
{
	return m_type;
}

unsigned int ParticleNode::GetCategory() const
{
	return static_cast<int>(ReceiverCategories::kParticleSystem);
}

void ParticleNode::UpdateCurrent(sf::Time dt, CommandQueue& commands)
{
	//Remove expired particles at beginning
	while (!m_particles.empty() && m_particles.front().m_lifetime <= sf::Time::Zero)
	{
		m_particles.pop_front();
	}

	//Decrease the lifetime of live particles
	for (Particle& particle : m_particles)
	{
		particle.m_lifetime -= dt;
	}
	m_needs_vertex_update = true;
}

void ParticleNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_needs_vertex_update)
	{
		ComputeVertices();
		m_needs_vertex_update = false;
	}

	//Apply particle texture
	states.texture = &m_texture;

	//Draw the vertices
	target.draw(m_vertex_array, states);
}

void ParticleNode::AddVertex(float worldX, float worldY, float texCoordX, float texCoordY, const sf::Color& color) const
{
	sf::Vertex vertex;
	vertex.position = sf::Vector2f(worldX, worldY);
	vertex.texCoords = sf::Vector2f(texCoordX, texCoordY);
	vertex.color = color;
	m_vertex_array.append(vertex);
}

void ParticleNode::ComputeVertices() const
{
	//Fade out the particles based on the lifetime value
	//Use alpha transpareny for this
	//The older the particle the more transparent it is
	sf::Vector2f size(m_texture.getSize());
	sf::Vector2f half = size / 2.f;

	m_vertex_array.clear();

	for (const Particle& particle : m_particles)
	{
		sf::Vector2f pos = particle.m_position;
		sf::Color color = particle.m_color;

		float ratio = particle.m_lifetime.asSeconds() / Table[static_cast<int>(m_type)].m_lifetime.asSeconds();
		color.a = static_cast<std::uint8_t>(255 * std::max(ratio, 0.f));

		AddVertex(pos.x - half.x, pos.y - half.y, 0.f, 0.f, color);
		AddVertex(pos.x + half.x, pos.y - half.y, size.x, 0.f, color);
		AddVertex(pos.x + half.x, pos.y + half.y, size.x, size.y, color);
		AddVertex(pos.x - half.x, pos.y + half.y, 0.f, size.y, color);



	}
}
