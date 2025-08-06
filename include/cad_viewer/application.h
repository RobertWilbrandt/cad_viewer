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

#include <QApplication>

namespace cad_viewer {

class Application
{
public:
  explicit Application(int argc, char* argv[]);

  [[nodiscard]] int exec();

private:
  QApplication m_app;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_APPLICATION_H_INCLUDED
