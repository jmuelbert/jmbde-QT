import qbs
import qbs.FileInfo

QbsProduct {
    type: ["application"]
    consoleApplication: true
    installDir:  app.app_libexec_path
    installTags: base.concat(["debuginfo_app"])
    useNonGuiPchFile: true

    cpp.rpaths: {
        var relativePathToLibs = FileInfo.relativePath('/' + app.app_libexec_path,
                                                       '/' + app.app_library_path);
        var relativePathToPlugins = FileInfo.relativePath('/' + app.app_libexec_path,
                                                          '/' + app.app_plugin_path);
        var prefix = qbs.targetOS.contains("macos") ? "@executable_path" : "$ORIGIN";
        return [
            FileInfo.joinPaths(prefix, relativePathToLibs),
            FileInfo.joinPaths(prefix, relativePathToPlugins)
        ];
    }
}
