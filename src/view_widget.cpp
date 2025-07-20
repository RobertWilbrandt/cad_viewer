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

#include <AIS_InteractiveContext.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Aspect_NeutralWindow.hxx>
#include <Graphic3d_Vec2.hxx>
#include <OpenGl_Context.hxx>
#include <OpenGl_FrameBuffer.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <QOpenGLContext>
#include <QSurfaceFormat>
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

ViewWidget::ViewWidget(const Handle(V3d_View) & view, QWidget* parent)
  : QOpenGLWidget{parent}
  , m_view{view}
{
  // Widget setup
  setMouseTracking(true);
  setBackgroundRole(QPalette::NoRole);
  setFocusPolicy(Qt::StrongFocus);
  setUpdatesEnabled(true);
  setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);

  // Set surface format
  QSurfaceFormat format{};
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  format.setProfile(QSurfaceFormat::CompatibilityProfile);
  setFormat(format);

  setAttribute(Qt::WA_NativeWindow); // Make sure winId() returns a valid handle later on
}

void ViewWidget::initializeGL()
{
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
}

void ViewWidget::paintGL()
{
  std::cerr << "paintGL" << std::endl;
  if (m_view.IsNull())
  {
    return;
  }

  const auto native_handle = static_cast<Aspect_Drawable>(winId());
  if (m_view->Window()->NativeHandle() != native_handle)
  {
    std::cerr << "Native window change!" << std::endl;
    initializeGL();
    return;
  }

  auto graphic_driver = Handle(OpenGl_GraphicDriver)::DownCast(m_view->Viewer()->Driver());
  Handle(OpenGl_Context) context          = graphic_driver->GetSharedContext();
  Handle(OpenGl_FrameBuffer) frame_buffer = context->DefaultFrameBuffer();
  if (frame_buffer.IsNull())
  {
    std::cerr << "Creating new FBO" << std::endl;
    frame_buffer = new OcctQtFrameBuffer{};
    context->SetDefaultFrameBuffer(frame_buffer);
  }
  else
  {
    std::cerr << "No new FBO needed" << std::endl;
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
  m_view->Redraw();
}

void ViewWidget::cleanup()
{
  m_view->Remove();
  m_view.Nullify();
}

} // namespace cad_viewer
