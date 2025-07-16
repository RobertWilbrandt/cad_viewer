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
#ifndef CAD_VIEWER_VIEW_WIDGET_H_INCLUDED
#define CAD_VIEWER_VIEW_WIDGET_H_INCLUDED

#include <QOpenGLWidget>

namespace cad_viewer {

class ViewWidget : public QOpenGLWidget
{
  Q_OBJECT
public:
  explicit ViewWidget(QWidget* parent = nullptr);

private:
};

} // namespace cad_viewer

#endif // CAD_VIEWER_VIEW_WIDGET_H_INCLUDED
