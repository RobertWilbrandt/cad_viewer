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
#ifndef CAD_VIEWER_WIDGET_VIEW_CONTROLLER_H_INCLUDED
#define CAD_VIEWER_WIDGET_VIEW_CONTROLLER_H_INCLUDED

#include <AIS_ViewController.hxx>
#include <Standard_Handle.hxx>

class QWidget;
class AIS_InteractiveContext;
class V3d_View;

namespace cad_viewer {

class WidgetViewController : public AIS_ViewController
{
public:
  explicit WidgetViewController(QWidget* widget);

protected:
  void handleViewRedraw(const Handle(AIS_InteractiveContext) & context,
                        const Handle(V3d_View) & view) override;

private:
  QWidget* m_widget;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_WIDGET_VIEW_CONTROLLER_H_INCLUDED
