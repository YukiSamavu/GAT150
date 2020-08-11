#include "pch.h"
#include "PhysicsComponent.h"
#include "Objects/GameObject.h"

namespace nc
{
	void PhysicsComponent::Create(void* data)
	{
	}

	void PhysicsComponent::Destroy()
	{
	}

	void PhysicsComponent::Update()
	{
		m_velocity = m_velocity + m_force; //*timer.DeltaTimer();
		m_velocity = m_velocity * m_drag;
		m_owner->m_transform.position = m_owner->m_transform.position + m_velocity; //*timer.DeltaTimer();
	}
}
