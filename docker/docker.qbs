import qbs

Project {
    Product {
        Depends { name: "docker"; required: false }

        name: "jmbde-docker-stretch"
        type: ["docker.docker-image"]
        builtByDefault: false
        condition: docker.present

        docker.imageTag: "appbuild/appdev:stretch"

        files: [
            "stretch/Dockerfile",
            "stretch/qtifwsilent.qs",
        ]
    }

    Product {
        Depends { name: "docker"; required: false }

        name: "app-docker-windowsservercore"
        type: ["docker.docker-image"]
        builtByDefault: false
        condition: docker.present

        docker.imageTag: "appbuild/appdev:windowsservercore"

        files: [
            "windowsservercore/Dockerfile",
            "windowsservercore/qtifwsilent.qs",
        ]
    }
}