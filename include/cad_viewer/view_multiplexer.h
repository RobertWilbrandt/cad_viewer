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

#include <QMetaObject>
#include <QObject>
#include <QTabWidget>

namespace cad_viewer {
class Application;
class Document;
class Scene;
class SceneViewer;
class ViewWidget;
} // namespace cad_viewer


namespace cad_viewer {

class ViewMultiplexer : public QTabWidget
{
  Q_OBJECT
public:
  explicit ViewMultiplexer(Application* app, QWidget* parent = nullptr);

  [[nodiscard]] ViewWidget* currentView() const;

private slots:
  void showDocument(Document* document);
  void viewInitialized();

  void tabChanged(int index);

private:
  Application* m_app;

  QMetaObject::Connection m_cur_initialization;
  ViewWidget* m_cur_view;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_VIEW_MULTIPLEXER_H_INCLUDED
