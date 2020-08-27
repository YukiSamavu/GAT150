#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/AudioComponent.h"

namespace nc
{
void PlayerComponent::Create(void* data)
	{
		m_owner = static_cast<GameObject*>(data);
	}

	void PlayerComponent::Destroy()
	{
	}

	void PlayerComponent::Update()
	{
		auto contatcs = m_owner->GetContactsWithTag("Floor");
		bool onGround = !contatcs.empty();

		//player controller
		nc::Vector2 force{ 0,0 };

		if (m_owner->m_enigne->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{
			force.x = -75;
		}

		if (m_owner->m_enigne->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			force.x = 75;
		}

		if (onGround && m_owner->m_enigne->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::PRESSED)
		{
			force.y = -1350;
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			if (audioComponent)
			{
				audioComponent->Play();
			}
		}

		force = nc::Vector2::Rotate(force, nc::DegreeToRadians(m_owner->m_transform.angle));

		PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->SetForce(force);
		}

		//check collision
		auto coinContatcs = m_owner->GetContactsWithTag("Coin");
		for (auto contact : coinContatcs)
		{
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			if (audioComponent)
			{
				audioComponent->Play();
			}
			contact->m_flags[GameObject::eFlags::DESTROY] = true;
		}
	}
}
