qt_add_executable(cad_viewer)

#
# Define sources and headers
#
target_sources(cad_viewer
  PRIVATE
    main.cpp
    main_window.cpp
    view_widget.cpp
)
target_sources(cad_viewer
  PRIVATE
  FILE_SET headers
  TYPE HEADERS
  BASE_DIRS ${CMAKE_SOURCE_DIR}/include
  FILES
    ${CMAKE_SOURCE_DIR}/include/cad_viewer/main_window.h
    ${CMAKE_SOURCE_DIR}/include/cad_viewer/view_widget.h
)

target_link_libraries(cad_viewer
  PRIVATE
    Qt6::Widgets
    Qt6::OpenGLWidgets
)

target_compile_options(cad_viewer
  PRIVATE
    ${CAD_VIEWER_COMPILE_FLAGS}
)
target_link_libraries(cad_viewer
  PRIVATE
    ${CAD_VIEWER_LINK_FLAGS}
)
