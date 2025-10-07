#include "texture_holder.hpp"

void TextureHolder::Load(const TextureID id, const std::string& filename)
{
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    if (!texture->loadFromFile(filename))
    {
        throw std::runtime_error("TextureHolder::Load failed to load " + filename);
    }
    auto inserted = m_texture_map.insert(std::make_pair(id, std::move(texture)));
    assert(inserted.second);
}

sf::Texture& TextureHolder::Get(TextureID id)
{
    auto found = m_texture_map.find(id);
    assert(found != m_texture_map.end());
    return *found->second;
}

const sf::Texture& TextureHolder::Get(TextureID id) const
{
    auto found = m_texture_map.find(id);
    assert(found != m_texture_map.end());
    return *found->second;
}
