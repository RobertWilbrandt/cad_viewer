// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-08-08
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/model.h"

#include <BRepPrimAPI_MakeBox.hxx>
#include <TDF_Label.hxx>
#include <TDF_Tool.hxx>
#include <TDataStd_Name.hxx>
#include <TDataXtd_Plane.hxx>
#include <TNaming_Builder.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Solid.hxx>
#include <gp_Pln.hxx>

namespace cad_viewer {

Model::Model(Handle(TDF_Data) data, QObject* parent)
  : QObject{parent}
  , m_data{std::move(data)}
{
  const auto origin = m_data->Root().NewChild();
  TDataStd_Name::Set(origin, "Origin");
  createOrigin(origin);
}

QString Model::name() const
{
  Handle(TDataStd_Name) name;
  if (!m_data->Root().FindAttribute(TDataStd_Name::GetID(), name))
  {
    throw std::runtime_error{"Missing model name"};
  }

  std::u16string name_str{name->Get().ToExtString(),
                          static_cast<std::size_t>(name->Get().Length())};
  return QString::fromStdU16String(name_str);
}

void Model::setName(const QString& name)
{
  const auto name_str = name.toStdU16String();
  const TCollection_ExtendedString name_extstr{name_str.data()};

  Handle(TDataStd_Name) name_attr;
  if (m_data->Root().FindAttribute(TDataStd_Name::GetID(), name_attr))
  {
    if (!name_attr->Get().IsEqual(name_extstr))
    {
      name_attr->Set(name_extstr);

      emit nameChanged(name);
    }
  }
  else
  {
    name_attr = new TDataStd_Name{};
    name_attr->Set(name_extstr);
    m_data->Root().AddAttribute(name_attr);

    emit nameChanged(name);
  }
}

TDF_Label Model::main() const
{
  return m_data->Root();
}

void Model::createBox(double sx, double sy, double sz)
{
  BRepPrimAPI_MakeBox box{sx, sy, sz};
  const auto& solid = box.Solid();

  TDF_Label label = m_data->Root().NewChild();
  TNaming_Builder builder{label};
  builder.Generated(solid);

  for (auto explorer = TopExp_Explorer{solid, TopAbs_FACE}; explorer.More(); explorer.Next())
  {
    TopoDS_Face face = TopoDS::Face(explorer.Current());

    TDF_Label child_label = label.NewChild();
    TNaming_Builder child_builder{child_label};
    child_builder.Generated(face);
  }

  emit shapeAdded(label);
}

void Model::createOrigin(const TDF_Label& label)
{
  const auto create_plane =
    [&](const TCollection_ExtendedString& name, const gp_Dir& dir, const gp_Dir& x_dir) {
      TDF_Label plane_label = label.NewChild();
      TDataStd_Name::Set(plane_label, name);

      gp_Ax3 plane_ax{gp_Pnt{}, dir, x_dir};
      TDataXtd_Plane::Set(plane_label, gp_Pln{plane_ax});
    };

  create_plane("XY", gp_Dir{0, 0, 1}, gp_Dir{1, 0, 0});
  create_plane("XZ", gp_Dir{0, 1, 0}, gp_Dir{1, 0, 0});
  create_plane("YZ", gp_Dir{1, 0, 0}, gp_Dir{0, 1, 0});
}

} // namespace cad_viewer
