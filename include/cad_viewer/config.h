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
#ifndef CAD_VIEWER_CONFIG_H_INCLUDED
#define CAD_VIEWER_CONFIG_H_INCLUDED

#include <QObject>

namespace cad_viewer {
class ViewerConfig;
}


namespace cad_viewer {

class Config : public QObject
{
public:
  explicit Config(QObject* parent = nullptr);

  [[nodiscard]] ViewerConfig* viewer() const;

private:
  ViewerConfig* m_viewer_config;
};

} // namespace cad_viewer

#endif // CAD_VIEWER_CONFIG_H_INCLUDED
