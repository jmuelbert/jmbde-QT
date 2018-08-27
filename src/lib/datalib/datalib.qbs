import qbs 1.0
import qbs.Utilities

QbsLibrary {
    Depends { name: "cpp" }
    Depends { name: "Qt"; submodules: ["core-private", "network", "sql", "xml"] }
    name: "jmbdedata"
    cpp.includePaths: base.concat([
        ".",
        "../.." // for the plugin headers
    ])


    cpp.defines: [
        "DATA_LIBRARY",
        "QT_NO_CAST_FROM_ASCII",
        "QT_NO_CAST_TO_ASCII",
        "QT_NO_URL_CAST_FROM_STRING"
    ]

    Properties {
        condition: qbs.targetOS.contains("windows")
        cpp.dynamicLibraries: base.concat(["Psapi", "shell32"])
    }
    cpp.dynamicLibraries: base

    Properties {
        condition: qbs.targetOS.contains("darwin")
        cpp.frameworks: ["Foundation", "Security"]
    }


    Group {
        name: "datacontext"
        prefix: name + '/'
        files: [
            "../data_global.h",
            "datacontext.qrc",
            "datacontext.cpp",
            "datacontext.h",
        ]
    }
 }
