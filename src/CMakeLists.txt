qt_add_executable(cad_viewer)

target_sources(cad_viewer
  PRIVATE
    main.cpp
)
target_link_libraries(cad_viewer
  PRIVATE
    Qt6::Widgets
)
