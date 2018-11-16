import qbs 1.0

DynamicLibrary {
    Depends { name: "libjmbde" }
    Depends { name: "cpp" }
    Depends { name: "Qt"; submodules: "gui" }

    cpp.cxxLanguageVersion: "c++14"
    cpp.visibility: "minimal"
    cpp.useRPaths: project.useRPaths
    cpp.rpaths: {
        if (qbs.targetOS.contains("darwin"))
            return ["@loader_path/../Frameworks"];
        else if (project.linuxArchive)
            return ["$ORIGIN/.."]
        else
            return ["$ORIGIN/../.."];
    }
    cpp.defines: [
        "QT_DEPRECATED_WARNINGS",
        "QT_DISABLE_DEPRECATED_BEFORE=0x050900",
        "QT_NO_FOREACH",
        "QT_NO_URL_CAST_FROM_STRING"
    ]
    bundle.isBundle: false

    Properties {
        condition: qbs.targetOS.contains("macos")
        cpp.cxxFlags: ["-Wno-unknown-pragmas"]
    }
