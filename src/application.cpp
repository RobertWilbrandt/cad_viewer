// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-08-06
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/application.h"

namespace cad_viewer {

Application::Application(int argc, char* argv[])
  : m_app{argc, argv}
{
}

int Application::exec()
{
  return m_app.exec();
}

} // namespace cad_viewer
