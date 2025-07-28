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
#include "cad_viewer/scene_viewer.h"
#include "cad_viewer/tool_bar.h"
#include "cad_viewer/viewer_config.h"

#include <QAction>
#include <QCoreApplication>
#include <QIcon>
#include <QMenuBar>
#include <QVBoxLayout>

namespace cad_viewer {

MainWindow::MainWindow(GraphicDriver* graphic_driver, QWidget* parent)
  : QMainWindow{parent}
{
  createMenus();

  auto* viewer_config = new ViewerConfig{this};

  auto* tool_bar = new ToolBar{this};
  QObject::connect(
    tool_bar, &ToolBar::gridTypeSelectionChanged, viewer_config, &ViewerConfig::setGridType);
  addToolBar(Qt::TopToolBarArea, tool_bar);

  auto* scene_viewer = new SceneViewer{graphic_driver, this};
  QObject::connect(
    viewer_config, &ViewerConfig::gridTypeChanged, scene_viewer, &SceneViewer::setGridType);

  auto* scene_view_widget = scene_viewer->createView();
  setCentralWidget(scene_view_widget);

  QObject::connect(this,
                   &MainWindow::closeRequestReceived,
                   scene_viewer,
                   &SceneViewer::cleanup,
                   Qt::DirectConnection);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  emit closeRequestReceived();
  QMainWindow::closeEvent(event);
}

void MainWindow::createMenus()
{
  auto* file_menu = menuBar()->addMenu(tr("&File"));

  auto* exit_action =
    new QAction{QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit), tr("&Exit"), this};
  exit_action->setShortcuts(QKeySequence::Quit);
  exit_action->setStatusTip(tr("Exit Application"));
  QObject::connect(exit_action, &QAction::triggered, this, &MainWindow::exit);
  file_menu->addAction(exit_action);
}

void MainWindow::exit()
{
  QCoreApplication::quit();
}

} // namespace cad_viewer
