import qbs 1.0

Product {
    name: "SharedContent"
    Depends { name: "app" }

    Group {
        name: "Unconditional"
        qbs.install: true
        qbs.installDir: app.app_data_path
        qbs.installSourceBase: "jmbde"
        prefix: "jmbde/"
        files: [
            "qml/**/*",
            "qml-type-descriptions/**/*",
            "qmlicons/**/*",
        ]
        excludeFiles: [

        ]
    }
    
    Group {
        name: "3rdparty"
        qbs.install: true
        qbs.installDir: app.app_data_path
        qbs.installSourceBase: project.app_source_tree + "/src/share/3rdparty"
        prefix: project.app_source_tree + "/src/share/3rdparty"
        files: []
    }
}
