import qbs
import qbs.FileInfo

Product {
    name: "precompiled headers"
    condition: app.make_dev_package
    Depends { name: "app" }
    Group {
        files: [
            "app_pch.h",
            "app_gui_pch.h",
        ]
        qbs.install: true
        qbs.installDir: app.app_shared_sources_path
    }
}
