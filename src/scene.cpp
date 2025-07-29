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

#include <AIS_InteractiveContext.hxx>
#include <AIS_Plane.hxx>
#include <Geom_Plane.hxx>
#include <Prs3d_LineAspect.hxx>
#include <gp_Ax3.hxx>

namespace cad_viewer {

Scene::Scene(Handle(AIS_InteractiveContext) context, QObject* parent)
  : QObject{parent}
  , m_context{std::move(context)}
{
  Handle(Prs3d_Drawer) drawer = new Prs3d_Drawer{};
  drawer->SetupOwnDefaults();

  m_context->Display(
    createConstructionPlane(gp_Pnt{0, 0, 0}, gp_Dir{1, 0, 0}, gp_Dir{0, 1, 0}, drawer),
    AIS_Shaded,
    0,
    false);
  m_context->Display(
    createConstructionPlane(gp_Pnt{0, 0, 0}, gp_Dir{0, 1, 0}, gp_Dir{-1, 0, 0}, drawer),
    AIS_Shaded,
    0,
    false);
  m_context->Display(
    createConstructionPlane(gp_Pnt{0, 0, 0}, gp_Dir{0, 0, 1}, gp_Dir{0, 1, 0}, drawer),
    AIS_Shaded,
    0,
    false);
}

Handle(AIS_Plane) Scene::createConstructionPlane(const gp_Pnt& position,
                                                 const gp_Dir& dir,
                                                 const gp_Dir& x_dir,
                                                 const Handle(Prs3d_Drawer) & drawer) const
{
  Handle(Geom_Plane) geom_plane = new Geom_Plane{gp_Ax3{position, dir, x_dir}};
  Handle(AIS_Plane) plane       = new AIS_Plane{geom_plane};
  plane->SetAttributes(drawer);

  plane->SetColor(Quantity_NOC_RED);
  plane->SetTransparency(0.5);
  plane->SetSize(100);

  return plane;
}

} // namespace cad_viewer
