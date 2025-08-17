// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-08-07
 *
 */
//----------------------------------------------------------------------
#ifndef CAD_VIEWER_TOOL_BAR_MODEL_H_INCLUDED
#define CAD_VIEWER_TOOL_BAR_MODEL_H_INCLUDED

#include <QWidget>

namespace cad_viewer {
class ModelInterface;
}


namespace cad_viewer::tool_bar {

class Model : public QWidget
{
  Q_OBJECT
public:
  explicit Model(ModelInterface* model_interface, QWidget* parent = nullptr);

private slots:
  void primitiveBox();

private:
  ModelInterface* m_model_interface;
};

} // namespace cad_viewer::tool_bar

#endif // CAD_VIEWER_TOOL_BAR_MODEL_H_INCLUDED
