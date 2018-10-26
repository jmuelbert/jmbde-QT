import qbs
import qbs.FileInfo

QbsProduct {
    type: ["application", "autotest"]

    Depends { name: "Qt.testlib" }
    Depends { name: "copyable_resource" }

    targetName: "tst_" + name.split(' ').join("")

    // This needs to be absolute, because it is passed to one of the source files.
    destinationDirectory: project.buildDirectory + '/'  
                            + FileInfo.relativePath(project.app_source_tree, sourceDirectory)

    cpp.rpaths: [
        project.buildDirectory + '/' + app.app_library_path,
        project.buildDirectory + '/' + app.app_plugin_path
    ]    

    cpp.defines: base.filter(function(d) {
        return d !== "QT_RESTRICTED_CAST_FROM_ASCII"
            && d !== "QT_USE_FAST_OPERATOR_PLUS"
            && d !== "QT_USE_FAST_CONCATENATION";
    })

    Group {
        fileTagsFilter: product.type
        qbs.install: false
    }
}
