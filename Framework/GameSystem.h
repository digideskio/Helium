#pragma once

#include "Framework/System.h"
#include "Framework/SystemDefinition.h"
#include "Framework/TaskScheduler.h"

#define NO_GFX (1)

namespace Helium
{
	class AssetType;

	class CommandLineInitialization;
	class MemoryHeapPreInitialization;
	class AssetLoaderInitialization;
	class ConfigInitialization;
	class WindowManagerInitialization;
	class RendererInitialization;
	class SceneDefinition;
	class Window;
	class World;

	/// Base interface for game application systems.
	class HELIUM_FRAMEWORK_API GameSystem : public System
	{
	public:
		/// @name Construction/Destruction
		//@{
		GameSystem();
		virtual ~GameSystem();
		//@}

		/// @name Initialization
		//@{
		virtual bool Initialize(
			CommandLineInitialization& rCommandLineInitialization, 
			MemoryHeapPreInitialization& rMemoryHeapPreInitialization,
			AssetLoaderInitialization& rAssetLoaderInitialization, 
			ConfigInitialization& rConfigInitialization,
			WindowManagerInitialization& rWindowManagerInitialization,
			RendererInitialization& rRendererInitialization,
			AssetPath &rSystemDefinitionPath);
		virtual void Shutdown();
		
		World *LoadScene( Helium::SceneDefinition *spSceneDefinition );
		//@}

		/// @name Application Loop
		//@{
		virtual int32_t Run();
		//@}

		/// @name Static Initialization
		//@{
		static GameSystem* CreateStaticInstance();
		//@}

		virtual void StopRunning();

	protected:
		/// AssetLoader initialization interface.
		AssetLoaderInitialization*   m_pAssetLoaderInitialization;
		RendererInitialization*      m_pRendererInitialization;
		SystemDefinitionPtr          m_spSystemDefinition;
		AssetAwareThreadSynchronizer m_AssetSyncUtility;
		TaskSchedule                 m_Schedule;
		bool                         m_bStopRunning;
	};
}
