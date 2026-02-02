#include "projectile.hpp"
#include "data_tables.hpp"
#include "utility.hpp"
#include "emitter_node.hpp"
#include "particletype.hpp"

namespace
{
    const std::vector<ProjectileData> Table = InitializeProjectileData();
}

Projectile::Projectile(ProjectileType type, const TextureHolder& textures) : Entity(1), m_type(type), m_sprite(textures.Get(Table[static_cast<int>(type)].m_texture), Table[static_cast<int>(type)].m_texture_rect)
{
    Utility::CentreOrigin(m_sprite);

    //Add particle system for missiles
    if (IsGuided())
    {
        std::unique_ptr<EmitterNode> smoke(new EmitterNode(ParticleType::kSmoke));
        smoke->setPosition(sf::Vector2f(0.f, GetBoundingRect().size.y / 2.f));
        AttachChild(std::move(smoke));

        std::unique_ptr<EmitterNode> propellant(new EmitterNode(ParticleType::kPropellant));
        propellant->setPosition(sf::Vector2f(0.f, GetBoundingRect().size.y / 2.f));
        AttachChild(std::move(propellant));
    }
}

void Projectile::GuideTowards(sf::Vector2f position)
{
    assert(IsGuided());
    m_target_direction = Utility::Normalise(position - GetWorldPosition());
}

bool Projectile::IsGuided() const
{
    return m_type == ProjectileType::kMissile;
}

unsigned int Projectile::GetCategory() const
{
    if (m_type == ProjectileType::kEnemyBullet)
    {
        return static_cast<int>(ReceiverCategories::kEnemyProjectile);
    }
    else
        return static_cast<int>(ReceiverCategories::kAlliedProjectile);
}

sf::FloatRect Projectile::GetBoundingRect() const
{
    return GetWorldTransform().transformRect(m_sprite.getGlobalBounds());
}

float Projectile::GetMaxSpeed() const
{
    return Table[static_cast<int>(m_type)].m_speed;
}

float Projectile::GetDamage() const
{
    return Table[static_cast<int>(m_type)].m_damage;
}

void Projectile::UpdateCurrent(sf::Time dt, CommandQueue& commands)
{
    if (IsGuided())
    {
        const float approach_rate = 200;
        sf::Vector2f new_velocity = Utility::Normalise(approach_rate * dt.asSeconds() * m_target_direction + GetVelocity());
        new_velocity *= GetMaxSpeed();
        float angle = std::atan2(new_velocity.y, new_velocity.x);
        setRotation(sf::degrees(Utility::ToDegrees(angle) + 90.f));
        SetVelocity(new_velocity);
    }
    Entity::UpdateCurrent(dt, commands);
}

void Projectile::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
