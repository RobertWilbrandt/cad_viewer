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

#include "cad_viewer/graphic_driver.h"
#include "cad_viewer/scene.h"
#include "cad_viewer/view_widget.h"
#include "cad_viewer/widget_view_controller.h"

#include <AIS_InteractiveContext.hxx>
#include <AIS_ViewCube.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <QCoreApplication>
#include <QOpenGLContext>
#include <QVBoxLayout>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>

namespace cad_viewer {

SceneViewWidget::SceneViewWidget(GraphicDriver* graphic_driver, QWidget* parent)
  : QWidget{parent}
{
  m_viewer = new V3d_Viewer{graphic_driver->driver()};
  m_viewer->SetDefaultBackgroundColor(Quantity_NOC_LIGHTGRAY);
  m_viewer->SetDefaultLights();
  m_viewer->SetLightOn();
  m_viewer->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines);

  m_context = new AIS_InteractiveContext{m_viewer};
  m_scene   = std::make_shared<Scene>(m_context, this);

  m_view = m_viewer->CreateView();
  m_view->SetImmediateUpdate(false);

  m_view_widget = new ViewWidget{m_view, m_context};
  QObject::connect(this,
                   &SceneViewWidget::updateRequested,
                   m_view_widget,
                   &ViewWidget::updateView,
                   Qt::DirectConnection);

  auto* layout = new QVBoxLayout{this};
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(m_view_widget);
  setLayout(layout);

  m_view_cube = createDefaultViewCube();
  m_context->Display(m_view_cube, 0, 0, false);

  QObject::connect(QCoreApplication::instance(),
                   &QCoreApplication::aboutToQuit,
                   this,
                   &SceneViewWidget::cleanup,
                   Qt::DirectConnection);
}

void SceneViewWidget::setGridType(ViewerConfig::GridType grid_type)
{
  if (m_viewer.IsNull())
  {
    return;
  }

  switch (grid_type)
  {
    case ViewerConfig::GridTypeNone:
      m_viewer->DeactivateGrid();
      break;
    case ViewerConfig::GridTypeRectangular:
      m_viewer->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines);
      break;
    case ViewerConfig::GridTypeCircular:
      m_viewer->ActivateGrid(Aspect_GT_Circular, Aspect_GDM_Lines);
      break;
  }

  m_viewer->Invalidate();
  emit updateRequested();
}

Scene& SceneViewWidget::scene()
{
  return *m_scene;
}

const Scene& SceneViewWidget::scene() const
{
  return *m_scene;
}

void SceneViewWidget::cleanup()
{
  if (!m_view_widget)
  {
    return;
  }
  m_view_widget->makeCurrent();

  Handle(Aspect_DisplayConnection) display_connection =
    m_viewer->Driver()->GetDisplayConnection(); // Make sure to not destroy connection yet

  m_view_widget->cleanup();
  m_view.Nullify();
  m_viewer.Nullify();

  display_connection.Nullify();

  m_view_widget->doneCurrent();

  m_view_widget->setParent(nullptr);
  delete m_view_widget;
  m_view_widget = nullptr;
}

Handle(AIS_ViewCube) SceneViewWidget::createDefaultViewCube() const
{
  Handle(AIS_ViewCube) result = new AIS_ViewCube{};
  result->SetViewAnimation(m_view_widget->cameraAnimation());
  result->SetFixedAnimationLoop(false);
  result->SetAutoStartAnimation(true);
  return result;
}

} // namespace cad_viewer
