#include "PostEffect.hpp"
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "SFML/Graphics/Vertex.hpp"

PostEffect::~PostEffect() = default;

bool PostEffect::IsSupported()
{
    return sf::Shader::isAvailable();
}

void PostEffect::ApplyShader(const sf::Shader& shader, sf::RenderTarget& output)
{
    sf::Vector2f output_size = static_cast<sf::Vector2f>(output.getSize());
    sf::VertexArray vertices(sf::PrimitiveType::TriangleStrip, 4);
    vertices[0] = sf::Vertex({0.f, 0.f}, sf::Color::White, {0.f, 1.f});
    vertices[1] = sf::Vertex({ output_size.x, 0 }, sf::Color::White, {1, 1});
    vertices[2] = sf::Vertex({ 0, output_size.y }, sf::Color::White, {0, 0});
    vertices[3] = sf::Vertex(sf::Vector2f(output_size), sf::Color::White, {1, 0});

    sf::RenderStates states;
    states.shader = &shader;
    states.blendMode = sf::BlendNone;

    output.draw(vertices, states);

}
