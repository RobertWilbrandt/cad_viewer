cmake_minimum_required(VERSION 3.20)

project(cad_viewer
  VERSION 0.1.0
  LANGUAGES
    CXX
)

#
# Build options
#
option(ASAN "Enable address sanitizer" OFF)

if (ASAN)
  set(CAD_VIEWER_COMPILE_FLAGS "${CAD_VIEWER_COMPILE_FLAGS};-fsanitize=address")
  set(CAD_VIEWER_LINK_FLAGS "${CAD_VIEWER_COMPILE_FLAGS};-fsanitize=address")
endif()

# Qt6 Setup
find_package(Qt6 CONFIG REQUIRED
  COMPONENTS
    Core
    Widgets
    OpenGLWidgets
)
qt_standard_project_setup()

# OpenCASCADE setup
find_package(OpenCASCADE CONFIG REQUIRED)

add_subdirectory(src)
