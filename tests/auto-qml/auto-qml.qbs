import qbs

Product {
    name: 'jmbde-test-qml'
    type: [ 
        'application',
        'autotest',
        ]

    Depends {
        name: 'Qt'
        submodules: [
            'qmltest',
        ]    
    }

    Group {
        fileTagsFilter: "application"
        qbs.install: true
    }

    Group {
        name: 'C++ source files'
        prefix: './'
        files: [
            "tst_test.cpp",
        ]
    }

    Group {
        name: 'QML Files'
        prefix: './'
        qbs.installDir: "."
        files: [
            "tst_test.qml",
        ]
    }
}
