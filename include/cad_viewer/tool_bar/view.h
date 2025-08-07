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
#ifndef CAD_VIEWER_TOOL_BAR_VIEW_H_INCLUDED
#define CAD_VIEWER_TOOL_BAR_VIEW_H_INCLUDED

#include "cad_viewer/viewer_config.h"

#include <QWidget>

class QCheckBox;
class QComboBox;

namespace cad_viewer::tool_bar {

class View : public QWidget
{
  Q_OBJECT
public:
  explicit View(const ViewerConfig* config, QWidget* parent = nullptr);

signals:
  void gridTypeSelectionChanged(ViewerConfig::GridType grid_type);

private slots:
  void activateGridCbChanged(Qt::CheckState state);
  void gridTypeCbIndexChanged(int index);

private:
  const ViewerConfig* m_config;

  QCheckBox* m_activate_grid_cb;
  QComboBox* m_grid_type_selection_cb;
};

} // namespace cad_viewer::tool_bar

#endif // CAD_VIEWER_TOOL_BAR_VIEW_H_INCLUDED
