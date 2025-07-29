// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-07-29
 *
 */
//----------------------------------------------------------------------
#ifndef CAD_VIEWER_SCENE_OBJECT_H_INCLUDED
#define CAD_VIEWER_SCENE_OBJECT_H_INCLUDED

#include <QObject>

namespace cad_viewer {

class SceneObject : public QObject
{
  Q_OBJECT
public:
  explicit SceneObject(QObject* parent = nullptr);
  virtual ~SceneObject() = default;

private:
};

} // namespace cad_viewer

#endif // CAD_VIEWER_SCENE_OBJECT_H_INCLUDED
