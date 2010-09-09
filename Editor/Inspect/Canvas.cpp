#include "Precompile.h"
#include "Canvas.h"

#include "Editor/Inspect/Widgets/LabelWidget.h"
#include "Editor/Inspect/Widgets/ValueWidget.h"
#include "Editor/Inspect/Widgets/SliderWidget.h"
#include "Editor/Inspect/Widgets/ChoiceWidget.h"
#include "Editor/Inspect/Widgets/CheckBoxWidget.h"
#include "Editor/Inspect/Widgets/ColorPickerWidget.h"
#include "Editor/Inspect/Widgets/ListWidget.h"
#include "Editor/Inspect/Widgets/ButtonWidget.h"
#include "Editor/Inspect/Widgets/FileDialogButtonWidget.h"

using namespace Helium;
using namespace Helium::Editor;

Canvas::Canvas( wxWindow* window )
: m_Window( window )
{
    SetWidgetCreator< LabelWidget, Inspect::Label >();
    SetWidgetCreator< ValueWidget, Inspect::Value >();
    SetWidgetCreator< SliderWidget, Inspect::Slider >();
    SetWidgetCreator< ChoiceWidget, Inspect::Choice >();
    SetWidgetCreator< CheckBoxWidget, Inspect::CheckBox >();
    SetWidgetCreator< ColorPickerWidget, Inspect::ColorPicker >();
    SetWidgetCreator< ListWidget, Inspect::List >();
    SetWidgetCreator< ButtonWidget, Inspect::Button >();
    SetWidgetCreator< FileDialogButtonWidget, Inspect::FileDialogButton >();

    m_Window->Connect( m_Window->GetId(), wxEVT_SHOW, wxShowEventHandler( Canvas::OnShow ), NULL, this );
    m_Window->Connect( m_Window->GetId(), wxEVT_LEFT_DOWN, wxMouseEventHandler( Canvas::OnClick ), NULL, this );
    m_Window->Connect( m_Window->GetId(), wxEVT_MIDDLE_DOWN, wxMouseEventHandler( Canvas::OnClick ), NULL, this );
    m_Window->Connect( m_Window->GetId(), wxEVT_RIGHT_DOWN, wxMouseEventHandler( Canvas::OnClick ), NULL, this );
}

void Canvas::OnShow(wxShowEvent& event)
{
    e_Show.Raise( event.GetShow() );
}

void Canvas::OnClick(wxMouseEvent& event)
{
    m_Window->SetFocus();

    event.Skip();
}

void Canvas::RealizeControl( Inspect::Control* control )
{
    HELIUM_ASSERT( control );

    WidgetCreators::const_iterator found = m_WidgetCreators.find( control->GetType() );
    HELIUM_ASSERT( found != m_WidgetCreators.end() );
    WidgetPtr widget = found->second( control );
    HELIUM_ASSERT( widget );

    // associate the widget with the control
    control->SetWidget( widget );

    // find the window pointer for the parent window
    Inspect::Container* parent = control->GetParent();
    HELIUM_ASSERT( parent );
    Widget* parentWidget = Reflect::AssertCast< Widget >( parent->GetWidget() );
    HELIUM_ASSERT( parentWidget );
    wxWindow* parentWindow = parentWidget->GetWindow();
    HELIUM_ASSERT( parentWindow );

    // this will cause the widget to allocate its corresponding window (since it has the parent pointer)
    widget->Create( parentWindow );
}