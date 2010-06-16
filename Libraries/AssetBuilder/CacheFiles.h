#pragma once

#include "API.h"
#include "Pipeline/Dependencies/Dependencies.h"
#include "Pipeline/Dependencies/Info/FileInfo.h"

#include "Reflect/Serializers.h"
#include "Reflect/Element.h"
#include "Reflect/Archive.h"
#include "Reflect/Registry.h"

namespace CacheFiles
{
  ASSETBUILDER_API void Initialize();
  ASSETBUILDER_API void Cleanup();

  ASSETBUILDER_API const std::string& GetCacheFilesPath();
  ASSETBUILDER_API std::string GetOutputFilename( const Dependencies::DependencyInfoPtr& file );

  ASSETBUILDER_API bool Get( Dependencies::DependencyGraph& depGraph, const Dependencies::V_DependencyInfo& files );
  ASSETBUILDER_API bool Get( Dependencies::DependencyGraph& depGraph, const Dependencies::FileInfoPtr& file );

  ASSETBUILDER_API void Put( Dependencies::DependencyGraph& depGraph, const Dependencies::V_DependencyInfo& files );
  ASSETBUILDER_API void Put( Dependencies::DependencyGraph& depGraph, const Dependencies::FileInfoPtr& file );
}
