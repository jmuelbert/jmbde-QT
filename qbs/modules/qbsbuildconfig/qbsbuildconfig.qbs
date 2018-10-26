import qbs
import qbs.FileInfo

Module {
    Depends { name: "app" }

    property bool enableUnitTests: false
    property bool enableProjectFileUpdates: true
    property bool installApiHeaders: false
    property bool enableBundledQt: false
    property string libInstallDir: app.app_library_path
    property stringList libRPaths: qbs.targetOS.contains("macos")
            ? ["@loader_path/" + FileInfo.relativePath('/' + appInstallDir, '/' + libInstallDir )]
            : ["$ORIGIN/..", "$ORIGIN/../.." + app.app_library_path]

    property string resourcesInstallDir: app.app_data_path + "/qbs"
    property string pluginsInstallDir: app.app_plugin_path + "/qbs/plugins"
    property string qmlTypeDescriptionsInstallDir: app.app_data_path + "/qml-type-descriptions"             
    property string appInstallDir: app.app_bin_path
    property string libexecInstallDir: app.app_libexec_path
    property bool installHtml: false
    property bool installQch: !qbs.targetOS.contains("macos")
    property string docInstallDir: app.app_doc_path
    property string relativeLibexecPath: FileInfo.relativePath('/' + appInstallDir,
                                                               '/' + libexecInstallDir)
    property string relativePluginsPath: FileInfo.relativePath('/' + appInstallDir,
                                                               '/' + pluginsInstallDir)
    property string relativeSearchPath: FileInfo.relativePath('/' + appInstallDir,
                                                              '/' + resourcesInstallDir)

}
