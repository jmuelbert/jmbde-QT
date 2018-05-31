import qbs

Project {
    name: "Libs"
    references: [
        "utils/utils.qbs",
        "datalib/datalib.qbs",
    ].concat(project.additionalLibs)
}
