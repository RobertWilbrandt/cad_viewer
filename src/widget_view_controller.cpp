// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-07-20
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/widget_view_controller.h"

#include <AIS_InteractiveContext.hxx>
#include <QWidget>

namespace cad_viewer {

WidgetViewController::WidgetViewController(QWidget* widget)
  : m_widget{widget}
{
  SetRotationMode(AIS_RotationMode_CameraAt);
}

void WidgetViewController::handleViewRedraw(const Handle(AIS_InteractiveContext) & context,
                                            const Handle(V3d_View) & view)
{
  AIS_ViewController::handleViewRedraw(context, view);
  if (myToAskNextFrame)
  {
    m_widget->update();
  }
}

void WidgetViewController::OnSelectionChanged(const Handle(AIS_InteractiveContext) & context,
                                              const Handle(V3d_View) & view)
{
}

} // namespace cad_viewer
