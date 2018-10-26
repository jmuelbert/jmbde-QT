import qbs 1.0
import qbs.FileInfo
import "qbsfunctions/functions.js" as QbsFunctions

QbsProduct {
    type: ["dynamiclibrary", "dynamiclibrary_symlink", "app.dev-module"]
    installDir: app.app_library_path
    installTags: ["dynamiclibrary", "dynamiclibrary_symlink", "debuginfo_dll"]
    useNonGuiPchFile: true
    Depends {
        condition: app.testsEnabled
        name: "Qt.testlib"
    }

    targetName: QbsFunctions.qtLibraryName(qbs, name)
    destinationDirectory: FileInfo.joinPaths(project.buildDirectory, app.app_library_path)

    cpp.linkerFlags: {
        var flags = base;
        if (qbs.buildVariant == "debug" && qbs.toolchain.contains("msvc"))
            flags.push("/INCREMENTAL:NO"); // Speed up startup time when debugging with cdb
        if (qbs.targetOS.contains("macos"))
            flags.push("-compatibility_version", app.app_compat_version);
        return flags;
    }
    cpp.sonamePrefix: qbs.targetOS.contains("macos")
            ? "@rpath"
            : undefined
    cpp.rpaths: qbs.targetOS.contains("macos")
            ? ["@loader_path/../Frameworks"]
            : ["$ORIGIN", "$ORIGIN/.."]
    property string libIncludeBase: ".." // #include <lib/header.h>
    cpp.includePaths: [libIncludeBase]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [product.libIncludeBase]
    }
}
