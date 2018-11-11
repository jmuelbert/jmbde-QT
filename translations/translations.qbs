
import qbs 1.0

Project {
    Product {
        name: "translations"
        type: "qm"
        files: [ "*.ts" ]

        excludeFiles: [
            "jmbde_lv.ts"
        ]

        Depends { name: "Qt.core" }

    Group {
        fileTagsFilter: product.type
        qbs.install: true
        qbs.installDir: {
            if (qbs.targetOS.contains("windows") || project.linuxArchive)
                return "translations"
            else if (qbs.targetOS.contains("macos"))
                return "jmbde.app/Contents/Translations"
            else
                return "share/tiled/translations"
        }
    }
}