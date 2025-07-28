// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-07-16
 *
 */
//----------------------------------------------------------------------
#ifndef CAD_VIEWER_MAIN_WINDOW_H_INCLUDED
#define CAD_VIEWER_MAIN_WINDOW_H_INCLUDED

#include <QMainWindow>

class QCloseEvent;

namespace cad_viewer {

class GraphicDriver;

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(GraphicDriver* graphic_driver, QWidget* parent = nullptr);

signals:
  void closeRequestReceived();

protected:
  void closeEvent(QCloseEvent* event) override;

private:
  GraphicDriver* m_graphic_driver;

  void createMenus();

private slots:
  void exit();
};

} // namespace cad_viewer

#endif // CAD_VIEWER_MAIN_WINDOW_H_INCLUDED
