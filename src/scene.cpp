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

#include "cad_viewer/document.h"
#include "cad_viewer/model.h"
#include "cad_viewer/object_owner.h"
#include "cad_viewer/scene_object.h"

#include <AIS_InteractiveContext.hxx>
#include <AIS_Plane.hxx>
#include <AIS_Shape.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <Geom_Plane.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDataXtd_Plane.hxx>
#include <TNaming_NamedShape.hxx>
#include <TPrsStd_AISPresentation.hxx>
#include <TPrsStd_AISViewer.hxx>
#include <TopoDS_Face.hxx>
#include <gp_Ax3.hxx>

namespace cad_viewer {

Scene::Scene(Document* document, Handle(AIS_InteractiveContext) context, QObject* parent)
  : QObject{parent}
  , m_document{document}
  , m_context{std::move(context)}
{
  Handle(TPrsStd_AISViewer) m_model_viewer =
    TPrsStd_AISViewer::New(m_document->model()->main(), m_context);
  QObject::connect(m_document->model(), &Model::shapeAdded, this, &Scene::addShapePresentation);

  const auto main = m_document->model()->main();
  for (TDF_ChildIterator it{main, true}; it.More(); it.Next())
  {
    const auto label = it.Value();

    Handle(TDF_Attribute) presentation;
    if (!label.FindAttribute(TPrsStd_AISPresentation::GetID(), presentation))
    {
      const auto driver_guid = presentationDriver(label);
      if (driver_guid)
      {
        addPresentation(label, *driver_guid);
      }
    }
  }
}

Scene::~Scene()
{
  auto main_label = m_document->model()->main();

  cleanupPresentations(main_label);

  Handle(TPrsStd_AISViewer) viewer;
  if (TPrsStd_AISViewer::Find(main_label, viewer))
  {
    main_label.ForgetAttribute(viewer);
  }
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

void Scene::addShapePresentation(TDF_Label label)
{
  addPresentation(label, TNaming_NamedShape::GetID());
}

std::optional<Standard_GUID> Scene::presentationDriver(const TDF_Label& label) const
{
  Handle(TDataXtd_Plane) plane;
  if (label.FindAttribute(TDataXtd_Plane::GetID(), plane))
  {
    return TDataXtd_Plane::GetID();
  }

  Handle(TNaming_NamedShape) named_shape;
  if (label.FindAttribute(TNaming_NamedShape::GetID(), named_shape))
  {
    return TNaming_NamedShape::GetID();
  }

  return std::nullopt;
}

void Scene::addPresentation(TDF_Label label, const Standard_GUID& driver)
{
  Handle(TPrsStd_AISPresentation) presentation = TPrsStd_AISPresentation::Set(label, driver);
  presentation->SetMode(AIS_Shaded);
  presentation->Display(true);

  Handle(AIS_InteractiveObject) object = presentation->GetAIS();

  if (driver == TDataXtd_Plane::GetID())
  {
    Handle(AIS_Plane) plane = Handle(AIS_Plane)::DownCast(object);
    plane->SetSize(100);
    plane->SetColor(Quantity_NOC_RED);
  }

  m_context->Display(object, AIS_Shaded, 0, true);
  emit viewUpdateRequested();
}

void Scene::cleanupPresentations(const TDF_Label& label)
{
  Handle(TPrsStd_AISPresentation) presentation;
  if (label.FindAttribute(TPrsStd_AISPresentation::GetID(), presentation))
  {
    presentation->Erase(false);
  }

  for (TDF_ChildIterator it{label, true}; it.More(); it.Next())
  {
    auto label = it.Value();
    Handle(TPrsStd_AISPresentation) presentation;
    if (label.FindAttribute(TPrsStd_AISPresentation::GetID(), presentation))
    {
      presentation->Erase(false);
      label.ForgetAttribute(presentation);
    }
  }
}

} // namespace cad_viewer
