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
#include "cad_viewer/model.h"
#include "cad_viewer/model_interface.h"
#include "cad_viewer/scene.h"
#include "cad_viewer/scene_browser.h"
#include "cad_viewer/scene_viewer.h"
#include "cad_viewer/tool_bar.h"
#include "cad_viewer/view_multiplexer.h"
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
{
  createMenus();

  auto* view_multiplexer = new ViewMultiplexer{m_app, this};
  setCentralWidget(view_multiplexer);

  auto* model_interface = new ModelInterface{this};
  QObject::connect(view_multiplexer,
                   &ViewMultiplexer::currentViewChanged,
                   model_interface,
                   &ModelInterface::setCurrentView);

  auto* tool_bar = new ToolBar{model_interface, &m_app->config(), this};
  addToolBar(Qt::TopToolBarArea, tool_bar);

  /*auto* scene_browser             = new SceneBrowser{scene_viewer->scene(), this};
  auto* scene_browser_dock_widget = new QDockWidget{this};
  scene_browser_dock_widget->setWidget(scene_browser);
  addDockWidget(Qt::LeftDockWidgetArea, scene_browser_dock_widget);*/

  m_app->newDocument();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  m_app->requestShutdown();
  QMainWindow::closeEvent(event);
}

void MainWindow::exit()
{
  QCoreApplication::quit();
}

void MainWindow::createMenus()
{
  auto* file_menu = menuBar()->addMenu(tr("&File"));

  auto new_action = new QAction{tr("&New"), this};
  new_action->setShortcut(QKeySequence::New);
  new_action->setStatusTip(tr("Create new document"));
  QObject::connect(new_action, &QAction::triggered, m_app, &Application::newDocument);
  file_menu->addAction(new_action);

  auto* exit_action =
    new QAction{QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit), tr("&Exit"), this};
  exit_action->setShortcuts(QKeySequence::Quit);
  exit_action->setStatusTip(tr("Exit Application"));
  QObject::connect(exit_action, &QAction::triggered, this, &MainWindow::exit);
  file_menu->addAction(exit_action);
}

} // namespace cad_viewer
