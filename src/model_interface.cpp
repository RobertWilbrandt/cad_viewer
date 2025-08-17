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

#include <BRepPrimAPI_MakeBox.hxx>

namespace cad_viewer {

ModelInterface::ModelInterface(QObject* parent)
  : QObject{parent}
{
}

void ModelInterface::setCurrentView(ViewWidget* view)
{
  m_cur_view = view;
}

void ModelInterface::createBox(double sx, double sy, double sz)
{
  auto* cur_model = currentModel();
  if (!cur_model)
  {
    return;
  }

  BRepPrimAPI_MakeBox box_builder{sx, sy, sz};
  cur_model->createSolid(box_builder.Solid());
}

Model* ModelInterface::currentModel() const
{
  if (!m_cur_view)
  {
    return nullptr;
  }

  const auto viewer = m_cur_view->viewer().lock();
  if (!viewer)
  {
    return nullptr;
  }
  return viewer->scene()->document()->model();
}

} // namespace cad_viewer
