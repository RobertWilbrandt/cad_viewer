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

namespace cad_viewer {

ViewMultiplexer::ViewMultiplexer(ViewWidget* initial_view, QObject* parent)
  : QObject{parent}
  , m_cur_view{initial_view}
{
}

ViewWidget* ViewMultiplexer::currentView() const
{
  return m_cur_view;
}

void ViewMultiplexer::viewChanged(ViewWidget* view)
{
  m_cur_view = view;
}

} // namespace cad_viewer
