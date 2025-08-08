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
#include "cad_viewer/view_widget.h"

#include "cad_viewer/graphic_driver.h"
#include "cad_viewer/scene_viewer.h"
#include "cad_viewer/widget_view_controller.h"

#include <AIS_InteractiveContext.hxx>
#include <AIS_ViewCube.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Aspect_NeutralWindow.hxx>
#include <Graphic3d_Vec2.hxx>
#include <OpenGl_Context.hxx>
#include <OpenGl_FrameBuffer.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <QMouseEvent>
#include <QOpenGLContext>
#include <QSurfaceFormat>
#include <QWheelEvent>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>

class OcctQtFrameBuffer : public OpenGl_FrameBuffer
{
  DEFINE_STANDARD_RTTI_INLINE(OcctQtFrameBuffer, OpenGl_FrameBuffer)
public:
  void BindBuffer(const Handle(OpenGl_Context) & theGlCtx) override
  {
    OpenGl_FrameBuffer::BindBuffer(theGlCtx);
    theGlCtx->SetFrameBufferSRGB(true, false);
  }

  void BindDrawBuffer(const Handle(OpenGl_Context) & theGlCtx) override
  {
    OpenGl_FrameBuffer::BindDrawBuffer(theGlCtx);
    theGlCtx->SetFrameBufferSRGB(true, false);
  }

  void BindReadBuffer(const Handle(OpenGl_Context) & theGlCtx) override
  {
    OpenGl_FrameBuffer::BindReadBuffer(theGlCtx);
  }
};

namespace cad_viewer {

ViewWidget::ViewWidget(Config* config, QWidget* parent)
  : QOpenGLWidget{parent}
  , m_config{config}
  , m_view_controller{std::make_shared<WidgetViewController>(this)}
{
  // Widget setup
  setMouseTracking(true);
  setBackgroundRole(QPalette::NoRole);
  setFocusPolicy(Qt::StrongFocus);
  setUpdatesEnabled(true);
  setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);

  setAttribute(Qt::WA_NativeWindow); // Make sure winId() returns a valid handle later on
}

void ViewWidget::initializeGL()
{
  m_graphic_driver          = std::make_shared<GraphicDriver>();
  Handle(V3d_Viewer) viewer = new V3d_Viewer{m_graphic_driver->driver()};
  viewer->SetDefaultBackgroundColor(Quantity_NOC_LIGHTGRAY);
  viewer->SetDefaultLights();
  viewer->SetLightOn();


  m_view = viewer->CreateView();
  m_view->SetImmediateUpdate(false);

  m_context = new AIS_InteractiveContext{viewer};
  m_viewer  = new SceneViewer{viewer, m_context, m_config, this};
  QObject::connect(m_viewer, &SceneViewer::viewUpdateRequested, this, &ViewWidget::updateView);

  const auto cur_rect = rect();

  Handle(OpenGl_Context) gl_context = new OpenGl_Context{};
  if (!gl_context->Init(false))
  {
    throw std::runtime_error{"Cannot wrap OpenGL Context"};
  }

  const auto native_handle = static_cast<Aspect_Drawable>(winId());
  auto window              = Handle(Aspect_NeutralWindow)::DownCast(m_view->Window());
  if (window.IsNull())
  {
    window = new Aspect_NeutralWindow{};
    window->SetVirtual(true);
  }

  window->SetSize(cur_rect.right() - cur_rect.left(), cur_rect.bottom() - cur_rect.top());
  window->SetNativeHandle(native_handle);
  m_view->SetWindow(window, gl_context->RenderingContext());

  // Create view cube
  m_context->Display(createDefaultViewCube(), 0, 0, false);
}

void ViewWidget::paintGL()
{
  if (m_view.IsNull())
  {
    return;
  }

  const auto native_handle = static_cast<Aspect_Drawable>(winId());
  if (m_view->Window()->NativeHandle() != native_handle)
  {
    initializeGL();
    return;
  }

  auto graphic_driver = Handle(OpenGl_GraphicDriver)::DownCast(m_view->Viewer()->Driver());
  Handle(OpenGl_Context) context          = graphic_driver->GetSharedContext();
  Handle(OpenGl_FrameBuffer) frame_buffer = context->DefaultFrameBuffer();
  if (frame_buffer.IsNull())
  {
    frame_buffer = new OcctQtFrameBuffer{};
    context->SetDefaultFrameBuffer(frame_buffer);
  }

  if (!frame_buffer->InitWrapper(context))
  {
    throw std::runtime_error{"Could not initialize fbo wrapper"};
  }

  // Check for changing size
  const auto view_size_cur = frame_buffer->GetVPSize();
  Graphic3d_Vec2i view_size_old;
  auto window = Handle(Aspect_NeutralWindow)::DownCast(m_view->Window());
  window->Size(view_size_old.x(), view_size_old.y());
  if (view_size_cur != view_size_old)
  {
    window->SetSize(view_size_cur.x(), view_size_cur.y());
    m_view->MustBeResized();
    m_view->Invalidate();
  }

  m_view->InvalidateImmediate();
  m_view_controller->FlushViewEvents(m_context, m_view, true);
}

void ViewWidget::cleanup()
{
  if (m_view.IsNull())
  {
    return;
  }

  makeCurrent();

  m_view->Remove();
  m_view.Nullify();

  m_context.Nullify();

  doneCurrent();
}

void ViewWidget::updateView()
{
  update();
}

Handle(AIS_ViewCube) ViewWidget::createDefaultViewCube() const
{
  Handle(AIS_ViewCube) result = new AIS_ViewCube{};
  result->SetViewAnimation(m_view_controller->ViewAnimation());
  result->SetFixedAnimationLoop(false);
  result->SetAutoStartAnimation(true);
  return result;
}

void ViewWidget::mousePressEvent(QMouseEvent* event)
{
  QOpenGLWidget::mousePressEvent(event);
  if (m_view.IsNull())
  {
    return;
  }

  if (m_view_controller->UpdateMouseButtons(
        mousePosition(event), convert(event->buttons()), convert(event->modifiers()), false))
  {
    update();
  }
}

void ViewWidget::mouseReleaseEvent(QMouseEvent* event)
{
  QOpenGLWidget::mouseReleaseEvent(event);
  if (m_view.IsNull())
  {
    return;
  }

  if (m_view_controller->UpdateMouseButtons(
        mousePosition(event), convert(event->buttons()), convert(event->modifiers()), false))
  {
    update();
  }
}

void ViewWidget::mouseMoveEvent(QMouseEvent* event)
{
  QOpenGLWidget::mouseMoveEvent(event);
  if (m_view.IsNull())
  {
    return;
  }

  if (m_view_controller->UpdateMousePosition(
        mousePosition(event), convert(event->buttons()), convert(event->modifiers()), false))
  {
    update();
  }
}

void ViewWidget::wheelEvent(QWheelEvent* event)
{
  QOpenGLWidget::wheelEvent(event);
  if (m_view.IsNull())
  {
    return;
  }

  if (m_view_controller->UpdateZoom(
        Aspect_ScrollDelta{mousePosition(event), event->angleDelta().y() / 8.0}))
  {
    update();
  }
}

Graphic3d_Vec2i ViewWidget::mousePosition(QSinglePointEvent* event) const
{
  return Graphic3d_Vec2i{static_cast<int>(event->position().x()),
                         static_cast<int>(event->position().y())};
}

Aspect_VKeyMouse ViewWidget::convert(Qt::MouseButtons buttons) const
{
  Aspect_VKeyMouse result = Aspect_VKeyMouse_NONE;
  if ((buttons & Qt::LeftButton) != 0)
  {
    result |= Aspect_VKeyMouse_LeftButton;
  }
  if ((buttons & Qt::MiddleButton) != 0)
  {
    result |= Aspect_VKeyMouse_MiddleButton;
  }
  if ((buttons & Qt::RightButton) != 0)
  {
    result |= Aspect_VKeyMouse_RightButton;
  }

  return result;
}

Aspect_VKeyFlags ViewWidget::convert(Qt::KeyboardModifiers modifiers) const
{
  Aspect_VKeyFlags result = Aspect_VKeyFlags_NONE;
  if ((modifiers & Qt::ShiftModifier) != 0)
  {
    result |= Aspect_VKeyFlags_SHIFT;
  }
  if ((modifiers & Qt::ControlModifier) != 0)
  {
    result |= Aspect_VKeyFlags_CTRL;
  }
  if ((modifiers & Qt::AltModifier) != 0)
  {
    result |= Aspect_VKeyFlags_ALT;
  }

  return result;
}

} // namespace cad_viewer
