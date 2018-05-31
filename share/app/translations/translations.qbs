
import qbs 

Project {
    Product {
        name: "translations"
        type: "qm"
        Depends { name: "Qt.core" }
        Depends { name: "app" }

        Group {
           files: [ "*.ts" ]
           excludeFiles: [
                "jmbde_lv.ts",
           ]
        }
     
        Group {
            fileTagsFilter: product.type
            qbs.install: true
            qbs.installDir: app.app_data_path + "/translations"
        }
    }
}