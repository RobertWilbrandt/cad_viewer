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

#include <TDF_Label.hxx>
#include <TDataStd_Name.hxx>

namespace cad_viewer {

Model::Model(Handle(TDF_Data) data, QObject* parent)
  : QObject{parent}
  , m_data{std::move(data)}
{
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

} // namespace cad_viewer
