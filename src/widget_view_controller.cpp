// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-07-20
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/widget_view_controller.h"

#include "cad_viewer/object_owner.h"

#include <AIS_InteractiveContext.hxx>
#include <QWidget>

namespace cad_viewer {

WidgetViewController::WidgetViewController(QWidget* widget)
  : m_widget{widget}
{
  SetRotationMode(AIS_RotationMode_CameraAt);
}

void WidgetViewController::handleViewRedraw(const Handle(AIS_InteractiveContext) & context,
                                            const Handle(V3d_View) & view)
{
  AIS_ViewController::handleViewRedraw(context, view);
  if (myToAskNextFrame)
  {
    m_widget->update();
  }
}

void WidgetViewController::OnSelectionChanged(const Handle(AIS_InteractiveContext) & context,
                                              const Handle(V3d_View) & view)
{
  std::vector<Handle(ObjectOwner)> selected_objs;
  selected_objs.reserve(context->NbSelected());
  for (context->InitSelected(); context->MoreSelected(); context->NextSelected())
  {
    auto obj   = context->SelectedInteractive();
    auto owner = obj->GetOwner();
    if (owner.IsNull())
    {
      continue;
    }
    if (owner->IsKind(ObjectOwner::get_type_descriptor()))
    {
      selected_objs.push_back(Handle(ObjectOwner)::DownCast(owner));
    }
  }

  for (const auto& prev_selected : m_cur_selected)
  {
    if (const auto find_it = std::find(selected_objs.begin(), selected_objs.end(), prev_selected);
        find_it == selected_objs.end())
    {
      prev_selected->setSelected(false);
    }
  }
  for (const auto& now_selected : selected_objs)
  {
    if (const auto find_it = std::find(m_cur_selected.begin(), m_cur_selected.end(), now_selected);
        find_it == m_cur_selected.end())
    {
      now_selected->setSelected(true);
    }
  }

  std::swap(selected_objs, m_cur_selected);
}

} // namespace cad_viewer
