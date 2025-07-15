// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-07-15
 *
 */
//----------------------------------------------------------------------
#include <QApplication>
#include <iostream>

int main(int argc, char* argv[]) {
  QApplication app{argc, argv};
  std::cout << "Hello World!" << std::endl;

  return app.exec();
}
