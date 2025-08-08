qt_add_executable(cad_viewer)

add_subdirectory(tool_bar)

#
# Define sources and headers
#
target_sources(cad_viewer
  PRIVATE
    application.cpp
    asan.cpp
    config.cpp
    document.cpp
    graphic_driver.cpp
    main.cpp
    main_window.cpp
    object_owner.cpp
    scene.cpp
    scene_browser.cpp
    scene_object.cpp
    scene_viewer.cpp
    tool_bar.cpp
    view_widget.cpp
    viewer_config.cpp
    widget_view_controller.cpp
)
target_sources(cad_viewer
  PRIVATE
  FILE_SET headers
  TYPE HEADERS
  BASE_DIRS ${CMAKE_SOURCE_DIR}/include
  FILES
    ${CMAKE_SOURCE_DIR}/include/cad_viewer/application.h
    ${CMAKE_SOURCE_DIR}/include/cad_viewer/config.h
    ${CMAKE_SOURCE_DIR}/include/cad_viewer/document.h
    ${CMAKE_SOURCE_DIR}/include/cad_viewer/graphic_driver.h
    ${CMAKE_SOURCE_DIR}/include/cad_viewer/main_window.h
    ${CMAKE_SOURCE_DIR}/include/cad_viewer/object_owner.h
    ${CMAKE_SOURCE_DIR}/include/cad_viewer/scene.h
    ${CMAKE_SOURCE_DIR}/include/cad_viewer/scene_browser.h
    ${CMAKE_SOURCE_DIR}/include/cad_viewer/scene_object.h
    ${CMAKE_SOURCE_DIR}/include/cad_viewer/scene_viewer.h
    ${CMAKE_SOURCE_DIR}/include/cad_viewer/tool_bar.h
    ${CMAKE_SOURCE_DIR}/include/cad_viewer/viewer_config.h
    ${CMAKE_SOURCE_DIR}/include/cad_viewer/view_widget.h
    ${CMAKE_SOURCE_DIR}/include/cad_viewer/widget_view_controller.h
)

# Target_include_directories(cad_viewer
#   PRIVATE
#     ${OpenCASCADE_INCLUDE_DIR}
# )
target_link_libraries(cad_viewer
  PRIVATE
    Qt6::Widgets
    Qt6::OpenGLWidgets
    TKOpenGl
    TKV3d
    TKernel
    TKStd
)
target_compile_features(cad_viewer
  PRIVATE
    cxx_std_20
    c_std_17
)

target_compile_options(cad_viewer
  PRIVATE
    ${CAD_VIEWER_COMPILE_FLAGS}
)
target_link_libraries(cad_viewer
  PRIVATE
    ${CAD_VIEWER_LINK_FLAGS}
)

set_target_properties(cad_viewer
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
