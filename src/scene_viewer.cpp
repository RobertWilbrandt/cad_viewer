// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-07-28
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/scene_viewer.h"

#include "cad_viewer/graphic_driver.h"
#include "cad_viewer/scene.h"
#include "cad_viewer/scene_view_widget.h"

#include <AIS_InteractiveContext.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <QCoreApplication>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>

namespace cad_viewer {

SceneViewer::SceneViewer(GraphicDriver* graphic_driver, QObject* parent)
  : QObject{parent}
{
  m_viewer = new V3d_Viewer{graphic_driver->driver()};
  m_viewer->SetDefaultBackgroundColor(Quantity_NOC_LIGHTGRAY);
  m_viewer->SetDefaultLights();
  m_viewer->SetLightOn();
  m_viewer->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines);

  m_context = new AIS_InteractiveContext{m_viewer};
  m_scene   = std::make_shared<Scene>(m_context, this);

  QObject::connect(QCoreApplication::instance(),
                   &QCoreApplication::aboutToQuit,
                   this,
                   &SceneViewer::cleanup,
                   Qt::DirectConnection);
}

SceneViewWidget* SceneViewer::createView(QWidget* parent)
{
  Handle(V3d_View) view = m_viewer->CreateView();
  view->SetImmediateUpdate(false);

  auto* view_widget = new SceneViewWidget{view, m_context, parent};
  m_views.push_back(view_widget);
  QObject::connect(
    this, &SceneViewer::viewUpdateRequested, view_widget, &SceneViewWidget::updateView);
  return view_widget;
}

void SceneViewer::setGridType(ViewerConfig::GridType grid_type)
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
  emit viewUpdateRequested();
}

void SceneViewer::cleanup()
{
  // The display connection and graphics driver should live longer than this class in any scenario,
  // so no special action is needed

  // Make sure we don't try to clean up twice
  if (m_viewer.IsNull())
  {
    return;
  }

  // Delete own references
  m_viewer.Nullify();
  m_context.Nullify();
  m_scene.reset();

  for (auto* view : m_views)
  {
    view->setParent(nullptr);
    delete view;
  }
}

} // namespace cad_viewer
