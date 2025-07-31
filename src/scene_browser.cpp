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
    switch (static_cast<SceneObject::ObjectType>(parent.row()))
    {
      case SceneObject::ObjectTypeConstruction:
        return createIndex(row, column, m_construction_objects[static_cast<std::size_t>(row)]);

      default:
        return QModelIndex{};
    }
  }

  if (row == 0)
  {
    return createIndex(row, column, nullptr);
  }

  return QModelIndex{};
}

QModelIndex SceneBrowserModel::parent(const QModelIndex& index) const
{
  const void* data = index.constInternalPointer();
  if (data != nullptr)
  {
    const auto* scene_object = static_cast<const SceneObject*>(data);
    return createIndex(static_cast<int>(scene_object->objectType()), 0, nullptr);
  }
  return QModelIndex{};
}

int SceneBrowserModel::rowCount(const QModelIndex& parent) const
{
  if (parent.isValid())
  {
    const void* ptr = parent.constInternalPointer();
    if (ptr == nullptr)
    {
      switch (static_cast<SceneObject::ObjectType>(parent.row()))
      {
        case SceneObject::ObjectTypeConstruction:
          return static_cast<int>(m_construction_objects.size());

        default:
          return 0;
      }
    }
    else
    {
      return 0;
    }
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

  const void* ptr = index.constInternalPointer();
  if (ptr == nullptr)
  {
    switch (role)
    {
      case Qt::DisplayRole:
        switch (index.row())
        {
          case 0:
            return QString::fromLocal8Bit("Construction");

          default:
            return QVariant{};
        }

      default:
        return QVariant{};
    }
  }

  const auto* scene_object = static_cast<const SceneObject*>(ptr);
  switch (role)
  {
    case Qt::DisplayRole:
      return scene_object->name();

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
