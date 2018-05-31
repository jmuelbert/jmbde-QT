import qbs 1.0
import qbs.FileInfo

Project {
    name: "Utils"

    QbsDevHeaders { }

    QbsLibrary {

        cpp.defines: base.concat([
            "UTILS_LIBRARY",
            "QBS_REL_TOOL_PATH=\"" + FileInfo.relativePath('/' + app.app_bin_path,
                                                            '/' + app.app_libexec_path) + "\""

        ])

        cpp.dynamicLibraries: {
            var libs = [];
            if (qbs.targetOS.contains("windows")) {
                libs.push("user32", "iphlpapi", "ws2_32", "shell32");
            } else if (qbs.targetOS.contains("unix")) {
                if (!qbs.targetOS.contains("macos"))
                    libs.push("X11");
                if (!qbs.targetOS.contains("openbsd"))
                    libs.push("pthread");
            }
            return libs;
        }

        cpp.enableExceptions: true

        cpp.includePaths: [
            project.app_source_tree + "/src/",
            project.app_source_tree + "/src/app",
            project.app_source_tree + "/src/libs/utils",
            project.app_source_tree + "/src/libs/utils/models",
            project.app_source_tree + "/src/libs/utils/views",


        ]
        Properties {
            condition: qbs.targetOS.contains("macos")
            cpp.frameworks: ["Foundation", "AppKit"]
        }

        Depends { name: "Qt"; submodules: ["concurrent", "network", "qml", "widgets", "sql", "printsupport", "help"] }
        Depends { name: "app_version_header" }

        files: [
        ]

        Group {
            name: "Theme"
            prefix: "theme/"
            files: [

            ]
        }

        Export {
            Depends { name: "Qt"; submodules: ["concurrent", "widgets" ]}
        }
    }
}
