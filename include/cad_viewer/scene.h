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
#ifndef CAD_VIEWER_SCENE_H_INCLUDED
#define CAD_VIEWER_SCENE_H_INCLUDED

#include <QObject>
#include <Standard_Handle.hxx>

class AIS_InteractiveContext;

namespace cad_viewer {

class Scene : public QObject
{
  Q_OBJECT
public:
  explicit Scene(Handle(AIS_InteractiveContext) context, QObject* parent = nullptr);

private:
  Handle(AIS_InteractiveContext) m_context;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_SCENE_H_INCLUDED
