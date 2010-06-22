#include "Pipeline/Content/Nodes/Geometry/Shader.h"
#include "Pipeline/Content/ContentVisitor.h"

using namespace Reflect;
using namespace Content;
using namespace Component;

REFLECT_DEFINE_CLASS(Shader)

void Shader::EnumerateClass( Reflect::Compositor<Shader>& comp )
{
  Reflect::Field* fieldWrapU = comp.AddField( &Shader::m_WrapU, "m_WrapU" );
  Reflect::Field* fieldWrapV = comp.AddField( &Shader::m_WrapV, "m_WrapV" );
  Reflect::Field* fieldRepeatU = comp.AddField( &Shader::m_RepeatU, "m_RepeatU" );
  Reflect::Field* fieldRepeatV = comp.AddField( &Shader::m_RepeatV, "m_RepeatV" );
  Reflect::Field* fieldBaseColor = comp.AddField( &Shader::m_BaseColor, "m_BaseColor" );
}

void Shader::Host(ContentVisitor* visitor)
{
  visitor->VisitShader(this); 
}