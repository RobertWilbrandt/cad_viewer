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

#include <QAction>
#include <QCoreApplication>
#include <QIcon>
#include <QMenuBar>

namespace cad_viewer {

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow{parent}
{
  createMenus();

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

void MainWindow::createMenus()
{
  auto* file_menu = menuBar()->addMenu(tr("&File"));

  auto* exit_action =
    new QAction{QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit), tr("&Exit"), this};
  exit_action->setShortcuts(QKeySequence::Close);
  exit_action->setStatusTip(tr("Exit Application"));
  QObject::connect(exit_action, &QAction::triggered, this, &MainWindow::exit);
  file_menu->addAction(exit_action);
}

void MainWindow::exit()
{
  QCoreApplication::quit();
}

} // namespace cad_viewer
