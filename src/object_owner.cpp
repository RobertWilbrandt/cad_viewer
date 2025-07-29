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
#include "cad_viewer/object_owner.h"

#include "cad_viewer/scene_object.h"

namespace cad_viewer {

IMPLEMENT_STANDARD_RTTIEXT(ObjectOwner, Standard_Transient)

ObjectOwner::ObjectOwner(SceneObject* scene_object)
  : m_scene_object{scene_object}
{
}

void ObjectOwner::setSelected(bool value)
{
  m_scene_object->setSelected(value);
}

} // namespace cad_viewer
