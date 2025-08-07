target_sources(cad_viewer
  PRIVATE
    view.cpp
)

target_sources(cad_viewer
  PRIVATE
  FILE_SET headers
  TYPE HEADERS
  BASE_DIRS ${CMAKE_SOURCE_DIR}/include
  FILES
    ${CMAKE_SOURCE_DIR}/include/cad_viewer/tool_bar/view.h
)
