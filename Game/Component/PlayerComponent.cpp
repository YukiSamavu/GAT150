#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/AudioComponent.h"
#include "Objects/Scene.h"
#include "Objects/ObjectFactory.h"

namespace nc
{
void PlayerComponent::Create(void* data)
	{
		m_owner = static_cast<GameObject*>(data);
		EventManager::Instance().Subscribe("CollisionEnter", std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1), m_owner);
		EventManager::Instance().Subscribe("CollisionExit", std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1), m_owner);
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
			force.x = -150;
		}

		if (m_owner->m_enigne->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			force.x = 150;
		}

		if (onGround && m_owner->m_enigne->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::PRESSED)
		{
			force.y = -2800;
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			if (audioComponent)
			{
				audioComponent->SetSoundName("jump.wav");
				audioComponent->Play();
			}
		}

		force = nc::Vector2::Rotate(force, nc::DegreeToRadians(m_owner->m_transform.angle));

		PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->ApplyForce(force);

			SpriteComponent* spriteComponent = m_owner->GetComponent<SpriteComponent>();

			Vector2 velocity = component->GetVelocity();
			if (velocity.x >= 0.5f) spriteComponent->Flip(false);
			if (velocity.x <= -0.5f) spriteComponent->Flip(true);
		}

		auto enemyContacts = m_owner->GetContactsWithTag("Enemy");
		if (!enemyContacts.empty()) std::cout << "Enemy Hit\n";
	}

	void PlayerComponent::OnCollisionEnter(const Event& event)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);

		if (gameObject->m_tag == "Enemy")
		{
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			audioComponent->SetSoundName("Death.wav");
			audioComponent->Play();

			m_owner->m_flags[GameObject::eFlags::DESTROY] = true;
		
			Event event;
			event.type = "PlayerDead";
			event.data = &m_score;
			EventManager::Instance().Notify(event);
		}

		if (gameObject->m_tag == "Coin")
		{
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			audioComponent->SetSoundName("Pickup_Coin.wav");
			audioComponent->Play();

			m_score += 10;

			gameObject->m_flags[GameObject::eFlags::DESTROY] = true;

			nc::GameObject* newGameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("ProtoCoin");
			newGameObject->m_transform.position = { nc::random(0, 800), nc::random(0, 450) };
			m_owner->m_scene->AddGameObject(newGameObject);
		}

		std::cout << "collision enter : " << gameObject->m_name << std::endl;
	}
	void PlayerComponent::OnCollisionExit(const Event& event)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);

		std::cout << "collision exit : " << gameObject->m_name << std::endl;
	}
}
