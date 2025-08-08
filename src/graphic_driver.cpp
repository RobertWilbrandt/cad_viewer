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
#include "cad_viewer/graphic_driver.h"

#include <Aspect_DisplayConnection.hxx>
#include <OpenGl_Context.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <QOpenGLContext>

namespace cad_viewer {

GraphicDriver::GraphicDriver()
{
  Handle(Aspect_DisplayConnection) displayConnection = new Aspect_DisplayConnection();
  m_driver                                     = new OpenGl_GraphicDriver(displayConnection, false);
  m_driver->ChangeOptions().buffersNoSwap      = true;  // QOpenGLWidget handles buffer swap
  m_driver->ChangeOptions().buffersOpaqueAlpha = true;  // Don't write to alpha channel
  m_driver->ChangeOptions().useSystemBuffer    = false; // Always use offscreen FBO
}

const Handle(OpenGl_GraphicDriver) & GraphicDriver::driver() const
{
  return m_driver;
}

} // namespace cad_viewer
