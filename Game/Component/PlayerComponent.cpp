#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"

namespace nc
{
void PlayerComponent::Create(void* data)
	{
	}

	void PlayerComponent::Destroy()
	{
	}

	void PlayerComponent::Update()
	{
		//player controller
		if (m_owner->m_enigne->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{
			m_owner->m_transform.angle = m_owner->m_transform.angle - 200.0f * m_owner->m_enigne->GetTime().DeltaTimer();
		}
		if (m_owner->m_enigne->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			m_owner->m_transform.angle = m_owner->m_transform.angle + 200.0f * m_owner->m_enigne->GetTime().DeltaTimer();
		}
		nc::Vector2 force{ 0,0 };
		if (m_owner->m_enigne->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD)
		{
			force = nc::Vector2::forward * 1000.0f;
		}
		if (m_owner->m_enigne->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_S) == nc::InputSystem::eButtonState::HELD)
		{
			force = nc::Vector2::forward * -1000.0f;
		}
		force = nc::Vector2::Rotate(force, nc::DegreeToRadians(m_owner->m_transform.angle));

		PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->SetForce(force);
		}
	}
}
