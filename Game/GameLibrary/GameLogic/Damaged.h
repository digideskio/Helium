#pragma once

#include "Reflect/MetaStruct.h"
#include "Engine/Asset.h"
#include "Framework/ComponentDefinition.h"
#include "Foundation/DynamicArray.h"
#include "Framework/TaskScheduler.h"
#include "Framework/Entity.h"
#include "Components/TransformComponent.h"
#include "Bullet/BulletBodyComponent.h"

#include "MathSimd/Vector2.h"

namespace GameLibrary
{
	class DamagedComponentDefinition;

	typedef Helium::StrongPtr<DamagedComponentDefinition> DamagedComponentDefinitionPtr;	
	typedef Helium::StrongPtr<const DamagedComponentDefinition> ConstDamagedComponentDefinitionPtr;

	struct GAME_LIBRARY_API DamagedComponent : public Helium::Component
	{
		HELIUM_DECLARE_COMPONENT( GameLibrary::DamagedComponent, Helium::Component );
		static void PopulateMetaType( Helium::Reflect::MetaStruct& comp );

		void Initialize( float damageAmount );

		float m_DamageAmount;
	};
}
