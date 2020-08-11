#pragma once
#include "Core/System.h"
#include "Resources/Resource.h"
#include <map>

namespace nc
{
	class ResourceManager : public System
	{
	public:
		virtual bool Startup() override;
		virtual void Shutdown() override;
		virtual void Update() override;

		void RemoveAll();

		template<typename T>
		T* Get(const std::string& name, void* data = 0)
		{
			T* resource = dynamic_cast<T*>(m_resources[name]);

			if (resource == nullptr)
			{
				resource = new T;
				resource->Create(name, data);

				m_resources[name] = resource;
			}

			return resource;
		}

	protected:
		std::map<std::string, Resource*> m_resources;

	};
}

