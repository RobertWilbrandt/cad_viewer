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

#if defined(__SANITIZE_ADDRESS__)

extern "C" const char* __lsan_default_suppressions()
{
  return "leak:OpenGl_View::prepareFrameBuffers\n"
         "leak:OpenGl_FrameBuffer::OpenGl_FrameBuffer";
}

#endif
