// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-07-21
 *
 */
//----------------------------------------------------------------------
#ifndef CAD_VIEWER_TOOL_BAR_H_INCLUDED
#define CAD_VIEWER_TOOL_BAR_H_INCLUDED

#include <QToolBar>

namespace cad_viewer {
class Config;
class ModelInterface;
} // namespace cad_viewer

namespace cad_viewer {

class ToolBar : public QToolBar
{
  Q_OBJECT
public:
  explicit ToolBar(ModelInterface* model_interface,
                   const Config* config,
                   QWidget* parent = nullptr);
};

} // namespace cad_viewer

#endif // CAD_VIEWER_TOOL_BAR_H_INCLUDED
