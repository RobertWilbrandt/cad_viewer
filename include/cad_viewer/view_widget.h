// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-07-16
 *
 */
//----------------------------------------------------------------------
#ifndef CAD_VIEWER_VIEW_WIDGET_H_INCLUDED
#define CAD_VIEWER_VIEW_WIDGET_H_INCLUDED

#include <Aspect_VKey.hxx>
#include <QOpenGLWidget>
#include <Standard_Handle.hxx>
#include <memory>

class QMouseEvent;

class V3d_View;
class AIS_InteractiveContext;
class AIS_ViewController;

namespace cad_viewer {

class ViewWidget : public QOpenGLWidget
{
  Q_OBJECT
public:
  explicit ViewWidget(const Handle(V3d_View) & view,
                      const Handle(AIS_InteractiveContext) & context,
                      QWidget* parent = nullptr);

  void initializeGL() override;
  void paintGL() override;

  void cleanup();

protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;

private:
  Aspect_VKeyMouse convert(Qt::MouseButtons buttons) const;
  Aspect_VKeyFlags convert(Qt::KeyboardModifiers modifiers) const;

  Handle(V3d_View) m_view;
  Handle(AIS_InteractiveContext) m_context;

  std::shared_ptr<AIS_ViewController> m_view_controller;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_VIEW_WIDGET_H_INCLUDED
