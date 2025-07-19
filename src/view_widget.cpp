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
#include "cad_viewer/view_widget.h"

#include <Aspect_DisplayConnection.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <QSurfaceFormat>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>

namespace cad_viewer {

ViewWidget::ViewWidget(QWidget* parent)
  : QOpenGLWidget{parent}
{
  Handle(Aspect_DisplayConnection) display_connection = new Aspect_DisplayConnection{};
  Handle(OpenGl_GraphicDriver) graphic_driver = new OpenGl_GraphicDriver{display_connection, false};
  graphic_driver->ChangeOptions().buffersNoSwap      = true;  // QOpenGLWidget handles buffer swap
  graphic_driver->ChangeOptions().buffersOpaqueAlpha = true;  // Don't write to alpha channel
  graphic_driver->ChangeOptions().useSystemBuffer    = false; // Always use offscreen FBO

  m_viewer = new V3d_Viewer{graphic_driver};
  m_view   = m_viewer->CreateView();
  m_view->SetImmediateUpdate(false);

  // Widget setup
  setMouseTracking(true);
  setBackgroundRole(QPalette::NoRole);
  setFocusPolicy(Qt::StrongFocus);
  setUpdatesEnabled(true);
  setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);

  // Set surface format
  QSurfaceFormat format{};
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  format.setProfile(QSurfaceFormat::CompatibilityProfile);
  setFormat(format);
}

} // namespace cad_viewer
