#include "Utility.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

namespace
{
    std::default_random_engine CreateRandomEngine()
    {
        auto seed = static_cast<unsigned long>(std::time(nullptr));
        return std::default_random_engine(seed);
    }
    auto RandomEngine = CreateRandomEngine();
}

sf::Vector2f Utility::Normalise(const sf::Vector2f& source)
{
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
    {
        return sf::Vector2f(source.x / length, source.y / length);
    }
    else
    {
        return source;
    }
    return sf::Vector2f();
}

void Utility::CentreOrigin(sf::Sprite& sprite)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(sf::Vector2f(std::floor(bounds.position.x + bounds.size.x / 2.f), std::floor(bounds.position.y + bounds.size.y / 2.f)));
}

void Utility::CentreOrigin(sf::Text& text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(std::floor(bounds.position.x + bounds.size.x / 2.f), std::floor(bounds.position.y + bounds.size.y / 2.f)));
}

void Utility::CentreOrigin(Animation& animation)
{
    sf::FloatRect bounds = animation.GetLocalBounds();
    animation.setOrigin(sf::Vector2f(std::floor(bounds.position.x + bounds.size.x / 2.f), std::floor(bounds.position.y + bounds.size.y / 2.f)));
}

std::string Utility::toString(sf::Keyboard::Scancode key)
{
    return sf::Keyboard::getDescription(key);
}

double Utility::toRadians(double degrees)
{
    return (degrees * M_PI)/180;
}

double Utility::ToDegrees(double angle)
{
    return angle*(180/M_PI);
}

int Utility::RandomInt(int exclusive_max)
{
    std::uniform_int_distribution<> distr(0, exclusive_max - 1);
    return distr(RandomEngine);
}

int Utility::Length(sf::Vector2f vector)
{
    return sqrtf(powf(vector.x, 2) + powf(vector.y, 2));
}
