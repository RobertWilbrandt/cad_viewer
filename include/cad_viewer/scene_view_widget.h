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
#ifndef CAD_VIEWER_SCENE_VIEW_WIDGET_H_INCLUDED
#define CAD_VIEWER_SCENE_VIEW_WIDGET_H_INCLUDED

#include <QWidget>
#include <Standard_Handle.hxx>
#include <memory>

class V3d_Viewer;
class V3d_View;
class AIS_InteractiveContext;
class AIS_ViewCube;

namespace cad_viewer {

class Scene;
class ViewWidget;

class SceneViewWidget : public QWidget
{
  Q_OBJECT

  Q_PROPERTY(GridType gridType READ gridType WRITE setGridType)
public:
  explicit SceneViewWidget(QWidget* parent = nullptr);

  enum GridType
  {
    GridTypeNone,
    GridTypeRectangular,
    GridTypeCircular
  };
  Q_ENUM(GridType);

  GridType gridType() const;
  void setGridType(GridType grid_type);

  [[nodiscard]] Scene& scene();
  [[nodiscard]] const Scene& scene() const;

signals:
  void updateRequested();

public slots:
  void cleanup();

private:
  Handle(AIS_ViewCube) createDefaultViewCube() const;

  Handle(V3d_Viewer) m_viewer;
  Handle(V3d_View) m_view;
  Handle(AIS_InteractiveContext) m_context;

  std::shared_ptr<Scene> m_scene;

  Handle(AIS_ViewCube) m_view_cube;

  ViewWidget* m_view_widget;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_SCENE_VIEW_WIDGET_H_INCLUDED
