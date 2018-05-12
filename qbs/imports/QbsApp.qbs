import qbs
import qbs.FileInfo

QbsProduct {
    Depends { name: "jmbdedata" }
    Depends { name: "cpp" }
    Depends { name: "qbsversion" }
    type: ["application", "qbsapplication"]
    version: qbsversion.version
    consoleApplication: true
    destinationDirectory: FileInfo.joinPaths(project.buildDirectory, "bin")
    cpp.includePaths: [
        "../shared",    // for the logger
    ]
    Group {
        fileTagsFilter: product.type
            .concat(qbs.buildVariant === "debug" ? ["debuginfo_app"] : [])
        qbs.install: true
        qbs.installSourceBase: destinationDirectory
        qbs.installDir: targetInstallDir
    }
    targetInstallDir: qbsbuildconfig.appInstallDir
}
