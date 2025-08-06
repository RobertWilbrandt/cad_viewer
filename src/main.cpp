// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-07-15
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/application.h"
#include "cad_viewer/graphic_driver.h"
#include "cad_viewer/main_window.h"

#include <QSurfaceFormat>

using namespace cad_viewer;

int main(int argc, char* argv[])
{
  GraphicDriver graphic_driver{};

  Application app{argc, argv};

  QSurfaceFormat format{};
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  format.setProfile(QSurfaceFormat::CompatibilityProfile);
  QSurfaceFormat::setDefaultFormat(format);

  MainWindow window{&graphic_driver};
  window.show();

  return app.exec();
}
