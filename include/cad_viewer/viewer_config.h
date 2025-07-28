// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-07-28
 *
 */
//----------------------------------------------------------------------
#ifndef CAD_VIEWER_VIEWER_CONFIG_H_INCLUDED
#define CAD_VIEWER_VIEWER_CONFIG_H_INCLUDED

#include <QObject>

namespace cad_viewer {

class ViewerConfig : public QObject
{
  Q_OBJECT

  Q_PROPERTY(GridType gridType READ gridType WRITE setGridType NOTIFY gridTypeChanged)
public:
  explicit ViewerConfig(QObject* parent = nullptr);

  enum GridType
  {
    GridTypeNone,
    GridTypeRectangular,
    GridTypeCircular
  };
  Q_ENUM(GridType);

  [[nodiscard]] GridType gridType() const;

signals:
  void gridTypeChanged(GridType grid_type);

public slots:
  void setGridType(GridType grid_type);

private:
  GridType m_grid_type = GridType::GridTypeRectangular;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_VIEWER_CONFIG_H_INCLUDED
