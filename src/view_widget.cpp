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
#include "cad_viewer/view_widget.h"

#include <QSurfaceFormat>

namespace cad_viewer {

ViewWidget::ViewWidget(QWidget* parent)
  : QOpenGLWidget{parent}
{
  // Set surface format
  QSurfaceFormat format{};
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  format.setProfile(QSurfaceFormat::CompatibilityProfile);
  setFormat(format);
}

} // namespace cad_viewer
