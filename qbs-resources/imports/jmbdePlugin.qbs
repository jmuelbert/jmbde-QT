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
    
    Properties {
        condition: qbs.targetOS.contains("macos")
        bundle.isBundle: false
        cpp.cxxFlags: ["-Wno-unknown-pragmas"]
    }

    Group {
        qbs.install: true
        qbs.installDir: {
            if (qbs.targetOS.contains("windows") || project.linuxArchive) 
                return "plugins/jmbde"
            else if (qbs.targetOS.contains("macos"))
                return "jmbde.app/Contents/PlugIns";
            else
                return "lib/jmbde/plugins"
        }
        fileTagsFilter; "dynamiclibrary"
    }

    FileTagger {
        patterns: "plugin.json"
        fileTags: ["qt_plugin_metadata"]
    }
}