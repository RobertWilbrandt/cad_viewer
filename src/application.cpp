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
#include "cad_viewer/application.h"

#include "cad_viewer/document.h"

#include <TDocStd_Application.hxx>
#include <TDocStd_Document.hxx>

namespace cad_viewer {

Application::Application(int argc, char* argv[])
  : m_qapp{argc, argv}
  , m_app{new TDocStd_Application{}}
{
}

Config& Application::config()
{
  return m_config;
}

const Config& Application::config() const
{
  return m_config;
}

int Application::exec()
{
  return m_qapp.exec();
}

void Application::newDocument()
{
  Handle(TDocStd_Document) document;
  m_app->NewDocument("", document);

  auto* new_document = new Document{document, &m_qapp};
  emit documentOpened(new_document);
}

void Application::requestShutdown()
{
  emit shutdownRequested();
}

} // namespace cad_viewer
