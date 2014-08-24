#pragma once

#include "Game/GameLibrary/Graphics/Camera.h"
#include "Graphics/GraphicsManagerComponent.h"

#define EXAMPLE_GAME_MAX_WORLDS (1)
#define EXAMPLE_GAME_MAX_CAMERAS (4)

#define HELIUM_DEBUG_CAMERA_ENABLED (1)

namespace GameLibrary
{
	class CameraManagerComponentDefinition;
	
	typedef Helium::StrongPtr<CameraManagerComponentDefinition> CameraManagerComponentDefinitionPtr;
	typedef Helium::StrongPtr<const CameraManagerComponentDefinition> ConstCameraManagerComponentDefinitionPtr;
		
	//////////////////////////////////////////////////////////////////////////
	// CameraManagerComponent
	class GAME_LIBRARY_API CameraManagerComponent : public Helium::Component
	{
		HELIUM_DECLARE_COMPONENT( GameLibrary::CameraManagerComponent, Helium::Component );
		static void PopulateMetaType( Helium::Reflect::MetaStruct& comp );
		
		CameraManagerComponent();
		
		void Initialize( const CameraManagerComponentDefinition &definition);

		void Tick();

		bool RegisterNamedCamera(Helium::Name cameraName, CameraComponent *pCameraC);
		bool UnregisterNamedCamera(Helium::Name cameraName, CameraComponent *pCameraC);

		void SetCurrentCameraByName(Helium::Name cameraName);
		void SetCurrentCamera(CameraComponent *pCameraC);

		Helium::Map<Helium::Name, CameraComponent *> m_Cameras;
		Helium::Name m_CurrentCameraName;
		CameraComponentPtr m_CurrentCamera;
		Helium::GraphicsManagerComponentPtr m_GraphicsManager;
		bool m_CameraChanged;

#if HELIUM_DEBUG_CAMERA_ENABLED
		bool m_DebugCameraEnabled;
		Helium::Simd::Vector3 m_DebugCameraPosition;
		float m_DebugCameraYaw;
		float m_DebugCameraPitch;

		void SetDebugCameraEnabled(bool enabled);
		void UpdateDebugCamera();
#endif
	};
	
	class GAME_LIBRARY_API CameraManagerComponentDefinition : public Helium::ComponentDefinitionHelper<CameraManagerComponent, CameraManagerComponentDefinition>
	{
		HELIUM_DECLARE_CLASS( GameLibrary::CameraManagerComponentDefinition, Helium::ComponentDefinition );
		static void PopulateMetaType( Helium::Reflect::MetaStruct& comp );

		CameraManagerComponentDefinition();

		Helium::Name m_DefaultCameraName;
	};

	//////////////////////////////////////////////////////////////////////////
	// CameraManagerTick
	struct GAME_LIBRARY_API CameraManagerTick : public Helium::TaskDefinition
	{
		HELIUM_DECLARE_TASK(CameraManagerTick)

		virtual void DefineContract(Helium::TaskContract &rContract);
	};
}
