// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-07-28
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/viewer_config.h"

namespace cad_viewer {

ViewerConfig::ViewerConfig(QObject* parent)
  : QObject{parent}
{
}

ViewerConfig::GridType ViewerConfig::gridType() const
{
  return m_grid_type;
}

void ViewerConfig::setGridType(GridType grid_type)
{
  const auto old_grid_type = m_grid_type;
  m_grid_type              = grid_type;
  if (old_grid_type != grid_type)
  {
    emit gridTypeChanged(grid_type);
  }
}

} // namespace cad_viewer
