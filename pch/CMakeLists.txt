file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/empty_pch.cpp "/*empty file*/")
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/empty_pch.c "/*empty file*/")

add_library(${TARGET_NAME}pch STATIC ${CMAKE_CURRENT_BINARY_DIR}/empty_pch.cpp
                                     ${CMAKE_CURRENT_BINARY_DIR}/empty_pch.c)
target_precompile_headers(${TARGET_NAME}pch PRIVATE pch.h)
set_target_properties(${TARGET_NAME}pch PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(${TARGET_NAME}pch PRIVATE Qt::Core Qt::Gui Qt::Widgets)
