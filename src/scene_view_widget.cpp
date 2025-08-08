// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Robert Wilbrandt <robert@stamm-wilbrandt.de>
 * \date    2025-07-20
 *
 */
//----------------------------------------------------------------------
#include "cad_viewer/scene_view_widget.h"

#include "cad_viewer/graphic_driver.h"
#include "cad_viewer/scene.h"
#include "cad_viewer/view_widget.h"
#include "cad_viewer/widget_view_controller.h"

#include <AIS_InteractiveContext.hxx>
#include <AIS_ViewCube.hxx>
#include <QVBoxLayout>
#include <V3d_View.hxx>

namespace cad_viewer {

SceneViewWidget::SceneViewWidget(Handle(V3d_View) view,
                                 Handle(AIS_InteractiveContext) context,
                                 QWidget* parent)
  : QWidget{parent}
  , m_view{std::move(view)}
{
  // m_view_widget = new ViewWidget{m_view, context};

  auto* layout = new QVBoxLayout{this};
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(m_view_widget);
  setLayout(layout);

  m_view_cube = createDefaultViewCube();
  context->Display(m_view_cube, 0, 0, false);
}

SceneViewWidget::~SceneViewWidget()
{
  if (m_view_widget == nullptr)
  {
    return;
  }

  m_view_widget->makeCurrent();

  m_view_widget->cleanup();
  m_view.Nullify();

  m_view_widget->doneCurrent();
}

void SceneViewWidget::updateView()
{
  if (m_view_widget != nullptr)
  {
    m_view_widget->update();
  }
}

Handle(AIS_ViewCube) SceneViewWidget::createDefaultViewCube() const
{
  Handle(AIS_ViewCube) result = new AIS_ViewCube{};
  result->SetViewAnimation(m_view_widget->cameraAnimation());
  result->SetFixedAnimationLoop(false);
  result->SetAutoStartAnimation(true);
  return result;
}

} // namespace cad_viewer
