// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-07-20
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/scene_view_widget.h"

#include "cad_viewer/view_widget.h"

#include <QVBoxLayout>

namespace cad_viewer {

SceneViewWidget::SceneViewWidget(QWidget* parent)
  : QWidget{parent}
  , m_view_widget{new ViewWidget{this}}
{
  auto* layout = new QVBoxLayout{this};
  layout->addWidget(m_view_widget);
  setLayout(layout);
}

} // namespace cad_viewer
