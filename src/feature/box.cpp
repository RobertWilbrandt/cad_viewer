// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-08-26
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/feature/box.h"

#include <BRepPrimAPI_MakeBox.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDataStd_Name.hxx>
#include <TDataStd_Real.hxx>
#include <TFunction_ExecutionStatus.hxx>
#include <TFunction_Logbook.hxx>
#include <TNaming_Builder.hxx>

namespace cad_viewer::feature {

Standard_Integer Box::Execute(Handle(TFunction_Logbook) & log) const
{
  const auto property_label = Label().FindChild(0);

  // Evaluate properties
  std::vector<double> arguments;
  for (const auto* name : {"width", "length", "height"})
  {
    if (const auto prop = findProperty(property_label, name); prop)
    {
      if (const auto value = evaluateProperty(*prop); value)
      {
        arguments.push_back(*value);
      }
    }
  }
  if (arguments.size() != 3)
  {
    return TFunction_ES_WrongDefinition;
  }

  // Create solid
  BRepPrimAPI_MakeBox make_box{arguments[0], arguments[1], arguments[2]};

  // Ensure proper naming
  TNaming_Builder builder{Label()};
  builder.Generated(make_box.Solid());
  log->SetImpacted(Label());

  std::size_t i = 1;
  for (const auto& face : {make_box.BottomFace(),
                           make_box.TopFace(),
                           make_box.BackFace(),
                           make_box.FrontFace(),
                           make_box.LeftFace(),
                           make_box.RightFace()})
  {
    const auto child_label = Label().FindChild(i++);
    TNaming_Builder child_builder{child_label};
    child_builder.Generated(face);
    log->SetImpacted(child_label);
  }

  return TFunction_ES_Succeeded;
}

void Box::Arguments(TDF_LabelList& args) const
{
  const auto property_label = Label().FindChild(0);
  for (const auto* name : {"width", "length", "height"})
  {
    if (const auto prop = findProperty(property_label, name); prop)
    {
      args.Append(*prop);
    }
  }
}

void Box::Results(TDF_LabelList& res) const
{
  res.Append(Label());
}

std::optional<TDF_Label> Box::findProperty(const TDF_Label& label, const std::string& name) const
{
  for (TDF_ChildIterator it{Label(), false}; it.More(); it.Next())
  {
    const auto child = it.Value();

    if (Handle(TDataStd_Name) name_attr; child.FindAttribute(TDataStd_Name::GetID(), name_attr))
    {
      if (name_attr->Get() == name.c_str())
      {
        return child;
      }
    }
  }

  return std::nullopt;
}

std::optional<double> Box::evaluateProperty(const TDF_Label& label) const
{
  if (Handle(TDataStd_Real) value; label.FindAttribute(TDataStd_Real::GetID(), value))
  {
    return value->Get();
  }
  return std::nullopt;
}

} // namespace cad_viewer::feature
