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

#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QTabWidget>

namespace cad_viewer {

ToolBar::ToolBar(QWidget* parent)
  : QToolBar{parent}
{
  setFloatable(false);
  setMovable(false);

  auto* tab_bar = new QTabWidget{this};

  auto* view_tab = createViewTab();
  tab_bar->addTab(view_tab, tr("View"));

  addWidget(tab_bar);
}

void ToolBar::activateGridCbChanged(Qt::CheckState state)
{
  switch (state)
  {
    case Qt::Checked:
      m_grid_type_selection_cb->setDisabled(false);
      break;

    case Qt::Unchecked:
      m_grid_type_selection_cb->setDisabled(true);
      break;

    default:
      break;
  }
}

QWidget* ToolBar::createViewTab()
{
  auto* tab = new QWidget{};

  auto* layout = new QHBoxLayout{tab};
  tab->setLayout(layout);

  auto* activate_grid_cb = new QCheckBox{tab};
  activate_grid_cb->setChecked(true);
  QObject::connect(
    activate_grid_cb, &QCheckBox::checkStateChanged, this, &ToolBar::activateGridCbChanged);
  layout->addWidget(activate_grid_cb);

  m_grid_type_selection_cb = new QComboBox{tab};
  m_grid_type_selection_cb->addItem("Grid");
  m_grid_type_selection_cb->addItem("Circular");
  layout->addWidget(m_grid_type_selection_cb);

  return tab;
}

} // namespace cad_viewer
