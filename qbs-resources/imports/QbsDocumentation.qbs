import qbs
import qbs.FileInfo

Product {
    builtByDefault: false
    type: [isOnlineDoc ? "qdoc-output" : "qch"]
    Depends { name: "Qt.core"  }
    Depends { name: "app" }

    property path mainDocConfFile
    property bool isOnlineDoc

    Group {
        name: "main qdocconf file"
        prefix: product.sourceDirectory + '/'
        files: [mainDocConfFile]
        fileTags: ["qdocconf-main"]
    }

    property string versionTag: app.app_version.replace(/\.|-/g, "")
    Qt.core.qdocEnvironment: [
        "APP_VERSION=" + app.app_version,
        "APP_VERSION_TAG=" + app.app_version,
        "SRCDIR=" + sourceDirectory,
        "QT_INSTALL_DOCS=" + Qt.core.docPath,
        "QDOC_INDEX_DIR=" + Qt.core.docPath,
        "VERSION_TAG=" + versionTag
    ]

    Group {
        fileTagsFilter: ["qch"]
        qbs.install: !qbs.targetOS.contains("macos")
        qbs.installDir: app.app_doc_path
    }
}
