import qbs 1.0

DynamicLibrary {
    targetName: "jmbde"

    Depends { name: "cpp" }
    Depends { name: "Qt"; submodules: "gui", "sql"; versionAtLeast: "5.5" }

    Properties {
        condition: !qbs.toolchain.contains("msvc")
        cpp.dynamicLibraries: base.concat(["z"])
    }

    cpp.cxxLanguageVersion: "c++14"
    cpp.visibility: "minimal"
    cpp.defines: [
        "JMBDE_LIBRARY",
        "QT_NO_CAST_FROM_ASCII",
        "QT_NO_CAST_TO_ASCII",
        "QT_NO_URL_CAST_FROM_STRING",
        "_USE_MATH_DEFINES"
    ]

    Properties {
        condition: qbs.targetOS.contains("macos")
        cpp.cxxFlags: ["-Wno-unknown-pragmas"]
    }

    bundle.isBundle: false
    cpp.sonamePrefix: qbs.targetOS.contains("darwin") ? "@rpath" : undefined

    files: [
        "libdata_global.h",
        "libdatacontext.cpp",
        "libdatacontext.h",
        "libdatacontext.qrc"
    ]

    Group {
        condition: project.installHeaders
        qbs.install: true
        qbs.installDir: "include/jmbde"
        fileTagsFilter: "hpp"
    }

    Export {
        Depends { name: "cpp" }
        Depends {
            name: "Qt"
            submodules: ["gui"]
        }

        cpp.includePaths: "."
    }

    Group {
        qbs.install: true
        qbs.installDir: {
            if (qbs.targetOS.contains("windows"))
                return ""
            else if (qbs.targetOS.contains("darwin"))
                return "jmbde.app/Contents/Frameworks"
            else
                return "lib"
        }
        fileTagsFilter: "dynamiclibrary"
    }
}
