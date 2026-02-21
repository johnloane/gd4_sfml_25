#pragma once
#include "scene_node.hpp"
#include "resource_identifiers.hpp"

class TextNode : public SceneNode
{
public:
	explicit TextNode(const FontHolder& fonts, std::string& text);
	void SetString(const std::string& text);
	//virtual unsigned int GetCategory() const override;

private:
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Text m_text;
};

