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

#include "cad_viewer/scene_viewer.h"
#include "cad_viewer/view_widget.h"

namespace cad_viewer {

ViewMultiplexer::ViewMultiplexer(ViewWidget* initial_view, QObject* parent)
  : QObject{parent}
{
  viewChanged(initial_view);
}

ViewWidget* ViewMultiplexer::currentView() const
{
  return m_cur_view;
}

void ViewMultiplexer::viewChanged(ViewWidget* view)
{
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

void ViewMultiplexer::viewInitialized()
{
  m_cur_view = static_cast<ViewWidget*>(sender());
  QObject::disconnect(m_cur_initialization);
}

} // namespace cad_viewer
