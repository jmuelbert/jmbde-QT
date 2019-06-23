add_executable(jmbdequick
    main.cpp
    qml/qml.qrc
)

target_compile_definitions(jmbdequick PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(jmbdequick PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Sql
    Qt5::Network
    Qt5::PrintSupport
    Qt5::Help
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickWidgets
    )
