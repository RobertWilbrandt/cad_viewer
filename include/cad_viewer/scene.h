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
#ifndef CAD_VIEWER_SCENE_H_INCLUDED
#define CAD_VIEWER_SCENE_H_INCLUDED

#include <QObject>
#include <Standard_Handle.hxx>
#include <vector>

class AIS_InteractiveContext;
class AIS_Shape;
class gp_Pnt;
class gp_Dir;
class Prs3d_Drawer;

namespace cad_viewer {

class SceneObject;

class Scene : public QObject
{
  Q_OBJECT
public:
  explicit Scene(Handle(AIS_InteractiveContext) context, QObject* parent = nullptr);

  std::vector<SceneObject*> sceneObjects() const;

signals:
  void objectAdded(SceneObject* object);

private:
  Handle(AIS_Shape) createConstructionPlane(const QString& name,
                                            const gp_Pnt& position,
                                            const gp_Dir& dir,
                                            const gp_Dir& x_dir);

  Handle(AIS_InteractiveContext) m_context;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_SCENE_H_INCLUDED
