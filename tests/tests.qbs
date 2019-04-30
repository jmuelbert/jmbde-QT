import qbs

Project {
    name: "Tests"
    references: [
        "auto-cpp/auto-cpp.qbs",
    ]

    AutotestRunner {
        Depends {
            name: 'Qt.core'
        }
        environment: [ 'PATH=' + Qt.core.binPath ] 
    }
}
