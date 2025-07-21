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

#include "scene_view_widget.h"

#include <QToolBar>

class QComboBox;
class QCheckBox;

namespace cad_viewer {

class ToolBar : public QToolBar
{
  Q_OBJECT
public:
  explicit ToolBar(QWidget* parent = nullptr);

signals:
  void gridTypeSelectionChanged(SceneViewWidget::GridType grid_type);

private slots:
  void activateGridCbChanged(Qt::CheckState state);
  void gridTypeCbIndexChanged(int index);

private:
  QWidget* createViewTab();

  QCheckBox* m_activate_grid_cb;
  QComboBox* m_grid_type_selection_cb;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_TOOL_BAR_H_INCLUDED
