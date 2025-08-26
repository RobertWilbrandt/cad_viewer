// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-08-08
 *
 */
//----------------------------------------------------------------------
#ifndef CAD_VIEWER_MODEL_H_INCLUDED
#define CAD_VIEWER_MODEL_H_INCLUDED

#include <QObject>
#include <QString>
#include <Standard_Handle.hxx>
#include <TDF_Label.hxx>

class TDF_Data;
class TopoDS_Solid;


namespace cad_viewer {

class Model : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
  explicit Model(Handle(TDF_Data) data, QObject* parent = nullptr);

  [[nodiscard]] QString name() const;
  void setName(const QString& name);

  TDF_Label main() const;

signals:
  void nameChanged(const QString&);
  void shapeAdded(TDF_Label label);

public slots:
  void createBox(double sx, double sy, double sz);

private:
  void createOrigin(const TDF_Label& label);
  void setProperty(const TDF_Label& label, const std::string& name, double value);

  Handle(TDF_Data) m_data;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_MODEL_H_INCLUDED
