// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-07-29
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/scene_object.h"

#include <iostream>

namespace cad_viewer {

SceneObject::SceneObject(QObject* parent)
  : QObject{parent}
{
}

bool SceneObject::selected() const
{
  return m_selected;
}

void SceneObject::setSelected(bool selected)
{
  bool before_selected = m_selected;
  m_selected           = selected;
  if (selected != before_selected)
  {
    emit selectedChanged(selected);
  }
}

} // namespace cad_viewer
