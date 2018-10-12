import qbs

Project {
    references: [
        "archive/archive.qbs"
    ]

    // Virtual product for building all possible packagings
    Product {
        Depends { name: "jmbde archive"; required: false }
        Depends { name: "jmbde chocolatey"; required: false }
        name: "dist"
        builtByDefault: false
    }
}