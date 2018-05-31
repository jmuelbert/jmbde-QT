import qbs
import qbs.Environment
import qbs.File
import qbs.FileInfo

Project {
    name: "Sources"
    references: [
        "app/apps.qbs",
        "app/app_version_header.qbs",
        "libs/libs.qbs",
        "packages/packages.qbs",
        "plugins/plugins.qbs",
        "tools/tools.qbs",
        project.sharedSourcesDir + "/json",
        project.sharedSourcesDir + "/proparser",
        project.sharedSourcesDir + "/pch_files.qbs",
    ]

    property bool qbsSubModulesExists: File.exists(qbsProject.qbsBaseDir + "/qbs.qbs")
    property path qbs_install_dir: Environment.getEnv("QBS_INSTALL_DIR")
    property bool useExternalQbs: qbs_install_dir
    property bool buildQbsProjectManager: useExternalQbs || qbsSubModulesExists

    Project {
        name: "qbs project"
        id: qbsProject
        property string qbsBaseDir: project.sharedSourcesDir + "/qbs"
        condition: qbsSubModulesExists && !useExternalQbs

        // The first entry is for overriding qbs' own qbsbuildconfig module.
        qbsSearchPaths: [project.app_source_tree + "/qbs", qbsBaseDir + "/qbs-resources"]

        references: [
            qbsBaseDir + "/src/libs/libs.qbs",
            qbsBaseDir + "/src/libexec/libexec.qbs",
            qbsBaseDir + "/src/plugins/plugins.qbs",
            qbsBaseDir + "/share/share.qbs",
            qbsBaseDir + "/src/app/apps.qbs",
            qbsBaseDir + "/src/shared/bundledqt/bundledqt.qbs",
            qbsBaseDir + "/src/shared/json/json.qbs",
        ]
    }
}
