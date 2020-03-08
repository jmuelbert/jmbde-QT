add_library(qtsingleapplication-lib STATIC "")
add_library(jmbde::qtsingleapp ALIAS qtsingleapplication-lib)

#
# Finding Qt
#
find_package(Qt5 ${QT_MIN_VERSION} 
    QUIET 
    REQUIRED
    COMPONENTS
    Core
    Network
    Widgets
)

include(GenerateExportHeader)

generate_export_header(
    qtsingleapplication-lib
    EXPORT_FILE_NAME qtsingleapplication_export.h
    EXPORT_MACRO_NAME QTSINGLEAPPLICATION_EXPORT
)

target_include_directories(
    qtsingleapplication-lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(
    qtsingleapplication-lib
    PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
)

# Use a single application on MacOS + Windows instead of dbus.
if(APPLE OR WIN32)

    target_sources(
        qtsingleapplication-lib  
        PRIVATE
        src/qtlocalpeer.cpp
        src/qtsingleapplication.cpp
        src/qtlockedfile.cpp             
    )

    if(WIN32)
        target_sources(qtsingleapplication-lib PRIVATE src/qtlockedfile_win.cpp)
    else()
        target_sources(qtsingleapplication-lib PRIVATE src/qtlockedfile_unix.cpp)        
    endif()
endif()
