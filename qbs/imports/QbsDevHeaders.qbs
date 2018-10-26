import qbs
import qbs.FileInfo

Product {
    property string productName: project.name
    property string baseDir: sourceDirectory
    name: productName + " dev headers"
    condition: app.make_dev_package
    Depends { name: "app" }
    Group {
        prefix: baseDir + '/'
        files: ["**/*.h"]
        qbs.install: true
        qbs.installDir: app.app_include_path + '/' + FileInfo.fileName(product.sourceDirectory)
        qbs.installSourceBase: baseDir
    }
}
