import qbs

Project {
    name: "documentation"

    QtcDocumentation {
        name: "user doc online"
        isOnlineDoc: true
        mainDocConfFile: "jmbde-online.qdocconf"

        files: [
            "src/**/*",
        ]
    }

    QtcDocumentation {
        name: "user doc offline"
        isOnlineDoc: false
        mainDocConfFile: "jmbde.qdocconf"

        files: [
            "src/**/*",
        ]
    }

    QtcDocumentation {
        name: "API doc online"
        isOnlineDoc: true
        mainDocConfFile: "api/jmbde-dev-online.qdocconf"

        Group {
            name: "sources"
            files: [
                "api/*.qdoc",
                "api/**/*",
            ]
            excludeFiles: [mainDocConfFile]
        }
    }

    QtcDocumentation {
        name: "API doc offline"
        isOnlineDoc: false
        mainDocConfFile: "api/jmbde-dev.qdocconf"

        Group {
            name: "sources"
            files: [
                "api/*.qdoc",
                "api/**/*",
            ]
            excludeFiles: [mainDocConfFile]
        }
    }
}