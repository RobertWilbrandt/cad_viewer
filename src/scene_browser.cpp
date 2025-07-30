// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-07-30
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/scene_browser.h"

namespace cad_viewer {

SceneBrowserModel::SceneBrowserModel(QObject* parent)
  : QAbstractItemModel{parent}
{
}

QModelIndex SceneBrowserModel::index(int row, int column, const QModelIndex& parent) const
{
  if (!hasIndex(row, column, parent))
  {
    return QModelIndex{};
  }

  if (parent.isValid())
  {
    return QModelIndex{};
  }

  if (row == 0)
  {
    return createIndex(row, column, nullptr);
  }

  return QModelIndex{};
}

QModelIndex SceneBrowserModel::parent(const QModelIndex& index) const
{
  return QModelIndex{};
}

int SceneBrowserModel::rowCount(const QModelIndex& parent) const
{
  if (parent.isValid())
  {
    return 0;
  }

  return 1;
}

int SceneBrowserModel::columnCount(const QModelIndex& parent) const
{
  return 1;
}

QVariant SceneBrowserModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
  {
    return QVariant{};
  }

  switch (role)
  {
    case Qt::DisplayRole:
      return QString::fromLocal8Bit("Test");

    default:
      return QVariant{};
  }
}

SceneBrowser::SceneBrowser(QWidget* parent)
  : QTreeView{parent}
{
  auto* model = new SceneBrowserModel{this};
  setModel(model);

  setHeaderHidden(true);
}

} // namespace cad_viewer
