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

#include "cad_viewer/scene.h"
#include "cad_viewer/scene_object.h"

namespace cad_viewer {

SceneBrowserModel::SceneBrowserModel(const Scene& scene, QObject* parent)
  : QAbstractItemModel{parent}
{
  QObject::connect(&scene, &Scene::objectAdded, this, &SceneBrowserModel::addObject);
  for (auto* scene_object : scene.sceneObjects())
  {
    switch (scene_object->objectType())
    {
      case SceneObject::ObjectTypeConstruction:
        m_construction_objects.push_back(scene_object);
        break;

      default:
        break;
    }
  }
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

void SceneBrowserModel::addObject(SceneObject* object) {}

SceneBrowser::SceneBrowser(const Scene& scene, QWidget* parent)
  : QTreeView{parent}
{
  auto* model = new SceneBrowserModel{scene, this};
  setModel(model);

  setHeaderHidden(true);
}

} // namespace cad_viewer
