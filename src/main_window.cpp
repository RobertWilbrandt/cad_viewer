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

#include "cad_viewer/application.h"
#include "cad_viewer/config.h"
#include "cad_viewer/document.h"
#include "cad_viewer/scene.h"
#include "cad_viewer/scene_browser.h"
#include "cad_viewer/scene_viewer.h"
#include "cad_viewer/tool_bar.h"
#include "cad_viewer/view_widget.h"

#include <QAction>
#include <QCoreApplication>
#include <QDockWidget>
#include <QIcon>
#include <QMenuBar>
#include <QTabWidget>
#include <QVBoxLayout>

namespace cad_viewer {

MainWindow::MainWindow(Application* application, QWidget* parent)
  : QMainWindow{parent}
  , m_app{application}
  , m_config{new Config{this}}
{
  createMenus();

  auto* tool_bar = new ToolBar{m_config, this};
  addToolBar(Qt::TopToolBarArea, tool_bar);

  m_center = new QTabWidget{this};
  m_center->setTabPosition(QTabWidget::South);

  auto* document    = application->newDocument();
  auto* view_widget = new ViewWidget{m_config, this};
  m_center->addTab(view_widget, document->name());

  setCentralWidget(m_center);

  /*auto* scene_browser             = new SceneBrowser{scene_viewer->scene(), this};
  auto* scene_browser_dock_widget = new QDockWidget{this};
  scene_browser_dock_widget->setWidget(scene_browser);
  addDockWidget(Qt::LeftDockWidgetArea, scene_browser_dock_widget);*/

  QObject::connect(this,
                   &MainWindow::closeRequestReceived,
                   view_widget,
                   &ViewWidget::cleanup,
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

  auto new_action = new QAction{tr("&New"), this};
  new_action->setShortcut(QKeySequence::New);
  new_action->setStatusTip(tr("Create new document"));
  QObject::connect(new_action, &QAction::triggered, this, &MainWindow::newDocument);
  file_menu->addAction(new_action);

  auto* exit_action =
    new QAction{QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit), tr("&Exit"), this};
  exit_action->setShortcuts(QKeySequence::Quit);
  exit_action->setStatusTip(tr("Exit Application"));
  QObject::connect(exit_action, &QAction::triggered, this, &MainWindow::exit);
  file_menu->addAction(exit_action);
}

void MainWindow::newDocument()
{
  auto* document = m_app->newDocument();
  auto* new_tab  = new ViewWidget{m_config, this};
  QObject::connect(
    this, &MainWindow::closeRequestReceived, new_tab, &ViewWidget::cleanup, Qt::DirectConnection);

  m_center->addTab(new_tab, document->name());
  m_center->setCurrentWidget(new_tab);
}

void MainWindow::exit()
{
  QCoreApplication::quit();
}

} // namespace cad_viewer
