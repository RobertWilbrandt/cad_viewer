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

class V3d_Viewer;
class V3d_View;

namespace cad_viewer {

class ViewWidget;

class SceneViewWidget : public QWidget
{
  Q_OBJECT
public:
  explicit SceneViewWidget(QWidget* parent = nullptr);
  ~SceneViewWidget();

  SceneViewWidget(const SceneViewWidget&)            = delete;
  SceneViewWidget& operator=(const SceneViewWidget&) = delete;

public slots:
  void cleanup();

private:
  Handle(V3d_Viewer) m_viewer;
  Handle(V3d_View) m_view;

  ViewWidget* m_view_widget;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_SCENE_VIEW_WIDGET_H_INCLUDED
