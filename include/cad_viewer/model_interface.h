// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-08-13
 *
 */
//----------------------------------------------------------------------
#ifndef CAD_VIEWER_MODEL_INTERFACE_H_INCLUDED
#define CAD_VIEWER_MODEL_INTERFACE_H_INCLUDED

#include <QObject>

namespace cad_viewer {
class ViewWidget;
class Model;
} // namespace cad_viewer


namespace cad_viewer {

class ModelInterface : public QObject
{
public:
  explicit ModelInterface(QObject* parent = nullptr);

public slots:
  void setCurrentView(ViewWidget* view);

  void createBox(double sx, double sy, double sz);

private:
  Model* currentModel() const;

  ViewWidget* m_cur_view;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_MODEL_INTERFACE_H_INCLUDED
