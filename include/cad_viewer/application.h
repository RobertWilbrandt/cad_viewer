// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-08-06
 *
 */
//----------------------------------------------------------------------
#ifndef CAD_VIEWER_APPLICATION_H_INCLUDED
#define CAD_VIEWER_APPLICATION_H_INCLUDED

#include "cad_viewer/config.h"

#include <QApplication>
#include <QObject>
#include <Standard_Handle.hxx>

class TDocStd_Application;
namespace cad_viewer {
class Document;
} // namespace cad_viewer


namespace cad_viewer {

class Application : public QObject
{
  Q_OBJECT
public:
  explicit Application(int argc, char* argv[]);
  ~Application();

  Application(const Application&)            = delete;
  Application& operator=(const Application&) = delete;

  [[nodiscard]] Config& config();
  [[nodiscard]] const Config& config() const;

  [[nodiscard]] int exec();

signals:
  void documentOpened(Document* document);

  void shutdownRequested();

public slots:
  void newDocument();

  void requestShutdown();

private:
  Config m_config;

  QApplication m_qapp;
  Handle(TDocStd_Application) m_app;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_APPLICATION_H_INCLUDED
