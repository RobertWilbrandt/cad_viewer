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

namespace cad_viewer {

Scene::Scene(Handle(AIS_InteractiveContext) context, QObject* parent)
  : QObject{parent}
  , m_context{std::move(context)}
{
}

} // namespace cad_viewer
