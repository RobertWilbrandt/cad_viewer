// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-08-13
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/model_interface.h"

#include "cad_viewer/document.h"
#include "cad_viewer/model.h"
#include "cad_viewer/scene.h"
#include "cad_viewer/scene_viewer.h"
#include "cad_viewer/view_widget.h"

namespace cad_viewer {

ModelInterface::ModelInterface(QObject* parent)
  : QObject{parent}
{
}

void ModelInterface::setCurrentView(ViewWidget* view)
{
  m_cur_view = view;
}

Model* ModelInterface::currentModel() const
{
  if (!m_cur_view)
  {
    return nullptr;
  }

  auto* scene = m_cur_view->viewer()->scene();
  return scene->document()->model();
}

} // namespace cad_viewer
