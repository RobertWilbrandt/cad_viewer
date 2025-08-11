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
#include "cad_viewer/view_multiplexer.h"

#include "cad_viewer/application.h"
#include "cad_viewer/document.h"
#include "cad_viewer/model.h"
#include "cad_viewer/scene_viewer.h"
#include "cad_viewer/view_widget.h"

namespace cad_viewer {

ViewMultiplexer::ViewMultiplexer(Application* app, QWidget* parent)
  : QTabWidget{parent}
  , m_app{app}
{
  setTabPosition(QTabWidget::South);
  QObject::connect(this, &QTabWidget::currentChanged, this, &ViewMultiplexer::tabChanged);

  QObject::connect(m_app, &Application::documentOpened, this, &ViewMultiplexer::showDocument);
}

ViewWidget* ViewMultiplexer::currentView() const
{
  return m_cur_view;
}

void ViewMultiplexer::showDocument(Document* document)
{
  auto* view_widget = new ViewWidget{&m_app->config(), document, this};
  QObject::connect(m_app,
                   &Application::shutdownRequested,
                   view_widget,
                   &ViewWidget::cleanup,
                   Qt::DirectConnection);

  addTab(view_widget, document->model()->name());
  setCurrentWidget(view_widget);
}

void ViewMultiplexer::viewInitialized()
{
  m_cur_view = static_cast<ViewWidget*>(sender());
  QObject::disconnect(m_cur_initialization);
}

void ViewMultiplexer::tabChanged(int index)
{
  auto* view = static_cast<ViewWidget*>(widget(index));

  if (view->initialized())
  {
    m_cur_view = view;
  }
  else
  {
    if (m_cur_initialization)
    {
      QObject::disconnect(m_cur_initialization);
    }
    m_cur_initialization = QObject::connect(
      view, &ViewWidget::initializationDone, this, &ViewMultiplexer::viewInitialized);
  }
}

} // namespace cad_viewer
