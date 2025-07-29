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

namespace cad_viewer {

IMPLEMENT_STANDARD_RTTIEXT(ObjectOwner, Standard_Transient)

ObjectOwner::ObjectOwner(SceneObject* scene_object)
  : m_scene_object{scene_object}
{
}

} // namespace cad_viewer
