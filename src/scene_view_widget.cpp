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
#include "cad_viewer/scene_view_widget.h"

#include "cad_viewer/view_widget.h"

#include <Aspect_DisplayConnection.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <QOpenGLContext>
#include <QVBoxLayout>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>

namespace cad_viewer {

SceneViewWidget::SceneViewWidget(QWidget* parent)
  : QWidget{parent}
{
  Handle(Aspect_DisplayConnection) display_connection = new Aspect_DisplayConnection{};
  Handle(OpenGl_GraphicDriver) graphic_driver = new OpenGl_GraphicDriver{display_connection, false};
  graphic_driver->ChangeOptions().buffersNoSwap      = true;  // QOpenGLWidget handles buffer swap
  graphic_driver->ChangeOptions().buffersOpaqueAlpha = true;  // Don't write to alpha channel
  graphic_driver->ChangeOptions().useSystemBuffer    = false; // Always use offscreen FBO

  m_viewer = new V3d_Viewer{graphic_driver};
  m_viewer->SetDefaultBackgroundColor(Quantity_NOC_LIGHTGRAY);
  m_viewer->SetDefaultLights();
  m_viewer->SetLightOn();
  m_viewer->ActivateGrid(Aspect_GT_Circular, Aspect_GDM_Lines);

  m_view = m_viewer->CreateView();
  m_view->SetImmediateUpdate(false);

  m_view_widget = new ViewWidget{m_view, nullptr};

  auto* layout = new QVBoxLayout{this};
  layout->addWidget(m_view_widget);
  setLayout(layout);
}

SceneViewWidget::~SceneViewWidget()
{
  m_view_widget->makeCurrent();

  Handle(Aspect_DisplayConnection) display_connection =
    m_viewer->Driver()->GetDisplayConnection(); // Make sure to not destroy connection yet

  m_view_widget->cleanup();
  m_view.Nullify();
  m_viewer.Nullify();

  display_connection.Nullify();

  m_view_widget->doneCurrent();
}

} // namespace cad_viewer
