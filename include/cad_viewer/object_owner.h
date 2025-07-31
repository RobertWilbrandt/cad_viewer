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
#ifndef CAD_VIEWER_OBJECT_OWNER_H_INCLUDED
#define CAD_VIEWER_OBJECT_OWNER_H_INCLUDED

#include <Standard_Transient.hxx>
#include <Standard_Type.hxx>

namespace cad_viewer {

class SceneObject;

class ObjectOwner : public Standard_Transient
{
public:
  DEFINE_STANDARD_RTTIEXT(ObjectOwner, Standard_Transient)

  explicit ObjectOwner(SceneObject* scene_object);
  virtual ~ObjectOwner() = default;

  [[nodiscard]] SceneObject* sceneObject() const;

  void setSelected(bool value);

private:
  SceneObject* m_scene_object;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_OBJECT_OWNER_H_INCLUDED
