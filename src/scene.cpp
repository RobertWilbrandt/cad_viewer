// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-07-28
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/scene.h"

#include "cad_viewer/object_owner.h"
#include "cad_viewer/scene_object.h"

#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <Geom_Plane.hxx>
#include <TopoDS_Face.hxx>
#include <gp_Ax3.hxx>

namespace cad_viewer {

Scene::Scene(Document* document, Handle(AIS_InteractiveContext) context, QObject* parent)
  : QObject{parent}
  , m_document{document}
  , m_context{std::move(context)}
{
  m_context->Display(
    createConstructionPlane("yz", gp_Pnt{0, 0, 0}, gp_Dir{1, 0, 0}, gp_Dir{0, 1, 0}),
    AIS_Shaded,
    0,
    false);
  m_context->Display(
    createConstructionPlane("xz", gp_Pnt{0, 0, 0}, gp_Dir{0, 1, 0}, gp_Dir{-1, 0, 0}),
    AIS_Shaded,
    0,
    false);
  m_context->Display(
    createConstructionPlane("xy", gp_Pnt{0, 0, 0}, gp_Dir{0, 0, 1}, gp_Dir{0, 1, 0}),
    AIS_Shaded,
    0,
    false);
}

std::vector<SceneObject*> Scene::sceneObjects() const
{
  AIS_ListOfInteractive interactive_objects;
  m_context->DisplayedObjects(interactive_objects);

  std::vector<SceneObject*> result;
  for (const auto& object : interactive_objects)
  {
    const auto owner = object->GetOwner();
    if (owner.IsNull())
    {
      continue;
    }
    if (owner->IsKind(ObjectOwner::get_type_descriptor()))
    {
      result.push_back(Handle(ObjectOwner)::DownCast(owner)->sceneObject());
    }
  }

  return result;
}

Document* Scene::document() const
{
  return m_document;
}

Handle(AIS_Shape) Scene::createConstructionPlane(const QString& name,
                                                 const gp_Pnt& position,
                                                 const gp_Dir& dir,
                                                 const gp_Dir& x_dir)
{
  TopoDS_Face face =
    BRepBuilderAPI_MakeFace{gp_Pln{gp_Ax3{position, dir, x_dir}}, -50, 50, -50, 50};
  Handle(AIS_Shape) plane = new AIS_Shape{face};

  auto* scene_object        = new SceneObject{SceneObject::ObjectTypeConstruction, name, this};
  Handle(ObjectOwner) owner = new ObjectOwner{scene_object};
  plane->SetOwner(owner);

  plane->SetColor(Quantity_NOC_RED);
  plane->SetTransparency(0.5);

  emit objectAdded(scene_object);
  return plane;
}

} // namespace cad_viewer
