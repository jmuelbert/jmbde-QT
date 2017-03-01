import qbs 1.0

Product {
    name: "SharedContent"
    Depends { name: "jmbde" }

    Group {
        name: "Unconditional"
        qbs.install: true
        qbs.installDir: qtc.ide_data_path
        qbs.installSourceBase: "jmbder"
        prefix: "jmbde/"
        files: [
            "qml/**/*",
            "qmlicons/**/*",
            "qml-type-descriptions/**/*",
            "styles/**/*",
            "templates/**/*",
            "themes/**/*",
            "welcomescreen/**/*"
        ]
    }
}