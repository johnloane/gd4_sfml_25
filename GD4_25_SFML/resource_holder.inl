//TODO ?? can we preinstantiate each type and write as .hpp and .cpp
#pragma once
#include "resource_holder.hpp"
#include <string>
#include <SFML/Graphics/Font.hpp>
#include <iostream>

template<typename Identifier, typename Resource>
void ResourceHolder<Identifier, Resource>::Load(const Identifier id, const std::string& filename)
{
    bool loaded = false;
    std::unique_ptr<Resource> resource(new Resource());
    if constexpr (std::is_same_v<Resource, sf::Font>)
    {
        loaded = resource->openFromFile(filename);
    }
    else
    {
        loaded = resource->loadFromFile(filename);
    }
    if(!loaded)
    {
        throw std::runtime_error("ResourceHolder::Load failed to load " + filename);
    }
    auto inserted = m_resource_map.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

template<typename Identifier, typename Resource>
template<typename Parameter>
void ResourceHolder<Identifier, Resource>::Load(const Identifier id, const std::string& filename, const Parameter& second_param)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename, second_param))
    {
        throw std::runtime_error("ResourceHolder::Load failed to load " + filename);
    }
    auto inserted = m_resource_map.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

template<typename Identifier, typename Resource>
const Resource& ResourceHolder<Identifier, Resource>::Get(Identifier id) const
{
    auto found = m_resource_map.find(id);
    assert(found != m_resource_map.end());
    return *found->second;
}


template<typename Identifier, typename Resource>
Resource& ResourceHolder<Identifier, Resource>::Get(Identifier id)
{
    auto found = m_resource_map.find(id);
    assert(found != m_resource_map.end());
    return *found->second;
}