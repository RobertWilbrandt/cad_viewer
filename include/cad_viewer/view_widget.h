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
#include <Graphic3d_Vec2.hxx>
#include <QOpenGLWidget>
#include <Standard_Handle.hxx>
#include <memory>

class QSinglePointEvent;
class AIS_InteractiveContext;
class AIS_AnimationCamera;
class AIS_ViewController;
class AIS_ViewCube;
class OpenGl_Context;
class V3d_View;
namespace cad_viewer {
class Config;
class GraphicDriver;
class SceneViewer;
} // namespace cad_viewer


namespace cad_viewer {

class ViewWidget : public QOpenGLWidget
{
  Q_OBJECT

  Q_PROPERTY(bool initialized READ initialized NOTIFY initializationDone)
public:
  explicit ViewWidget(Config* config, QWidget* parent = nullptr);

  void initializeGL() override;
  void paintGL() override;

  [[nodiscard]] bool initialized() const;

  SceneViewer* viewer() const;

  void cleanup();

signals:
  void initializationDone();

public slots:
  void updateView();

protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;

private:
  Handle(AIS_ViewCube) createDefaultViewCube() const;

  Graphic3d_Vec2i mousePosition(QSinglePointEvent* event) const;
  Aspect_VKeyMouse convert(Qt::MouseButtons buttons) const;
  Aspect_VKeyFlags convert(Qt::KeyboardModifiers modifiers) const;

  std::shared_ptr<GraphicDriver> m_graphic_driver;

  bool m_initialized = false;

  Handle(OpenGl_Context) m_gl_context;
  Handle(V3d_View) m_view;
  Handle(AIS_InteractiveContext) m_context;

  Config* m_config;
  SceneViewer* m_viewer;

  std::shared_ptr<AIS_ViewController> m_view_controller;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_VIEW_WIDGET_H_INCLUDED
