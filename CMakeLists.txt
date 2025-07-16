cmake_minimum_required(VERSION 3.20)

project(cad_viewer
  VERSION 0.1.0
  LANGUAGES
    CXX
)

# Qt6 Setup
find_package(Qt6 CONFIG REQUIRED
  COMPONENTS
    Core
    Widgets
    OpenGLWidgets
)
qt_standard_project_setup()

add_subdirectory(src)
