#pragma once
#include "Core/System.h"
#include "box2d/box2d.h"

namespace nc
{
	class PhysicsSystem : public System
	{
	public:
		struct RigidBodyData
		{
			Vector2 size;
			float density{ 0 };
			float friction{ 1 };
			float restitution{ 0 };
			bool lockAngle{ false };
			bool isDynamic{ false };
		};

	public:
		virtual bool Startup() override;
		virtual void Shutdown() override;

		virtual void Update() override;

		b2Body* CreateBody(const Vector2& position, const Vector2& size, float density, bool isDynamic = true);
		b2Body* CreateBody(const Vector2& position, float angle, const RigidBodyData& data, class GameObject* gameobject = nullptr);

	protected:
		b2World* m_world{ nullptr };
		class ContactListener* m_conactListener{ nullptr };
	};
}