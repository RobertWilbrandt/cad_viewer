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
#include "cad_viewer/tool_bar.h"

#include "cad_viewer/tool_bar/view.h"

#include <QTabWidget>

namespace cad_viewer {

ToolBar::ToolBar(const ViewerConfig* viewer_config, QWidget* parent)
  : QToolBar{parent}
{
  setFloatable(false);
  setMovable(false);

  auto* tab_bar = new QTabWidget{this};

  auto* view_tab = new tool_bar::View{viewer_config, this};
  tab_bar->addTab(view_tab, tr("View"));

  addWidget(tab_bar);
}

} // namespace cad_viewer
