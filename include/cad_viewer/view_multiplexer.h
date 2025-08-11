// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-08-09
 *
 */
//----------------------------------------------------------------------
#ifndef CAD_VIEWER_VIEW_MULTIPLEXER_H_INCLUDED
#define CAD_VIEWER_VIEW_MULTIPLEXER_H_INCLUDED

#include <QObject>

#include <QMetaObject>

namespace cad_viewer {
class Scene;
class SceneViewer;
class ViewWidget;
} // namespace cad_viewer


namespace cad_viewer {

class ViewMultiplexer : public QObject
{
  Q_OBJECT
public:
  explicit ViewMultiplexer(ViewWidget* initial_view, QObject* parent = nullptr);

  [[nodiscard]] ViewWidget* currentView() const;

public slots:
  void viewChanged(ViewWidget* view);
  void viewInitialized();

private:
  QMetaObject::Connection m_cur_initialization;

  ViewWidget* m_cur_view;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_VIEW_MULTIPLEXER_H_INCLUDED
