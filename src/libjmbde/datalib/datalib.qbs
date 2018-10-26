import qbs 1.0

Project {
    name: "DataLib"

    QbsDevHeaders { }

    QbsLibrary {
        Depends { name: "Qt.core" }
        Depends { name: "Qt.sql" }
        cpp.defines: base.concat("LIBRARY")

        cpp.includePaths: [
            project.app_source_tree + "/src/",
            project.app_source_tree + "/src/app",
            project.app_source_tree + "/src/libs/utils",
            project.app_source_tree + "/src/libs/utils/models",
            project.app_source_tree + "/src/libs/utils/views",
        ]

        files: [
            "data_global.h",
            "datacontext/datacontext.cpp",
            "datacontext/datacontext.h",
            "datacontext/datacontext.qrc",
            "datacontext/script.sql",
        ]
    }
}
