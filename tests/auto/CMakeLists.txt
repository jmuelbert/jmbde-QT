include_directories(../../src/libjmbde/)

add_executable(uitest
        ui/tst_employeeinputarea.cpp
)

find_package(Qt5Test REQUIRED)


target_compile_definitions(uitest PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(uitest PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Sql
    Qt5::Network
    Qt5::PrintSupport
    Qt5::Help
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickWidgets
    Qt5::Test
    libjmbde
    )
