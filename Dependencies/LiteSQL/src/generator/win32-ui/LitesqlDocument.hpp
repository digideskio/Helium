//////////////////////////////////////////////////////
// SimpleMDIChild.h
//  Declaration of the CLitesqlView and CSimpleMDIChild class

#ifndef LITESQLDOCUMENT_H
#define LITESQLDOCUMENT_H

#include "objectmodel.hpp"

namespace litesql {
  class ObjectModel;
}

class LitesqlDocument 
{
public:
  
  LitesqlDocument(LPCTSTR pszFilename);
  void setModified(bool bModified=true);
  bool isModified();

  const LITESQL_String& getFilename();
  void setFilename(const LITESQL_String& filename);
  litesql::ObjectModel& getModel();

  virtual bool Load(LPCTSTR pszFilename);  
  
  virtual void Save();
  virtual void SaveAs(LPCTSTR pszFilename);
  
private:
  bool m_bModified;
  LITESQL_String m_filename;
  litesql::ObjectModel m_model;
};

#endif  //#ifndef LITESQLDOCUMENT_H
