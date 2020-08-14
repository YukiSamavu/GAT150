#pragma once
#include "Components/Component.h"

namespace nc
{
	class PlayerComponent : public Component
	{
	public:
		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual void Update() override;
	};
}