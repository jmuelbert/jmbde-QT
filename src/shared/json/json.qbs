import qbs

StaticLibrary {
    name: "qbsjson"
    Depends { name: "cpp" }
    cpp.cxxLanguageVersion: "c++14"
    cpp.minimumMacosVersion: project.minimumMacosVersion
    files: [

    ]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [product.sourceDirectory]
    }
}