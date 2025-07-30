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

namespace cad_viewer {

SceneObject::SceneObject(QString name, QObject* parent)
  : QObject{parent}
  , m_name{std::move(name)}
{
}

const QString& SceneObject::name() const
{
  return m_name;
}

void SceneObject::setName(QString name)
{
  std::swap(name, m_name);
  if (name != m_name)
  {
    emit nameChanged(m_name);
  }
}

bool SceneObject::selected() const
{
  return m_selected;
}

void SceneObject::setSelected(bool selected)
{
  std::swap(selected, m_selected);
  if (selected != m_selected)
  {
    emit selectedChanged(m_selected);
  }
}

} // namespace cad_viewer
