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
#ifndef CAD_VIEWER_SCENE_VIEWER_H_INCLUDED
#define CAD_VIEWER_SCENE_VIEWER_H_INCLUDED

#include "cad_viewer/viewer_config.h"

#include <QObject>
#include <Standard_Handle.hxx>
#include <memory>
#include <vector>

class QWidget;
class V3d_Viewer;
class AIS_InteractiveContext;

namespace cad_viewer {

class GraphicDriver;
class Scene;
class SceneViewWidget;

class SceneViewer : public QObject
{
  Q_OBJECT
public:
  explicit SceneViewer(GraphicDriver* graphic_driver, QObject* parent = nullptr);

  SceneViewWidget* createView(QWidget* parent = nullptr);

signals:
  void viewUpdateRequested();

public slots:
  void setGridType(ViewerConfig::GridType grid_type);

  void cleanup();

private:
  Handle(V3d_Viewer) m_viewer;
  Handle(AIS_InteractiveContext) m_context;

  std::shared_ptr<Scene> m_scene;
  std::vector<SceneViewWidget*> m_views;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_SCENE_VIEWER_H_INCLUDED
