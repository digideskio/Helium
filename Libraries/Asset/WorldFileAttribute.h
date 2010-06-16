#pragma once

#include "API.h"

#include "EntityAsset.h"

#include "FileBackedAttribute.h"

namespace Asset
{
  class ASSET_API WorldFileAttribute : public FileBackedAttribute
  {
  private:
    REFLECT_DECLARE_CLASS( WorldFileAttribute, FileBackedAttribute );
    static void EnumerateClass( Reflect::Compositor<WorldFileAttribute>& comp );

  private:
    static const Finder::FinderSpec& s_FileFilter;

  public:

    WorldFileAttribute()
    {
    }

    virtual Attribute::AttributeUsage GetAttributeUsage() const NOC_OVERRIDE;
    virtual Attribute::AttributeCategoryType GetCategoryType() const NOC_OVERRIDE;

    virtual const Finder::FinderSpec* GetFileFilter() const NOC_OVERRIDE;
  };

  typedef Nocturnal::SmartPtr< WorldFileAttribute > WorldFileAttributePtr;
}