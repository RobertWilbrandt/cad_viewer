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
#include <QString>

namespace cad_viewer {

class SceneObject : public QObject
{
  Q_OBJECT

  Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
  Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
  explicit SceneObject(QString name, QObject* parent = nullptr);
  virtual ~SceneObject() = default;

  [[nodiscard]] const QString& name() const;
  void setName(QString name);

  [[nodiscard]] bool selected() const;
  void setSelected(bool selected);

signals:
  void nameChanged(const QString& name);

  void selectedChanged(bool selected);

private:
  QString m_name;

  bool m_selected = false;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_SCENE_OBJECT_H_INCLUDED
