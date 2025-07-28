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

ToolBar::ToolBar(const ViewerConfig* viewer_config, QWidget* parent)
  : QToolBar{parent}
{
  setFloatable(false);
  setMovable(false);

  auto* tab_bar = new QTabWidget{this};

  auto* view_tab = createViewTab(viewer_config);
  tab_bar->addTab(view_tab, tr("View"));

  addWidget(tab_bar);

  QObject::connect(
    this, &ToolBar::gridTypeSelectionChanged, viewer_config, &ViewerConfig::setGridType);
}

void ToolBar::activateGridCbChanged(Qt::CheckState state)
{
  switch (state)
  {
    case Qt::Checked:
      m_grid_type_selection_cb->setDisabled(false);
      emit gridTypeSelectionChanged(
        static_cast<ViewerConfig::GridType>(m_grid_type_selection_cb->currentData().toInt()));
      break;

    case Qt::Unchecked:
      m_grid_type_selection_cb->setDisabled(true);
      emit gridTypeSelectionChanged(ViewerConfig::GridTypeNone);
      break;

    default:
      break;
  }
}

void ToolBar::gridTypeCbIndexChanged(int index)
{
  if (m_activate_grid_cb->checkState() != Qt::Checked)
  {
    return;
  }

  emit gridTypeSelectionChanged(
    static_cast<ViewerConfig::GridType>(m_grid_type_selection_cb->currentData().toInt()));
}

QWidget* ToolBar::createViewTab(const ViewerConfig* viewer_config)
{
  auto* tab = new QWidget{};

  auto* layout = new QHBoxLayout{tab};
  tab->setLayout(layout);

  m_activate_grid_cb = new QCheckBox{tab};
  m_activate_grid_cb->setChecked(viewer_config->gridType() != ViewerConfig::GridTypeNone);
  QObject::connect(
    m_activate_grid_cb, &QCheckBox::checkStateChanged, this, &ToolBar::activateGridCbChanged);
  layout->addWidget(m_activate_grid_cb);

  m_grid_type_selection_cb = new QComboBox{tab};
  m_grid_type_selection_cb->addItem("Grid",
                                    QVariant{static_cast<int>(ViewerConfig::GridTypeRectangular)});
  m_grid_type_selection_cb->addItem("Circular",
                                    QVariant{static_cast<int>(ViewerConfig::GridTypeCircular)});
  m_grid_type_selection_cb->setDisabled(viewer_config->gridType() == ViewerConfig::GridTypeNone);
  if (viewer_config->gridType() != ViewerConfig::GridTypeNone)
  {
    if (const auto grid_type_i =
          m_grid_type_selection_cb->findData(QVariant{static_cast<int>(viewer_config->gridType())});
        grid_type_i >= 0)
    {
      m_grid_type_selection_cb->setCurrentIndex(grid_type_i);
    }
  }

  QObject::connect(m_grid_type_selection_cb,
                   &QComboBox::currentIndexChanged,
                   this,
                   &ToolBar::gridTypeCbIndexChanged);
  layout->addWidget(m_grid_type_selection_cb);

  return tab;
}

} // namespace cad_viewer
