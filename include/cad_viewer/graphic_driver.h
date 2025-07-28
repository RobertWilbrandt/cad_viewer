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
#ifndef CAD_VIEWER_GRAPHIC_DRIVER_H_INCLUDED
#define CAD_VIEWER_GRAPHIC_DRIVER_H_INCLUDED

#include <Standard_Handle.hxx>

class Aspect_DisplayConnection;
class OpenGl_GraphicDriver;

namespace cad_viewer {

class GraphicDriver
{
public:
  explicit GraphicDriver();

  const Handle(OpenGl_GraphicDriver) & driver() const;

private:
  Handle(OpenGl_GraphicDriver) m_driver;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_GRAPHIC_DRIVER_H_INCLUDED
