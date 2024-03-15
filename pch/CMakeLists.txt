file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/empty_pch.cpp "/*empty file*/")
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/empty_pch.c "/*empty file*/")

add_library(${PCH_TARGET_NAME} STATIC ${CMAKE_CURRENT_BINARY_DIR}/empty_pch.cpp
                                      ${CMAKE_CURRENT_BINARY_DIR}/empty_pch.c)
target_precompile_headers(${PCH_TARGET_NAME} PRIVATE pch.h)
set_target_properties(${PCH_TARGET_NAME} PROPERTIES POSITION_INDEPENDENT_CODE
                                                    ON)
target_link_libraries(${PCH_TARGET_NAME} PRIVATE Qt::Core Qt::Gui Qt::Widgets)
