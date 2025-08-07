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
#include "cad_viewer/tool_bar/view.h"

#include "cad_viewer/viewer_config.h"

#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>

namespace cad_viewer::tool_bar {

View::View(const ViewerConfig* config, QWidget* parent)
  : QWidget{parent}
  , m_config{config}
{
  auto* layout = new QHBoxLayout{this};
  setLayout(layout);

  m_activate_grid_cb = new QCheckBox{this};
  m_activate_grid_cb->setChecked(m_config->gridType() != ViewerConfig::GridTypeNone);
  QObject::connect(
    m_activate_grid_cb, &QCheckBox::checkStateChanged, this, &View::activateGridCbChanged);
  layout->addWidget(m_activate_grid_cb);

  m_grid_type_selection_cb = new QComboBox{this};
  m_grid_type_selection_cb->addItem("Grid",
                                    QVariant{static_cast<int>(ViewerConfig::GridTypeRectangular)});
  m_grid_type_selection_cb->addItem("Circular",
                                    QVariant{static_cast<int>(ViewerConfig::GridTypeCircular)});
  m_grid_type_selection_cb->setDisabled(m_config->gridType() == ViewerConfig::GridTypeNone);
  if (m_config->gridType() != ViewerConfig::GridTypeNone)
  {
    if (const auto grid_type_i =
          m_grid_type_selection_cb->findData(QVariant{static_cast<int>(m_config->gridType())});
        grid_type_i >= 0)
    {
      m_grid_type_selection_cb->setCurrentIndex(grid_type_i);
    }
  }

  QObject::connect(
    m_grid_type_selection_cb, &QComboBox::currentIndexChanged, this, &View::gridTypeCbIndexChanged);
  layout->addWidget(m_grid_type_selection_cb);

  QObject::connect(this, &View::gridTypeSelectionChanged, m_config, &ViewerConfig::setGridType);
}

void View::activateGridCbChanged(Qt::CheckState state)
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

void View::gridTypeCbIndexChanged(int index)
{
  if (m_activate_grid_cb->checkState() != Qt::Checked)
  {
    return;
  }

  emit gridTypeSelectionChanged(
    static_cast<ViewerConfig::GridType>(m_grid_type_selection_cb->currentData().toInt()));
}

} // namespace cad_viewer::tool_bar
