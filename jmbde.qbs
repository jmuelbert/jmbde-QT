import qbs 
import qbs.Environment

Project {
    name: "jmbde"

    qbsSearchPaths: "qbs"
    minimumQbsVersion: "1.8.0"

    property string minimumMacosVersion: "10.8"
    property bool withAutotests: qbs.buildVariant === "debug"
    property path app_source_tree: path
    property pathList additionalPlugins: []
    property pathList additionalLibs: []
    property pathList additionalTools: []
    property pathList additionalAutotests: []
    property string version: Environment.getEnv("JMBDE_VERSION") || "0.4.12";
    property bool snapshot: Environment.getEnv("JMBDE_SNAPSHOT")
    property bool release: Environment.getEnv("JMBDE_RELEASE")
    property bool installHeaders: false
    property bool useRPaths: true
    property bool windowsInstaller: false

    references: [
        "dist/archive.qbs",
        "dist/distribute.qbs",
        "dist/win/installer.qbs",
        "src/lib",
        "src/lib/3rdparty/qtsingleapplication",
        "src/app",
        "translations",
    ]
}
