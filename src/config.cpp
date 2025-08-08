// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-08-08
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/config.h"

#include "cad_viewer/viewer_config.h"

namespace cad_viewer {

Config::Config(QObject* parent)
  : QObject{parent}
  , m_viewer_config{new ViewerConfig{this}}
{
}

ViewerConfig* Config::viewer() const
{
  return m_viewer_config;
}

} // namespace cad_viewer
