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

#include "cad_viewer/config.h"
#include "cad_viewer/tool_bar/model.h"
#include "cad_viewer/tool_bar/view.h"

#include <QTabWidget>

namespace cad_viewer {

ToolBar::ToolBar(ModelInterface* model_interface, const Config* config, QWidget* parent)
  : QToolBar{parent}
{
  setFloatable(false);
  setMovable(false);

  auto* tab_bar = new QTabWidget{this};
  tab_bar->addTab(new tool_bar::Model{model_interface, this}, tr("&Model"));
  tab_bar->addTab(new tool_bar::View{config->viewer(), this}, tr("&View"));

  addWidget(tab_bar);
}

} // namespace cad_viewer
