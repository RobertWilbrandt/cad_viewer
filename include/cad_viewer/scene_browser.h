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
#ifndef CAD_VIEWER_SCENE_BROWSER_H_INCLUDED
#define CAD_VIEWER_SCENE_BROWSER_H_INCLUDED

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QTreeView>

class QWidget;

namespace cad_viewer {

class SceneBrowserModel : public QAbstractItemModel
{
  Q_OBJECT
public:
  explicit SceneBrowserModel(QObject* parent = nullptr);

  QModelIndex index(int row, int column, const QModelIndex& parent) const override;
  QModelIndex parent(const QModelIndex& index) const override;

  int rowCount(const QModelIndex& parent) const override;
  int columnCount(const QModelIndex& parent) const override;

  QVariant data(const QModelIndex& index, int role) const override;

private:
};

class SceneBrowser : public QTreeView
{
public:
  explicit SceneBrowser(QWidget* parent = nullptr);

private:
};

} // namespace cad_viewer

#endif // CAD_VIEWER_SCENE_BROWSER_H_INCLUDED
