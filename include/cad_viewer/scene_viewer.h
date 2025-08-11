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

class AIS_InteractiveContext;
class V3d_Viewer;
namespace cad_viewer {
class Config;
class Scene;
} // namespace cad_viewer


namespace cad_viewer {

class SceneViewer : public QObject
{
  Q_OBJECT
public:
  explicit SceneViewer(Handle(V3d_Viewer) viewer,
                       Handle(AIS_InteractiveContext) context,
                       Config* config,
                       QObject* parent = nullptr);

  [[nodiscard]] Scene* scene() const;

signals:
  void viewUpdateRequested();

public slots:
  void setGridType(ViewerConfig::GridType grid_type);

private:
  Handle(V3d_Viewer) m_viewer;
  Handle(AIS_InteractiveContext) m_context;

  Scene* m_scene;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_SCENE_VIEWER_H_INCLUDED
