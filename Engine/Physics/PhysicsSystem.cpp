#include "pch.h"
#include "PhysicsSystem.h"
#include "ContactListener.h"

namespace nc
{
    bool PhysicsSystem::Startup()
    {
        b2Vec2 gravity = { 0,150 };
        m_world = new b2World(gravity);
        m_conactListener = new ContactListener;
        m_world->SetContactListener(m_conactListener);

        return true;
    }

    void PhysicsSystem::Shutdown()
    {
        delete (m_world);
        m_world = { nullptr };
        delete m_conactListener;
        m_conactListener = { nullptr };
    }

    void PhysicsSystem::Update()
    {
        float timeStep = (1.0f / 60.0f);
        m_world->Step(timeStep, 8, 3);
    }

    b2Body* PhysicsSystem::CreateBody(const Vector2& position, const Vector2& size, float density, bool isDynamic)
    {
        b2BodyDef bodyDef;

        bodyDef.type = (isDynamic) ? b2_dynamicBody : b2_staticBody;
        bodyDef.position.Set(position.x, position.y);
        b2Body* body = m_world->CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(size.x, size.y);

        body->CreateFixture(&shape, density);

        return body;
    }

    b2Body* PhysicsSystem::CreateBody(const Vector2& position, float angle, const RigidBodyData& data, GameObject* gameobject)
    {
        b2BodyDef bodyDef;

        bodyDef.type = (data.isDynamic) ? b2_dynamicBody : b2_staticBody;
        bodyDef.position.Set(position.x, position.y);
        bodyDef.angle = nc::DegreeToRadians(angle);
        bodyDef.fixedRotation = data.lockAngle;
        b2Body* body = m_world->CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(data.size.x, data.size.y);

        b2FixtureDef fixtureDef;
        fixtureDef.density = data.density;
        fixtureDef.friction = data.friction;
        fixtureDef.restitution = data.restitution;
        fixtureDef.userData = gameobject;
        fixtureDef.shape = &shape;

        body->CreateFixture(&fixtureDef);

        return body;
    }
}
