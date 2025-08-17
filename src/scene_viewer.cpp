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

#include "cad_viewer/config.h"
#include "cad_viewer/scene.h"

#include <V3d_Viewer.hxx>

namespace cad_viewer {

SceneViewer::SceneViewer(Handle(V3d_Viewer) viewer,
                         Handle(AIS_InteractiveContext) context,
                         Document* document,
                         Config* config,
                         QObject* parent)
  : QObject{parent}
  , m_viewer{std::move(viewer)}
  , m_context{std::move(context)}
{
  switch (config->viewer()->gridType())
  {
    case ViewerConfig::GridTypeRectangular:
      m_viewer->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines);
      break;
    case ViewerConfig::GridTypeCircular:
      m_viewer->ActivateGrid(Aspect_GT_Circular, Aspect_GDM_Lines);
      break;
    default:
      break;
  }

  m_scene = new Scene{document, m_context, this};
  QObject::connect(m_scene, &Scene::viewUpdateRequested, this, &SceneViewer::viewUpdateRequested);

  QObject::connect(
    config->viewer(), &ViewerConfig::gridTypeChanged, this, &SceneViewer::setGridType);

  emit viewUpdateRequested();
}

Scene* SceneViewer::scene() const
{
  return m_scene;
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

} // namespace cad_viewer
