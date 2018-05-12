import qbs
import qbs.FileInfo
import qbs.File
import qbs.TextFile

AppleApplicationDiskImage {
    builtByDefault: false;

    condition: {
        if (project.macInstaller) {
        }

        return project.macInstaller;
    }

    Depends { productTypes: ["application", "dynamiclibrary"] }
    type: base.concat(["appcast"])

    Depends { name: "cpp" }
    Depends { name: "Qt.core" }

    name: "jmbde-installer"
    dmg.volumeName: name
    dmg.iconSize: 128
    dmg.windowWidth: 640
    dmg.windowHeight: 280
    dmg.iconPositions: [
        {"path": "Applications", "x": 128, "y": 128},
        {"path": "jmbde.app", "x": 256, "y": 128}
    ]
    files: ["images/background.tiff", "images/volume-icon.icns"]
    Group {
        files: ["*.lproj/**"] // licenses
        fileTags: ["dmg.license.input"]
    }
}