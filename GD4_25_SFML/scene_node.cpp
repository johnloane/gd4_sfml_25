#include "scene_node.hpp"

SceneNode::SceneNode():m_children(), m_parent(nullptr)
{
}

void SceneNode::AttachChild(Ptr child)
{
	child->m_parent = this;
	//Use emplace_back rather than push_back and understand why
	m_children.emplace_back(std::move(child));
}


SceneNode::Ptr SceneNode::DetachChild(const SceneNode& node)
{
	auto found = std::find_if(m_children.begin(), m_children.end(), [&](Ptr& p) {return p.get() == &node; });
	assert(found != m_children.end());
	
	Ptr result = std::move(*found);
	result->m_parent = nullptr;
	m_children.erase(found);
	return result;
}

void SceneNode::Update(sf::Time dt)
{

}

sf::Vector2f SceneNode::GetWorldPosition() const
{
	return sf::Vector2f();
}

sf::Transform SceneNode::GetWorldTransform() const
{
	return sf::Transform();
}

void SceneNode::UpdateCurrent(sf::Time dt)
{
}

void SceneNode::UpdateChildren(sf::Time dt)
{
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void SceneNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void SceneNode::DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
}

