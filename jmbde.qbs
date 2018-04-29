import qbs 
import qbs.Environment

Project {
    name: "jmbde"

    qbsSearchPaths: "qbs"
    minimumQbsVersion: "1.8"

    property string version: Environment.getEnv("JMBDE_VERSION") || "0.4.11";
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
        "src/app",
        "translations"
    ]
}