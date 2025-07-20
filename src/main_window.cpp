// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-07-16
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/main_window.h"

#include "cad_viewer/scene_view_widget.h"

namespace cad_viewer {

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow{parent}
{
  auto* scene_view_widget = new SceneViewWidget{this};
  setCentralWidget(scene_view_widget);

  QObject::connect(this,
                   &MainWindow::closeRequestReceived,
                   scene_view_widget,
                   &SceneViewWidget::cleanup,
                   Qt::DirectConnection);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  emit closeRequestReceived();
  QMainWindow::closeEvent(event);
}

} // namespace cad_viewer
