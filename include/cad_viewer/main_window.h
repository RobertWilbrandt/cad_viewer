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

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget* parent = nullptr);

signals:
  void closeRequestReceived();

protected:
  void closeEvent(QCloseEvent* event) override;

private:
  void createMenus();

private slots:
  void exit();
};

} // namespace cad_viewer

#endif // CAD_VIEWER_MAIN_WINDOW_H_INCLUDED
