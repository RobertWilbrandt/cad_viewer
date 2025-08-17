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
#include <TDF_Label.hxx>
#include <vector>

class AIS_InteractiveContext;
class AIS_Shape;
class gp_Pnt;
class gp_Dir;
class Prs3d_Drawer;
class TPrsStd_AISViewer;
namespace cad_viewer {
class Document;
}


namespace cad_viewer {

class SceneObject;

class Scene : public QObject
{
  Q_OBJECT
public:
  explicit Scene(Document* document,
                 Handle(AIS_InteractiveContext) context,
                 QObject* parent = nullptr);
  ~Scene();

  Scene(const Scene&)            = delete;
  Scene& operator=(const Scene&) = delete;

  std::vector<SceneObject*> sceneObjects() const;

  [[nodiscard]] Document* document() const;

signals:
  void objectAdded(SceneObject* object);

  void viewUpdateRequested();

private slots:
  void addPresentation(TDF_Label label);

private:
  Handle(AIS_Shape) createConstructionPlane(const QString& name,
                                            const gp_Pnt& position,
                                            const gp_Dir& dir,
                                            const gp_Dir& x_dir);

  void cleanupPresentations(const TDF_Label& label);

  Document* m_document;
  Handle(AIS_InteractiveContext) m_context;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_SCENE_H_INCLUDED
