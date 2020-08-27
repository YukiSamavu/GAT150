#pragma once
#include "Object.h"
#include "Core/Factory.h"
#include "Core/Singleton.h"

namespace nc
{
	class ObjectFactoryImpl : public Factory<Object, std::string>
	{
	public:
		void Initialize();
	};

	class ObjectFactory : public Singleton<ObjectFactoryImpl>
	{
	private:
		ObjectFactory() {}
	};
}