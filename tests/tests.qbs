import qbs

Project {
    name: "Tests"
    references: [
        "auto/ui/ui.qbs",
    ]

    AutotestRunner {
        Depends {
            name: 'Qt.core'
        }
        environment: [ 'PATH=' + Qt.core.binPath ] 
    }
}
