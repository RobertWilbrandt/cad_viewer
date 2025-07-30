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

Scene::Scene(Handle(AIS_InteractiveContext) context, QObject* parent)
  : QObject{parent}
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

Handle(AIS_Shape) Scene::createConstructionPlane(const QString& name,
                                                 const gp_Pnt& position,
                                                 const gp_Dir& dir,
                                                 const gp_Dir& x_dir)
{
  TopoDS_Face face =
    BRepBuilderAPI_MakeFace{gp_Pln{gp_Ax3{position, dir, x_dir}}, -50, 50, -50, 50};
  Handle(AIS_Shape) plane = new AIS_Shape{face};

  auto* scene_object        = new SceneObject{name, this};
  Handle(ObjectOwner) owner = new ObjectOwner{scene_object};
  plane->SetOwner(owner);

  plane->SetColor(Quantity_NOC_RED);
  plane->SetTransparency(0.5);

  return plane;
}

} // namespace cad_viewer
