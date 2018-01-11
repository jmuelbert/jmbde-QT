import qbs 1.0
import qbs.Environment

Project {
    name: "jmbde"

    qbsSearchPaths: "qbs"
    minimumQbsVersion: "1.10"

    property string version: Environment.getEnv("JMBDE_VERSION") || "0.4.8";
    property bool snapshot: Environment.getEnv("JMBDE_SNAPSHOT")
    property bool release: Environment.getEnv("JMBDE_RELEASE")
    property bool installHeaders: false
    property bool useRPaths: true
    property bool windowsInstaller: false

    references: [
        "src",
        "translations",
    ]
}
