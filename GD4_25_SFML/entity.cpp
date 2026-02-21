#include "Entity.hpp"
#include "command_queue.hpp"

Entity::Entity(int hitpoints) :m_hitpoints(hitpoints)
{
}

void Entity::SetVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}

void Entity::SetVelocity(float vx, float vy)
{
	m_velocity.x = vx;
	m_velocity.y = vy;
}

sf::Vector2f Entity::GetVelocity() const
{
	return m_velocity;
}

void Entity::Accelerate(sf::Vector2f velocity)
{
	m_velocity += velocity;
}

void Entity::Accelerate(float vx, float vy)
{
	m_velocity.x += vx;
	m_velocity.y += vy;
}

int Entity::GetHitPoints() const
{
	return m_hitpoints;
}

void Entity::SetHitpoints(int points)
{
	//assert(points > 0);
	m_hitpoints = points;
}

void Entity::Repair(int points)
{
	assert(points >= 0);
	m_hitpoints += points;
}

void Entity::Damage(int points)
{
	assert(points > 0);
	m_hitpoints -= points;
}

void Entity::Destroy()
{
	m_hitpoints = 0;
}

bool Entity::IsDestroyed() const
{
	return m_hitpoints <= 0;
}

void Entity::UpdateCurrent(sf::Time dt, CommandQueue& commands)
{
	move(m_velocity * dt.asSeconds());
}

void Entity::Remove()
{
	Destroy();
}