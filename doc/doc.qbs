import qbs
import qbs.File
import qbs.FileInfo

Project {
    name: "documentation"

    QbsDocumentation {
        name: "user doc online"
        isOnlineDoc: true
        mainDocConfFile: "app-online.qdocconf"

        files: [
            "src/**/*",
        ]
    }

    QbsDocumentation {
        name: "user doc offline"
        isOnlineDoc: false
        mainDocConfFile: "app.qdocconf"

        files: [
            "src/**/*",
        ]
    }

    QbsDocumentation {
        name: "API doc online"
        isOnlineDoc: true
        mainDocConfFile: "api/app-dev-online.qdocconf"

        Group {
            name: "sources"
            files: [
                "api/*.qdoc",
                "api/**/*",
            ]
            excludeFiles: [ mainDocConfFile ]
        }
    }

    QbsDocumentation {
        name: "API doc offline"
        isOnlineDoc: true
        mainDocConfFile: "api/app-dev.qdocconf"

        Group {
            name: "sources"
            files: [
                "api/*.qdoc",
                "api/**/*",
            ]
            excludeFiles: [ mainDocConfFile ]
        }
    }

    property string qbsBaseDir: project.sharedSourcesDir + "/qbs"
    property bool qbsSubModulesExists: File.exists(qbsBaseDir + "/qbs.qbs")

    Properties {
        condition: qbsSubModulesExists

        references: [ qbsBaseDir + "/doc/doc.qbs" ]

        // The first entry is for overriding qbs' own qbsbuildconfig module.
        qbsSearchPaths: [project.ide_source_tree + "/qbs", qbsBaseDir + "/qbs-resources"]

    }

}
