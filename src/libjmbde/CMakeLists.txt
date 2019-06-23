
# List of Sourcefiles
file(GLOB_RECURSE SRCS *.cpp *.ui *.qrc)


add_library(libjmbde SHARED
    ${SRCS}
    )

target_link_libraries( libjmbde
    Qt5::Core
    Qt5::Widgets
    Qt5::PrintSupport
    Qt5::Sql
    Qt5::Help
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickWidgets
    )
